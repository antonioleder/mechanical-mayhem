//------------------------------------------------------------------------------
//
// File Name:	Health.cpp
// Author(s):	A.J. Bussman
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
#include "Health.h"

// Systems
#include <Space.h>
#include <Parser.h> // Read/WriteVariable
//#include <Event.h>

// Components
#include <GameObject.h>
#include <Sprite.h>
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
	// Params:
	//   maxHealth = The max health for the object.
	//   damage = The amount of health that is lost per hit.
	//	 flashTime = Time to spend flashing.
	//	 fc1/fc2 = Colors to switch between when flashing
	Health::Health(int maxHealth, int damage) : Component("Health"),
		health(maxHealth), maxHealth(maxHealth), damage(damage)
	{
	}

	// Return a new copy of the component.
	Component* Health::Clone() const
	{
		return new Health(*this);
	}

	// Initialize data for this object.
	void Health::Initialize()
	{
	}

	// Update function for this component.
	// Params:
	//   dt = The change in time since the last step.
	void Health::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		//if (health <= 0)
			//GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(ET_Death, "Death", 0.0f, GetOwner()->GetID(), GetOwner()->GetID()));
	}

	// Returns the damage it deals
	int Health::GetDamage()
	{
		return damage;
	}

	//// Write object data to file
	//// Params:
	////   parser = The parser that is writing this object to a file.
	//void Health::Serialize(Parser& parser) const
	//{
	//	parser.WriteVariable("maxHealth", maxHealth);
	//	parser.WriteVariable("damage", damage);
	//}

	//// Read object data from a file
	//// Params:
	////   parser = The parser that is reading this object's data from a file.
	//void Health::Deserialize(Parser& parser)
	//{
	//	parser.ReadVariable("maxHealth", maxHealth);
	//	parser.ReadVariable("damage", damage);
	//}

	//// Receive an event and handle it (if applicable).
	//// Params:
	////   event = The event that has been received.
	//void Health::HandleEvent(const Event& event)
	//{
	//	// Handle Damage event
	//	if (event.name == "Damage")
	//	{
	//		// Get the damage the other object deals
	//		int dam = static_cast<GameObject*>(BetaObject::GetObjectByID(event.sender))->GetComponent<Health>()->GetDamage();
	//		// Decrement health by dam
	//		health -= dam;
	//	}
	//	// Handle Heal event
	//	if (event.name == "Heal")
	//	{
	//		health += damage;
	//	}
	//}
}