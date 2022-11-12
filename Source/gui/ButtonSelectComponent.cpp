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
    : button_names_(buttons), buttons_(sizeof(button_names_))
{
    //label_.setColour(juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
    //label_.setFont(juce::Font(FONT_SIZE, juce::Font::FontStyleFlags::bold));
    //label_.setJustificationType(juce::Justification::centred);
    //label_.setText(name, juce::dontSendNotification);
    //addAndMakeVisible(label_);

    // The combo box is not visible in the gui but set by the buttons callback functions.
    // This is because it is easy to attach a combo box with the apvts instead of implementing a
    // new custom attachment class for the ButtonSelectComponent.
    invisible_combo_box_.addItemList(buttons, 1);
    invisible_combo_box_.setSelectedId(0);
    invisible_combo_box_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        apvts, param_id, invisible_combo_box_);

    int i = 0;
    for (auto& button : buttons_) {
        button.setButtonText(button_names_[++i]);
        button.setColour(juce::ToggleButton::ColourIds::textColourId, juce::Colours::darkgrey);
        addAndMakeVisible(button);
    }

}

void ButtonSelectComponent::resized()
{
    // label_.setBounds(0, 0, TEXT_LABEL_WIDTH * 2, TEXT_LABEL_HEIGHT);
    int i = 0;
    for (auto& button : buttons_) {
        button.setBounds(0, i, TEXT_LABEL_WIDTH * 2, TEXT_LABEL_HEIGHT);
        i += 20;
    }
}
