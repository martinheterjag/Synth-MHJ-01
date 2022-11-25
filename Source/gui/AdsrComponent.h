/*
  ==============================================================================

    AdsrComponent.h
    Created: 26 Oct 2022 11:32:27pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include "SliderComponent.h"
#include "SynthModuleComponent.h"
#include <JuceHeader.h>

class AdsrComponent : public SynthModuleComponent
{
public:
    AdsrComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts, ParamIdPrefix param_id_prefix);
    ~AdsrComponent();
    void resized() override;

private:
    SliderComponent attack_slider_;
    SliderComponent decay_slider_;
    SliderComponent sustain_slider_;
    SliderComponent release_slider_;
};