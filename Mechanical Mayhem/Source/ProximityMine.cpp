//------------------------------------------------------------------------------
//
// File Name:	ProximityMine.cpp
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

#include "ProximityMine.h"

// Systems
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>

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
	ProximityMine::ProximityMine() : Ability("Proximity Mine"), maxProximityMines(4)
	{
	}

	// Initialize this ability.
	void ProximityMine::Initialize()
	{

	}

	// Update function for this ability.
	// Params:
	//   dt = The change in time since the last update.
	void ProximityMine::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
	}

	// Callback for when the player attempts to use this ability.
	void ProximityMine::OnUse()
	{
		if (proximityMines.size() >= maxProximityMines)
		{
			proximityMines.front()->Destroy();
			proximityMines.pop();
		}

		GameObjectManager& objectManager = GetOwner()->GetSpace()->GetObjectManager();

		GameObject* mine = new GameObject(*objectManager.GetArchetypeByName("Mine"));
		objectManager.AddObject(*mine);
		proximityMines.push(mine);
	}
}

//------------------------------------------------------------------------------
