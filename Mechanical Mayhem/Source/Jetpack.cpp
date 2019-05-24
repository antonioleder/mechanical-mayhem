//------------------------------------------------------------------------------
//
// File Name:	Jetpack.cpp
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
#include "Jetpack.h"

// Components
#include "PlayerMovement.h"
#include <Physics.h>

// Systems
#include <Engine.h>
#include <Input.h>
#include <Parser.h>
#include <SoundManager.h>
#include <Space.h>

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Default Constructor
	Jetpack::Jetpack()
		: Ability("Jetpack"),
		playerMovement(nullptr), physics(nullptr),
		jetpackForce(1), currentFuel(0), maxFuel(100), fuelRefillRate(0.5f), fuelConsumptionRate(1.0f)
	{
	}

	// Return a new copy of the component.
	Component* Jetpack::Clone() const
	{
		return new Jetpack(*this);
	}

	// Initialize data for this object.
	void Jetpack::Initialize()
	{
		// Get components
		playerMovement = GetOwner()->GetComponent<PlayerMovement>();
		physics = GetOwner()->GetComponent<Physics>();

		// Fill fuel tank
		currentFuel = maxFuel;
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void Jetpack::Update(float dt)
	{
		// Check if user is even using the jetpack
		if (Input::GetInstance().CheckHeld(playerMovement->GetUpKeybind()))
		{
			active = true;
		}
		else
		{
			active = false;
		}

		// Manage fuel amounts
		FuelManagement(dt);

		// Can't use jetpack if out of fuel
		if (currentFuel <= 0.0f)
		{
			active = false;
		}

		if (active)
		{
			// Add force if active
			physics->AddForce(Vector2D(0.0f, jetpackForce));
		}
	}

	// Sets whether the jetpack is active
	void Jetpack::setActive(bool active_)
	{
		active = active_;
	}

	// Gets whether the jetpack is active
	bool Jetpack::getActive() const
	{
		return active;
	}

	// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
	void Jetpack::Serialize(Parser& parser) const
	{
		parser.WriteVariable("jetpackForce", jetpackForce);
		parser.WriteVariable("currentFuel", currentFuel);
		parser.WriteVariable("maxFuel", maxFuel);
		parser.WriteVariable("fuelRefillRate", fuelRefillRate);
		parser.WriteVariable("fuelConsumptionRate", fuelConsumptionRate);
	}

	// Read object data from a file
	// Params:
	//   parser = The parser that is reading this object's data from a file.
	void Jetpack::Deserialize(Parser& parser)
	{
		parser.ReadVariable("jetpackForce", jetpackForce);
		parser.ReadVariable("currentFuel", currentFuel);
		parser.ReadVariable("maxFuel", maxFuel);
		parser.ReadVariable("fuelRefillRate", fuelRefillRate);
		parser.ReadVariable("fuelConsumptionRate", fuelConsumptionRate);
	}

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Handles fuel consumption/refilling
	void Jetpack::FuelManagement(float dt)
	{
		// Check if player is grounded
		if (playerMovement->getOnGround()/*physics->GetVelocity().y == 0.0f*/)
		{
			// Check if fuel tank is not full
			if (currentFuel < maxFuel)
			{
				// Fill fuel tank at refill rate
				currentFuel += dt * fuelRefillRate;

				// Cap fuel amount at max
				if (currentFuel > maxFuel)
				{
					currentFuel = maxFuel;
				}
			}
		}
		// Not on ground and jetpack is active
		else if (active)
		{
			// Check if fuel tank is not empty
			if (currentFuel > 0.0f)
			{
				// Empty fuel at consumption rate
				currentFuel -= dt * fuelConsumptionRate;

				// Don't go below zero fuel
				if (currentFuel < 0.0f)
				{
					currentFuel = 0.0f;
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
