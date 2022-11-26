/*
  ==============================================================================

    SynthBlockComponent.h
    Created: 26 Oct 2022 11:32:03pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include "GuiConstants.h"
#include <JuceHeader.h>

class SynthModuleComponent : public juce::Component
{
public:
    explicit SynthModuleComponent (juce::String name);
    void paint (juce::Graphics& g) override;

protected:
    juce::String name_;
    juce::Label module_label_;
};