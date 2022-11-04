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
    return lfo1_output_;
}

void Modulation::process(juce::AudioProcessorValueTreeState& apvts, const juce::AudioSourceChannelInfo bufferToFill)
{
    auto block = juce::dsp::AudioBlock<float>(*bufferToFill.buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    auto f = apvts.getRawParameterValue("LFO_1_FREQUENCY")->load();
    lfo1_.setFrequency(apvts.getRawParameterValue("LFO_1_FREQUENCY")->load());
    lfo1_output_ = lfo1_.processSample(0.0);
    lfo1_.process(context);
}
