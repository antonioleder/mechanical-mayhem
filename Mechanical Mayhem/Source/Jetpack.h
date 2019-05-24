//------------------------------------------------------------------------------
//
// File Name:	Jetpack.h
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

#include "Ability.h"
#include "PlayerMovement.h"

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Physics;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	class Jetpack : public Ability
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Default Constructor
		Jetpack();

		// Return a new copy of the component.
		Component* Clone() const;

		// Initialize data for this object.
		void Initialize();

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		virtual void Update(float dt) override;

		// Sets whether the jetpack is active
		void setActive(bool active_);

		// Gets whether the jetpack is active
		bool getActive() const;

		// Write object data to file
		// Params:
		//   parser = The parser that is writing this object to a file.
		void Serialize(Parser& parser) const override;

		// Read object data from a file
		// Params:
		//   parser = The parser that is reading this object's data from a file.
		void Deserialize(Parser& parser) override;

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// Handles fuel consumption/refilling
		void FuelManagement(float dt);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Other components
		PlayerMovement* playerMovement;
		Physics* physics;

		// Jetpack is being used
		bool active;

		// Speed
		float jetpackForce;			// Force jetpack exerts when active
		
		// Fuel
		float currentFuel;			// Current amount of fuel (f)
		float maxFuel;				// Maximum fuel capacity (f)
		float fuelRefillRate;		// Rate at which the fuel refills on the ground (f/s)
		float fuelConsumptionRate;	// Rate at which the fuel is consumed (f/s)
	};
}

//------------------------------------------------------------------------------