/*
  ==============================================================================

    ButtonSelectComponent.h
    Created: 12 Nov 2022 10:24:15pm
    Author:  Martin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ButtonSelectComponent : public juce::Component {
public:
    ButtonSelectComponent(const juce::String& name, juce::AudioProcessorValueTreeState& apvts, juce::String param_id, juce::StringArray& buttons);
    void resetColours();
    void resized() override;
private:
    juce::Label label_;
    juce::ComboBox invisible_combo_box_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> invisible_combo_box_attachment_;
    juce::StringArray button_names_;
    std::vector<juce::TextButton> buttons_;
    int active_button_ = 0;
};
