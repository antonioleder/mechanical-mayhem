//------------------------------------------------------------------------------
//
// File Name:	Pickup.h
// Author(s):	Daniel Walther (daniel.walther)
// Project:		Yesterday's Mayonnaise
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <Component.h>

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class Sprite;

//------------------------------------------------------------------------------

namespace Behaviors
{
	class Pickup : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		// Params:
		//   cooldown = The cooldown after collected
		Pickup(float cooldown = 30.0f);

		// Initializes the component
		void Initialize() override;

		// Updates the component
		void Update(float dt) override;

		// Receive an event and handle it (if applicable).
		// Params:
		//   event = The event that has been received.
		void HandleEvent(const Event& event) override;

		// Returns whether the collectible is active
		bool IsActive() const;

		// Set active
		void SetActive(bool active_);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

	private:
		Sprite* sprite;

		float cooldown;
		float timer;

		bool active;
	};
}

//------------------------------------------------------------------------------