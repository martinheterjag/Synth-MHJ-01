/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "gui/AdsrComponent.h"
#include "gui/AftertouchComponent.h"
#include "gui/FilterComponent.h"
#include "gui/LfoComponent.h"
#include "gui/ModWheelComponent.h"
#include "gui/NoiseGeneratorComponent.h"
#include "gui/OscComponent.h"
#include "gui/SliderComponent.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class Mhj01AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit Mhj01AudioProcessorEditor (Mhj01AudioProcessor&);
    ~Mhj01AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    OscComponent osc1_;
    OscComponent osc2_;
    NoiseGeneratorComponent noise_;
    FilterComponent filter_;
    AdsrComponent env1_;
    AdsrComponent env2_;
    LfoComponent lfo1_;
    LfoComponent lfo2_;
    // General controls, individual controls that are not grouped
    SliderComponent volume_knob_;
    ModWheelComopnent modwheel_controls_;
    AftertouchComponent aftertouch_controls_;

    Mhj01AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mhj01AudioProcessorEditor)
};
