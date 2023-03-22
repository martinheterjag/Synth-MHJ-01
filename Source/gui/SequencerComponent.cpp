/*
  ==============================================================================

    SequencerComponent.cpp
    Created: 6 Dec 2022 12:03:11pm
    Author:  Martin

  ==============================================================================
*/

#include "SequencerComponent.h"
#include <JuceHeader.h>

//==============================================================================
SequencerComponent::SequencerComponent (juce::String name,
                                        juce::AudioProcessorValueTreeState& apvts)
    : SynthModuleComponent (name),
      trigger_selector_ ("Trigger",
                         apvts,
                         "SEQUENCER_TRIGGER",
                         juce::StringArray ({ "LFO1", "Keyboard" })),
      step_1_ ("1"),
      step_2_ ("2"),
      step_3_ ("3"),
      step_4_ ("4"),
      step_5_ ("5")
{
    addAndMakeVisible (trigger_selector_);

    step_1_.attatchToParameter (apvts, "SEQUENCER_STEP_1");
    addAndMakeVisible (step_1_);

    step_2_.attatchToParameter (apvts, "SEQUENCER_STEP_2");
    addAndMakeVisible (step_2_);

    step_3_.attatchToParameter (apvts, "SEQUENCER_STEP_3");
    addAndMakeVisible (step_3_);

    step_4_.attatchToParameter (apvts, "SEQUENCER_STEP_4");
    addAndMakeVisible (step_4_);

    step_5_.attatchToParameter (apvts, "SEQUENCER_STEP_5");
    addAndMakeVisible (step_5_);
}

SequencerComponent::~SequencerComponent() {}

void SequencerComponent::setActiveStep (unsigned int step)
{
    step_1_.lightUp (step == 0 ? 1.0 : 0.0);
    step_2_.lightUp (step == 1 ? 1.0 : 0.0);
    step_3_.lightUp (step == 2 ? 1.0 : 0.0);
    step_4_.lightUp (step == 3 ? 1.0 : 0.0);
    step_5_.lightUp (step == 4 ? 1.0 : 0.0);
}

void SequencerComponent::resized()
{
    trigger_selector_.setBounds (
        MODULE_PADDING, MODULE_PADDING, SLIDER_COMPONENT_WIDTH, SLIDER_COMPONENT_HEIGHT);
    step_1_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
    step_2_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 2,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
    step_3_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 3,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
    step_4_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 4,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
    step_5_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 5,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
}
