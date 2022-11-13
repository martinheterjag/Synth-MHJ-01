/*
  ==============================================================================

    ModWheelComponent.cpp
    Created: 13 Nov 2022 8:36:30pm
    Author:  Martin

  ==============================================================================
*/

#include "ModWheelComponent.h"
#include "GuiConstants.h"

ModWheelComopnent::ModWheelComopnent(juce::AudioProcessorValueTreeState& apvts)
    : osc1_lfo1_("Osc 1 LFO 1"), osc1_waveform_("Osc 1 Shape"),
      osc2_lfo1_("Osc 2 LFO 1"), osc2_waveform_("Osc 2 Shape"),
      filter_lfo1_("Filter LFO1"), filter_cutoff_("Filter Freq")
{
    addAndMakeVisible(osc1_lfo1_);
    osc1_lfo1_.setClickingTogglesState(true);
    osc1_lfo1_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    osc1_lfo1_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "MOD_WHEEL_OSC_1_LFO_1", osc1_lfo1_);
    addAndMakeVisible(osc1_waveform_);
    osc1_waveform_.setClickingTogglesState(true);
    osc1_waveform_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    osc1_waveform_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "MOD_WHEEL_OSC_1_WAVEFORM", osc1_waveform_);
    addAndMakeVisible(osc2_lfo1_);
    osc2_lfo1_.setClickingTogglesState(true);
    osc2_lfo1_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    osc2_lfo1_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "MOD_WHEEL_OSC_2_LFO_1", osc2_lfo1_);
    addAndMakeVisible(osc2_waveform_);
    osc2_waveform_.setClickingTogglesState(true);
    osc2_waveform_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    osc2_waveform_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "MOD_WHEEL_OSC_2_WAVEFORM", osc2_waveform_);
    addAndMakeVisible(filter_lfo1_);
    filter_lfo1_.setClickingTogglesState(true);
    filter_lfo1_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    filter_lfo1_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "MOD_WHEEL_FILTER_LFO_1", filter_lfo1_);
    addAndMakeVisible(filter_cutoff_);
    filter_cutoff_.setClickingTogglesState(true);
    filter_cutoff_.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::gold);
    filter_cutoff_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "MOD_WHEEL_FILTER_CUTOFF", filter_cutoff_);
}


void ModWheelComopnent::resized()
{
    osc1_lfo1_.setBounds(0, 0, 45, 20);
    osc1_waveform_.setBounds(50, 0, 45, 20);
    osc2_lfo1_.setBounds(0, 25, 45, 20);
    osc2_waveform_.setBounds(50, 25, 45, 20);
    filter_lfo1_.setBounds(0, 50, 45, 20);
    filter_cutoff_.setBounds(50, 50, 45, 20);
}
