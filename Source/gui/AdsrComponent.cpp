/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 26 Oct 2022 11:32:27pm
    Author:  Martin

  ==============================================================================
*/

#include "AdsrComponent.h"

AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, ParamIdPrefix param_id_prefix)
    : SynthModuleComponent(name), attack_slider_("Attack"),
    decay_slider_("Decay"), sustain_slider_("Sustain"), release_slider_("Release")
{
    attack_slider_.attatchToParameter(apvts, param_id_string_map.at(param_id_prefix) + "ATTACK");
    addAndMakeVisible(attack_slider_);

    decay_slider_.attatchToParameter(apvts, param_id_string_map.at(param_id_prefix) + "DECAY");
    addAndMakeVisible(decay_slider_);

    sustain_slider_.attatchToParameter(apvts, param_id_string_map.at(param_id_prefix) + "SUSTAIN");
    addAndMakeVisible(sustain_slider_);

    release_slider_.attatchToParameter(apvts, param_id_string_map.at(param_id_prefix) + "RELEASE");
    addAndMakeVisible(release_slider_);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::resized()
{
    attack_slider_.setBounds(MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
    decay_slider_.setBounds(MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE + 75,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
    sustain_slider_.setBounds(MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE + 150,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
    release_slider_.setBounds(MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE + 225,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
}
