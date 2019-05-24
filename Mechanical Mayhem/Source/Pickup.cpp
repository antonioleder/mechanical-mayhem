//------------------------------------------------------------------------------
//
// File Name:	Pickup.cpp
// Author(s):	Daniel Walther (daniel.walther)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Pickup.h"

#include <Transform.h>						// Transform
#include <Sprite.h>							// Sprite
#include <Collider.h>						// Collider
#include <GameObject.h>						// Game Object

//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	Pickup::Pickup(float cooldown)
		: Component("Pickup"), sprite(nullptr), cooldown(cooldown), timer(0.0f), active(true)
	{
	}

	// Initialize
	void Pickup::Initialize()
	{
		sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
	}

	// Update
	void Pickup::Update(float dt)
	{
		timer += dt;

		// set active after cooldown
		if (timer >= cooldown)
		{
			timer = 0;
			active = true;
		}

		// Make transparent if inactive
		if (active)
			sprite->SetAlpha(1.0f);
		else
			sprite->SetAlpha(0.3f);
	}

	// Receive an event and handle it (if applicable).
	// Params:
	//   event = The event that has been received.
	void Pickup::HandleEvent(const Event& event)
	{
		if (event.name == "CollisionStarted")
		{
			if (event.GetSender()->GetName() == "Player")
			{
				SetActive(false);
			}
		}
	}

	// Returns whether the collectible is active
	bool Pickup::IsActive() const
	{
		return active;
	}

	// Set active
	void Pickup::SetActive(bool active_)
	{
		active = active_;
		if (!active)
			timer = 0;
	}
}

//------------------------------------------------------------------------------