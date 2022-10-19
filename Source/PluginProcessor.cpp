/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
        synth_voices_.emplace_back();
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
    juce::dsp::ProcessSpec spec = { sampleRate, samplesPerBlock, 
                                  getMainBusNumOutputChannels() };
    for (auto& voice : synth_voices_) {
        voice.prepare(spec);
        auto& osc = voice.template get<osc_index>();
        osc.initialise([](double x) { return std::sin(x); }, 128);

        auto& vca = voice.template get<vca_index>();
        vca.prepare(spec);
    }
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
    static int note_count;

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
            // TODO: insead of denying new notes, implement voice stealing.
            ++note_count;
            if (note_count <= max_voices_ && note_count > 0) {
                //frequency[note_count - 1] = midi_msg.getMidiNoteInHertz(note_number);
                //gain[note_count - 1] = 1.0f;
                auto& osc = synth_voices_[note_count - 1].template get<osc_index>();
                osc.setFrequency(midi_msg.getMidiNoteInHertz(note_number), true);

                auto& vca = synth_voices_[note_count - 1].template get<vca_index>();
                vca.setGainLinear(0.5f);
                DBG("ON");
                DBG(note_count - 1);
                
            }
        }
        else if (midi_msg.isNoteOff()) {
            // TODO: since push and release order is not same, this implementation causes bugs
            //       Create a separate synth voice class to be able to check if active or not and
            //       to keep track of note number.
            --note_count;
            if (note_count < max_voices_ && note_count >= 0) {
                auto& vca = synth_voices_[note_count].template get<vca_index>();
                vca.setGainLinear(0.0f);
                DBG("OFF");
                DBG(note_count);
            }
        }
    }


    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto contextToUse = juce::dsp::ProcessContextReplacing<float>(block);

    //for (auto& voice : synth_voices_) {
    //    voice.process(contextToUse);
    //}

    synth_voices_[3].process(contextToUse);
    synth_voices_[2].process(contextToUse);
    synth_voices_[1].process(contextToUse);
    synth_voices_[0].process(contextToUse);

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

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Mhj01AudioProcessor();
}
