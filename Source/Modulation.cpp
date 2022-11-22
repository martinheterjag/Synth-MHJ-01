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
    lfo1_.resetLfo();
    lfo2_.prepare (spec);
    lfo2_.resetLfo();
}

void Modulation::setLfo1Waveform(Lfo::Waveform waveform){
    lfo1_.setWaveform(waveform);
}

void Modulation::setLfo2Waveform(Lfo::Waveform waveform){
    lfo2_.setWaveform(waveform);
}

void Modulation::resetLfo1() {
    lfo1_.resetLfo();
}

void Modulation::resetLfo2() {
    lfo2_.resetLfo();
}

double Modulation::getLfo1Output() {
    return lfo1_.getOutput();
}

double Modulation::getLfo2Output() {
    return lfo2_.getOutput();
}

void Modulation::process(juce::AudioProcessorValueTreeState& apvts, const juce::AudioSourceChannelInfo bufferToFill)
{
    auto block = juce::dsp::AudioBlock<float>(*bufferToFill.buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    lfo1_.setFrequency(apvts.getRawParameterValue("LFO_1_FREQUENCY")->load());
    Lfo::Waveform waveform_lfo1 = static_cast<Lfo::Waveform>(apvts.getRawParameterValue("LFO_1_WAVEFORM")->load());
    lfo1_.setWaveform(waveform_lfo1);
    lfo1_.update(context);

    lfo2_.setFrequency(apvts.getRawParameterValue("LFO_2_FREQUENCY")->load());
    Lfo::Waveform waveform_lfo2 = static_cast<Lfo::Waveform>(apvts.getRawParameterValue("LFO_2_WAVEFORM")->load());
    lfo2_.setWaveform(waveform_lfo2);
    lfo2_.update(context);
}
