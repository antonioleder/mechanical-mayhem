//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

// BetaFramework Engine
#include <Engine.h>

// Engine modules
#include <Space.h>
#include <SoundManager.h>
#include <FullscreenManager.h>

// Initial game state
#include "MainMenu.h"
#include "HUDLevel.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Main function
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR command_line, _In_ int show)
{
	// Enable memory leak checking
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	// Unused parameters
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(show);
	UNREFERENCED_PARAMETER(instance);

	// Create HUD space
	Space* HUDSpace = new Space("HUDSpace");
	// Create a new space called "GameSpace"
	Space* space = new Space("GameSpace");

	// Set initial level to the second level - GameSpace.
	space->SetLevel(new Levels::MainMenu());
	// Set initial level to the HUD level - HUDSpace.
	HUDSpace->SetLevel(new Levels::HUDLevel(space));

	Engine& engine = Engine::GetInstance();

	// Add additional modules to engine
	engine.AddModule(space);
	engine.AddModule(HUDSpace);
	engine.AddModule(new SoundManager());
	//engine.AddModule(new FullscreenManager());

	// Game engine goes!
	engine.Start(800, 600, 200);

	return 0;
}
