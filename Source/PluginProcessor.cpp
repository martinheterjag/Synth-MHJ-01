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
                       ),
    apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
    for (int i = 0; i < 8; i++) {
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
    juce::dsp::ProcessSpec spec = { sampleRate, static_cast<juce::uint32>(samplesPerBlock),
                                    static_cast<juce::uint32>(getMainBusNumOutputChannels()) };
    mod_.prepare(spec);
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
            int index = getAvailableVoiceIndex();
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
    mod_.process(apvts, juce::AudioSourceChannelInfo(buffer));
    double lfo1_mod = mod_.getLfo1Output();
    for (auto& voice : synth_voices_) {
        // TODO: Make helper functions
        // Oscillators
        double osc1_frequency_mod = juce::jmap<double>(
            lfo1_mod * apvts.getRawParameterValue("OSC_1_FREQUENCY_MOD_LFO_1")->load(),
            0.0, 2.0);
        voice.modulateOsc1Frequency(static_cast<double>(apvts.getRawParameterValue("OSC_1_FREQUENCY")->load()) + osc1_frequency_mod,
                                    apvts.getRawParameterValue("OSC_1_FREQUENCY_MOD_ENV_2")->load());
        double osc2_frequency_mod = juce::jmap<double>(
            lfo1_mod * apvts.getRawParameterValue("OSC_2_FREQUENCY_MOD_LFO_1")->load(),
            0.0, 2.0);
        voice.modulateOsc2Frequency(static_cast<double>(apvts.getRawParameterValue("OSC_2_FREQUENCY")->load()) + osc2_frequency_mod,
            apvts.getRawParameterValue("OSC_2_FREQUENCY_MOD_ENV_2")->load());
        voice.setWaveform(apvts.getRawParameterValue("OSC_1_WAVEFORM")->load(), 
                          apvts.getRawParameterValue("OSC_2_WAVEFORM")->load());

        // Filter
        float cutoff_mod = juce::jmap<float>(
            static_cast<float>(lfo1_mod) * apvts.getRawParameterValue("FILTER_CUTOFF_MOD_LFO_1")->load(),
            0.0f, 6500.0f);
        voice.setVcfParameters(apvts.getRawParameterValue("FILTER_CUTOFF")->load() + cutoff_mod,
                               apvts.getRawParameterValue("FILTER_RESONANCE")->load(),
                               apvts.getRawParameterValue("FILTER_CUTOFF_MOD_ENV_2")->load());

        // VCA
        voice.setVcaGain(apvts.getRawParameterValue("VCA_GAIN")->load());

        // Envepoles
        voice.setEnvelope1Parameters(apvts.getRawParameterValue("ENV_1_ATTACK")->load(),
                                     apvts.getRawParameterValue("ENV_1_DECAY")->load(),
                                     apvts.getRawParameterValue("ENV_1_SUSTAIN")->load(),
                                     apvts.getRawParameterValue("ENV_1_RELEASE")->load());
        voice.setEnvelope2Parameters(apvts.getRawParameterValue("ENV_2_ATTACK")->load(),
                                     apvts.getRawParameterValue("ENV_2_DECAY")->load(),
                                     apvts.getRawParameterValue("ENV_2_SUSTAIN")->load(),
                                     apvts.getRawParameterValue("ENV_2_RELEASE")->load());
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
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Mhj01AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

int Mhj01AudioProcessor::getAvailableVoiceIndex()
{
    // A ring buffer based voice stealing algrithm
    // Turn off the first note to check since it is likely to be an old one.
    unsigned int first_voice_to_check = next_voice_ % max_voices_;
    for (unsigned int i = 0; i < max_voices_; i++) {
        unsigned int voice_index = (i + next_voice_) % max_voices_;
        if (synth_voices_[voice_index].isActive()) {
            continue;
        }
        ++next_voice_;
        return voice_index;
    }

    synth_voices_[first_voice_to_check].noteOff();
    return first_voice_to_check;
}

juce::AudioProcessorValueTreeState::ParameterLayout Mhj01AudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // Signal chain parameters
    // Frequency parameter is not in Hertz, it's multiplied with the current note frequency for each synth voice.
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC_1_FREQUENCY", "Frequency", 0.25f, 2.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC_1_FREQUENCY_MOD_LFO_1", "LFO 1", 0.0f, 1.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC_1_FREQUENCY_MOD_ENV_2", "Envelope2 depth", 0.0f, 6000.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC_1_WAVEFORM", "Waveform", 0.0f, 2.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC_2_FREQUENCY", "Frequency", 0.25f, 2.0f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC_2_FREQUENCY_MOD_LFO_1", "LFO 1", 0.0f, 1.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC_2_FREQUENCY_MOD_ENV_2", "Envelope2 depth", 0.0f, 6000.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC_2_WAVEFORM", "Waveform", 0.0f, 2.0f, 0.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER_CUTOFF", "Cutoff", 10.0f, 12000.0f, 4500.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER_CUTOFF_MOD_LFO_1", "LFO 1", 0.0f, 1.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER_CUTOFF_MOD_ENV_2", "Envelope2 depth", 0.0f, 10000.0f, 1000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER_RESONANCE", "Resonance", 0.5f, 5.0f, 0.7f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("VCA_GAIN", "Gain", 0.0f, 1.0f, 0.7f));

    // Modulators parameters
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ENV_1_ATTACK", "Attack", 0.001f, 1.0f, 0.001f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ENV_1_DECAY", "Decay", 0.0f, 1.0f, 0.2f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ENV_1_SUSTAIN", "Sustain", 0.0f, 1.0f, 0.2f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ENV_1_RELEASE", "Release", 0.01f, 1.0f, 0.5f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ENV_2_ATTACK", "Attack", 0.001f, 1.0f, 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ENV_2_DECAY", "Decay", 0.0f, 1.0f, 0.2f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ENV_2_SUSTAIN", "Sustain", 0.0f, 1.0f, 0.2f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ENV_2_RELEASE", "Release", 0.01f, 1.0f, 0.5f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("LFO_1_FREQUENCY", "Frequency", 0.01f, 10.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("LFO_1_WAVEFORM", "Waveform", juce::StringArray { "Sine", "Saw", "Square", "Triangle" }, 1));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Mhj01AudioProcessor();
}
