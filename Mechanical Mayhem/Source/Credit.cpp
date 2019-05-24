//------------------------------------------------------------------------------
//
// File Name:	Credit.cpp
// Author(s):	A.J. Bussman
// Project:		Yesterday's Mayonnaise
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Credit.h"

// Systems
#include "Archetypes.h"
#include "Space.h"
#include <Input.h>
#include "MeshHelper.h"
#include <Texture.h>
#include <SpriteSource.h>
#include <Mesh.h>
#include <Graphics.h>
#include <Camera.h>
#include <GameObjectFactory.h>

// Components
#include <SpriteTextMono.h>
#include <Transform.h>
#include "Button.h"

// Levels
#include "MainMenu.h"
#include "Level1.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

namespace Levels
{
	// Creates an instance of Credit.
	Credit::Credit()
		: Level("Credit")
	{
	}

	// Load the resources associated with Credit.
	void Credit::Load()
	{
		std::cout << "Credit::Load" << std::endl;

		GameObjectFactory& objectFactory = GameObjectFactory::GetInstance();
		GameObjectManager& objectManager = GetSpace()->GetObjectManager();
		ResourceManager& resourceManager = GetSpace()->GetResourceManager();

		resourceManager.GetMesh("Quad", Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
		resourceManager.GetSpriteSource("Credits.png");
		resourceManager.GetSpriteSource("Button.png");
		resourceManager.GetMesh("FontAtlas", 12, 8);
		resourceManager.GetSpriteSource("Code New Roman@4x.png", 12, 8);

		objectManager.AddArchetype(*objectFactory.CreateObject("FullScreenImage", resourceManager.GetMesh("Quad"), resourceManager.GetSpriteSource("Credits.png")));
		objectManager.AddArchetype(*objectFactory.CreateObject("Button", resourceManager.GetMesh("Quad"), resourceManager.GetSpriteSource("Button.png")));
		objectManager.AddArchetype(*objectFactory.CreateObject("Text", resourceManager.GetMesh("FontAtlas"), resourceManager.GetSpriteSource("Code New Roman@4x.png")));
	}

	// Initialize the memory associated with Credit.
	void Credit::Initialize()
	{
		std::cout << "Credit::Initialize" << std::endl;

		GameObjectManager& objectManager = GetSpace()->GetObjectManager();

		objectManager.AddObject(*new GameObject(*objectManager.GetArchetypeByName("FullScreenImage")));

		AddMapButton("Main Menu", Vector2D(0.0f, -2.5f), Levels::Map::MainMenu);

		Camera& camera = Graphics::GetInstance().GetDefaultCamera();
		camera.SetTranslation(Vector2D());
		camera.SetFOV(60.0f);
	}

	// Update Credit.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Credit::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
	}

	// Unload the resources associated with Credit.
	void Credit::Unload()
	{
		std::cout << "Credit::Unload" << std::endl;
	}

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Adds a new map button.
	// name = The name of the level.
	// position = The position of the button.
	// map = The map the button should switch to.
	void Credit::AddMapButton(const char* name_, Vector2D position, Levels::Map map)
	{
		GameObjectManager& objectManager = GetSpace()->GetObjectManager();

		GameObject* levelButton = new GameObject(*objectManager.GetArchetypeByName("Button"));
		static_cast<Transform*>(levelButton->GetComponent("Transform"))->SetTranslation(position);
		static_cast<Behaviors::Button*>(levelButton->GetComponent("Button"))->SetMap(map);
		objectManager.AddObject(*levelButton);

		GameObject* text = new GameObject(*objectManager.GetArchetypeByName("Text"));
		text->GetComponent<SpriteTextMono>()->SetText(name_);
		text->GetComponent<SpriteTextMono>()->SetColor(Color(0.0f, 0.0f, 0.0f));
		text->GetComponent<Transform>()->SetTranslation(position);
		objectManager.AddObject(*text);
	}
}
//----------------------------------------------------------------------------