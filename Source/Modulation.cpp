/*
  ==============================================================================

    Modulation.cpp
    Created: 31 Oct 2022 1:28:28pm
    Author:  Martin

  ==============================================================================
*/

#include "Modulation.h"

Modulation::Modulation()
{
}

Modulation::~Modulation()
{
}

void Modulation::prepare(juce::dsp::ProcessSpec& spec)
{
    lfo1_.prepare (spec);
    lfo1_.initialise ([] (float x) {
        return std::sin(x);
    }, 128);
}

double Modulation::getLfo1Output() {
    DBG("lfo1_output_: " << lfo1_output_);
    return lfo1_output_;
}

void Modulation::process(juce::AudioProcessorValueTreeState& apvts)
{
    auto f = apvts.getRawParameterValue("LFO_1_FREQUENCY")->load();
    DBG("lfo1: " << f);
    lfo1_.setFrequency(apvts.getRawParameterValue("LFO_1_FREQUENCY")->load());
    lfo1_output_ = lfo1_.processSample(0.0f);
}
