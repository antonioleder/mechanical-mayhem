//------------------------------------------------------------------------------
//
// File Name:	Quadtree.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
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
#include "Shapes2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class GameObject;
class Transform;
typedef enum Quadrants : short Quadrants;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Object that intersects with ray
struct CastResult
{
	// Constructor
	CastResult(GameObject* object, float t);

	// Public variables
	GameObject* object;
	float t;
};

// Binary space partitioning data structure that allows for
// retrieval of objects near other objects.
class Quadtree
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Default constructor. Initializes all variables to 0.
	Quadtree();

	// Constructor for quadtree.
	// Params:
	//   bounds   = The area encompassed by this node.
	//   level    = The level of this node in the tree. Child nodes will have a level of one less.
	//   maxObjectsPerNode = The maximum number of game objects in this node before it will be split.
	Quadtree(const BoundingRectangle& bounds, int level, int maxObjects);

	// Destructor for quadtree. Calls Clear function.
	~Quadtree();

	// Draws each of the nodes in the tree (for debug purposes only).
	void Draw() const;

	// Adds an object to the tree
	// Params:
	//   object = The game object being added to the tree.
	//   transform = The transform component on the object. Will be calculated if nullptr. Fill it out if you have it to call GetComponent as few times as possible.
	void AddObject(GameObject* object, Transform* transform = nullptr);

	// Retrieve all objects from the tree that could collide with a given object.
	// Params:
	//   object  = The object for which we want to retrieve nearby objects.
	//   results = The list that stores the nearby objects.
	void RetrieveNearbyObjects(GameObject* object, std::vector<GameObject*>& results);

	// Retrieve all objects from the tree that could collide with a given bounding rectangle.
	// Params:
	//   object  = The bounding rectangle for which we want to retrieve nearby objects.
	//   results = The list that stores the nearby objects.
	void RetrieveNearbyObjects(const BoundingRectangle& object, std::vector<GameObject*>& results);

	// Remove all objects from the tree.
	void Clear();

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Splits the contents of a node into four child nodes.
	void Split();

	// Determines which of the four child nodes that an object belongs in.
	// Params:
	//   object = The object for which we need to find the index.
	Quadrants GetIndex(const BoundingRectangle& object);

	// Determines whether this node can contain objects.
	bool IsLeafNode() const;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	Quadtree* nodes[4]; // The four branching nodes of this tree.
	std::vector<GameObject*> objects; // List of objects contained in this node.
	BoundingRectangle bounds;   // Bounding rectangle that defines the area of the node in world space.
	int level;		    // Level of this node in the tree.
};

//------------------------------------------------------------------------------
