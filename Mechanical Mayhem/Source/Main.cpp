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

// Systems
#include <GameObjectFactory.h>

// Components
#include "Button.h"
#include "CameraFollow.h"
#include "ShiftPickup.h"
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
#include "AbilityHolder.h"
#include "AbilityPickup.h"
#include "Health.h"

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
	 
	// Create a new space called "GameSpace"
	Space* space = new Space("GameSpace");

	// Set initial level to the second level.
	space->SetLevel(new Levels::MainMenu());

	Engine& engine = Engine::GetInstance();

	// Add additional modules to engine
	engine.AddModule(new FullscreenManager());
	engine.AddModule(space);
	engine.AddModule(new SoundManager());

	// Register components
	GameObjectFactory& objectFactory = GameObjectFactory::GetInstance();

	{
		using namespace Behaviors;
		objectFactory.RegisterComponent<Button>();
		objectFactory.RegisterComponent<CameraFollow>();
		objectFactory.RegisterComponent<ShiftPickup>();
		objectFactory.RegisterComponent<ColorChange>();
		objectFactory.RegisterComponent<DimensionController>();
		objectFactory.RegisterComponent<Hazard>();
		objectFactory.RegisterComponent<MonkeyAnimation>();
		objectFactory.RegisterComponent<PlayerMovement>();
		objectFactory.RegisterComponent<PlayerShip>();
		objectFactory.RegisterComponent<RisingGears>();
		objectFactory.RegisterComponent<ScreenWrap>();
		objectFactory.RegisterComponent<TimedDeath>();
		objectFactory.RegisterComponent<AbilityHolder>();
		objectFactory.RegisterComponent<AbilityPickup>();
		objectFactory.RegisterComponent<Health>();
	}

	// Game engine goes!
	engine.Start(1920, 1080, 200);

	return 0;
}
