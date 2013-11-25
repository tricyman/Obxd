/*
==============================================================================

This file was auto-generated by the Introjucer!

It contains the basic startup code for a Juce application.

==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ObxdAudioProcessorEditor::ObxdAudioProcessorEditor (ObxdAudioProcessor* ownerFilter)
	: AudioProcessorEditor (ownerFilter)
{
	// This is where our plugin's editor size is set.
	setSize (800, 300);
	cutoffKnob = addNormalKnob(400,60,ownerFilter,CUTOFF,"Cutoff");
	resonanceKnob = addNormalKnob(450,60,ownerFilter,RESONANCE,"Resonance");
	filterEnvelopeAmtKnob = addNormalKnob(500,60,ownerFilter,ENVELOPE_AMT,"Envelope");
	multimodeKnob = addNormalKnob(450,115,ownerFilter,MULTIMODE,"Multimode");

	volumeKnob = addNormalKnob(10,70,ownerFilter,VOLUME,"Volume");
	portamentoKnob = addNormalKnob(60,70,ownerFilter,PORTAMENTO,"Portamento");
	osc1PitchKnob = addNormalKnob(160,60,ownerFilter,OSC1P,"Osc1Pitch");
	pulseWidthKnob = addNormalKnob(210,60,ownerFilter,PW,"PW");
	osc2PitchKnob = addNormalKnob(260,60,ownerFilter,OSC2P,"Osc2Pitch");

	osc1MixKnob = addTinyKnob(340,60,ownerFilter,OSC1MIX,"Osc1");
	osc2MixKnob = addTinyKnob(340,100,ownerFilter,OSC2MIX,"Osc2");
	noiseMixKnob = addTinyKnob(340,140,ownerFilter,NOISEMIX,"Noise");

	xmodKnob = addTinyKnob(215,140,ownerFilter,XMOD,"Xmod");
	osc2DetuneKnob = addTinyKnob(265,140,ownerFilter,OSC2_DET,"Detune");

	attackKnob = addNormalKnob(590,120,ownerFilter,LATK,"Atk");
	decayKnob = addNormalKnob(630,120,ownerFilter,LDEC,"Dec");
	sustainKnob = addNormalKnob(670,120,ownerFilter,LSUS,"Sus");
	releaseKnob = addNormalKnob(710,120,ownerFilter,LREL,"Rel");

	fattackKnob = addNormalKnob(590,60,ownerFilter,FATK,"Atk");
	fdecayKnob = addNormalKnob(630,60,ownerFilter,FDEC,"Dec");
	fsustainKnob = addNormalKnob(670,60,ownerFilter,FSUS,"Sus");
	freleaseKnob = addNormalKnob(710,60,ownerFilter,FREL,"Rel");

	hardSyncButton = addNormalTooglableButton(210,115,ownerFilter,OSC2HS,"Sync");
	osc1WfButton = addNormalTooglableButton(160,115,ownerFilter,OSC1P,"Form");
	osc2WfButton = addNormalTooglableButton(260,115,ownerFilter,OSC2P,"Form");
	pitchQuantButton =  addNormalTooglableButton(160,140,ownerFilter,OSCQuantize,"Step");

	filterKeyFollowButton =  addNormalTooglableButton(400,115,ownerFilter,FLT_KF,"Key");
	getFilter()->addChangeListener(this);
}

ObxdAudioProcessorEditor::~ObxdAudioProcessorEditor()
{
	getFilter()->removeChangeListener(this);
	deleteAllChildren();
}
Knob* ObxdAudioProcessorEditor::addNormalKnob(int x , int y ,ObxdAudioProcessor* filter, int parameter,String name)
{
	Knob* knob = new Knob();
	Label* knobl = new Label();
	knob->setSliderStyle(Slider::RotaryVerticalDrag);
	knob->setTextBoxStyle(knob->NoTextBox,true,0,0);
	knob->setRange(0,1);
	addAndMakeVisible(knob);
	addAndMakeVisible(knobl);
	knob->setBounds(x, y, 40,40);
	knob->setValue(filter->getParameter(parameter),dontSendNotification);
	knobl->setJustificationType(Justification::centred);
	knobl->setBounds(x-10,y+40,60,10);
	knobl->setText(name,dontSendNotification);
	knob->setTextBoxIsEditable(false);
	knob->addListener (this);
	return knob;
}
Knob* ObxdAudioProcessorEditor::addTinyKnob(int x , int y ,ObxdAudioProcessor* filter, int parameter,String name)
{
	Knob* knob = new Knob();
	Label* knobl = new Label();
	knob->setSliderStyle(Slider::RotaryVerticalDrag);
	knob->setTextBoxStyle(knob->NoTextBox,true,0,0);
	knob->setRange(0,1);
	addAndMakeVisible(knob);
	addAndMakeVisible(knobl);
	knob->setBounds(x, y, 30,30);
	knob->setValue(filter->getParameter(parameter),dontSendNotification);
	knobl->setJustificationType(Justification::centred);
	knobl->setBounds(x-10,y+25,50,10);
	knobl->setText(name,dontSendNotification);
	knob->setTextBoxIsEditable(false);
	knob->addListener (this);
	return knob;
}
TooglableButton*  ObxdAudioProcessorEditor::addNormalTooglableButton(int x , int y , ObxdAudioProcessor* filter,int parameter,String name)
{
	TooglableButton* button = new TooglableButton();
//	button->setButtonStyle(DrawableButton::ButtonStyle::ImageAboveTextLabel);
	addAndMakeVisible(button);
	button->setBounds(x,y,40,20);
	button->setButtonText(name);
	button->setValue(filter->getParameter(parameter),0);
	button->addListener(this);
	return button;
}
void ObxdAudioProcessorEditor::buttonClicked(Button * b)
{
	TooglableButton* tb = (TooglableButton*)(b);
	ObxdAudioProcessor* flt = getFilter();
#define bp(T) {flt->setParameterNotifyingHost(T,tb->getValue());}
#define handleBParam(K,T)  if (tb == K) {bp(T)} else
		handleBParam(hardSyncButton,OSC2HS)
		handleBParam(osc1WfButton,OSC1W)
		handleBParam(osc2WfButton,OSC2W)
		handleBParam(filterKeyFollowButton,FLT_KF)
		handleBParam(pitchQuantButton,OSCQuantize)
	{};
	
}
void ObxdAudioProcessorEditor::sliderValueChanged (Slider* c)
{
	ObxdAudioProcessor* flt = getFilter();
	//		flt->beginParameterChangeGesture();
#define sp(T) {flt->setParameterNotifyingHost(T,c->getValue());}
#define handleSParam(K,T)  if (c == K) {sp(T)} else
	handleSParam(cutoffKnob,CUTOFF)
	handleSParam(resonanceKnob,RESONANCE)
	handleSParam(volumeKnob,VOLUME)
	handleSParam(osc1PitchKnob,OSC1P)
	handleSParam(osc2PitchKnob,OSC2P)
	handleSParam(osc2DetuneKnob,OSC2_DET)
	handleSParam(portamentoKnob,PORTAMENTO)
	handleSParam(filterEnvelopeAmtKnob,ENVELOPE_AMT)
	handleSParam(pulseWidthKnob,PW)
	handleSParam(xmodKnob,XMOD)
	handleSParam(multimodeKnob,MULTIMODE)

	handleSParam(attackKnob,LATK)
	handleSParam(decayKnob,LDEC)
	handleSParam(sustainKnob,LSUS)
	handleSParam(releaseKnob,LREL)

	handleSParam(fattackKnob,FATK)
	handleSParam(fdecayKnob,FDEC)
	handleSParam(fsustainKnob,FSUS)
	handleSParam(freleaseKnob,FREL)

	handleSParam(osc1MixKnob,OSC1MIX)
	handleSParam(osc2MixKnob,OSC2MIX)
	handleSParam(noiseMixKnob,NOISEMIX)
	//magic crystal
	{};



//else if(c == cutoffKnob)
	//{sp(CUTOFF);}
	//else if(c == resonanceKnob)
	//{sp(RESONANCE);}
	//else if(c == portamentoKnob)
	//{sp(PORTAMENTO);}
	//else if(c == volumeKnob)
	//{sp(VOLUME);}
	//else if(c == osc1PitchKnob)
	//{sp(OSC1P);}
	//else if (c == osc2PitchKnob)
	//{sp(OSC2P);}
}
//==============================================================================
void ObxdAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster* source)
{
	ObxdAudioProcessor* filter = getFilter();
	float pr[PARAM_COUNT];
	filter->getCallbackLock().enter();
	for(int i = 0 ; i < PARAM_COUNT;++i)
		pr[i] = filter->parameters.values[i];
	filter->getCallbackLock().exit();
#define rn(T,P) (T->setValue(pr[P],dontSendNotification));
	rn(cutoffKnob,CUTOFF)
	rn(resonanceKnob,RESONANCE)
	rn(volumeKnob,VOLUME)
	rn(osc1PitchKnob,OSC1P)
	rn(osc2PitchKnob,OSC2P)
	rn(osc2DetuneKnob,OSC2_DET)
	rn(portamentoKnob,PORTAMENTO)
	rn(filterEnvelopeAmtKnob,ENVELOPE_AMT)
	rn(pulseWidthKnob,PW)
	rn(xmodKnob,XMOD)
	rn(multimodeKnob,MULTIMODE)

	rn(attackKnob,LATK)
	rn(decayKnob,LDEC)
	rn(sustainKnob,LSUS)
	rn(releaseKnob,LREL)

	rn(fattackKnob,FATK)
	rn(fdecayKnob,FDEC)
	rn(fsustainKnob,FSUS)
	rn(freleaseKnob,FREL)

	rn(osc1MixKnob,OSC1MIX)
	rn(osc2MixKnob,OSC2MIX)
	rn(noiseMixKnob,NOISEMIX)
	//buttons
	rn(hardSyncButton,OSC2HS)
		rn(osc1WfButton,OSC1W)
		rn(osc2WfButton,OSC2W)
		rn(filterKeyFollowButton,FLT_KF)
		rn(pitchQuantButton,OSCQuantize)


}
void ObxdAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll (Colours::white);
	// g.setColour (Colours::black);
	//g.setFont (15.0f);
	//g.drawFittedText ("Hello World!",
	//                0, 0, getWidth(), getHeight(),
	//                Justification::centred, 1);
}