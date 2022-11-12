/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Oct 2022 11:54:56am
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthVoice : public juce::AudioSource
{
public:
    SynthVoice(juce::uint32 main_bus_output_channels);
    SynthVoice(const SynthVoice& other) : main_bus_output_channels_(other.main_bus_output_channels_) {};
    ~SynthVoice();

    void setVoiceFrequency(double f_hz);
    void modulateOsc1Frequency(double factor, double env_depth, double pitch_wheel);
    void modulateOsc2Frequency(double factor, double env_depth, double pitch_wheel);
    void setVcfParameters(float cutoff_hz, float resonance, float env_depth);
    void noteOn();
    void noteOff();
    void setVelocity(const int velocity);
    void setVcaGain(float gain);
    void setEnvelope1Parameters(float attack, float decay, float sustain, float release);
    void setEnvelope2Parameters(float attack, float decay, float sustain, float release);
    void setWaveform(float osc1_shape, float osc2_shape, float osc1_env_depth, float osc2_env_depth);
    void setKey(const int key);
    int getKey();
    bool isActive();

    // Dirived from AudioSource
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    enum
    {
        osc1_index,
        osc2_index,
        vcf_index,
        vca_index
    };
    typedef juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter<float>,
                                           juce::dsp::StateVariableFilter::Parameters<float> > StereoFilter;
    juce::dsp::ProcessorChain<juce::dsp::Oscillator<double>,
                              juce::dsp::Oscillator<double>,
                              StereoFilter,
                              juce::dsp::Gain<float>> signal_chain_;
    juce::ADSR envelope1_;
    juce::ADSR::Parameters envelope1_params_;
    juce::ADSR envelope2_;
    double envelope2_output_ = 0.0;
    juce::ADSR::Parameters envelope2_params_;
    juce::uint32 main_bus_output_channels_;
    int key_ = 999;  // init to something out of midi key range
    double sample_rate_ = 0;
    double velocity_ = 1.0;
    double osc1_f_hz_ = 220.0;
    double osc2_f_hz_ = 220.0;
    float osc1_waveform_ = 1.0f;
    float osc2_waveform_ = 1.0f;
};
