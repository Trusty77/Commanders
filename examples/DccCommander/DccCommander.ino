/*************************************************************
project: <Commanders>
author: <Thierry PARIS>
description: <Dcc commander demo>
*************************************************************/

#include "Commanders.h"

void ReceiveEvent(unsigned long inId, COMMANDERS_EVENT_TYPE inEvent, int inData)
{
	DccCommander.printEvent(inId, inEvent, inData);
}

//////////////////////////////////
//
// Setup
//
void setup()
{
	Commanders::begin(ReceiveEvent, LED_BUILTIN);

	DccCommander.begin(0x0, 0x0, digitalPinToInterrupt(3));	// Manufacturer ID, Product ID, interrupt
}

void loop()
{
	Commanders::loop();
}
