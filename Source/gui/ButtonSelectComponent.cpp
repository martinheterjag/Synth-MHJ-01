/*
  ==============================================================================

    ButtonSelectComponent.cpp
    Created: 12 Nov 2022 10:24:15pm
    Author:  Martin

  ==============================================================================
*/

#include "ButtonSelectComponent.h"
#include "GuiConstants.h"

ButtonSelectComponent::ButtonSelectComponent(const juce::String& name, juce::AudioProcessorValueTreeState& apvts, juce::String param_id, juce::StringArray& buttons)
    : button_names_(buttons), buttons_(button_names_.size())
{
    // The combo box is not visible in the gui but set by the buttons callback functions.
    // This is because it is easy to attach a combo box with the apvts instead of implementing a
    // new custom attachment class for the ButtonSelectComponent.
    invisible_combo_box_.addItemList(buttons, 1);
    invisible_combo_box_.setSelectedId(0);
    invisible_combo_box_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        apvts, param_id, invisible_combo_box_);

    int i = 0;
    for (auto& button : buttons_) {
        button.setButtonText(button_names_[i]);
        button.onClick = [&, i]() {
            invisible_combo_box_.setSelectedId(i + 1);
            active_button_ = i;
            resetColours();
        };
        addAndMakeVisible(button);
        ++i;
    }
    resetColours();
}

void ButtonSelectComponent::resetColours() {
    for (int i = 0; i < buttons_.size(); ++i) {
        if (i == active_button_) {
            buttons_[i].setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::gold);
        }
        else {
            buttons_[i].setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkgrey);
        }
    }
}

void ButtonSelectComponent::resized()
{
    int i = 10;
    for (auto& button : buttons_) {
        button.setBounds(0, i, TEXT_LABEL_WIDTH, TEXT_LABEL_HEIGHT);
        i += 20;
    }
}
