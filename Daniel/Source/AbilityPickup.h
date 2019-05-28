//------------------------------------------------------------------------------
//
// File Name:	AbilityPickup.h
// Author(s):	David Cohen (david.cohen)
// Project:		Mechanical Mayhem
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Pickup.h"

// Abilities
#include "Ability.h"

//------------------------------------------------------------------------------

namespace Behaviors
{
	class AbilityPickup : public Pickup
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		AbilityPickup();

		// Clones the component
		Component* Clone() const override;

		// Write object data to file
		// Params:
		//   parser = The parser that is writing this object to a file.
		void Serialize(Parser& parser) const override;

		// Read object data from a file
		// Params:
		//   parser = The parser that is reading this object's data from a file.
		void Deserialize(Parser& parser) override;

		// Returns the type of this ability pickup.
		Abilities::Abilities GetAbilityType() const;

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		Abilities::Abilities abilityType;
	};
}

//------------------------------------------------------------------------------