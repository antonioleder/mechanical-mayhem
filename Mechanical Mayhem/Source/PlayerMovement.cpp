//------------------------------------------------------------------------------
//
// File Name:	PlayerMovement.cpp
// Author(s):	David Cohen (david.cohen) and A.J. Bussman (anthony.bussman)
// Project:		Yesterday's Mayonnaise
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "PlayerMovement.h"

// Systems
#include <Engine.h>
#include "GameObject.h"
#include <Input.h>
#include <SoundManager.h>
#include "Space.h"
#include <Interpolation.h>

// Components
#include "Transform.h"
#include "Physics.h"
#include "Collider.h"
#include "DimensionController.h"
#include "ChipCollectible.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	PlayerMovement::PlayerMovement(unsigned keyUp, unsigned keyLeft, unsigned keyRight, unsigned keySwitch) : Component("PlayerMovement"),
		keyUp(keyUp), keyLeft(keyLeft), keyRight(keyRight), keySwitch(keySwitch),
		walkSpeed(5.0f), walkSpeedOld(walkSpeed), jumpSpeed(0.0f, 11.0f), jumpSpeedOld(jumpSpeed), slidingJumpSpeed(6.0f, 6.75f),
		gravity(0.0f, -16.0f), slidingGravity(0.0f, -9.0f), terminalVelocity(9.0f), slidingTerminalVelocity(1.5f), gracePeriod(0.15f),
		transform(nullptr), physics(nullptr),
		playerID(0), chips(0),
		onGround(false), onLeftWall(false), onRightWall(false),
		hasJumped(false), airTime(0.0f), leftTime(0.0f), rightTime(0.0f), movementLerpGround(1.0f), movementLerpAir(0.98f),
		powerUp(POWER_UP_NONE), PUTimer(0.0f), PUMaxTime(10.0f), jumpBoost(0.0f, 11.5f), speedBoost(4.25f)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* PlayerMovement::Clone() const
	{
		return new PlayerMovement(*this);
	}

	// Initialize this component (happens at object creation).
	void PlayerMovement::Initialize()
	{
		// Store the required components for ease of access.
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));

		// Add sounds
		soundManager = Engine::GetInstance().GetModule<SoundManager>();
		soundManager->AddEffect("jump.wav");
		soundManager->AddEffect("step.wav");
		soundManager->AddEffect("wallattach.wav");
		soundManager->AddEffect("walloff.wav");
		soundManager->AddEffect("wallslide.wav");
	}

	// Fixed update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void PlayerMovement::Update(float dt)
	{
		// Check if the player has an active powerUp
		if (PUTimer -= dt <= 0.0f)
		{
			// Set the PUTimer to 0
			PUTimer = 0.0f;
			// Set the current powerUp to Nothing
			SetPowerUp();
		}

		// Handle horizontal movement.
		MoveHorizontal(dt);

		// Handle vertical movement.
		MoveVertical(dt);

		GameObject* gameController = GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("GameController");
		DimensionController& dimensionController = *static_cast<DimensionController*>(gameController->GetComponent("DimensionController"));

		// Switch dimensions when pressing the key, there are unused chips, and dimension switching is not on cooldown.
		Input& input = Input::GetInstance();
		if (input.CheckTriggered(keySwitch) && chips > 0 && dimensionController.GetSwitchCooldown() <= 0.0f)
		{
			// Calculate next dimension ID
			unsigned newDimension = (dimensionController.GetActiveDimension() + 1) % dimensionController.GetDimensionCount();
			dimensionController.SetActiveDimension(newDimension);
			--chips;
		}
	}

	// Receive an event and handle it (if applicable).
	// Params:
	//   event = The event that has been received.
	void PlayerMovement::HandleEvent(const Event& event)
	{
		GameObject& other = *static_cast<GameObject*>(event.GetSender());
		
		if (event.name == "CollisionStarted")
		{
			// Destroy collectibles when touching.
			if (other.GetName() == "Collectible")
			{
				ChipCollectible* collectible = static_cast<ChipCollectible*>(other.GetComponent("ChipCollectible"));

				// if chips are active, get more switcheroos and deactive the chips
				if (collectible->IsActive())
				{
					chips += 5;
					collectible->SetActive(false);
				}
			}

			// Jump & speed boost powerups
			if (other.GetName() == "JumpBoost" || other.GetName() == "SpeedBoost")
			{
				if (other.GetName() == "JumpBoost")
					SetPowerUp(POWER_UP_JUMP);
				else if (other.GetName() == "SpeedBoost")
					SetPowerUp(POWER_UP_SPEED);

				StartPUTimer();

				other.Destroy();
			}
		}

		if (event.name == "MapCollisionStarted" || event.name == "MapCollisionPersisted")
		{
			const MapCollisionEvent& mapCollisionEvent = static_cast<const MapCollisionEvent&>(event);
			// If the monkey's collider is colliding on the bottom, mark the monkey as on ground.
			if (mapCollisionEvent.collision.bottom)
			{
				onGround = true;
			}

			// Save whether the monkey is touching a wall, used for wall jumping.

			if (mapCollisionEvent.collision.left)
			{
				onLeftWall = true;
			}

			if (mapCollisionEvent.collision.right)
			{
				onRightWall = true;
			}
		}
	}

	// Sets the keybinds for the monkey.
	// Params:
	//   keyUp = The up keybind.
	//   keyLeft = The left keybind.
	//   keyRight = The right keybind.
	void PlayerMovement::SetKeybinds(unsigned keyUp_, unsigned keyLeft_, unsigned keyRight_, unsigned keySwitch_)
	{
		keyUp = keyUp_;
		keyLeft = keyLeft_;
		keyRight = keyRight_;
		keySwitch = keySwitch_;
	}

	// Gets the keybind for up
	unsigned PlayerMovement::GetUpKeybind() const
	{
		return keyUp;
	}

	// Sets the player's ID.
	// Params:
	//   newID = The ID to set to.
	void PlayerMovement::SetPlayerID(int newID)
	{
		playerID = newID;
	}

	// Sets the player's ID.
	// Returns:
	//   The player's ID.
	int PlayerMovement::GetPlayerID() const
	{
		return playerID;
	}

	// Returns current powerUp
	PowerUp PlayerMovement::GetPowerUp() const
	{
		return powerUp;
	}

	// Sets current powerUp
	// Default is no powerUp
	void PlayerMovement::SetPowerUp(PowerUp newPowerUp)
	{
		powerUp = newPowerUp;

		if (powerUp == POWER_UP_JUMP)
			jumpSpeed = jumpBoost;
		else if (powerUp == POWER_UP_SPEED)
			walkSpeed = speedBoost;
		else
		{
			jumpSpeed = jumpSpeedOld;
			walkSpeed = walkSpeedOld;
		}
	}

	// Starts PowerUp Timer
	void PlayerMovement::StartPUTimer()
	{
		PUTimer = PUMaxTime;
	}

	// Determines whether the player is grounded
	bool PlayerMovement::getOnGround() const
	{
		return onGround;
	}

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Moves horizontally based on input
	void PlayerMovement::MoveHorizontal(float dt) const
	{
		Input& input = Input::GetInstance();

		Vector2D velocity = physics->GetVelocity();

		// Initialize target velocity to 0.
		float targetVelocityX = 0.0f;

		// If the right arrow key is pressed, move to the right.
		if (input.CheckHeld(keyRight))
		{
			targetVelocityX += walkSpeed;
		}

		// If the right arrow key is pressed, move to the left.
		if (input.CheckHeld(keyLeft))
		{
			targetVelocityX -= walkSpeed;
		}

		// Smoothly interpolate the X component of the player's velocity.
		float movementMix = 1.0f - pow(1.0f - (airTime < 1e-6f ? movementLerpGround : movementLerpAir), dt);
		velocity.x = Interpolate(velocity.x, targetVelocityX, movementMix);

		// Set the velocity.
		physics->SetVelocity(velocity);
	}

	// Moves vertically based on input
	void PlayerMovement::MoveVertical(float dt)
	{
		Input& input = Input::GetInstance();

		Vector2D velocity = physics->GetVelocity();

		// Reset time since touching walls.
		if (onLeftWall && !onRightWall)
			leftTime = 0.0f;
		else
			leftTime += dt;

		if (onRightWall && !onLeftWall)
			rightTime = 0.0f;
		else
			rightTime += dt;

		bool onlyLeftWall = leftTime <= gracePeriod;
		bool onlyRightWall = rightTime <= gracePeriod;
		bool isSliding = (onlyLeftWall || onlyRightWall) && !onGround;

		if (onGround || (onLeftWall && !onRightWall) || (onRightWall && !onLeftWall))
		{
			// Reset time spent in the air.
			airTime = 0.0f;

			// The player has not jumped since leaving the ground.
			hasJumped = false;
		}
		else
		{
			// Keep track of time spent in the air.
			airTime += dt;
		}

		bool canJump = airTime <= gracePeriod || onlyLeftWall || onlyRightWall;

		// If the monkey has not jumped since landing, was on the ground recently, and the up arrow key is pressed, jump.
		if (!hasJumped && canJump && input.CheckHeld(keyUp))
		{
			if (isSliding)
			{
				// Increase Y velocity.
				velocity.y = slidingJumpSpeed.y;

				if (onlyLeftWall)
				{
					velocity.x = slidingJumpSpeed.x;
				}
				else if (onlyRightWall)
				{
					velocity.x = -slidingJumpSpeed.x;
				}

				// Hacky fix so ground movement lerp isn't used immediately after jumping off walls.
				airTime = 1e-6f;
			}
			else
			{
				// Increase Y velocity.
				velocity.y = jumpSpeed.y;
			}

			soundManager->PlaySound("jump.wav");
			hasJumped = true;
		}
		
		// Apply gravity if in air.
		if (!onGround)
		{
			// Use different gravity when sliding
			if (isSliding)
			{
				if (velocity.y > 0.0f)
					physics->AddForce(gravity);
				else
					physics->AddForce(slidingGravity);
			}
			else
			{
				physics->AddForce(gravity);
			}
		}

		// Clamp velocity.
		// Use different terminal velocity depending on whether the monkey is sliding.
		if (isSliding)
			velocity.y = max(-slidingTerminalVelocity, velocity.y);
		else
			velocity.y = max(-terminalVelocity, velocity.y);

		// Set the velocity.
		physics->SetVelocity(velocity);

		onGround = false;
		onLeftWall = false;
		onRightWall = false;
	}
}

//------------------------------------------------------------------------------
