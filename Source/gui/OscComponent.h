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


enum class ParamIdPrefix {
    OSC_1,
    OSC_2
};

const std::map<ParamIdPrefix, const juce::String> param_id_string_map = {
    {ParamIdPrefix::OSC_1, "OSC_1_"},
    {ParamIdPrefix::OSC_2, "OSC_2_"}
};


class OscComponent : public SynthModuleComponent {
public:
    OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, ParamIdPrefix param_id_prefix);
    ~OscComponent();
    void resized() override;
private:
    SliderComponent frequency_slider_;
    SliderComponent waveform_slider_;
};
