/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 26 Oct 2022 11:32:27pm
    Author:  Martin

  ==============================================================================
*/

#include "AdsrComponent.h"

AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, ParamIdPrefix param_id_prefix)
    : SynthModuleComponent(name), attack_slider_("Att"),
    decay_slider_("Dec"), sustain_slider_("Sus"), release_slider_("Rel")
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
    attack_slider_.setBounds(MODULE_PADDING,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    decay_slider_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    sustain_slider_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 2,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    release_slider_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 3,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
}
