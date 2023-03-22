/*
  ==============================================================================

    ModulationComponent.cpp
    Created: 31 Oct 2022 1:27:30pm
    Author:  Martin

  ==============================================================================
*/

#include "ModulationComponent.h"

ModulationComponent::ModulationComponent (juce::String name,
                                          juce::AudioProcessorValueTreeState& apvts,
                                          ParamIdPrefix module_id_prefix,
                                          ParamIdPrefix param_id_prefix)
    : lfo1_knob_ ("LFO 1", SliderComponent::Style::SMALL_KNOB),
      lfo2_knob_ ("LFO 2", SliderComponent::Style::SMALL_KNOB),
      env2_knob_ ("Env 2", SliderComponent::Style::SMALL_KNOB),
      seq_knob_ ("Seq", SliderComponent::Style::SMALL_KNOB)
{
    label_.setColour (juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
    label_.setFont (juce::Font (FONT_SIZE, juce::Font::FontStyleFlags::bold));
    label_.setJustificationType (juce::Justification::centred);
    label_.setText (name, juce::dontSendNotification);
    addAndMakeVisible (label_);

    juce::String param_id_full_prefix =
        param_id_string_map.at (module_id_prefix) + param_id_string_map.at (param_id_prefix);

    lfo1_knob_.attatchToParameter (apvts, param_id_full_prefix + "LFO_1");
    addAndMakeVisible (lfo1_knob_);

    lfo2_knob_.attatchToParameter (apvts, param_id_full_prefix + "LFO_2");
    addAndMakeVisible (lfo2_knob_);

    env2_knob_.attatchToParameter (apvts, param_id_full_prefix + "ENV_2");
    addAndMakeVisible (env2_knob_);

    seq_knob_.attatchToParameter (apvts, param_id_full_prefix + "SEQ");
    addAndMakeVisible (seq_knob_);
}

ModulationComponent::~ModulationComponent() {}

void ModulationComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::darkgrey);
    auto rect = getLocalBounds()
                    .withTrimmedBottom (MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT)
                    .withTrimmedTop (MODULE_BACKGROUND_TRIM_SIZE)
                    .withTrimmedLeft (MODULE_BACKGROUND_TRIM_SIZE)
                    .withTrimmedRight (MODULE_BACKGROUND_TRIM_SIZE);
    g.drawRoundedRectangle (rect.toFloat(), MODULE_BACKGROUND_CORNER_SIZE, LINE_THICKNESS);
}

void ModulationComponent::resized()
{
    lfo1_knob_.setBounds (MOD_COMPONENT_PADDING,
                          MOD_COMPONENT_PADDING,
                          SMALL_KNOB_WIDTH,
                          SMALL_KNOB_HEIGHT + SMALL_TEXT_LABEL_HEIGHT);
    lfo2_knob_.setBounds (MOD_COMPONENT_PADDING + SMALL_KNOB_WIDTH,
                          MOD_COMPONENT_PADDING,
                          SMALL_KNOB_WIDTH,
                          SMALL_KNOB_HEIGHT + SMALL_TEXT_LABEL_HEIGHT);
    env2_knob_.setBounds (MOD_COMPONENT_PADDING,
                          MOD_COMPONENT_PADDING + SMALL_KNOB_HEIGHT,
                          SMALL_KNOB_WIDTH,
                          SMALL_KNOB_HEIGHT + SMALL_TEXT_LABEL_HEIGHT);
    seq_knob_.setBounds (MOD_COMPONENT_PADDING + SMALL_KNOB_WIDTH,
                         MOD_COMPONENT_PADDING + SMALL_KNOB_HEIGHT,
                         SMALL_KNOB_WIDTH,
                         SMALL_KNOB_HEIGHT + SMALL_TEXT_LABEL_HEIGHT);
    label_.setBounds (0, SLIDER_HEIGHT, TEXT_LABEL_WIDTH * 2, TEXT_LABEL_HEIGHT);
}
