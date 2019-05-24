//------------------------------------------------------------------------------
//
// File Name:	ProximityMine.h
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

#include "Ability.h" // Base class

#include <queue>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class GameObject;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Abilities
{
	class ProximityMine : public Ability
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		ProximityMine();

		// Initialize this ability.
		void Initialize() override;

		// Update function for this ability.
		// Params:
		//   dt = The change in time since the last update.
		void Update(float dt) override;

		// Callback for when the player attempts to use this ability.
		void OnUse() override;

	protected:
		//------------------------------------------------------------------------------
		// Protected Variables:
		//------------------------------------------------------------------------------

		int maxProximityMines;
		std::queue<GameObject*> proximityMines;
	};
}

//------------------------------------------------------------------------------
