//------------------------------------------------------------------------------
//
// File Name:	ShiftPickup.cpp
// Author(s):	Daniel Walther (daniel.walther)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ShiftPickup.h"

// Systems
#include <Parser.h>							// Parser

//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	ShiftPickup::ShiftPickup() : Pickup("ShiftPickup"), charges(0)
	{
	}

	// Clones the component
	Component* ShiftPickup::Clone() const
	{
		return new ShiftPickup(*this);
	}

	// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
	void ShiftPickup::Serialize(Parser& parser) const
	{
		Pickup::Serialize(parser);

		parser.WriteVariable("charges", charges);
	}

	// Read object data from a file
	// Params:
	//   parser = The parser that is reading this object's data from a file.
	void ShiftPickup::Deserialize(Parser& parser)
	{
		Pickup::Deserialize(parser);

		parser.ReadVariable("charges", charges);
	}

	// Returns the number of charges this collectible has.
	int ShiftPickup::GetCharges() const
	{
		return charges;
	}
}

//------------------------------------------------------------------------------