//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h"

#include <unordered_set>
#include "Event.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class Physics;
class GameObject;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

typedef enum ColliderType
{
	ColliderTypePoint,
	ColliderTypeCircle,
	ColliderTypeRectangle,
	ColliderTypeTilemap,
	ColliderTypeLines,
	ColliderTypeConvex,
} ColliderType;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Booleans determining collision state for each side of the object.
struct MapCollision
{
	MapCollision(bool bottom, bool top, bool left, bool right);
	bool bottom;
	bool top;
	bool left;
	bool right;
};

struct MapCollisionEvent : public Event
{
	// Constructor
	// Params:
	//  name = Name of the event; allows for sub-types.
	//  collision = The map collision info.
	//  delay = How long to wait before sending this event.
	//  sender = GUID of the sending object.
	//  receiver = GUID of the receiving object (if none, all objects).
	MapCollisionEvent(const std::string& name, MapCollision collision, float delay = 0.0f, GUID sender = GUID(), GUID receiver = GUID());

	MapCollision collision;
};

// Collider class - Detects collisions between objects
class Collider : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Allocate a new collider component.
	// Params:
	//   type = The type of collider (see the ColliderType enum).
	Collider(ColliderType type);

	// Set component pointers.
	void Initialize() override;

	// Loads object data from a file.
	// Params:
	//   parser = The parser for the file.
	virtual void Deserialize(Parser& parser) override;

	// Saves object data to a file.
	// Params:
	//   parser = The parser for the file.
	virtual void Serialize(Parser& parser) const override;

	// Updates components using a fixed timestep (usually just for physics).
	// Params:
	//	 dt = A fixed change in time, usually 1/60th of a second.
	void FixedUpdate(float dt) override;

	// Draw collision shape
	virtual void Draw() = 0;

	// Check if two objects are able to collide (no conflicting collision groups/masks).
	// Params:
	//	 other = Reference to the second collider component.
	bool CanCollideWith(const Collider& other);

	// Check if two objects are colliding and send collision events.
	// Params:
	//	 other = Reference to the second collider component.
	void CheckCollision(const Collider& other);

	// Perform intersection test between two arbitrary colliders.
	// Params:
	//	 other = Reference to the second collider component.
	virtual bool IsCollidingWith(const Collider& other) const = 0;

	// Get the type of this component.
	ColliderType GetType() const;

	// Gets whether this collider was processed.
	bool WasProcessed() const;

	// Marks this collider as processed.
	void SetProcessed();

	// Gets the collision group.
	uint64_t GetGroup() const;

	// Sets the collision group.
	void SetGroup(uint64_t group);

	// Gets the collision mask. (bitmask of which groups to NOT collide with)
	uint64_t GetMask() const;

	// Sets the collision mask. (bitmask of which groups to NOT collide with)
	void SetMask(uint64_t mask);

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	// Component pointers
	Transform* transform;
	Physics* physics;

	static const uint64_t DEFAULT_MASK;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The collision group of this collider.
	uint64_t group;

	// The collision mask of this collider.
	uint64_t mask;

	// The type of collider used by this component.
	ColliderType type;

	// Whether this collider has had its collisions processed yet.
	bool processed;
	
	// The colliders we were colliding with the previous fixed update.
	std::unordered_set<GUID> collidersPrevious;

	// The colliders we are colliding with the current fixed update.
	std::unordered_set<GUID> collidersCurrent;
};

//------------------------------------------------------------------------------
