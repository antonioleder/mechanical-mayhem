//------------------------------------------------------------------------------
//
// File Name:	FullscreenManager.cpp
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

#include "FullscreenManager.h"

// Systems
#include <System.h>
#include <glfw3.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
// Params:
//   startFullscreen = Whether the game should start in fullscreen mode.
FullscreenManager::FullscreenManager(bool startFullscreen) : BetaObject("FullscreenManager"), startFullscreen(startFullscreen), screenDimensions()
{
}

// Make the game fullscreen.
void FullscreenManager::Initialize()
{
	// Get the primary monitor's resolution.
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
	screenDimensions = Vector2D(static_cast<float>(videoMode->width), static_cast<float>(videoMode->height));

	System& system = System::GetInstance();

	if (startFullscreen)
	{
		system.SetFullScreen(true);

		system.SetResolution(static_cast<unsigned>(screenDimensions.x), static_cast<unsigned>(screenDimensions.y));
	}
}

// Returns whether the game will start in fullscreen mode.
bool FullscreenManager::GetStartFullscreen() const
{
	return startFullscreen;
}

// Sets whether the game will start in fullscreen mode.
void FullscreenManager::SetStartFullscreen(bool startFullscreen_)
{
	startFullscreen = startFullscreen_;
}

// Returns the resolution of the primary monitor.
Vector2D FullscreenManager::GetScreenDimensions() const
{
	return screenDimensions;
}

//------------------------------------------------------------------------------
