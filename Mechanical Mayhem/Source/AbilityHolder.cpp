//------------------------------------------------------------------------------
//
// File Name:	AbilityHolder.cpp
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

#include "AbilityHolder.h"

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
	AbilityHolder::AbilityHolder() : Component("AbilityHolder"), ability(nullptr)
	{
		
	}

	// Destructor
	AbilityHolder::~AbilityHolder()
	{

	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* AbilityHolder::Clone() const
	{
		return new AbilityHolder(*this);
	}

	// Initialize this component (happens at object creation).
	void AbilityHolder::Initialize()
	{

	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void AbilityHolder::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
	}
}

//------------------------------------------------------------------------------
