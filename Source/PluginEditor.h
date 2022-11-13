/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "gui/AdsrComponent.h"
#include "gui/FilterComponent.h"
#include "gui/LfoComponent.h"
#include "gui/ModWheelComponent.h"
#include "gui/OscComponent.h"
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
    OscComponent osc1_;
    OscComponent osc2_;
    FilterComponent filter_;
    AdsrComponent env1_;
    AdsrComponent env2_;
    LfoComponent lfo1_;
    LfoComponent lfo2_;
    // General controls, individual controls that are not grouped
    SliderComponent volume_knob_;
    ModWheelComopnent modwheel_controls_;

    Mhj01AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mhj01AudioProcessorEditor)
};
