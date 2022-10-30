/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/OscComponent.h"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 330;

//==============================================================================
Mhj01AudioProcessorEditor::Mhj01AudioProcessorEditor(Mhj01AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
      osc1_("Osc 1", p.apvts, ParamIdPrefix::OSC_1),
      osc2_("Osc 2", p.apvts, ParamIdPrefix::OSC_2),
      filter_("Filter", p.apvts),
      env1_("Env 1", p.apvts, ParamIdPrefix::ENV_1),
      env2_("Env 2", p.apvts, ParamIdPrefix::ENV_2),
      volume_knob_("Volume", SliderComponent::Style::KNOB)
{
    addAndMakeVisible(osc1_);
    addAndMakeVisible(osc2_);
    addAndMakeVisible(filter_);
    addAndMakeVisible(env1_);
    addAndMakeVisible(env2_);
    volume_knob_.attatchToParameter(p.apvts, "VCA_GAIN");
    addAndMakeVisible(volume_knob_);

    setSize (WIDTH, HEIGHT);
}

Mhj01AudioProcessorEditor::~Mhj01AudioProcessorEditor()
{
}

//==============================================================================
void Mhj01AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (40.0f);
    g.drawFittedText ("MHJ-01", getLocalBounds(), juce::Justification::bottomRight, 1);
}

void Mhj01AudioProcessorEditor::resized()
{
    osc1_.setBounds (0, 0, 300, 130);
    osc2_.setBounds (0, 130, 300, 130);
    filter_.setBounds (300, 130, 300, 130);
    env1_.setBounds(300, 0, 225, 130);
    env2_.setBounds(525, 0, 225, 130);
    volume_knob_.setBounds(15, 260, 60, 60);
}
