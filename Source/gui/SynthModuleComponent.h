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

enum class ParamIdPrefix {
    OSC_1,
    OSC_2,
    ENV_1,
    ENV_2
};

const std::map<ParamIdPrefix, const juce::String> param_id_string_map = {
    {ParamIdPrefix::OSC_1, "OSC_1_"},
    {ParamIdPrefix::OSC_2, "OSC_2_"},
    {ParamIdPrefix::ENV_1, "ENV_1_"},
    {ParamIdPrefix::ENV_2, "ENV_2_"}
};

class SynthModuleComponent : public juce::Component {
public:
    SynthModuleComponent(juce::String name);
    void paint(juce::Graphics& g) override;
protected:
    juce::String name_;
    juce::Label module_label_;
};