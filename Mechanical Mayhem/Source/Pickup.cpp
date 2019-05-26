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

// Systems
#include <GameObject.h>						// Game Object
#include <Parser.h>							// Parser
#include <Space.h>							// Space
#include <GameObjectManager.h>				// Game Object Manager

// Components
#include <Transform.h>						// Transform
#include <Sprite.h>							// Sprite
#include <Collider.h>						// Collider

//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   name = The name of this component.
	//   cooldown = The cooldown for respawning after collected.
	Pickup::Pickup(const std::string& name, float cooldown)
		: Component(name), sprite(nullptr), cooldown(cooldown), timer(0.0f), active(true)
	{
	}

	// Initialize
	void Pickup::Initialize()
	{
		sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
	}

	// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
	void Pickup::Serialize(Parser& parser) const
	{
		parser.WriteVariable("cooldown", cooldown);
	}

	// Read object data from a file
	// Params:
	//   parser = The parser that is reading this object's data from a file.
	void Pickup::Deserialize(Parser& parser)
	{
		parser.ReadVariable("cooldown", cooldown);
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
				GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(ET_Generic, "Deactivate", 0.01f, GetOwner()->GetID(), GetOwner()->GetID()));
			}
		}
		else if (event.name == "Deactivate" && event.sender == GetOwner()->GetID())
		{
			SetActive(false);
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