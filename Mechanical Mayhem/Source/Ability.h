//------------------------------------------------------------------------------
//
// File Name:	Ability.h
// Author(s):	Daniel Walther (daniel.walther)
// Project:		Mechanical Mayhem
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h"

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Physics;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	class Ability : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Default Constructor
		Ability(const std::string& name = "Ability");

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		virtual void Update(float dt) override;

		// Sets whether the ability is currently active
		void setHasAbility(bool active_);

		// Returns whether the player currently has the ability
		bool getHasAbility() const;

	protected:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Determines whether the player currently has the ability
		bool hasAbility;

		// Timer
		float timer;
	};
}

//------------------------------------------------------------------------------