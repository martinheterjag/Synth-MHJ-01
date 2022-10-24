/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Oct 2022 11:54:56am
    Author:  Martin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SynthVoice.h"

SynthVoice::SynthVoice(juce::uint32 main_bus_output_channels)
    : main_bus_output_channels_(main_bus_output_channels)
{
}

SynthVoice::~SynthVoice()
{
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

juce::AudioBuffer<float> SynthVoice::process(juce::AudioBuffer<float> buffer)
{
    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto out_buffer = juce::AudioBuffer<float>(buffer.getNumChannels(), buffer.getNumSamples());
    auto out_block = juce::dsp::AudioBlock<float>(out_buffer);
    auto contextToUse = juce::dsp::ProcessContextNonReplacing<float>(block, out_block);
    signal_chain_.process(contextToUse);

    return out_buffer;
}

void SynthVoice::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    juce::dsp::ProcessSpec spec = { sampleRate, samplesPerBlockExpected,
                              main_bus_output_channels_ };
    signal_chain_.prepare(spec);
    auto& osc = signal_chain_.template get<osc_index>();
    // This sets the osc to a sawtooth waveform
    osc.initialise([](double x)
        {
            return juce::jmap(x,
                double(-juce::MathConstants<double>::pi),
                double(juce::MathConstants<double>::pi),
                double(-1),
                double(1));
        }, 2);
}

void SynthVoice::releaseResources()
{
    // Clean up if needed
}

void SynthVoice::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto block = juce::dsp::AudioBlock<float>(*bufferToFill.buffer);
    auto contextToUse = juce::dsp::ProcessContextReplacing<float>(block);
    signal_chain_.process(contextToUse);
}
