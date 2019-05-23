//------------------------------------------------------------------------------
//
// File Name:	Hazard.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Hazard.h"

// Systems
#include "Engine.h"
#include "GameObject.h"

// Components
#include "Collider.h"

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
	// Params:
	//   rotation = rotation of Hazard
	Hazard::Hazard(bool alwaysCollidable, bool collidable, float rotation) : Component("Hazard"), 
		alwaysCollidable(alwaysCollidable), collidable(collidable), rotation(rotation)
	{
	}

	// Return a new copy of the component.
	Component* Hazard::Clone() const
	{
		return new Hazard(*this);
	}

	// Initialize data for this object.
	void Hazard::Initialize()
	{
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void Hazard::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
	}

	// Receive an event and handle it (if applicable).
	// Params:
	//   event = The event that has been received.
	void Hazard::HandleEvent(const Event& event)
	{
		GameObject& other = *static_cast<GameObject*>(event.GetSender());
		if (other.GetName() == "Player")
		{
			if (collidable)
				other.Destroy();
		}
	}

	// Returns if the hazard is collidable
	bool Hazard::IsCollidable()
	{
		return collidable;
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