/*
  ==============================================================================

    RotaryDialLookAndFeel.cpp
    Created: 27 Mar 2026 1:43:32pm
    Author:  peter

  ==============================================================================
*/

#include "RotaryDialLookAndFeel.h"
#include "Colors.h"

void RotaryDialLookAndFeel::drawRotarySlider(
    juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    auto radius = juce::jmin(width, height) / 2.0f - 10.0f;
    auto centerX = x + width * 0.5f;
    auto centerY = y + height * 0.5f;

    // Dial
    g.setColour(Colors::dialColor);
    g.fillEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // Base angle
    float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    float innerRadius = radius * 0.6f;
    float outerRadius = radius;

    // Indicator
    juce::Line<float> line(
        centerX + innerRadius * std::cos(angle - juce::MathConstants<float>::halfPi),
        centerY + innerRadius * std::sin(angle - juce::MathConstants<float>::halfPi),
        centerX + outerRadius * std::cos(angle - juce::MathConstants<float>::halfPi),
        centerY + outerRadius * std::sin(angle - juce::MathConstants<float>::halfPi)
    );

    g.setColour(Colors::indicatorColor);
    g.drawLine(line, 10.0f);
}