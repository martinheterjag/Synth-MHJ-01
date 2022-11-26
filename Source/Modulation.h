/*
  ==============================================================================

    Modulation.h
    Created: 31 Oct 2022 1:28:28pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include "Lfo.h"
#include <JuceHeader.h>

class Modulation
{
public:
    Modulation();
    ~Modulation();
    void prepare (juce::dsp::ProcessSpec& spec);
    void resetLfo1();
    void resetLfo2();
    double getLfo1Output();
    double getLfo2Output();
    void process (juce::AudioProcessorValueTreeState& apvts, const juce::AudioSourceChannelInfo bufferToFill);

private:
    Lfo lfo1_;
    Lfo lfo2_;
};