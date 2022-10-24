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
    SynthVoice(SynthVoice&&) noexcept {}
    ~SynthVoice();

    void prepare(juce::dsp::ProcessSpec spec);
    void setOscFrequency(double f_hz);
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
        osc_index,
        vca_index
    };
    juce::dsp::ProcessorChain<juce::dsp::Oscillator<double>, juce::dsp::Gain<float>> signal_chain_;
    juce::uint32 main_bus_output_channels_;
    int key_ = 999;  // init to something out of midi key range
    bool active_ = false;
};