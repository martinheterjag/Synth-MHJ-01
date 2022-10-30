/*
  ==============================================================================

    OscComponent.cpp
    Created: 26 Oct 2022 11:32:59pm
    Author:  Martin

  ==============================================================================
*/

#include "OscComponent.h"

OscComponent::OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, ParamIdPrefix param_id_prefix)
    : SynthModuleComponent(name), frequency_slider_("Freq"), waveform_slider_("Shape")
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
    frequency_slider_.setBounds (MODULE_PADDING,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    waveform_slider_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
}
