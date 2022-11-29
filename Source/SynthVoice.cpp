/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Oct 2022 11:54:56am
    Author:  Martin

  ==============================================================================
*/

#include "SynthVoice.h"
#include <JuceHeader.h>
#include <algorithm>

// For some reason the audio waveforms are not centered so a bias level need to be added when creating the osc waveforms.
const double OSC_BIAS = 0.5;

SynthVoice::SynthVoice (juce::uint32 main_bus_output_channels)
    : main_bus_output_channels_ (main_bus_output_channels)
{
}

SynthVoice::~SynthVoice()
{
}

void SynthVoice::setVoiceFrequency (double f_hz)
{
    osc1_f_hz_ = f_hz;
    osc2_f_hz_ = f_hz;
}

void SynthVoice::modulateOsc1Frequency (double factor, double env_depth, double pitch_wheel)
{
    auto& osc1 = signal_chain_.template get<osc1_index>();
    double new_frequency = osc1_f_hz_ * factor + envelope2_output_ * env_depth;
    new_frequency *= pitch_wheel;
    new_frequency = std::min (std::max (new_frequency, 20.0), 20000.0);
    osc1.setFrequency (new_frequency, true);
}

void SynthVoice::modulateOsc2Frequency (double factor, double env_depth, double pitch_wheel)
{
    auto& osc2 = signal_chain_.template get<osc2_index>();
    double new_frequency = osc1_f_hz_ * factor + envelope2_output_ * env_depth;
    new_frequency = std::min (std::max (new_frequency, 20.0), 20000.0);
    new_frequency *= pitch_wheel;
    osc2.setFrequency (new_frequency, true);
}

void SynthVoice::setWaveform (float osc1_shape, float osc2_shape, float osc1_env_depth, float osc2_env_depth)
{
    float osc1_envmod = static_cast<float> (envelope2_output_) * osc1_env_depth;
    float osc2_envmod = static_cast<float> (envelope2_output_) * osc2_env_depth;
    osc1_waveform_ = std::min (std::max (osc1_shape + osc1_envmod, 0.0f), 2.0f);
    osc2_waveform_ = std::min (std::max (osc2_shape + osc2_envmod, 0.0f), 2.0f);
}

void SynthVoice::setOscsAmplitude (double osc1_amplitude, double osc2_amplitude)
{
    osc1_amplitude_ = osc1_amplitude;
    osc2_amplitude_ = osc2_amplitude;
}

void SynthVoice::setVcfParameters (float cutoff_hz, float resonance, float env_depth)
{
    if (sample_rate_ == 0)
    {
        DBG ("Error: Sample rate is not set 0 when setting filter cutoff, "
             "have this SynthVoice been PreparedToPlay?");
        return;
    }
    float cutoff = cutoff_hz + envelope2_output_ * env_depth;
    cutoff = std::min (std::max (cutoff, 15.0f), 20000.0f);
    auto& vcf = signal_chain_.template get<vcf_index>();
    auto vcf_state = vcf.state.get();
    vcf_state->setCutOffFrequency (sample_rate_, cutoff, resonance);
}

void SynthVoice::noteOn()
{
    if (envelope1_.isActive())
    {
        envelope1_.reset();
        envelope1_.noteOff();
    }
    envelope1_.noteOn();
    if (envelope2_.isActive())
    {
        envelope2_.reset();
        envelope2_.noteOff();
    }
    envelope2_.noteOn();
}

void SynthVoice::noteOff()
{
    envelope1_.noteOff();
    envelope2_.noteOff();
}

void SynthVoice::setVelocity (const int velocity)
{
    velocity_ = juce::jmap (static_cast<double> (velocity), 0.0, 127.0, 0.0, 1.0);
}

void SynthVoice::setVcaGain (float gain)
{
    auto& vca = signal_chain_.template get<vca_index>();
    // TODO: Knob response feels a bit off, need to investigate on how to improve it.
    //       The problem could be that ADSR is controlling the gain as well?

    // 0.7f will let the exponential curve hit y=1 just before x=1
    // cppcheck-suppress unpreciseMathCall
    vca.setGainLinear (juce::dsp::FastMathApproximations::exp (0.7f * gain * velocity_) - 1.0f);
}

