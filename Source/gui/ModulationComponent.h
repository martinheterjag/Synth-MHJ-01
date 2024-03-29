/*
  ==============================================================================

    ModulationComponent.h
    Created: 31 Oct 2022 1:27:30pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include "GuiConstants.h"
#include "SliderComponent.h"
#include <JuceHeader.h>

class ModulationComponent : public juce::Component
{
public:
    ModulationComponent (juce::String name,
                         juce::AudioProcessorValueTreeState& apvts,
                         ParamIdPrefix module_id_prefix,
                         ParamIdPrefix param_id_prefix);
    ~ModulationComponent();
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    juce::Label label_;
    SliderComponent lfo1_knob_;
    SliderComponent lfo2_knob_;
    SliderComponent env2_knob_;
    SliderComponent seq_knob_;
};