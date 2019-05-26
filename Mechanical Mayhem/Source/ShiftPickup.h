//------------------------------------------------------------------------------
//
// File Name:	ShiftPickup.h
// Author(s):	Daniel Walther (daniel.walther)
// Project:		Yesterday's Mayonnaise
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Pickup.h"

//------------------------------------------------------------------------------

namespace Behaviors
{
	class ShiftPickup : public Pickup
	{
		
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	
	public:
		// Constructor
		ShiftPickup();
		
		// Clones the component
		Component* Clone() const override;

		// Write object data to file
		// Params:
		//   parser = The parser that is writing this object to a file.
		void Serialize(Parser& parser) const override;

		// Read object data from a file
		// Params:
		//   parser = The parser that is reading this object's data from a file.
		void Deserialize(Parser& parser) override;

		// Returns the number of charges this collectible has.
		int GetCharges() const;

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		int charges;
	};
}

//------------------------------------------------------------------------------