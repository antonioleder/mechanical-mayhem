//------------------------------------------------------------------------------
//
// File Name:	AbilityHolder.h
// Author(s):	David Cohen (david.cohen)
// Project:		Mechanical Mayhem
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class

#include "Ability.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{

	class AbilityHolder : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		AbilityHolder();

		// Copy constructor
		AbilityHolder(const AbilityHolder& other);

		// Destructor
		~AbilityHolder();

		// Assignment operator
		AbilityHolder& operator=(const AbilityHolder& rhs);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Initialize this component (happens at object creation).
		void Initialize() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		// Sets the current ability.
		// Params:
		//   abilityType = The current ability.
		void SetAbility(Abilities::Abilities abilityType);

	private:
		//------------------------------------------------------------------------------
		// Private Structures:
		//------------------------------------------------------------------------------

		

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		Abilities::Abilities abilityType;
		Abilities::Ability* ability;
		float timer;
		float duration;
	};
}

//------------------------------------------------------------------------------
