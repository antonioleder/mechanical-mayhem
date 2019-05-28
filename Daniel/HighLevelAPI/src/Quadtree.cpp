//------------------------------------------------------------------------------
//
// File Name:	Quadtree.cpp
// Author(s):	David Cohen (david.cohen)
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

#include "Quadtree.h"

// Systems
#include "GameObject.h"
#include <DebugDraw.h>
#include <Graphics.h>

// Components
#include "Transform.h"
#include "ColliderTilemap.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Enums:
//------------------------------------------------------------------------------

enum Quadrants : short
{
	OUT_OF_BOUNDS = -2,
	PARTIAL_FIT = -1,
	TOP_RIGHT,
	TOP_LEFT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT,
	NUM_CHILDREN
};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
CastResult::CastResult(GameObject* object, float t) : object(object), t(t)
{
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default constructor. Initializes all variables to 0.
Quadtree::Quadtree() : bounds(Vector2D(), Vector2D()), level(0), nodes{nullptr, nullptr, nullptr, nullptr}
{
	for (int i = 0; i < NUM_CHILDREN; i++)
		nodes[i] = nullptr;
}

// Constructor for quadtree.
// Params:
//   bounds   = The area encompassed by this node.
//   level    = The level of this node in the tree. Child nodes will have a level of one less.
//   maxObjectsPerNode = The maximum number of game objects in this node before it will be split.
Quadtree::Quadtree(const BoundingRectangle& bounds, int level, int maxObjects) : bounds(bounds), level(level), nodes{nullptr, nullptr, nullptr, nullptr}
{
	objects.reserve(maxObjects);

	for (int i = 0; i < NUM_CHILDREN; i++)
		nodes[i] = nullptr;
}

// Destructor for quadtree. Calls Clear function.
Quadtree::~Quadtree()
{
	Clear();
}

// Draws each of the nodes in the tree (for debug purposes only).
void Quadtree::Draw() const
{
	if (IsLeafNode())
	{
		DebugDraw::GetInstance().AddRectangle(bounds.center, bounds.extents, Graphics::GetInstance().GetDefaultCamera());
	}
	else
	{
		for (int i = 0; i < NUM_CHILDREN; i++)
			nodes[i]->Draw();
	}
}

// Adds an object to the tree
// Params:
//   object = The game object being added to the tree.
	//   transform = The transform component on the object. Will be calculated if nullptr. Fill it out if you have it to call GetComponent as few times as possible.
//   placeInAll = Whether the object should be placed in all leaves. Useful for large objects such as tilemaps.
void Quadtree::AddObject(GameObject* object, Transform* transform)
{
	if (transform == nullptr)
		transform = object->GetComponent<Transform>();

	// 1. First, use the GetIndex function to find the index of the object
	Quadrants index = GetIndex(transform->GetBounds());

	// 2. If the object is not within node bounds (i.e., index is OUT_OF_BOUNDS) Return!
	if (index == OUT_OF_BOUNDS)
		return;

	// 3. If we are at a leaf node
	if (IsLeafNode())
	{
		// If we are not at the tree's max depth and there are too many objects
		if (level > 0 && objects.size() == objects.capacity())
		{
			// Split this node by calling the Split function
			Split();

			// Then try adding the object again (After splitting, there will be a different outcome.)
			AddObject(object, transform);
		}
		// Else, number of objects is okay or we are at max depth, so push object onto list.
		else
		{
			objects.push_back(object);
		}
	}
	// 4. Else, we are not at a leaf node
	else
	{
		// If object has total fit, add to the specific node that matches its index.
		if (index != PARTIAL_FIT)
		{
			// Call AddObject on the specific node that matches its index
			nodes[index]->AddObject(object, transform);
		}
		// Else, object has partial fit, so for each subnode,
		else
		{
			// Call AddObject on the subnode
			for (int i = 0; i < NUM_CHILDREN; i++)
				nodes[i]->AddObject(object, transform);
		}
	}
}

// Retrieve all objects from the tree that could collide with a given object.
// Params:
//   object  = The object for which we want to retrieve nearby objects.
//   results = The list that stores the nearby objects.
void Quadtree::RetrieveNearbyObjects(GameObject* object, std::vector<GameObject*>& results)
{// Place tilemaps in all nodes.
	if (object->GetComponent<ColliderTilemap>() != nullptr)
		return RetrieveNearbyObjects(BoundingRectangle(Vector2D(), Vector2D(FLT_MAX, FLT_MAX)), results);
	return RetrieveNearbyObjects(object->GetComponent<Transform>()->GetBounds(), results);
}

// Retrieve all objects from the tree that could collide with a given bounding rectangle.
// Params:
//   object  = The bounding rectangle for which we want to retrieve nearby objects.
//   results = The list that stores the nearby objects.
void Quadtree::RetrieveNearbyObjects(const BoundingRectangle& object, std::vector<GameObject*>& results)
{
	// 1. First, as always, get the index of the object.
	Quadrants index = GetIndex(object);

	// 2. If the object is not within bounds, LEAVE THIS PLACE!
	if (index == OUT_OF_BOUNDS)
		return;

	// 3. If we are at a leaf node
	if (IsLeafNode())
	{
		// For each object in our list of objects
		for (auto it = objects.begin(); it != objects.end(); ++it)
			// Add the object to our list of results
			results.push_back(*it);
	}
	// 4. Else (i.e. we are not at leaf node)
	else
	{
		// if the object has partial fit
		if (index == PARTIAL_FIT)
		{
			// For each child node, retrieve objects from that node
			for (int i = 0; i < NUM_CHILDREN; i++)
				nodes[i]->RetrieveNearbyObjects(object, results);
		}
		// else, object has total fit, so retrieve objects from the specific node
		else
		{
			nodes[index]->RetrieveNearbyObjects(object, results);
		}
	}
}

// Remove all objects from the tree.
void Quadtree::Clear()
{
	// 1. If we are at a leaf node
	if (IsLeafNode())
	{
		// Clear our list of objects
		objects.clear();
	}
	// 2. Else (i.e. not a leaf node)
	else
	{
		// For each node
		for (int i = 0; i < NUM_CHILDREN; i++)
		{
			// Delete the node
			delete nodes[i];

			// Set the node to null
			nodes[i] = nullptr;
		}
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Splits the contents of a node into four child nodes.
void Quadtree::Split()
{
	// 1. Create and initialize variables for the extents of the sub-nodes.
	// (Extents of every sub-node will be half of the extents of the current node.)
	Vector2D childExtents = bounds.extents / 2.0f;

	// 2. Create the four new nodes with centers located at the center of this node +/- the sub-node with and height.
	// NOTE: Maximum number of objects will remain the same for the subnodes.
	nodes[0] = new Quadtree(BoundingRectangle(bounds.center + childExtents, childExtents), level - 1, static_cast<int>(objects.capacity()));
	nodes[1] = new Quadtree(BoundingRectangle(Vector2D(bounds.center.x - childExtents.x, bounds.center.y + childExtents.y), childExtents), level - 1, static_cast<int>(objects.capacity()));
	nodes[2] = new Quadtree(BoundingRectangle(Vector2D(bounds.center.x + childExtents.x, bounds.center.y - childExtents.y), childExtents), level - 1, static_cast<int>(objects.capacity()));
	nodes[3] = new Quadtree(BoundingRectangle(bounds.center + childExtents * -1.0f, childExtents), level - 1, static_cast<int>(objects.capacity()));

	// 3. For each object in the current node
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		Transform* transform = (*it)->GetComponent<Transform>();

		// Get the index of the object
		Quadrants index = GetIndex(transform->GetBounds());

		// If it fits in a specific quadrant,
		if (index != PARTIAL_FIT)
		{
			// Add it to the appropriate node
			nodes[index]->AddObject(*it);
		}
		// Else, if it's only a partial fit, for each sub-node
		else
		{
			// Add it to the sub-node
			for (int i = 0; i < NUM_CHILDREN; i++)
				nodes[i]->AddObject(*it, transform);
		}
	}

	// 4. Remove all objects from our object list; objects should only exist in leaf nodes.
	objects.clear();
}

// Determines which of the four child nodes that an object belongs in.
// Params:
//   object = The object for which we need to find the index.
Quadrants Quadtree::GetIndex(const BoundingRectangle& object)
{
	// 1. Compare the bounds of the object with the bounds of the node.
	if (object.right < bounds.left || object.left > bounds.right || object.top < bounds.bottom || object.bottom > bounds.top)
	{
		// If the object is not within bounds of this node
		return OUT_OF_BOUNDS;
	}
	
	// Now we know that fit is at least partial!
	Quadrants index = PARTIAL_FIT;

	// 2. Determine whether object can completely fit within the top quadrants
	// HINT: Compare the bottom of the object with the center of this node.
	bool fitsTopQuadrant = object.bottom >= bounds.center.y && object.top <= bounds.top;

	// 3. Determine whether object can completely fit within the bottom quadrants
	// HINT: Compare the top of the object with the center of this node.
	bool fitsBottomQuadrant = object.top < bounds.center.y && object.bottom >= bounds.bottom;

	// 4. If it can fit within the left quadrants (similar to above)
	if (object.right < bounds.center.x && object.left >= bounds.left)
	{
		// if it fits in top quadrants
		if (fitsTopQuadrant)
			// index is top left
			index = TOP_LEFT;
		// else if it fits in bottom quadrants
		else if (fitsBottomQuadrant)
			// index is bottom left
			index = BOTTOM_LEFT;
	}
	// 5. Else, if object can completely fit within the right quadrants
	else if (object.left >= bounds.center.x && object.right <= bounds.right)
	{
		// if it fits in top quadrants
		if (fitsTopQuadrant)
			// index is top right
			index = TOP_RIGHT;
		// else if it fits in bottom quadrants
		else if (fitsBottomQuadrant)
			// index is bottom right
			index = BOTTOM_RIGHT;
	}

	// 6. Return the index
	return index;
}

// Determines whether this node can contain objects.
bool Quadtree::IsLeafNode() const
{
	return nodes[0] == nullptr;
}

//------------------------------------------------------------------------------
