/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Oct 2022 11:54:56am
    Author:  Martin

  ==============================================================================
*/

#include <algorithm>
#include <JuceHeader.h>
#include "SynthVoice.h"

SynthVoice::SynthVoice(juce::uint32 main_bus_output_channels)
    : main_bus_output_channels_(main_bus_output_channels)
{
}

SynthVoice::~SynthVoice()
{
}

void SynthVoice::setVoiceFrequency(double f_hz)
{
    osc1_f_hz_ = f_hz;
    osc2_f_hz_ = f_hz;
}

void SynthVoice::modulateOsc1Frequency(double factor)
{
    auto& osc1 = signal_chain_.template get<osc1_index>();
    osc1.setFrequency(osc1_f_hz_ * factor, true);
}

void SynthVoice::modulateOsc2Frequency(double factor)
{
    auto& osc2 = signal_chain_.template get<osc2_index>();
    osc2.setFrequency(osc2_f_hz_ * factor, true);
}

void SynthVoice::setVcfParameters(float cutoff_hz, float resonance)
{
    if (sample_rate_ == 0) {
        DBG("Error: Sample rate is not set 0 when setting filter cutoff, "
            "have this SynthVoice been PreparedToPlay?");
        return;
    }
    // TODO: make depth a data member (consider having depth as a range in Hertz instead of a factor)
    const float MAX_MODULATION_HZ = 10000.0f;
    float env_depth = 0.1 ;
    float cutoff = cutoff_hz + (envelope2_output_ * (env_depth * MAX_MODULATION_HZ));
    cutoff = std::min(std::max(cutoff, 15.0f), 25000.0f);
    auto& vcf = signal_chain_.template get<vcf_index>();
    auto vcf_state = vcf.state.get();
    vcf_state->setCutOffFrequency(sample_rate_, cutoff, resonance);
}

void SynthVoice::noteOn() {
    if (envelope1_.isActive()) {
        envelope1_.reset();
    }
    envelope1_.noteOn();
    if (envelope2_.isActive()) {
        envelope2_.reset();
    }
    envelope2_.noteOn();
}

void SynthVoice::noteOff() {
    envelope1_.noteOff();
    envelope2_.noteOff();
}

void SynthVoice::setVcaGain(float gain)
{
    auto& vca = signal_chain_.template get<vca_index>();
    vca.setGainLinear(gain);
}

void SynthVoice::setEnvelope1Parameters(float attack, float decay, float sustain, float release) {
    envelope1_params_.attack = attack;
    envelope1_params_.decay = decay;
    envelope1_params_.sustain = sustain;
    envelope1_params_.release = release;
    envelope1_.setParameters(envelope1_params_);
}

void SynthVoice::setEnvelope2Parameters(float attack, float decay, float sustain, float release) {
    envelope2_params_.attack = attack;
    envelope2_params_.decay = decay;
    envelope2_params_.sustain = sustain;
    envelope2_params_.release = release;
    envelope2_.setParameters(envelope2_params_);
}

void SynthVoice::setWaveform(float osc1_shape, float osc2_shape) {
    osc1_waveform_ = std::min(std::max(osc1_shape, 0.0f), 2.0f);
    osc2_waveform_ = std::min(std::max(osc2_shape, 0.0f), 2.0f);
}

void SynthVoice::setKey(const int key)
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

void SynthVoice::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    sample_rate_ = sampleRate;
    envelope1_.setSampleRate(sampleRate);
    envelope2_.setSampleRate(sampleRate);
    juce::dsp::ProcessSpec spec = { sampleRate, samplesPerBlockExpected,
                              main_bus_output_channels_ };
    signal_chain_.prepare(spec);
    auto& osc1 = signal_chain_.template get<osc1_index>();
    osc1.initialise([this](double x)
        {
            // Fade between sinewave (waveform == 0) then 
            // saw (waveform == 1) then square (waveform == 2)
            if (this->osc1_waveform_ < 1.0)
                return (1.0 - this->osc1_waveform_) * std::sin(x) +
                (-1 + this->osc1_waveform_ * x / juce::MathConstants<double>::pi);
            else
                return (-1.0 + (2.0 - this->osc1_waveform_) * (x / juce::MathConstants<double>::pi)) +
                (this->osc1_waveform_ - 1.0) * (x < 0.0 ? -1.0 : 2.0);

        });

    auto& osc2 = signal_chain_.template get<osc2_index>();
    osc2.initialise([this](double x)
        {
            // Fade between sinewave (waveform == 0) then 
            // saw (waveform == 1) then square (waveform == 2)
            if (this->osc2_waveform_ < 1.0)
                return (1.0 - this->osc2_waveform_) * std::sin(x) +
                        (-1 + this->osc2_waveform_ * x / juce::MathConstants<double>::pi);
            else
                return (-1.0 + (2.0 - this->osc2_waveform_) * (x / juce::MathConstants<double>::pi)) +
                        (this->osc2_waveform_ -1.0) * (x < 0.0 ? -1.0 : 2.0);

        });
}

void SynthVoice::releaseResources()
{
    // Clean up if needed
}

void SynthVoice::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    auto envelope_buffer = *bufferToFill.buffer;
    envelope_buffer.clear();
    envelope2_.applyEnvelopeToBuffer(envelope_buffer, 0, envelope_buffer.getNumSamples());
    envelope2_output_ = envelope2_.getNextSample();

    auto block = juce::dsp::AudioBlock<float>(*buffer);
    auto contextToUse = juce::dsp::ProcessContextReplacing<float>(block);
    signal_chain_.process(contextToUse);
    envelope1_.applyEnvelopeToBuffer(*buffer, 0, buffer->getNumSamples());
}
