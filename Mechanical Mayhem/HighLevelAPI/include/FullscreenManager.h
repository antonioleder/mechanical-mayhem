//------------------------------------------------------------------------------
//
// File Name:	FullscreenManager.h
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

#include <BetaObject.h>

#include <Vector2D.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Allows the game to start in fullscreen mode and handles related information.
class FullscreenManager : public BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   startFullscreen = Whether the game should start in fullscreen mode.
	FullscreenManager(bool startFullscreen = false);

	// Make the game fullscreen.
	void Initialize();

	// Returns whether the game will start in fullscreen mode.
	bool GetStartFullscreen() const;

	// Sets whether the game will start in fullscreen mode.
	void SetStartFullscreen(bool startFullscreen);

	// Returns the resolution of the primary monitor.
	Vector2D GetScreenDimensions() const;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	bool startFullscreen;
	Vector2D screenDimensions;
};

//------------------------------------------------------------------------------
