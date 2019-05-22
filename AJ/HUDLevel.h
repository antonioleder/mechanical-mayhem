//------------------------------------------------------------------------------
//
// File Name:	HUDLevel.h
// Author(s):	A.J. Bussman
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

#include "Vector2D.h"
#include "Level.h"

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Mesh;
class Texture;
class SpriteSource;
class GameObject;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

struct HUD
{
	// Constructor
	HUD(GameObject* PlayerIcon, GameObject* HealthBar, GameObject* HealthText, GameObject* AbilityBar, GameObject* AbilityIcon) :
		PlayerIcon(PlayerIcon), HealthBar(HealthBar),  HealthText(HealthText), AbilityBar(AbilityBar), AbilityIcon(AbilityIcon) {}

	GameObject* PlayerIcon;
	GameObject* HealthBar;
	GameObject* HealthText;
	GameObject* AbilityBar;
	GameObject* AbilityIcon;
};

namespace Levels
{
	enum class Map : int;

	class HUDLevel : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of MainMenu.
		HUDLevel(Space* gameSpace = nullptr);

		// Load the resources associated with MainMenu.
		void Load() override;

		// Initialize the memory associated with MainMenu.
		void Initialize() override;

		// Update MainMenu.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Unload the resources associated with MainMenu.
		void Unload() override;

		// Sets the GameSpace to the given gameSpace
		// Params:
		//	 gameSpace = gameSpace to set GameSpace to.
		void SetGameSpace(Space* gameSpace);

		// Returns if the HUD display is active
		bool IsActive();

		// Sets whether the HUD display is active
		// Params:
		//	 active = whether the HUD is active or not
		void SetActive(bool active);

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// Adds a new map button.
		// name = The name of the level.
		// position = The position of the button.
		// map = The map the button should switch to.
		HUD* AddPlayerHUD(const char* name, Vector2D position);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// HUDs & Players
		HUD* HUD1, * HUD2;
		GameObject* Player1, * Player2;

		Space* GameSpace;

		bool Active;

		Mesh* meshBackground;
		Texture * textureBackground;
		SpriteSource* spriteSourceBackground;
	};
}

//----------------------------------------------------------------------------
