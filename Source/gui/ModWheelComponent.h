/*
  ==============================================================================

    ModWheelComponent.h
    Created: 13 Nov 2022 8:36:30pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ModWheelComopnent : public juce::Component {
public:
    ModWheelComopnent(juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
private:
    juce::TextButton osc1_lfo1_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> osc1_lfo1_attachment_;
    juce::TextButton osc1_waveform_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> osc1_waveform_attachment_;
    juce::TextButton osc2_lfo1_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> osc2_lfo1_attachment_;
    juce::TextButton osc2_waveform_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> osc2_waveform_attachment_;
    juce::TextButton filter_lfo1_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> filter_lfo1_attachment_;
    juce::TextButton filter_cutoff_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> filter_cutoff_attachment_;

};