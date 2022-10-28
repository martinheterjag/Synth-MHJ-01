/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/OscComponent.h"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 400;

//==============================================================================
Mhj01AudioProcessorEditor::Mhj01AudioProcessorEditor (Mhj01AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
      osc1_("Osc 1", p.apvts, ParamIdPrefix::OSC_1),
      osc2_("Osc 2", p.apvts, ParamIdPrefix::OSC_2)
{
    addAndMakeVisible(osc1_);
    addAndMakeVisible(osc2_);

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
    g.drawFittedText ("MHJ-01", getLocalBounds(), juce::Justification::centred, 1);
}

void Mhj01AudioProcessorEditor::resized()
{
    osc1_.setBounds (0, 0, 400, 200);
    osc2_.setBounds (0, 200, 400, 200);
}
