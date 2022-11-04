/*
  ==============================================================================

    FilterComponent.cpp
    Created: 26 Oct 2022 11:32:41pm
    Author:  Martin

  ==============================================================================
*/

#include "FilterComponent.h"

FilterComponent::FilterComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts)
    : SynthModuleComponent(name),
      cutoff_slider_("Freq"),
      cutoff_modulation_("Freq mod", apvts, ParamIdPrefix::FILTER_CUTOFF_MOD),
      resonance_slider_("Res"),
      envelope2_depth_slider_("Env2")
{
    cutoff_slider_.attatchToParameter(apvts, "FILTER_CUTOFF");
    addAndMakeVisible(cutoff_slider_);

    addAndMakeVisible(cutoff_modulation_);

    resonance_slider_.attatchToParameter(apvts, "FILTER_RESONANCE");
    addAndMakeVisible(resonance_slider_);

     envelope2_depth_slider_.attatchToParameter(apvts, "FILTER_ENV2_DEPTH");
     addAndMakeVisible(envelope2_depth_slider_);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::resized()
{
    cutoff_slider_.setBounds(MODULE_PADDING,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    cutoff_modulation_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH,
        MODULE_PADDING,
        MOD_COMPONENT_WIDTH, MOD_COMPONENT_HEIGHT);
    resonance_slider_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH  + MOD_COMPONENT_WIDTH,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    envelope2_depth_slider_.setBounds(MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 2 + MOD_COMPONENT_WIDTH,
        MODULE_PADDING,
        SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
}
