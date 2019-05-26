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
	ET_Generic = 0,
	ET_Collision,
	ET_MapCollision,
	ET_MapChange,
	ET_Damage,
	ET_Heal,
	ET_Death,

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

struct MapChangeEvent : public Event
{
	// Constructor
	// Params:
	//  column = The column of the cell.
	//  row = The row of the cell.
	//  value = The new value of the cell.
	//  delay = How long to wait before sending this event.
	//  sender = GUID of the sending object.
	//  receiver = GUID of the receiving object (if none, all objects).
	MapChangeEvent(unsigned column, unsigned row, int value, float delay = 0.0f, GUID sender = GUID(), GUID receiver = GUID());

	unsigned column;
	unsigned row;
	int value;
};

struct DamageEvent : public Event
{
	// Constructor
	// Params:
	//  damage = How much damage to deal.
	//  delay = How long to wait before sending this event.
	//  sender = GUID of the sending object.
	//  receiver = GUID of the receiving object (if none, all objects).
	DamageEvent(int damage, float delay = 0.0f, GUID sender = GUID(), GUID receiver = GUID());

	int damage;
};

struct HealEvent : public Event
{
	// Constructor
	// Params:
	//  health = How much health to heal.
	//  delay = How long to wait before sending this event.
	//  sender = GUID of the sending object.
	//  receiver = GUID of the receiving object (if none, all objects).
	HealEvent(int health, float delay = 0.0f, GUID sender = GUID(), GUID receiver = GUID());

	int health;
};

struct DeathEvent : public Event
{
	// Constructor
	// Params:
	//  killer = The GUID of the object who killed the sender.
	//  delay = How long to wait before sending this event.
	//  sender = GUID of the sending object.
	//  receiver = GUID of the receiving object (if none, all objects).
	DeathEvent(GUID killer, float delay = 0.0f, GUID sender = GUID(), GUID receiver = GUID());

	// Returns a pointer to the killer beta object.
	BetaObject* GetKiller() const;

	GUID killer;
};

//------------------------------------------------------------------------------
