/*************************************************************
project: <Universal Accessory Decoder>
author: <Thierry PARIS>
description: <Base Commander>
*************************************************************/

#include "Commander.hpp"

#ifndef NO_COMMANDER
CommandersEventHandlerFunction Commander::EventHandler = 0;
Commander *Commander::pFirstCommander = 0;

#ifdef DEBUG_MODE
#define CHECK(val, text)	CheckIndex(val, F(text))
#else
#define CHECK(val, text)
#endif

void Commander::AddCommander(Commander *inCommander)
{
	if (Commander::pFirstCommander == 0)
	{
		Commander::pFirstCommander = inCommander;
		return;
	}

	Commander *pCurr = Commander::pFirstCommander;

	while (pCurr->pNextCommander != 0)
		pCurr = pCurr->pNextCommander;

	pCurr->pNextCommander = inCommander;
}

void Commander::CommanderPriorityLoop()
{
	Commander *pCurr = Commander::pFirstCommander;

	while (pCurr != 0)
	{
		pCurr->PriorityLoop();
		pCurr = pCurr->pNextCommander;
	}
}

void Commander::RaiseEvent(unsigned long inId, COMMANDERS_EVENT_TYPE inEvent, int inData)
{
	if (Commander::EventHandler != 0)
		Commander::EventHandler(inId, inEvent, inData);
}

unsigned long Commander::Loops()
{
	Commander *pCurr = Commander::pFirstCommander;

	while (pCurr != 0)
	{
		unsigned long ret = pCurr->Loop();
		if (ret != UNDEFINED_ID)
			return ret;
		pCurr = pCurr->pNextCommander;
	}

	return UNDEFINED_ID;
}

#ifdef DEBUG_MODE
void Commander::CheckIndex(byte inIndex, const __FlashStringHelper *inFunc)
{
}
#endif

#endif
