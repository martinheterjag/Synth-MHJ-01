/*
  ==============================================================================

    SynthBlockComponent.cpp
    Created: 26 Oct 2022 11:32:03pm
    Author:  Martin

  ==============================================================================
*/

#include "SynthModuleComponent.h"

SynthModuleComponent::SynthModuleComponent (juce::String name) : name_ (name)
{
    module_label_.setFont (juce::Font (TEXT_LABEL_HEIGHT, juce::Font::FontStyleFlags::bold));
    module_label_.setColour (juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
    module_label_.setText (name_, juce::dontSendNotification);
    module_label_.setJustificationType (juce::Justification::left);
    addAndMakeVisible (module_label_);
}

void SynthModuleComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::lightgoldenrodyellow);
    auto rect = getLocalBounds()
                    .withTrimmedBottom (MODULE_BACKGROUND_TRIM_SIZE)
                    .withTrimmedTop (MODULE_BACKGROUND_TRIM_SIZE)
                    .withTrimmedLeft (MODULE_BACKGROUND_TRIM_SIZE)
                    .withTrimmedRight (MODULE_BACKGROUND_TRIM_SIZE);
    g.fillRoundedRectangle (rect.toFloat(), MODULE_BACKGROUND_CORNER_SIZE);
    module_label_.setBounds (MODULE_BACKGROUND_TRIM_SIZE + MODULE_BACKGROUND_CORNER_SIZE,
                             MODULE_BACKGROUND_TRIM_SIZE,
                             100,
                             15);
}
