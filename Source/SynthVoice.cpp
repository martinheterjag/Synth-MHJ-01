/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Oct 2022 11:54:56am
    Author:  Martin

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice()
{
}

SynthVoice::~SynthVoice()
{
}

void SynthVoice::prepare(juce::dsp::ProcessSpec spec)
{
    signal_chain_.prepare(spec);
    auto& osc = signal_chain_.template get<osc_index>();
    osc.initialise([](double x) { return std::sin(x); }, 128);
}

void SynthVoice::setOscFrequency(double f_hz)
{
    auto& osc = signal_chain_.template get<osc_index>();
    osc.setFrequency(f_hz, true);
}

void SynthVoice::setVcaGain(float gain)
{
    auto& vca = signal_chain_.template get<vca_index>();
    vca.setGainLinear(gain);
    if (gain < 0.1) {
        active_ = false;
    }
    else {
        active_ = true;
    }
}

void SynthVoice::setKey(const int key)
{
    key_ = key;
}

int SynthVoice::getKey()
{
    return key_;
}

bool SynthVoice::isActive()
{
    return active_;
}

void SynthVoice::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    signal_chain_.process(context);
}
