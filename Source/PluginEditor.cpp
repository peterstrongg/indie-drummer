/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "KnobControl.h"

//==============================================================================
DrumMachineAudioProcessorEditor::DrumMachineAudioProcessorEditor (DrumMachineAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
	tempoKnob(audioProcessor.apvts, "TEMPO", "Tempo")
{
	addAndMakeVisible(tempoKnob);

    setSize (400, 300);
}

DrumMachineAudioProcessorEditor::~DrumMachineAudioProcessorEditor()
{

}

//==============================================================================
void DrumMachineAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void DrumMachineAudioProcessorEditor::resized()
{
	tempoKnob.setBounds(150, 50, 120, 120);
}
