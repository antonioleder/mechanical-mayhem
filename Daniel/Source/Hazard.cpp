//------------------------------------------------------------------------------
//
// File Name:	Hazard.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Hazard.h"

// Systems
#include <Engine.h>
#include <GameObject.h>
#include <Parser.h>
#include <Space.h>
#include <GameObjectManager.h>

// Components
#include <Collider.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	Hazard::Hazard() : Component("Hazard"), 
		alwaysCollidable(false), collidable(true), damage(100), destroyOnCollide(false), destroyOnCollideDelay(0.0f)
	{
	}

	// Return a new copy of the component.
	Component* Hazard::Clone() const
	{
		return new Hazard(*this);
	}

	// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
	void Hazard::Serialize(Parser& parser) const
	{
		parser.WriteVariable("alwaysCollidable", alwaysCollidable);
		parser.WriteVariable("collidable", collidable);
		parser.WriteVariable("damage", damage);
		parser.WriteVariable("destroyOnCollide", destroyOnCollide);
		parser.WriteVariable("destroyOnCollideDelay", destroyOnCollideDelay);
	}

	// Read object data from a file
	// Params:
	//   parser = The parser that is reading this object's data from a file.
	void Hazard::Deserialize(Parser& parser)
	{
		parser.ReadVariable("alwaysCollidable", alwaysCollidable);
		parser.ReadVariable("collidable", collidable);
		parser.ReadVariable("damage", damage);
		parser.ReadVariable("destroyOnCollide", destroyOnCollide);
		parser.ReadVariable("destroyOnCollideDelay", destroyOnCollideDelay);
	}

	// Receive an event and handle it (if applicable).
	// Params:
	//   event = The event that has been received.
	void Hazard::HandleEvent(const Event& event)
	{
		GameObject& other = *static_cast<GameObject*>(event.GetSender());

		if (&other == nullptr)
			return;

		if (event.name == "CollisionStarted")
		{
			if (IsCollidable())
			{
				GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new DamageEvent(damage, 0.0f, GetOwner()->GetID(), event.sender));

				if (destroyOnCollide)
				{
					GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(ET_Generic, "Destroy", destroyOnCollideDelay, GetOwner()->GetID(), GetOwner()->GetID()));
				}
			}
		}
	}

	// Returns if the hazard is collidable
	bool Hazard::IsCollidable()
	{
		return alwaysCollidable || collidable;
	}

	// Changes whether the hazard is collidable or not.
	// Params:
	//   collidable = Whether the hazard is collidable.
	void Hazard::SetCollidable(bool collidable_)
	{
		if (alwaysCollidable)
			return;

		collidable = collidable_;
	}
}