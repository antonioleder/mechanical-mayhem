//------------------------------------------------------------------------------
//
// File Name:	Event.h
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
// Forward References:
//------------------------------------------------------------------------------

class BetaObject;
class EventHandler;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

enum EventType
{
	ET_Generic = 0 ,
	ET_Collision,
	ET_MapCollision,
	ET_Damage,
	ET_Death,
	ET_EnemySpotted,

	ET_MAX
};

struct Event
{
	// Constructor
	// Params:
	//  type = Type of the event.
	//  name = Name of the event; allows for sub-types.
	//  delay = How long to wait before sending this event.
	//  sender = GUID of the sending object.
	//  receiver = GUID of the receiving object (if none, all objects).
	Event(EventType type, const std::string& name, float delay = 0.0f, GUID sender = GUID(), GUID receiver = GUID());

	// Virtual destructor
	// Events should be dynamically allocated/destroyed if inheritance is used.
	virtual ~Event();

	// Returns a pointer to the sender beta object.
	BetaObject* GetSender() const;

	// Returns a pointer to the receiver beta object.
	BetaObject* GetReceiver() const;

	// Event data, all publicly
	// accessible for convenience.
	EventType type;
	std::string name;
	float delay;
	GUID sender;
	GUID receiver;
};

//------------------------------------------------------------------------------
