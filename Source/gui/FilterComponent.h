/*
  ==============================================================================

    FilterComponent.h
    Created: 26 Oct 2022 11:32:41pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include "ModulationComponent.h"
#include "SliderComponent.h"
#include "SynthModuleComponent.h"
#include <JuceHeader.h>

class FilterComponent : public SynthModuleComponent
{
public:
    FilterComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts);
    ~FilterComponent();
    void resized() override;

private:
    SliderComponent cutoff_slider_;
    ModulationComponent cutoff_modulation_;
    SliderComponent resonance_slider_;
};
