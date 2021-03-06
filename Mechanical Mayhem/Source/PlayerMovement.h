//------------------------------------------------------------------------------
//
// File Name:	PlayerMovement.h
// Author(s):	David Cohen (david.cohen) and A.J. Bussman (anthony.bussman)
// Project:		Yesterday's Mayonnaise
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class

#include "Vector2D.h" // Vector2D

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class Physics;
struct MapCollision;
class SoundManager;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	class MonkeyAnimation;

	enum PowerUp {
		POWER_UP_NONE,
		POWER_UP_JUMP,
		POWER_UP_SPEED
	};

	class PlayerMovement : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		PlayerMovement(unsigned keyUp = 0, unsigned keyLeft = 0, unsigned keyRight = 0, unsigned keySwitch = 0);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Initialize this component (happens at object creation).
		void Initialize() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		// Receive an event and handle it (if applicable).
		// Params:
		//   event = The event that has been received.
		void HandleEvent(const Event& event) override;

		// Sets the keybinds for the monkey.
		// Params:
		//   keyUp = The up keybind.
		//   keyLeft = The left keybind.
		//   keyRight = The right keybind.
		//	 keySwitch = The dimension-switch keybind.
		void SetKeybinds(unsigned keyUp, unsigned keyLeft, unsigned keyRight, unsigned keySwitch);

		// Gets the keybind for up
		unsigned GetUpKeybind() const;

		// Sets the player's ID.
		// Params:
		//   newID = The ID to set to.
		void SetPlayerID(int newID);

		// Sets the player's ID.
		// Returns:
		//   The player's ID.
		int GetPlayerID() const;

		// Returns current powerUp
		PowerUp GetPowerUp() const;

		// Sets current powerUp
		// Default is no powerUp
		void SetPowerUp(PowerUp newPowerUp = POWER_UP_NONE);

		// Starts PowerUp Timer
		void StartPUTimer();

		// Determines whether the player is grounded
		bool getOnGround() const;

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// Moves horizontally based on input
		void MoveHorizontal(float dt) const;

		// Moves vertically based on input
		void MoveVertical(float dt);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Keybinds
		unsigned keyUp;
		unsigned keyLeft;
		unsigned keyRight;
		unsigned keySwitch;

		// Movement properties
		float walkSpeed;
		float walkSpeedOld;
		Vector2D jumpSpeed;
		Vector2D jumpSpeedOld;
		Vector2D slidingJumpSpeed;
		Vector2D gravity;
		Vector2D slidingGravity;
		float terminalVelocity;
		float slidingTerminalVelocity;
		float gracePeriod;

		// Components
		Transform* transform;
		Physics* physics;
		SoundManager* soundManager;

		// Misc
		int playerID;
		int chips;

		bool onGround;
		bool onLeftWall;
		bool onRightWall;
		bool hasJumped;
		float airTime;
		float leftTime;
		float rightTime;
		float movementLerpGround;
		float movementLerpAir;

		// PowerUps
		PowerUp powerUp;
		float PUTimer;
		float PUMaxTime;
		Vector2D jumpBoost;
		float speedBoost;

		friend class MonkeyAnimation;
	};
}

//------------------------------------------------------------------------------
