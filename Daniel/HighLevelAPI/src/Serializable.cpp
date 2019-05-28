//------------------------------------------------------------------------------
//
// File Name:	Serializable.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Serializable.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Loads object data from a file.
void Serializable::Deserialize(Parser& parser)
{
	UNREFERENCED_PARAMETER(parser);
}

// Saves object data to a file.
void Serializable::Serialize(Parser& parser) const
{
	UNREFERENCED_PARAMETER(parser);
}

Serializable::Serializable()
{
}

Serializable::~Serializable()
{
}

Serializable::Serializable(const Serializable&)
{
}

Serializable & Serializable::operator=(const Serializable&)
{
	return *this;
}

//------------------------------------------------------------------------------
