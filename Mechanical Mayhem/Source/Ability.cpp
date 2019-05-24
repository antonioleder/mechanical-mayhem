//------------------------------------------------------------------------------
//
// File Name:	Ability.cpp
// Author(s):	Daniel Walther (daniel.walther)
// Project:		Mechanical Mayhem
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Ability.h"

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Default Constructor
	Ability::Ability(const std::string& name)
		: Component(name),
		hasAbility(false), timer(0)
	{
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void Ability::Update(float dt)
	{
		// Increment timer
		timer += dt;
	}

	// Sets whether the player currently has this ability
	void Ability::setHasAbility(bool hasAbility_)
	{
		hasAbility = hasAbility_;
	}

	// Returns whether the player currently has this ability
	bool Ability::getHasAbility() const
	{
		return hasAbility;
	}
}

//------------------------------------------------------------------------------
