/*
  ==============================================================================

    OscComponent.h
    Created: 26 Oct 2022 11:32:59pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthModuleComponent.h"
#include "SliderComponent.h"

class OscComponent : public SynthModuleComponent {
public:
    OscComponent(juce::String name);
    ~OscComponent();
    void resized() override;
private:
    juce::String name_;
    SliderComponent frequency_;
};
