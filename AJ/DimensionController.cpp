//------------------------------------------------------------------------------
//
// File Name:	DimensionController.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		Yesterday's Mayonnaise
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "DimensionController.h"

// Systems
#include <GameObject.h>
#include <Input.h>
#include <Space.h>
#include <Interpolation.h>

// Components
#include <Transform.h>
#include <Physics.h>
#include <Sprite.h>
#include <ColliderTilemap.h>
#include "Hazard.h"

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
	DimensionController::DimensionController() : Component("DimensionController"), dimensions(std::vector<Dimension>()),
		cooldown(5.0f), currentCooldown(10.0f), gameTimer(0.0), cdCount(0), cdIndex(10)
	{
		// Set the different cooldown times
		cdCounts[0]  = 0.5f;
		cdCounts[1]  = 0.75f;
		cdCounts[2]  = 1.0f;
		cdCounts[3]  = 1.5f;
		cdCounts[4]  = 2.0f;
		cdCounts[5]  = 2.5f;
		cdCounts[6]  = 3.0f;
		cdCounts[7]  = 3.5f;
		cdCounts[8]  = 4.0f;
		cdCounts[9]  = 4.5f;
		cdCounts[10] = 5.0f;
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* DimensionController::Clone() const
	{
		return new DimensionController(*this);
	}

	// Initialize this component (happens at object creation).
	void DimensionController::Initialize()
	{
	}

	// Fixed update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void DimensionController::Update(float dt)
	{
		gameTimer += dt;

		currentCooldown = max(0.0f, currentCooldown - dt);
	}

	// Calculates how long until the dimension can be switched again.
	// Returns:
	//   How much longer until the dimension can be switched.
	float DimensionController::GetSwitchCooldown() const
	{
		return currentCooldown;
	}

	// Sets the active dimension and deactivates all others.
	// Params:
	//   dimension = The dimension to make active.
	void DimensionController::SetActiveDimension(unsigned dimension)
	{
		if (dimension >= dimensions.size())
			return;

		activeDimension = dimension;

		// Make all non-active dimensions transparent and non-collidable.
		for (unsigned i = 0; i < dimensions.size(); i++)
		{
			if (i == activeDimension)
				continue;

			static_cast<ColliderTilemap*>(dimensions[i].tilemap->GetComponent("Collider"))->SetActive(false);
			static_cast<Sprite*>(dimensions[i].tilemap->GetComponent("Sprite"))->SetAlpha(0.3f);
			for (GameObject* spike : dimensions[i].spikes)
			{
				UNREFERENCED_PARAMETER(spike);
				static_cast<Hazard*>(spike->GetComponent("Hazard"))->SetCollidable(false);
				static_cast<Sprite*>(spike->GetComponent("Sprite"))->SetAlpha(0.3f);
			}
		}

		// Make the active dimension opaque and collidable.
		static_cast<ColliderTilemap*>(dimensions[activeDimension].tilemap->GetComponent("Collider"))->SetActive(true);
		static_cast<Sprite*>(dimensions[activeDimension].tilemap->GetComponent("Sprite"))->SetAlpha(1.0f);
		for (GameObject* spike : dimensions[activeDimension].spikes)
		{
			static_cast<Hazard*>(spike->GetComponent("Hazard"))->SetCollidable(true);
			static_cast<Sprite*>(spike->GetComponent("Sprite"))->SetAlpha(1.0f);
		}

		++cdCount;

		if (cdCount >= 4 && cdIndex != 0)
			SetCoolDownTime();
	}

	// Returns the active dimension.
	unsigned DimensionController::GetActiveDimension() const
	{
		return activeDimension;
	}

	// Returns the number of dimensions.
	unsigned DimensionController::GetDimensionCount() const
	{
		return static_cast<unsigned>(dimensions.size());
	}

	// Adds a new dimension.
	// Params:
	//   tilemap = The game object with the tilemap for the dimension.
	// Returns:
	//   The ID of the new dimension.
	unsigned DimensionController::AddDimension(GameObject* tilemap)
	{
		Dimension dimension(tilemap);
		dimensions.push_back(tilemap);
		return static_cast<unsigned>(dimensions.size() - 1);
	}

	// Adds a spike to an existing dimension.
	// Params:
	//   dimension = The ID of the dimension to add the spike to.
	//   spike = The game object for the spike.
	void DimensionController::AddSpikeToDimension(unsigned dimension, GameObject* spike)
	{
		if (dimension >= dimensions.size())
			return;

		dimensions[dimension].spikes.push_back(spike);
	}

	//------------------------------------------------------------------------------
	// Private Structures:
	//------------------------------------------------------------------------------

	// Sets the cooldown time
	void DimensionController::SetCoolDownTime()
	{
		currentCooldown = cooldown;

		// Check if cooldowm is greater than or equal to 3.5 and has iterated 5 times
		if (cdCounts[static_cast<int>(cooldown * 2)] >= 3.5f && cdCount >= 5)
		{
			// Reset counter
			cdCount = 0;
			// Increment Index
			--cdIndex;
		}
		// Check if cooldowm is greater than or equal to 1.5 and has iterated 4 times
		else if (cdCounts[static_cast<int>(cooldown * 2)] >= 1.5f && cdCount >= 4)
		{
			// Reset counter
			cdCount = 0;
			// Increment Index
			--cdIndex;
		}
		// Check if cooldowm is greater than or equal to 1.0 and has iterated 10 times
		else if (cdCounts[static_cast<int>(cooldown * 2)] >= 1.0f && cdCount >= 10)
		{
			// Reset counter
			cdCount = 0;
			// Increment Index
			--cdIndex;
		}
		// Check if cooldowm is greater than or equal to 0.75 and has iterated 7 times
		else if (cdCounts[static_cast<int>(cooldown * 2)] >= 0.75f && cdCount >= 7)
		{
			// Reset counter
			cdCount = 0;
			// Increment Index
			--cdIndex;
		}
		// Otherwise use index 0
		else
			cdIndex = 0;

		cooldown = cdCounts[cdIndex];
	}

	// Constructor
	// Params:
	//   tilemap = The game oject with the tilemap for the dimension.
	DimensionController::Dimension::Dimension(GameObject* tilemap) : tilemap(tilemap), spikes(std::vector<GameObject*>())
	{
	}
}

//------------------------------------------------------------------------------
