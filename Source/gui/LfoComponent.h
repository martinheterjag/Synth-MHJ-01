/*
  ==============================================================================

    LfoComponent.h
    Created: 31 Oct 2022 1:27:09pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthModuleComponent.h"
#include "SliderComponent.h"

class LfoComponent : public SynthModuleComponent {
public:
    LfoComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts,
                 ParamIdPrefix param_id_prefix);
    ~LfoComponent();
    void resized() override;
private:
    SliderComponent frequency_slider_;
    // TODO: Combobox looks kinda crappy, consider some other gui component to select waveform.
    juce::ComboBox waveform_selector_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveform_attachment_;
};