/*
  ==============================================================================

    Modulation.cpp
    Created: 31 Oct 2022 1:28:28pm
    Author:  Martin

  ==============================================================================
*/

#include "Modulation.h"

// TODO: Refactor to get rid of loads of duplicate code
Modulation::Modulation()
{
}

Modulation::~Modulation()
{
}

void Modulation::prepare(juce::dsp::ProcessSpec& spec)
{
    lfo1_.prepare (spec);
    lfo2_.prepare(spec);
    resetLfo1();
    resetLfo2();
}

void Modulation::setLfo1Waveform(Waveform waveform){
    if (waveform == lfo1_waveform_)
        return;
    lfo1_waveform_ = waveform;
    resetLfo1();
}

void Modulation::setLfo2Waveform(Waveform waveform){
    if (waveform == lfo2_waveform_)
        return;
    lfo2_waveform_ = waveform;
    resetLfo2();
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
            return (x > 0.0f ?
                -0.5f :
                0.5f);
            }, 128);
        break;
    case(Waveform::TRIANGLE):
        lfo1_.initialise([](float x) {
            return (x > 0.0 ?
                2.0f * x - 0.5f :
                -2.0f * x - 0.5f);
            }, 128);
            break;
    default:
        DBG("Warning, we should not get here.");
    }
}

void Modulation::resetLfo2() {
    switch (lfo2_waveform_) {
    case(Waveform::SINE):
        lfo2_.initialise([](float x) {
            return std::sin(x);
            }, 128);
        break;
    case(Waveform::SAW):
        lfo2_.initialise([](float x) {
            return x / juce::MathConstants<double>::pi;
            }, 128);
        break;
    case(Waveform::SQUARE):
        lfo2_.initialise([](float x) {
            return (x > 0.0f ?
                -0.5f :
                0.5f);
            }, 128);
        break;
    case(Waveform::TRIANGLE):
        lfo2_.initialise([](float x) {
            return (x > 0.0 ?
                2.0f * x - 0.5f :
                -2.0f * x - 0.5f);
            }, 128);
        break;
    default:
        DBG("Warning, we should not get here.");
    }
}

double Modulation::getLfo1Output() {
    return lfo1_output_;
}

double Modulation::getLfo2Output() {
    return lfo2_output_;
}

void Modulation::process(juce::AudioProcessorValueTreeState& apvts, const juce::AudioSourceChannelInfo bufferToFill)
{
    auto block = juce::dsp::AudioBlock<float>(*bufferToFill.buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    lfo1_.setFrequency(apvts.getRawParameterValue("LFO_1_FREQUENCY")->load());
    Waveform waveform_lfo1 = static_cast<Waveform>(apvts.getRawParameterValue("LFO_1_WAVEFORM")->load());
    setLfo1Waveform(waveform_lfo1);

    lfo1_output_ = lfo1_.processSample(0.0);
    lfo1_.process(context);

    lfo2_.setFrequency(apvts.getRawParameterValue("LFO_2_FREQUENCY")->load());
    Waveform waveform_lfo2 = static_cast<Waveform>(apvts.getRawParameterValue("LFO_2_WAVEFORM")->load());
    setLfo2Waveform(waveform_lfo2);

    lfo2_output_ = lfo2_.processSample(0.0);
    lfo2_.process(context);
}
