/*
  ==============================================================================

    AftertouchComponent.h
    Created: 22 Nov 2022 12:15:43pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AftertouchComponent : public juce::Component
{
public:
    explicit AftertouchComponent (juce::AudioProcessorValueTreeState& apvts);
    void resized() override;

private:
    juce::Label label_;
    juce::TextButton osc1_lfo2_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> osc1_lfo2_attachment_;
    juce::TextButton osc1_waveform_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> osc1_waveform_attachment_;
    juce::TextButton osc2_lfo2_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> osc2_lfo2_attachment_;
    juce::TextButton osc2_waveform_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> osc2_waveform_attachment_;
    juce::TextButton filter_lfo2_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> filter_lfo2_attachment_;
    juce::TextButton filter_cutoff_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> filter_cutoff_attachment_;
};