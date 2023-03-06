/*
  ==============================================================================

    SequencerComponent.cpp
    Created: 6 Dec 2022 12:03:11pm
    Author:  Martin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SequencerComponent.h"

//==============================================================================
SequencerComponent::SequencerComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts)
    : SynthModuleComponent (name), 
      step_1_ ("1"),
      step_2_ ("2"),
      step_3_ ("3"),
      step_4_ ("4"),
      step_5_ ("5")
{
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

SequencerComponent::~SequencerComponent()
{
}

void SequencerComponent::resized()
{
    step_1_.setBounds (MODULE_PADDING,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
    step_2_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
    step_3_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 2,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
    step_4_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 3,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
    step_5_.setBounds (MODULE_PADDING + SLIDER_COMPONENT_WIDTH * 4,
                       MODULE_PADDING,
                       SLIDER_COMPONENT_WIDTH,
                       SLIDER_COMPONENT_HEIGHT);
}
