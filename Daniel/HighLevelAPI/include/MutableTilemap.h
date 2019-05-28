//------------------------------------------------------------------------------
//
// File Name:	MutableTilemap.h
// Author(s):	David Cohen (david.cohen)
// Project:		Mechanical Mayhem
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Tilemap;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Allows for the tilemap to be changed with events.
class MutableTilemap : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new mutable tilemap behavior.
	MutableTilemap();

	// Clone the behavior, returning a dynamically allocated copy.
	Component* Clone() const override;

	// Receive an event and handle it (if applicable).
	// Params:
	//   event = The event that has been received.
	void HandleEvent(const Event& event) override;

	// Sets the tilemap data.
	// Params:
	//   map = A pointer to the tilemap resource.
	void SetTilemap(Tilemap* map);

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The tilemap
	Tilemap* map;
};

//------------------------------------------------------------------------------
