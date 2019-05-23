//------------------------------------------------------------------------------
//
// File Name:	Event.cpp
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

#include "Event.h"

// Systems
#include <BetaObject.h>
#include "EventHandler.h"

//------------------------------------------------------------------------------

// Constructor
// Params:
//  type = Type of the event.
//  name = Name of the event; allows for sub-types.
//  delay = How long to wait before sending this event.
//  sender = GUID of the sending object.
//  receiver = GUID of the receiving object (if none, all objects).
Event::Event(EventType type, const std::string& name, float delay, GUID sender, GUID receiver) :
	type(type), name(name), delay(delay), sender(sender), receiver(receiver)
{
}

// Virtual destructor
// Events should be dynamically allocated/destroyed if inheritance is used.
Event::~Event()
{
}

// Returns a pointer to the sender beta object.
BetaObject* Event::GetSender() const
{
	return BetaObject::GetObjectByID(sender);
}

// Returns a pointer to the receiver beta object.
BetaObject* Event::GetReceiver() const
{
	return BetaObject::GetObjectByID(receiver);
}
