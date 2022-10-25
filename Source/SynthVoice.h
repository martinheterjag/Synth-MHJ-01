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
    void modulateOsc1Frequency(double factor);
    void modulateOsc2Frequency(double factor);
    void setVcfParameters(float cutoff_hz, float resonance);
    void setVcaGain(float gain);
    void setKey(const int key);
    int getKey();
    bool isActive();
    juce::AudioBuffer<float> process(juce::AudioBuffer<float> buffer);

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
    juce::uint32 main_bus_output_channels_;
    int key_ = 999;  // init to something out of midi key range
    bool active_ = false;
    double sample_rate_ = 0;
    double osc1_f_hz_ = 220.0;
    double osc2_f_hz_ = 220.0;
};