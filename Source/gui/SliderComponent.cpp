/*
  ==============================================================================

    SliderComponent.cpp
    Created: 26 Oct 2022 11:31:40pm
    Author:  Martin

  ==============================================================================
*/

#include "SliderComponent.h"

SliderComponent::SliderComponent (juce::String label_text, SliderComponent::Style style)
    : style_ (style), light_colour_ (juce::Colours::hotpink)
{
    switch (style_)
    {
    case Style::SLIDER:
        slider_.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
        thumb_colour_ = juce::Colours::gold;
        label_.setColour (juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
        label_.setFont (juce::Font (FONT_SIZE, juce::Font::FontStyleFlags::bold));
        break;
    case Style::KNOB:
        slider_.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
        thumb_colour_ = juce::Colours::lightgoldenrodyellow;
        label_.setColour (juce::Label::ColourIds::textColourId,
                          juce::Colours::lightgoldenrodyellow);
        label_.setFont (juce::Font (FONT_SIZE, juce::Font::FontStyleFlags::bold));
        break;
    case Style::SMALL_KNOB:
        slider_.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
        thumb_colour_ = juce::Colours::gold;
        label_.setColour (juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
        label_.setFont (juce::Font (SMALL_FONT_SIZE, juce::Font::FontStyleFlags::bold));
        break;
    }

    slider_.setColour (juce::Slider::ColourIds::thumbColourId, thumb_colour_);

    slider_.setTextBoxStyle (juce::Slider::NoTextBox, true, 25, 25);
    addAndMakeVisible (slider_);

    label_.setText (label_text, juce::dontSendNotification);
    label_.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label_);

    startTimer (10);
}

void SliderComponent::lightUp (double amount)
{
    // Set the target value and let timerCallback animate the light.
    light_amount_target_ = amount;
    slider_.setColour (juce::Slider::ColourIds::thumbColourId,
                       thumb_colour_.interpolatedWith (light_colour_, light_amount_));
}

void SliderComponent::attatchToParameter (juce::AudioProcessorValueTreeState& apvts,
                                          juce::String param_id)
{
    attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, param_id, slider_);
}

void SliderComponent::resized()
{
    switch (style_)
    {
    case Style::SLIDER:
        slider_.setBounds (0, 0, SLIDER_WIDTH, SLIDER_HEIGHT);
        label_.setBounds (0, SLIDER_HEIGHT, SLIDER_WIDTH, TEXT_LABEL_HEIGHT);
        break;
    case Style::KNOB:
        slider_.setBounds (0, 0, KNOB_WIDTH, KNOB_HEIGHT);
        label_.setBounds (0, KNOB_HEIGHT, KNOB_WIDTH, TEXT_LABEL_HEIGHT);
        break;
    case Style::SMALL_KNOB:
        slider_.setBounds (0, 0, SMALL_KNOB_WIDTH, SMALL_KNOB_HEIGHT);
        label_.setBounds (0, SMALL_KNOB_HEIGHT - 10, SMALL_KNOB_WIDTH, SMALL_TEXT_LABEL_HEIGHT);
        break;
    }
}

void SliderComponent::timerCallback()
{
    // Light up fast but slowly decay, like a real LED behaves
    if (light_amount_target_ > light_amount_)
    {
        light_amount_ = light_amount_target_;
    }
    else
    {
        light_amount_ = (4.0 * light_amount_target_ + light_amount_) / 5.0;
    }
}
