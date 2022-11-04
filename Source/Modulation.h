/*
  ==============================================================================

    Modulation.h
    Created: 31 Oct 2022 1:28:28pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Modulation {
public:
    Modulation();
    ~Modulation();
    void prepare(juce::dsp::ProcessSpec& spec);
    double getLfo1Output();
    void process(juce::AudioProcessorValueTreeState& apvts, const juce::AudioSourceChannelInfo bufferToFill);
    enum class Waveform {
        SINE,
        SAW,
        SQUARE,
        TRIANGLE
    };
private:
    juce::dsp::Oscillator<double> lfo1_;
    Waveform lfo1_waveform_ { Waveform::SINE };
    double lfo1_output_;
};