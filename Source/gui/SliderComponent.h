/*
  ==============================================================================

    SliderComponent.h
    Created: 26 Oct 2022 11:31:40pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SliderComponent : public juce::Component
{
public:
    enum class Style {
        SLIDER,
        KNOB,
        SMALL_KNOB
    };

    SliderComponent(juce::String label_text,
        SliderComponent::Style style = SliderComponent::Style::SLIDER);
    void attatchToParameter(juce::AudioProcessorValueTreeState& apvts, juce::String param_id);
    void resized() override;

private:
    SliderComponent::Style style_;
    juce::Slider slider_;
    juce::Label label_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment_;
};
