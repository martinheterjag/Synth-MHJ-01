/*
  ==============================================================================

    Lfo.cpp
    Created: 10 Nov 2022 10:10:26pm
    Author:  Martin

  ==============================================================================
*/

#include "Lfo.h"

void Lfo::setWaveform (Waveform waveform)
{
    if (waveform == waveform_)
        return;
    waveform_ = waveform;
    resetLfo();
}

std::vector<double> Lfo::getOutput()
{
    if (output_.size() > 0)
        return output_;
    else
        return { 0.0 };
}

void Lfo::update (juce::dsp::ProcessContextReplacing<float>& context)
{
    output_.clear();
    for (int i = 0; i < context.getOutputBlock().getNumSamples(); i++)
    {
        output_.push_back (processSample (0.0));
    }
    process (context);
}

void Lfo::resetLfo()
{
    switch (waveform_)
    {
    case (Waveform::SINE):
        initialise ([] (float x) { return std::sin (x); }, 128);
        break;
    case (Waveform::SAW):
        initialise ([] (float x) { return x / juce::MathConstants<double>::pi; }, 128);
        break;
    case (Waveform::SQUARE):
        initialise ([] (float x) { return (x > 0.0f ? -0.5f : 0.5f); }, 128);
        break;
    case (Waveform::TRIANGLE):
        initialise ([] (float x) { return (x > 0.0 ? 2.0f * x - 0.5f : -2.0f * x - 0.5f); }, 128);
        break;
    default:
        DBG ("Warning, we should not get here.");
    }
}
