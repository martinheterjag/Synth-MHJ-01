/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Oct 2022 11:54:56am
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthVoice
{
public:
    SynthVoice();
    SynthVoice(SynthVoice&&) {}
    ~SynthVoice();

    void prepare(juce::dsp::ProcessSpec spec);
    void setOscFrequency(double f_hz);
    void setVcaGain(float gain);
    void process(const juce::dsp::ProcessContextReplacing<float>& context);

private:
    enum
    {
        osc_index,
        vca_index
    };
    juce::dsp::ProcessorChain<juce::dsp::Oscillator<double>, juce::dsp::Gain<float>> signal_chain_;
};