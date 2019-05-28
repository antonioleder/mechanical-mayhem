//------------------------------------------------------------------------------
//
// File Name:	AbilityPickup.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		Mechanical Mayhem
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "AbilityPickup.h"

// Systems
#include <Parser.h>

//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	AbilityPickup::AbilityPickup() : Pickup("AbilityPickup"), abilityType(Abilities::ABILITY_NONE)
	{
	}

	// Clones the component
	Component* AbilityPickup::Clone() const
	{
		return new AbilityPickup(*this);
	}

	// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
	void AbilityPickup::Serialize(Parser& parser) const
	{
		Pickup::Serialize(parser);
			
		unsigned abilityType_ = static_cast<unsigned>(abilityType);
		parser.WriteVariable("abilityType", abilityType_);
	}

	// Read object data from a file
	// Params:
	//   parser = The parser that is reading this object's data from a file.
	void AbilityPickup::Deserialize(Parser& parser)
	{
		Pickup::Deserialize(parser);

		unsigned abilityType_;
		parser.ReadVariable("abilityType", abilityType_);
		abilityType = static_cast<Abilities::Abilities>(abilityType_);
	}

	// Returns the type of this ability pickup.
	Abilities::Abilities AbilityPickup::GetAbilityType() const
	{
		return abilityType;
	}
}

//------------------------------------------------------------------------------