//------------------------------------------------------------------------------
//
// File Name:	Ability.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		Mechanical Mayhem
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Ability.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Abilities
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   name = The name of this ability.
	Ability::Ability(const std::string& name) : BetaObject(name), owner(nullptr)
	{
	}

	// Sets the owner of this ability.
	void Ability::SetOwner(GameObject* owner_)
	{
		owner = owner_;
	}

	// Gets the owner of this ability.
	GameObject* Ability::GetOwner() const
	{
		return owner;
	}

	// Creates a new Ability based on the enum.
	Ability* Ability::FromEnum(Abilities ability)
	{
		switch (ability)
		{
		case ABILITY_JETPACK:
			return nullptr;
		case ABILITY_FLAMETHROWER:
			return nullptr;
		case ABILITY_PROXIMITYMINE:
			return nullptr;
		}

		return nullptr;
	}
}

//------------------------------------------------------------------------------
