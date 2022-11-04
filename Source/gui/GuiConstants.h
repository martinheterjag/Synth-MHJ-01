/*
  ==============================================================================

    GuiConstants.h
    Created: 4 Nov 2022 10:25:58pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// SliderComponent constants
constexpr int SLIDER_WIDTH = 45;
constexpr int SLIDER_HEIGHT = 85;
constexpr int KNOB_WIDTH = SLIDER_WIDTH;
constexpr int KNOB_HEIGHT = SLIDER_WIDTH;
constexpr int SMALL_KNOB_WIDTH = 10;
constexpr int SMALL_KNOB_HEIGHT = 10;
constexpr int TEXT_LABEL_HEIGHT = 15;
constexpr int FONT_SIZE = 12;

// General constants
constexpr float MODULE_BACKGROUND_CORNER_SIZE = 10.0f;
constexpr float MODULE_BACKGROUND_TRIM_SIZE = 5.0f;
constexpr float MODULE_PADDING = MODULE_BACKGROUND_CORNER_SIZE + MODULE_BACKGROUND_TRIM_SIZE;
constexpr float SLIDER_COMPONENT_WIDTH = SLIDER_WIDTH;
constexpr float SLIDER_COMPONENT_HEIGHT = SLIDER_HEIGHT + TEXT_LABEL_HEIGHT;
constexpr float TEXT_LABEL_WIDTH = SLIDER_COMPONENT_WIDTH;

enum class ParamIdPrefix {
    OSC_1,
    OSC_2,
    ENV_1,
    ENV_2,
    LFO_1,
    LFO_2
};

const std::map<ParamIdPrefix, const juce::String> param_id_string_map = {
    {ParamIdPrefix::OSC_1, "OSC_1_"},
    {ParamIdPrefix::OSC_2, "OSC_2_"},
    {ParamIdPrefix::ENV_1, "ENV_1_"},
    {ParamIdPrefix::ENV_2, "ENV_2_"},
    {ParamIdPrefix::LFO_1, "LFO_1_"},
    {ParamIdPrefix::LFO_2, "LFO_2_"}
};
