/*
  ==============================================================================

    OscComponent.h
    Created: 26 Oct 2022 11:32:59pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModulationComponent.h"
#include "SynthModuleComponent.h"
#include "SliderComponent.h"


class OscComponent : public SynthModuleComponent {
public:
    OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, ParamIdPrefix param_id_prefix);
    ~OscComponent();
    void resized() override;
private:
    SliderComponent frequency_slider_;
    SliderComponent fine_pitch_slider_;
    ModulationComponent frequency_modulation_;
    SliderComponent waveform_slider_;
    ModulationComponent waveform_modulation_;
};
