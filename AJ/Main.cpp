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
#include "HUDEmpty.h"

// Systems
#include <GameObjectFactory.h>

// Components
#include "Button.h"
#include "CameraFollow.h"
#include "ChipCollectible.h"
#include "ColorChange.h"
#include "DimensionController.h"
#include "Jetpack.h"
#include "Hazard.h"
#include "MonkeyAnimation.h"
#include "PlayerMovement.h"
#include "PlayerShip.h"
#include "RisingGears.h"
#include "ScreenWrap.h"
#include "TimedDeath.h"

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
	space->SetLevel(new Levels::MainMenu(HUDSpace));
	// Set initial level to the HUD level - HUDSpace.
	HUDSpace->SetLevel(new Levels::HUDEmpty(space));

	Engine& engine = Engine::GetInstance();

	// Add additional modules to engine
	engine.AddModule(new FullscreenManager(true));
	engine.AddModule(space);
	engine.AddModule(HUDSpace);
	engine.AddModule(new SoundManager());
	//engine.AddModule(new FullscreenManager());

	// Register components
	GameObjectFactory& objectFactory = GameObjectFactory::GetInstance();

	{
		using namespace Behaviors;
		objectFactory.RegisterComponent<Button>();
		objectFactory.RegisterComponent<CameraFollow>();
		objectFactory.RegisterComponent<ChipCollectible>();
		objectFactory.RegisterComponent<ColorChange>();
		objectFactory.RegisterComponent<DimensionController>();
		objectFactory.RegisterComponent<Jetpack>();
		objectFactory.RegisterComponent<Hazard>();
		objectFactory.RegisterComponent<MonkeyAnimation>();
		objectFactory.RegisterComponent<PlayerMovement>();
		objectFactory.RegisterComponent<PlayerShip>();
		objectFactory.RegisterComponent<RisingGears>();
		objectFactory.RegisterComponent<ScreenWrap>();
		objectFactory.RegisterComponent<TimedDeath>();
	}

	// Game engine goes!
	engine.Start(1920, 1080, 200);

	return 0;
}
