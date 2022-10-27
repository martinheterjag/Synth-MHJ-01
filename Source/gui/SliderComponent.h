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
    SliderComponent(juce::String label_text);
    void attatchToParameter(juce::AudioProcessorValueTreeState& apvts, juce::String param_id);
    void resized() override;

private:
    juce::Slider slider_;
    juce::Label label_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment_;
};
