/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 400;

//==============================================================================
Mhj01AudioProcessorEditor::Mhj01AudioProcessorEditor (Mhj01AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
      osc1_frequency_slider_("Frequency"),
      osc2_frequency_slider_("Frequency")
{
    osc1_frequency_slider_.attatchToParameter(audioProcessor.apvts, "OSC_1_FREQUENCY");
    addAndMakeVisible(osc1_frequency_slider_);
    osc2_frequency_slider_.attatchToParameter(audioProcessor.apvts, "OSC_2_FREQUENCY");
    addAndMakeVisible(osc2_frequency_slider_);

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
    osc1_frequency_slider_.setBounds (0, 0, 75, 115);
    osc2_frequency_slider_.setBounds (75, 0, 75, 115);
}
