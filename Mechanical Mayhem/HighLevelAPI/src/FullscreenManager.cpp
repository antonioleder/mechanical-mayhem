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
	// Get the primary monitor's resolution.
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
	screenDimensions = Vector2D(videoMode->width, videoMode->height);
}

// Make the game fullscreen.
void FullscreenManager::Initialize()
{
	System& system = System::GetInstance();

	if (startFullscreen)
	{
		system.SetFullScreen(true);

		system.SetResolution(screenDimensions.x, screenDimensions.y);
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
