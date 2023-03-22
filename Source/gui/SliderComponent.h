/*
  ==============================================================================

    SliderComponent.h
    Created: 26 Oct 2022 11:31:40pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include "GuiConstants.h"
#include <JuceHeader.h>

class SliderComponent : public juce::Component, juce::Timer
{
public:
    enum class Style
    {
        SLIDER,
        KNOB,
        SMALL_KNOB
    };

    explicit SliderComponent (juce::String label_text,
                              SliderComponent::Style style = SliderComponent::Style::SLIDER);
    void lightUp (double amount);
    void attatchToParameter (juce::AudioProcessorValueTreeState& apvts, juce::String param_id);
    void resized() override;
    void timerCallback() override;

private:
    SliderComponent::Style style_;
    juce::Slider slider_;
    juce::Label label_;
    juce::Colour thumb_colour_;
    juce::Colour light_colour_;
    double light_amount_ { 0.0 };
    double light_amount_target_ { 0.0 };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment_;
};
