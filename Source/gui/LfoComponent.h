/*
  ==============================================================================

    LfoComponent.h
    Created: 31 Oct 2022 1:27:09pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include "ButtonSelectComponent.h"
#include "SliderComponent.h"
#include "SynthModuleComponent.h"
#include <JuceHeader.h>

class LfoComponent : public SynthModuleComponent
{
public:
    LfoComponent (juce::String name,
                  juce::AudioProcessorValueTreeState& apvts,
                  ParamIdPrefix param_id_prefix);
    ~LfoComponent();
    void resized() override;

private:
    SliderComponent frequency_slider_;
    ButtonSelectComponent waveform_selector_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveform_attachment_;
};
