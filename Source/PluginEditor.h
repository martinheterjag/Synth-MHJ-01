/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "gui/SliderComponent.h"

//==============================================================================
/**
*/
class Mhj01AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Mhj01AudioProcessorEditor (Mhj01AudioProcessor&);
    ~Mhj01AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SliderComponent osc1_frequency_slider_;
    SliderComponent osc2_frequency_slider_;

    Mhj01AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mhj01AudioProcessorEditor)
};
