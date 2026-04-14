#pragma once
#include <JuceHeader.h>
#include "RotaryDialLookAndFeel.h"

class KnobControl : public juce::Component,
    private juce::AudioProcessorValueTreeState::Listener
{
public:
    KnobControl(juce::AudioProcessorValueTreeState& apvts,
        const juce::String& paramID,
        const juce::String& label)
        : parameterID(paramID), apvtsRef(apvts)
    {
        titleLabel.setText(label, juce::dontSendNotification);
        titleLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(titleLabel);

        valueLabel.setJustificationType(juce::Justification::centred);
        // valueLabel.setFont(juce::Font(14.0f));
        addAndMakeVisible(valueLabel);

        knobLookAndFeel = std::make_unique<RotaryDialLookAndFeel>();
        slider.setLookAndFeel(knobLookAndFeel.get());

        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

        addAndMakeVisible(slider);

        sliderAttachment = std::make_unique<
            juce::AudioProcessorValueTreeState::SliderAttachment>(
                apvts, paramID, slider);

        apvts.addParameterListener(paramID, this);

        valueLabel.setText(juce::String(slider.getValue(), 0),
            juce::dontSendNotification);
    }

    ~KnobControl() override
    {
        slider.setLookAndFeel(nullptr);
        apvtsRef.removeParameterListener(parameterID, this);
    }

    void parameterChanged(const juce::String& id, float newValue) override
    {
        if (id == parameterID)
        {
            juce::MessageManager::callAsync([this, newValue]()
                {
                    valueLabel.setText(juce::String((int)newValue),
                        juce::dontSendNotification);
                });
        }
    }

    void resized() override
    {
        auto area = getLocalBounds();

        titleLabel.setBounds(area.removeFromTop(20));
        valueLabel.setBounds(area.removeFromBottom(20));
        slider.setBounds(area);
    }

private:
    juce::AudioProcessorValueTreeState& apvtsRef;
    juce::String parameterID;

    juce::Label titleLabel;
    juce::Label valueLabel;
    juce::Slider slider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
    std::unique_ptr<RotaryDialLookAndFeel> knobLookAndFeel;
};