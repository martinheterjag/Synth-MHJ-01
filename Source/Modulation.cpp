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
    resetLfo1();
}

void Modulation::setLfo1Waveform(Waveform waveform){
    if (waveform == lfo1_waveform_)
        return;
    lfo1_waveform_ = waveform;
    resetLfo1();
}

void Modulation::resetLfo1() {
    switch (lfo1_waveform_) {
    case(Waveform::SINE):
        lfo1_.initialise([](float x) {
            return std::sin(x);
            }, 128);
        break;
    case(Waveform::SAW):
        lfo1_.initialise([](float x) {
            return x / juce::MathConstants<double>::pi;
            }, 128);
        break;
    case(Waveform::SQUARE):
        lfo1_.initialise([](float x) {
            return (x > 0.0 ? 
                0.0 : 
                1.0);
            }, 128);
        break;
    case(Waveform::TRIANGLE):
        lfo1_.initialise([](float x) {
            return (x > 0.0 ?
                (2.0 * x / (juce::MathConstants<double>::pi)) :
                juce::MathConstants<double>::pi - (2.0 * x / (juce::MathConstants<double>::pi)));
            }, 128);
            break;
    default:
        DBG("Warning, we should not get here.");
    }
}

double Modulation::getLfo1Output() {
    return lfo1_output_;
}

void Modulation::process(juce::AudioProcessorValueTreeState& apvts, const juce::AudioSourceChannelInfo bufferToFill)
{
    auto block = juce::dsp::AudioBlock<float>(*bufferToFill.buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    lfo1_.setFrequency(apvts.getRawParameterValue("LFO_1_FREQUENCY")->load());
    Waveform waveform = static_cast<Waveform>(apvts.getRawParameterValue("LFO_1_WAVEFORM")->load());
    setLfo1Waveform(waveform);

    lfo1_output_ = lfo1_.processSample(0.0);
    lfo1_.process(context);
}
