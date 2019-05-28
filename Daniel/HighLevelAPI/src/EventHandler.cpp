//------------------------------------------------------------------------------
//
// File Name:	EventHandler.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "EventHandler.h"

//------------------------------------------------------------------------------

// Receive an event and handle it (if applicable).
// Params:
//   event = The event that has been received.
void EventHandler::HandleEvent(const Event& event)
{
	UNREFERENCED_PARAMETER(event);
}

// These functions are protected to ensure that EventHandler
// instances can only be created by subclasses.

// Constructor(s)
EventHandler::EventHandler()
{
}

// Destructor
EventHandler::~EventHandler()
{
}
