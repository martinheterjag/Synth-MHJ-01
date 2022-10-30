/*
  ==============================================================================

    SliderComponent.cpp
    Created: 26 Oct 2022 11:31:40pm
    Author:  Martin

  ==============================================================================
*/

#include "SliderComponent.h"

constexpr int SLIDER_WIDTH = 45;
constexpr int SLIDER_HEIGHT = 85;
constexpr int KNOB_WIDTH = 45;
constexpr int KNOB_HEIGHT = 45;
constexpr int SMALL_KNOB_WIDTH = 10;
constexpr int SMALL_KNOB_HEIGHT = 10;
constexpr int LABEL_HEIGHT = 15;
constexpr int FONT_SIZE = 12;

SliderComponent::SliderComponent(juce::String label_text, SliderComponent::Style style)
    : style_(style)
{
    switch (style_) {
    case Style::SLIDER:
        slider_.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        slider_.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::gold);
        label_.setColour(juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
        break;
    case Style::KNOB:
        slider_.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        slider_.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::lightgoldenrodyellow);
        label_.setColour(juce::Label::ColourIds::textColourId, juce::Colours::lightgoldenrodyellow);
        break;
    case Style::SMALL_KNOB:
        slider_.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        slider_.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::gold);
        label_.setColour(juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
        break;
    }

    slider_.setTextBoxStyle(juce::Slider::NoTextBox, true, 25, 25);
    addAndMakeVisible(slider_);

    label_.setFont(juce::Font(FONT_SIZE, juce::Font::FontStyleFlags::bold));
    label_.setText(label_text, juce::dontSendNotification);
    label_.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label_);
}

void SliderComponent::attatchToParameter(juce::AudioProcessorValueTreeState& apvts, juce::String param_id) {
    attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, param_id, slider_);
}

void SliderComponent::resized()
{
    switch (style_) {
    case Style::SLIDER:
        slider_.setBounds(0, 0, SLIDER_WIDTH, SLIDER_HEIGHT);
        label_.setBounds(0, SLIDER_HEIGHT, SLIDER_WIDTH, LABEL_HEIGHT);
        break;
    case Style::KNOB:
        slider_.setBounds(0, 0, KNOB_WIDTH, KNOB_HEIGHT);
        label_.setBounds(0, KNOB_HEIGHT, KNOB_WIDTH, LABEL_HEIGHT);
        break;
    case Style::SMALL_KNOB:
        slider_.setBounds(0, 0, SMALL_KNOB_WIDTH, SMALL_KNOB_HEIGHT);
        label_.setBounds(0, SMALL_KNOB_HEIGHT, SMALL_KNOB_WIDTH, LABEL_HEIGHT);
        break;
    }
}
