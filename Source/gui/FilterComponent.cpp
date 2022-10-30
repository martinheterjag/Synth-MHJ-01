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
      cutoff_slider_("Cutoff"),
      resonance_slider_("Resonance"),
      envelope2_depth_slider_("Envelope 2")
{
    cutoff_slider_.attatchToParameter(apvts, "FILTER_CUTOFF");
    addAndMakeVisible(cutoff_slider_);

    resonance_slider_.attatchToParameter(apvts, "FILTER_RESONANCE");
    addAndMakeVisible(resonance_slider_);

    // TODO: Implement filter depth
    // envelope2_depth_slider_.attatchToParameter(apvts, "FLTER_ENV2_DEPTH");
    // addAndMakeVisible(envelope2_depth_slider_);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::resized()
{
    cutoff_slider_.setBounds(MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
    resonance_slider_.setBounds(MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE + 75,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
    envelope2_depth_slider_.setBounds(MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE + 150,
        MODULE_BACKGROUND_TRIM_SIZE + TEXT_LABEL_HEIGHT,
        75, 115);
}
