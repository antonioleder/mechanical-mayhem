//------------------------------------------------------------------------------
//
// File Name:	GameObjectFactory.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObjectFactory.h"

#include "GameObject.h" // GetComponent
#include "Parser.h"

// Components
#include "ColliderCircle.h"
#include "ColliderPoint.h"
#include "ColliderRectangle.h"
#include "ColliderTilemap.h"
#include "Transform.h"
#include "Animation.h"
#include "Sprite.h"
#include "SpriteTilemap.h"
#include "SpriteTextMono.h"
#include "Physics.h"
#include "MutableTilemap.h"

#include "Engine.h" // GetFilePath

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a single instance of the specified game object.
// Loads the object from a text file (if it exists).
// Params:
//   name = The name of the object.
//   mesh = The mesh used for the object's sprite (if any).
//   spriteSource = The sprite source used for the object's sprite (if any).
// Returns:
//	 If the object file exists and can be loaded, then return a pointer to a new instance 
//    of the specified game object type, else nullptr.
GameObject* GameObjectFactory::CreateObject(const std::string& name,
	Mesh* mesh, SpriteSource* spriteSource)
{
	// Create game object
	GameObject* object = new GameObject(name);

	// Create filename
	const std::string& enginePath = Engine::GetInstance().GetFilePath();
	std::string filename = enginePath + objectFilePath + name + ".txt";
	Parser parser(filename, std::fstream::in);
	try
	{
		// Attempt to load object
		object->Deserialize(parser);

		// Set mesh and sprite source
		Sprite* sprite = object->GetComponent<Sprite>();
		if (sprite != nullptr)
		{
			sprite->SetMesh(mesh);
			sprite->SetSpriteSource(spriteSource);
		}
	}
	catch(const ParseException& exception)
	{
		std::cerr << "Exception in GameObjectFactory::CreateObject - " << exception.what() << std::endl;
		delete object;
		object = nullptr;
	}

	return object;
}

// Create a single instance of the specified component.
// Params:
//   name = The name of the component.
// Returns:
//	 If the component exists, then return a pointer to a new instance 
//    of the specified component, else nullptr.
Component* GameObjectFactory::CreateComponent(const std::string& name)
{
	for (unsigned i = 0; i < registeredComponents.size(); ++i)
	{
		std::string componentTypeName = std::string(typeid(*registeredComponents[i]).name());

		if (componentTypeName.find(name) != std::string::npos)
			return registeredComponents[i]->Clone();
	}

	return nullptr;
}

// Saves an object to an archetype file so it can be loaded later.
void GameObjectFactory::SaveObjectToFile(GameObject * object)
{
	// Create filename
	const std::string& enginePath = Engine::GetInstance().GetFilePath();
	std::string filename = enginePath + objectFilePath + object->GetName() + ".txt";
	Parser parser(filename, std::fstream::out);
	try
	{
		// Attempt to save object
		object->Serialize(parser);
		std::cout << "Wrote object " << object->GetName() << " to file " << filename << std::endl;
	}
	catch (const ParseException& exception)
	{
		std::cerr << "Exception in GameObjectFactory::SaveObjectToFile - " << exception.what() << std::endl;
	}
}

// Returns an instance of the factory.
GameObjectFactory & GameObjectFactory::GetInstance()
{
	static GameObjectFactory factory;
	return factory;
}

//------------------------------------------------------------------------------
// Private Functions
//------------------------------------------------------------------------------

// Constructor is private to prevent accidental instantiation
GameObjectFactory::GameObjectFactory()
	: objectFilePath("Objects/")
{
	// Register all components
	RegisterComponent<ColliderCircle>();
	RegisterComponent<ColliderPoint>();
	RegisterComponent<ColliderRectangle>();
	RegisterComponent<ColliderTilemap>();
	RegisterComponent<Transform>();
	RegisterComponent<Animation>();
	RegisterComponent<Sprite>();
	RegisterComponent<SpriteTilemap>();
	RegisterComponent<SpriteTextMono>();
	RegisterComponent<Physics>();
	RegisterComponent<MutableTilemap>();
}

// Destructor is private to prevent accidental destruction
GameObjectFactory::~GameObjectFactory()
{
	// Delete all registered components
	for (unsigned i = 0; i < registeredComponents.size(); ++i)
		delete registeredComponents[i];
	registeredComponents.clear();
}
