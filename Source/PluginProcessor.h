/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "Modulation.h"
#include "StepSequencer.h"
#include "SynthVoice.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class Mhj01AudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    Mhj01AudioProcessor();
    ~Mhj01AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processMidi (juce::MidiBuffer& midi_messages);
    void processOscs (SynthVoice& voice, double lfo1_mod, double lfo2_mod, double seq_mod);
    void processNoise (SynthVoice& voice);
    void processFilter (SynthVoice& voice, double lfo1_mod, double lfo2_mod);
    void processVca (SynthVoice& voice);
    void processEnvelopes (SynthVoice& voice);

    void triggerSeqOnRisingEdge (double value);
    double getCoarse (double frequency);
    double getModWheelAmount (juce::String parameter);
    double getChannelPressureAmount (juce::String parameter);

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

private:
    int getAvailableVoiceIndex();
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    std::vector<SynthVoice> synth_voices_;
    unsigned int max_voices_ = 0;
    unsigned int next_voice_ = 0;
    juce::MixerAudioSource voice_mixer_;
    Modulation mod_;
    StepSequencer seq_;
    double pitch_wheel_ = 1.0;
    double mod_wheel_ = 0.0;
    double channel_pressure_ = 0.0;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mhj01AudioProcessor)
};
