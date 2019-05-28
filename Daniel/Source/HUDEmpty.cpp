//------------------------------------------------------------------------------
//
// File Name:	HUDEmpty.cpp
// Author(s):	A.J. Bussman
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
#include "HUDEmpty.h"

// Systems
#include "Archetypes.h"
#include "Space.h"
#include <Input.h>
#include <Graphics.h>
#include <Camera.h>
#include <Mesh.h>
#include <MeshHelper.h>
#include <Texture.h>
#include <SpriteSource.h>

// Components
#include "SpriteText.h"
#include <Transform.h>
#include "Sprite.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

namespace Levels
{
	// Creates an instance of HUDEmpty.
	HUDEmpty::HUDEmpty() : Level("HUDEmpty")
	{
	}

	// Load the resources associated with MainMenu.
	void HUDEmpty::Load()
	{
		std::cout << "HUDEmpty::Load" << std::endl;
	}

	// Initialize the memory associated with MainMenu.
	void HUDEmpty::Initialize()
	{
		std::cout << "HUDEmpty::Initialize" << std::endl;

		Camera& camera = Graphics::GetInstance().GetDefaultCamera();
		camera.SetTranslation(Vector2D());
		camera.SetSize(10.0f);
	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void HUDEmpty::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
	}

	// Unload the resources associated with MainMenu.
	void HUDEmpty::Unload()
	{
		std::cout << "HUDEmpty::Unload" << std::endl;
	}
}
//----------------------------------------------------------------------------
