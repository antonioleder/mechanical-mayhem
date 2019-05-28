//------------------------------------------------------------------------------
//
// File Name:	Serializable.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "BetaObject.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References
//------------------------------------------------------------------------------

class Parser;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   modify the public interface (function prototypes) declared in the header.
class Serializable
{
public:
	// Loads object data from a file.
	// Params:
	//   parser = The parser for the file we want to read from.
	virtual void Deserialize(Parser& parser);

	// Saves object data to a file.
	// Params:
	//   parser = The parser for the file we want to write to.
	virtual void Serialize(Parser& parser) const;

protected:
	// These functions are protected to ensure this class is effectively abstract.

	// Constructor
	Serializable();
	// Destructor
	virtual ~Serializable(); 

	// Copy constructor
	// Params:
	//   other = Another serializable object.
	Serializable(const Serializable& other);
	
	// Assignment operator
	// Params:
	//   other = Another serializable object.
	Serializable& operator=(const Serializable& other); 
};

//------------------------------------------------------------------------------
