//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
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
#include "Collider.h"

// Systems
#include "Space.h"
#include "GameObjectManager.h"
#include "Event.h"
#include "Parser.h"

// Components
#include "GameObject.h" // GetComponent
#include "Transform.h" // Transform
#include "Physics.h"   // Physics

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

const uint64_t Collider::DEFAULT_MASK = 0x0000000000000000;

// MapCollision constructor.
// Params:
//   bottom = Whether the bottom is colliding or not.
//   top = Whether the top is colliding or not.
//   left = Whether the left is colliding or not.
//   right = Whether the right is colliding or not.
MapCollision::MapCollision(bool bottom, bool top, bool left, bool right) : bottom(bottom), top(top), left(left), right(right)
{
}

// Constructor
// Params:
//  type = Type of the event.
//  name = Name of the event; allows for sub-types.
//  collision = The map collision info.
//  delay = How long to wait before sending this event.
//  sender = GUID of the sending object.
//  receiver = GUID of the receiving object (if none, all objects).
MapCollisionEvent::MapCollisionEvent(const std::string& name, MapCollision collision, float delay, GUID sender, GUID receiver)
	: Event(ET_MapCollision, name, delay, sender, receiver), collision(collision)
{
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Allocate a new collider component.
// Params:
//   type = The type of collider (circle, line, etc.).
Collider::Collider(ColliderType type)
	: Component("Collider"), transform(nullptr), physics(nullptr), type(type), processed(false),
	group(0), mask(DEFAULT_MASK)
{
}

// Set component pointers.
void Collider::Initialize()
{
	transform = GetOwner()->GetComponent<Transform>();
	physics = GetOwner()->GetComponent<Physics>();
}

// Loads object data from a file.
// Params:
//   parser = The parser for the file.
void Collider::Deserialize(Parser& parser)
{
	parser.ReadVariable("group", group);
	parser.ReadVariable("mask", mask);
}

// Saves object data to a file.
// Params:
//   parser = The parser for the file.
void Collider::Serialize(Parser& parser) const
{
	parser.WriteVariable("group", group);
	parser.WriteVariable("mask", mask);
}

// Updates components using a fixed timestep (usually just for physics).
// Params:
//	 dt = A fixed change in time, usually 1/60th of a second.
void Collider::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Reset processed so the collider is ready to do collision checks.
	processed = false;

	GameObjectManager& objectManager = GetOwner()->GetSpace()->GetObjectManager();

	// Handle collision ended events.
	for (auto it = collidersPrevious.begin(); it != collidersPrevious.end(); ++it)
	{
		// If the collider is still colliding, skip this collider.
		if (collidersCurrent.find(*it) != collidersCurrent.end())
			continue;
		
		// Dispatch collision events to both objects.
		objectManager.DispatchEvent(new Event(ET_Collision, "CollisionEnded", 0.0f, GetOwner()->GetID(), *it));
		objectManager.DispatchEvent(new Event(ET_Collision, "CollisionEnded", 0.0f, *it, GetOwner()->GetID()));
	}

	// Move the current array into the previous array and clear the current array.
	std::swap(collidersCurrent, collidersPrevious);

	collidersCurrent.clear();
}

void Collider::Draw()
{
}

// Check if two objects are able to collide (no conflicting collision groups/masks).
// Params:
//	 other = Reference to the second collider component.
bool Collider::CanCollideWith(const Collider& other)
{
	// Check collision groups
	return !((1ull << group) & other.mask) || !((1ull << other.group) & mask);
}

// Check if two objects are colliding and send collision events.
// Params:
//	 other = Pointer to the second collider component.
void Collider::CheckCollision(const Collider& other)
{
	if (&other == this)
		return;

	if (!CanCollideWith(other))
		return;

	// Perform the actual collision math for collisions between objects
	bool colliding = IsCollidingWith(other);

	// If they collide, call respective handlers
	if (colliding)
	{
		GameObjectManager& objectManager = GetOwner()->GetSpace()->GetObjectManager();

		// Figure out what type of collision occurred and dispatch collision events to both objects.

		if (collidersPrevious.find(other.GetOwner()->GetID()) != collidersPrevious.end())
		{
			objectManager.DispatchEvent(new Event(ET_Collision, "CollisionPersisted", 0.0f, GetOwner()->GetID(), other.GetOwner()->GetID()));
			objectManager.DispatchEvent(new Event(ET_Collision, "CollisionPersisted", 0.0f, other.GetOwner()->GetID(), GetOwner()->GetID()));
		}
		else if (collidersCurrent.find(other.GetOwner()->GetID()) == collidersCurrent.end())
		{
			objectManager.DispatchEvent(new Event(ET_Collision, "CollisionStarted", 0.0f, GetOwner()->GetID(), other.GetOwner()->GetID()));
			objectManager.DispatchEvent(new Event(ET_Collision, "CollisionStarted", 0.0f, other.GetOwner()->GetID(), GetOwner()->GetID()));
		}

		// Remember that we collided with this collider.
		collidersCurrent.insert(other.GetOwner()->GetID());
	}
}

// Get the type of this component.
ColliderType Collider::GetType() const
{
	return type;
}

// Gets whether this collider was processed.
bool Collider::WasProcessed() const
{
	return processed;
}

// Marks this collider as processed.
void Collider::SetProcessed()
{
	processed = true;
}

// Gets the collision group.
uint64_t Collider::GetGroup() const
{
	return group;
}

// Sets the collision group.
void Collider::SetGroup(uint64_t group_)
{
	group = group_;
}

// Gets the collision mask. (bitmask of which groups to NOT collide with)
uint64_t Collider::GetMask() const
{
	return mask;
}

// Sets the collision mask. (bitmask of which groups to NOT collide with)
void Collider::SetMask(uint64_t mask_)
{
	mask = mask_;
}

//------------------------------------------------------------------------------
