/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"


//==============================================================================
Mhj01AudioProcessor::Mhj01AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    for (int i = 0; i < 4; i++) {
        synth_voices_.push_back(SynthVoice(getMainBusNumOutputChannels()));
        ++max_voices_;
    }
}

Mhj01AudioProcessor::~Mhj01AudioProcessor()
{
}

//==============================================================================
const juce::String Mhj01AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Mhj01AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Mhj01AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Mhj01AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Mhj01AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Mhj01AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Mhj01AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Mhj01AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Mhj01AudioProcessor::getProgramName (int index)
{
    return {};
}

void Mhj01AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Mhj01AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (auto& voice : synth_voices_) {
        voice_mixer_.addInputSource(&voice, false);
    }
    voice_mixer_.prepareToPlay(samplesPerBlock, sampleRate);
}

void Mhj01AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Mhj01AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Mhj01AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    static double frequency[4];
    static float gain[4];

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (auto m : midiMessages) {
        juce::MidiMessage midi_msg = m.getMessage();
        if (midi_msg.isNoteOn()) {
            int note_number = midi_msg.getNoteNumber();
            // TODO: instead of denying new notes, implement voice stealing.
            int index = getAvailableVoiceIndex();
            if (index < 0) {
                continue;
            }
            synth_voices_[index].setVoiceFrequency(midi_msg.getMidiNoteInHertz(note_number));
            synth_voices_[index].setKey(note_number);
            synth_voices_[index].noteOn();
        }
        else if (midi_msg.isNoteOff()) {
            // Turn off all notes that have been set to the released key.
            for (auto& voice : synth_voices_) {
                if (voice.getKey() == midi_msg.getNoteNumber())
                    voice.noteOff();
            }
        }
    }
    for (auto& voice : synth_voices_) {
        voice.setVcfParameters(1800.0f, 0.9f);
        voice.modulateOsc1Frequency(0.5);
        voice.modulateOsc2Frequency(1.9);
        voice.setVcaGain(0.7f);
    }
    voice_mixer_.getNextAudioBlock(juce::AudioSourceChannelInfo(buffer));
}

//==============================================================================
bool Mhj01AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Mhj01AudioProcessor::createEditor()
{
    return new Mhj01AudioProcessorEditor (*this);
}

//==============================================================================
void Mhj01AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Mhj01AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

int Mhj01AudioProcessor::getAvailableVoiceIndex()
{
    for (int i = 0; i < max_voices_; i++) {
        if (synth_voices_[i].isActive()) {
            continue;
        }
        DBG("voice on " + std::to_string(i));
        return i;
    }
    return -1;  // No available voices
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Mhj01AudioProcessor();
}
