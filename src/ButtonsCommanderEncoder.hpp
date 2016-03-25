//-------------------------------------------------------------------
#ifndef __buttonsCommanderEncoder_H__
#define __buttonsCommanderEncoder_H__
//-------------------------------------------------------------------

#include "Commanders.h"

class ButtonsCommanderPush;

//-------------------------------------------------------------------

class ButtonsCommanderEncoder : public ButtonsCommanderButton
{
 private:
	int currentValue;
	GPIO_pin_t pin1;
	GPIO_pin_t pin2;
	int moveAccuracy;
	int mini, maxi;
	int lastEncoded;

public:
	ButtonsCommanderPush *pPush;
	
 public:
	ButtonsCommanderEncoder(unsigned long inId, int inStartingCurrentValue, int inMinimum, int inMaximum, bool inAssociatedPushButton = false);

	inline bool IsAnalog() const { return false; }
	inline int GetPosition() const { return this->currentValue; }

	void Setup(int inPin1, int inPin2, int inMoveAccuracy = 1);
	unsigned long Loop();
};

#define ENCODER_BUTTON(name, pin1, pin2, ID, start, min, max) \
	ButtonsCommanderEncoder *name = new ButtonsCommanderEncoder(ID, start, min, max); \
	name->Setup(pin1, pin2); \
	macro_buttons.Add(name);

#define ENCODER_BUTTON_WITHPUSH(name, pin1, pin2, ID, start, min, max, pushPin, pushID) \
	ButtonsCommanderEncoder *name = new ButtonsCommanderEncoder(ID, start, min, max, true); \
	name->Setup(pin1, pin2); \
	name->pPush->Setup(pushPin); \
	name->pPush->AddId(pushID); \
	macro_buttons.Add(name);

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
