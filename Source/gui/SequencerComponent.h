/*
  ==============================================================================

    SequencerComponent.h
    Created: 6 Dec 2022 12:03:11pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include "SliderComponent.h"
#include "SynthModuleComponent.h"
#include <JuceHeader.h>

class SequencerComponent : public SynthModuleComponent
{
public:
    SequencerComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts);
    ~SequencerComponent() override;

    void setActiveStep (unsigned int step);

    void resized() override;

private:
    SliderComponent step_1_;
    SliderComponent step_2_;
    SliderComponent step_3_;
    SliderComponent step_4_;
    SliderComponent step_5_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerComponent)
};