void SynthVoice::setEnvelope1Parameters (float attack, float decay, float sustain, float release)
{
    envelope1_params_.attack = attack;
    envelope1_params_.decay = decay;
    envelope1_params_.sustain = sustain;
    envelope1_params_.release = release;
    envelope1_.setParameters (envelope1_params_);
}

void SynthVoice::setEnvelope2Parameters (float attack, float decay, float sustain, float release)
{
    envelope2_params_.attack = attack;
    envelope2_params_.decay = decay;
    envelope2_params_.sustain = sustain;
    envelope2_params_.release = release;
    envelope2_.setParameters (envelope2_params_);
}

void SynthVoice::setNoiseLevel (const double level)
{
    noise_level_ = level;
}

void SynthVoice::setKey (const int key)
{
    key_ = key;
}

int SynthVoice::getKey()
{
    return key_;
}

bool SynthVoice::isActive()
{
    return envelope1_.isActive();
}

void SynthVoice::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    sample_rate_ = sampleRate;
    envelope1_.setSampleRate (sampleRate);
    envelope2_.setSampleRate (sampleRate);
    juce::dsp::ProcessSpec spec = { sampleRate, samplesPerBlockExpected, main_bus_output_channels_ };
    signal_chain_.prepare (spec);
    auto& osc1 = signal_chain_.template get<osc1_index>();
    osc1.initialise ([this] (double x) {
        // Fade between sinewave (waveform == 0) then
        // saw (waveform == 1) then square (waveform == 2)
        if (this->osc1_waveform_ < 1.0)
            return ((1.0 - this->osc1_waveform_) * std::sin (x) + (this->osc1_waveform_ * x / juce::MathConstants<double>::pi) + OSC_BIAS)
                   * this->osc1_amplitude_;
        else
            return (((2.0 - this->osc1_waveform_) * (x / juce::MathConstants<double>::pi)) + (this->osc1_waveform_ - 1.0) * (x < 0.0 ? -1.0 : 1.0)) * this->osc1_amplitude_ + OSC_BIAS;
    });

    auto& osc2 = signal_chain_.template get<osc2_index>();
    osc2.initialise ([this] (double x) {
        // Fade between sinewave (waveform == 0) then
        // saw (waveform == 1) then square (waveform == 2)
        if (this->osc2_waveform_ < 1.0)
            return ((1.0 - this->osc2_waveform_) * std::sin (x) + (this->osc2_waveform_ * x / juce::MathConstants<double>::pi) + OSC_BIAS)
                   * this->osc2_amplitude_;
        else
            return (((2.0 - this->osc2_waveform_) * (x / juce::MathConstants<double>::pi)) + (this->osc2_waveform_ - 1.0) * (x < 0.0 ? -1.0 : 1.0)) * this->osc2_amplitude_ + OSC_BIAS;
    });

    auto& noise = signal_chain_.template get<noise_index>();
    noise.initialise ([this] (double x) {
        // * 2 -1 because we want to offset signal from 0 to 1 => -1 to 1
        return juce::Random::getSystemRandom().nextDouble() * noise_level_ * 2.0 - 1.0;
    });
}

void SynthVoice::releaseResources()
{
    // Clean up if needed
}

void SynthVoice::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    auto envelope_buffer = *bufferToFill.buffer;
    envelope_buffer.clear();
    envelope2_.applyEnvelopeToBuffer (envelope_buffer, 0, envelope_buffer.getNumSamples());
    envelope2_output_ = static_cast<double> (envelope2_.getNextSample());

    auto block = juce::dsp::AudioBlock<float> (*buffer);
    auto contextToUse = juce::dsp::ProcessContextReplacing<float> (block);
    signal_chain_.process (contextToUse);
    envelope1_.applyEnvelopeToBuffer (*buffer, 0, buffer->getNumSamples());
}
