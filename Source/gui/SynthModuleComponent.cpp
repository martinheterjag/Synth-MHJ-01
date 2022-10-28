/*
  ==============================================================================

    SynthBlockComponent.cpp
    Created: 26 Oct 2022 11:32:03pm
    Author:  Martin

  ==============================================================================
*/

#include "SynthModuleComponent.h"

SynthModuleComponent::SynthModuleComponent()
{
}

void SynthModuleComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::lightgoldenrodyellow);
    auto rect = getLocalBounds()
        .withTrimmedBottom(MODULE_BACKGROUND_TRIM_SIZE)
        .withTrimmedTop(MODULE_BACKGROUND_TRIM_SIZE)
        .withTrimmedLeft(MODULE_BACKGROUND_TRIM_SIZE)
        .withTrimmedRight(MODULE_BACKGROUND_TRIM_SIZE);
    g.fillRoundedRectangle(rect.toFloat(), MODULE_BACKGROUND_CORNER_SIZE);

}
