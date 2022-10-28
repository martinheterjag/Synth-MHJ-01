/*
  ==============================================================================

    SynthBlockComponent.h
    Created: 26 Oct 2022 11:32:03pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

constexpr float MODULE_BACKGROUND_CORNER_SIZE = 15.0f;
constexpr float MODULE_BACKGROUND_TRIM_SIZE = 10.0f;
constexpr float TEXT_LABEL_WIDTH = 100.0f;
constexpr float TEXT_LABEL_HEIGHT = 15.0f;

class SynthModuleComponent : public juce::Component {
public:
    SynthModuleComponent(juce::String name);
    void paint(juce::Graphics& g) override;
protected:
    juce::String name_;
    juce::Label module_label_;
};