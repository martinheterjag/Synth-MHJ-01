/*
  ==============================================================================

    FilterComponent.h
    Created: 26 Oct 2022 11:32:41pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SliderComponent.h"
#include "SynthModuleComponent.h"

class FilterComponent : public SynthModuleComponent {
public:
    FilterComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts);
    ~FilterComponent();
    void resized() override;
private:
    SliderComponent cutoff_slider_;
    SliderComponent resonance_slider_;
    SliderComponent envelope2_depth_slider_;
};
