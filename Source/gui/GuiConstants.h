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
constexpr int SMALL_KNOB_WIDTH = 35;
constexpr int SMALL_KNOB_HEIGHT = 35;
constexpr int TEXT_LABEL_HEIGHT = 15;
constexpr int FONT_SIZE = 12;
constexpr int SMALL_TEXT_LABEL_HEIGHT = 10;
constexpr int SMALL_FONT_SIZE = 10;

// General constants
constexpr int MODULE_BACKGROUND_CORNER_SIZE = 10;
constexpr int MODULE_BACKGROUND_TRIM_SIZE = 5;
constexpr int MODULE_PADDING = MODULE_BACKGROUND_CORNER_SIZE + MODULE_BACKGROUND_TRIM_SIZE;
constexpr int MOD_COMPONENT_PADDING = 5;
constexpr int SLIDER_COMPONENT_WIDTH = SLIDER_WIDTH;
constexpr int SLIDER_COMPONENT_HEIGHT = SLIDER_HEIGHT + TEXT_LABEL_HEIGHT;
constexpr int TEXT_LABEL_WIDTH = SLIDER_COMPONENT_WIDTH;
constexpr int MOD_COMPONENT_WIDTH = SLIDER_COMPONENT_WIDTH * 2;
constexpr int MOD_COMPONENT_HEIGHT = SLIDER_COMPONENT_HEIGHT;
constexpr int LINE_THICKNESS = 2;

enum class ParamIdPrefix {
    OSC_1,
    OSC_2,
    FREQUENCY_MOD,
    FILTER,
    CUTOFF_MOD,
    ENV_1,
    ENV_2,
    LFO_1,
    LFO_2
};

const std::map<ParamIdPrefix, const juce::String> param_id_string_map = {
    {ParamIdPrefix::OSC_1, "OSC_1_"},
    {ParamIdPrefix::OSC_2, "OSC_2_"},
    {ParamIdPrefix::FREQUENCY_MOD, "FREQUENCY_MOD_"},
    {ParamIdPrefix::FILTER, "FILTER_"},
    {ParamIdPrefix::CUTOFF_MOD, "CUTOFF_MOD_"},
    {ParamIdPrefix::ENV_1, "ENV_1_"},
    {ParamIdPrefix::ENV_2, "ENV_2_"},
    {ParamIdPrefix::LFO_1, "LFO_1_"},
    {ParamIdPrefix::LFO_2, "LFO_2_"}
};
