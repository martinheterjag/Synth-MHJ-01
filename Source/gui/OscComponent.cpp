/*
  ==============================================================================

    OscComponent.cpp
    Created: 26 Oct 2022 11:32:59pm
    Author:  Martin

  ==============================================================================
*/

#include "OscComponent.h"

OscComponent::OscComponent(juce::String name) : name_(name), frequency_("Frequency")
{
}

OscComponent::~OscComponent()
{
}

void OscComponent::resized()
{
}
