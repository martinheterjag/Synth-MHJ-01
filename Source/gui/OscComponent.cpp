/*
  ==============================================================================

    OscComponent.cpp
    Created: 26 Oct 2022 11:32:59pm
    Author:  Martin

  ==============================================================================
*/

#include "OscComponent.h"



OscComponent::OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, ParamIdPrefix param_id_prefix)
    : SynthModuleComponent(name), frequency_slider_("Frequency"), waveform_slider_("Waveform")
{
    juce::String param_id = param_id_string_map.at(param_id_prefix) + "FREQUENCY";
    frequency_slider_.attatchToParameter(apvts, param_id);
    addAndMakeVisible(frequency_slider_);

    waveform_slider_.attatchToParameter(apvts, param_id_string_map.at(param_id_prefix) + "WAVEFORM");
    addAndMakeVisible(waveform_slider_);
}

OscComponent::~OscComponent()
{
}

void OscComponent::resized()
{
    frequency_slider_.setBounds (MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
    waveform_slider_.setBounds(MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE + 75,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
}
