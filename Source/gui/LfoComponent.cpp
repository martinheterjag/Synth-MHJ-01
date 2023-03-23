/*
  ==============================================================================

    LfoComponent.cpp
    Created: 31 Oct 2022 1:27:09pm
    Author:  Martin

  ==============================================================================
*/

#include "LfoComponent.h"

LfoComponent::LfoComponent (juce::String name,
                            juce::AudioProcessorValueTreeState& apvts,
                            ParamIdPrefix param_id_prefix)
    : SynthModuleComponent (name),
      frequency_slider_ ("Freq"),
      waveform_selector_ ("Waveform",
                          apvts,
                          param_id_string_map.at (param_id_prefix) + "WAVEFORM",
                          juce::StringArray ({ "sine", "saw", "square", "triangle" }))
{
    frequency_slider_.attatchToParameter (apvts,
                                          param_id_string_map.at (param_id_prefix) + "FREQUENCY");
    addAndMakeVisible (frequency_slider_);
    addAndMakeVisible (waveform_selector_);
}

void LfoComponent::lightUp (double amount) { frequency_slider_.lightUp (amount); }

LfoComponent::~LfoComponent() {}

void LfoComponent::resized()
{
    frequency_slider_.setBounds (
        MODULE_PADDING, MODULE_PADDING, SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    waveform_selector_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH,
                                  MODULE_PADDING,
                                  SLIDER_COMPONENT_WIDTH,
                                  SLIDER_COMPONENT_HEIGHT);
}
