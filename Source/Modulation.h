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
    enum class Waveform {
        SINE = 0,
        SAW,
        SQUARE,
        TRIANGLE
    };
    Modulation();
    ~Modulation();
    void prepare(juce::dsp::ProcessSpec& spec);
    void resetLfo1();
    void setLfo1Waveform(Waveform waveform);
    double getLfo1Output();
    void process(juce::AudioProcessorValueTreeState& apvts, const juce::AudioSourceChannelInfo bufferToFill);
private:
    juce::dsp::Oscillator<double> lfo1_;
    Waveform lfo1_waveform_ { Waveform::SINE };
    double lfo1_output_;
};