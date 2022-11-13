/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gui/OscComponent.h"
#include "gui/ModWheelComponent.h"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 365;

//==============================================================================
Mhj01AudioProcessorEditor::Mhj01AudioProcessorEditor(Mhj01AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
      osc1_("Osc 1", p.apvts, ParamIdPrefix::OSC_1),
      osc2_("Osc 2", p.apvts, ParamIdPrefix::OSC_2),
      filter_("Filter", p.apvts),
      env1_("Env 1", p.apvts, ParamIdPrefix::ENV_1),
      env2_("Env 2", p.apvts, ParamIdPrefix::ENV_2),
      lfo1_("LFO 1", p.apvts, ParamIdPrefix::LFO_1),
      lfo2_("LFO 2", p.apvts, ParamIdPrefix::LFO_2),
      volume_knob_("Volume", SliderComponent::Style::KNOB),
      modwheel_controls_(p.apvts)
{
    addAndMakeVisible(osc1_);
    addAndMakeVisible(osc2_);
    addAndMakeVisible(filter_);
    addAndMakeVisible(env1_);
    addAndMakeVisible(env2_);
    addAndMakeVisible(lfo1_);
    addAndMakeVisible(lfo2_);
    volume_knob_.attatchToParameter(p.apvts, "VCA_GAIN");
    addAndMakeVisible(volume_knob_);
    addAndMakeVisible(modwheel_controls_);

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
    osc1_.setBounds (0, 0, 345, 130);
    osc2_.setBounds (0, 130, 345, 130);
    filter_.setBounds (345, 130, 300, 130);
    env1_.setBounds(345, 0, 225, 130);
    env2_.setBounds(570, 0, 225, 130);
    lfo1_.setBounds(795, 0, 200, 130);
    lfo2_.setBounds(795, 130, 200, 130);
    volume_knob_.setBounds(15, 260, 60, 95);
    modwheel_controls_.setBounds(75, 260, 105, 95);
}
