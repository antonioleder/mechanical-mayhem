//------------------------------------------------------------------------------
//
// File Name:	EventHandler.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References
//------------------------------------------------------------------------------

struct Event;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   modify the public interface (function prototypes) declared in the header.
class EventHandler
{
public:
	// Receive an event and handle it (if applicable).
	// Params:
	//   event = The event that has been received.
	virtual void HandleEvent(const Event& event);

protected:
	// These functions are protected to ensure that EventHandler
	// instances can only be created by subclasses.

	// Constructor(s)
	EventHandler();

	// Destructor
	virtual ~EventHandler();
};

//------------------------------------------------------------------------------
