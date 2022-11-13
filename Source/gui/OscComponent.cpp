/*
  ==============================================================================

    OscComponent.cpp
    Created: 26 Oct 2022 11:32:59pm
    Author:  Martin

  ==============================================================================
*/

#include "OscComponent.h"

OscComponent::OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, ParamIdPrefix param_id_prefix)
    : SynthModuleComponent(name), frequency_slider_("Coarse"),
      fine_pitch_slider_("Fine"),
      frequency_modulation_("Freq mod", apvts, param_id_prefix, ParamIdPrefix::FREQUENCY_MOD),
      waveform_slider_("Shape"),
      waveform_modulation_("Shape mod", apvts, param_id_prefix, ParamIdPrefix::WAVEFORM_MOD)
{
    frequency_slider_.attatchToParameter(apvts, param_id_string_map.at(param_id_prefix) + "FREQUENCY");
    addAndMakeVisible(frequency_slider_);

    fine_pitch_slider_.attatchToParameter(apvts, param_id_string_map.at(param_id_prefix) + "FREQUENCY_FINE");
    addAndMakeVisible(fine_pitch_slider_);

    addAndMakeVisible(frequency_modulation_);

    waveform_slider_.attatchToParameter(apvts, param_id_string_map.at(param_id_prefix) + "WAVEFORM");
    addAndMakeVisible(waveform_slider_);

    addAndMakeVisible(waveform_modulation_);
}

OscComponent::~OscComponent()
{
}

void OscComponent::resized()
{
    frequency_slider_.setBounds (MODULE_PADDING,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    fine_pitch_slider_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    frequency_modulation_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 2,
        MODULE_PADDING,
        MOD_COMPONENT_WIDTH, MOD_COMPONENT_HEIGHT);
    waveform_slider_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 2 + MOD_COMPONENT_WIDTH,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    waveform_modulation_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 3 + MOD_COMPONENT_WIDTH,
        MODULE_PADDING,
        MOD_COMPONENT_WIDTH, MOD_COMPONENT_HEIGHT);
}
