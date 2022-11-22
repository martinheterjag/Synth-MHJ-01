/*
  ==============================================================================

    AftertouchComponent.cpp
    Created: 22 Nov 2022 12:15:43pm
    Author:  Martin

  ==============================================================================
*/

#include "AftertouchComponent.h"


#include "ModWheelComponent.h"
#include "GuiConstants.h"

AftertouchComponent::AftertouchComponent(juce::AudioProcessorValueTreeState& apvts)
    : osc1_lfo2_("Osc 1 LFO 2"), osc1_waveform_("Osc 1 Shape"),
    osc2_lfo2_("Osc 2 LFO 2"), osc2_waveform_("Osc 2 Shape"),
    filter_lfo2_("Filter LFO 2"), filter_cutoff_("Filter Freq")
{
    label_.setColour(juce::Label::ColourIds::textColourId, juce::Colours::gold);
    label_.setFont(juce::Font(FONT_SIZE, juce::Font::FontStyleFlags::bold));
    label_.setJustificationType(juce::Justification::centred);
    label_.setText("Aftertouch destination", juce::dontSendNotification);
    addAndMakeVisible(label_);
    addAndMakeVisible(osc1_lfo2_);
    osc1_lfo2_.setClickingTogglesState(true);
    osc1_lfo2_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    osc1_lfo2_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "AFTERTOUCH_OSC_1_LFO_2", osc1_lfo2_);
    addAndMakeVisible(osc1_waveform_);
    osc1_waveform_.setClickingTogglesState(true);
    osc1_waveform_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    osc1_waveform_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "AFTERTOUCH_OSC_1_WAVEFORM", osc1_waveform_);
    addAndMakeVisible(osc2_lfo2_);
    osc2_lfo2_.setClickingTogglesState(true);
    osc2_lfo2_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    osc2_lfo2_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "AFTERTOUCH_OSC_2_LFO_2", osc2_lfo2_);
    addAndMakeVisible(osc2_waveform_);
    osc2_waveform_.setClickingTogglesState(true);
    osc2_waveform_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    osc2_waveform_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "AFTERTOUCH_OSC_2_WAVEFORM", osc2_waveform_);
    addAndMakeVisible(filter_lfo2_);
    filter_lfo2_.setClickingTogglesState(true);
    filter_lfo2_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    filter_lfo2_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "AFTERTOUCH_FILTER_LFO_2", filter_lfo2_);
    addAndMakeVisible(filter_cutoff_);
    filter_cutoff_.setClickingTogglesState(true);
    filter_cutoff_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    filter_cutoff_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "AFTERTOUCH_FILTER_CUTOFF", filter_cutoff_);
}


void AftertouchComponent::resized()
{
    label_.setBounds(0, 0, 105, 20);
    osc1_lfo2_.setBounds(5, 20, 45, 20);
    osc1_waveform_.setBounds(55, 20, 45, 20);
    osc2_lfo2_.setBounds(5, 45, 45, 20);
    osc2_waveform_.setBounds(55, 45, 45, 20);
    filter_lfo2_.setBounds(5, 70, 45, 20);
    filter_cutoff_.setBounds(55, 70, 45, 20);
}
