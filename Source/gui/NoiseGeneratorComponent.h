/*
  ==============================================================================

    NoiseGeneratorComponent.h
    Created: 14 Nov 2022 1:11:51pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthModuleComponent.h"
#include "SliderComponent.h"

//==============================================================================
/*
*/
class NoiseGeneratorComponent  : public SynthModuleComponent
{
public:
    NoiseGeneratorComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts);
    ~NoiseGeneratorComponent() override;

    void resized() override;

private:
    SliderComponent volume_slider_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGeneratorComponent)
};
