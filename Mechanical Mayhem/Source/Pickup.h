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
		//   name = The name of this component.
		//   cooldown = The cooldown for respawning after collected.
		Pickup(const std::string& name, float cooldown = 0.0f);

		// Initializes the component
		void Initialize() override;

		// Write object data to file
		// Params:
		//   parser = The parser that is writing this object to a file.
		void Serialize(Parser& parser) const override;

		// Read object data from a file
		// Params:
		//   parser = The parser that is reading this object's data from a file.
		void Deserialize(Parser& parser) override;

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