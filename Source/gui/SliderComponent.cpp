/*
  ==============================================================================

    SliderComponent.cpp
    Created: 26 Oct 2022 11:31:40pm
    Author:  Martin

  ==============================================================================
*/

#include "SliderComponent.h"

int WIDTH = 75;
int HEIGHT = 100;
int FONT_SIZE = 12;

SliderComponent::SliderComponent(juce::String label_text) {
    slider_.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider_.setTextBoxStyle(juce::Slider::NoTextBox, true, 25, 25);
    addAndMakeVisible(slider_);

    label_.setFont(juce::Font(15.0f, juce::Font::FontStyleFlags::bold));
    label_.setColour(juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
    label_.setText(label_text, juce::dontSendNotification);
    label_.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label_);
}

void SliderComponent::attatchToParameter(juce::AudioProcessorValueTreeState& apvts, juce::String param_id) {
    attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, param_id, slider_);
}

void SliderComponent::resized()
{
    slider_.setBounds(0, 0, WIDTH, HEIGHT);
    label_.setBounds(0, HEIGHT, WIDTH, 15);
}
