//------------------------------------------------------------------------------
//
// File Name:	Ability.h
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

#include <BetaObject.h> // Base class

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class GameObject;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Abilities
{
	enum Abilities
	{
		ABILITY_NONE = 0,
		ABILITY_JETPACK,
		ABILITY_FLAMETHROWER,
		ABILITY_PROXIMITYMINE,

		ABILITY_MAX
	};

	class Ability : public BetaObject
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		// Params:
		//   name = The name of this ability.
		Ability(const std::string& name);

		// Callback for when the player attempts to use this ability.
		virtual void OnUse() = 0;

		// Sets the owner of this ability.
		void SetOwner(GameObject* owner);

		// Gets the owner of this ability.
		GameObject* GetOwner() const;

		// Creates a new Ability based on the enum.
		static Ability* FromEnum(Abilities ability);

	protected:
		//------------------------------------------------------------------------------
		// Protected Variables:
		//------------------------------------------------------------------------------

		GameObject* owner;
	};
}

//------------------------------------------------------------------------------
