//------------------------------------------------------------------------------
//
// File Name:	Input.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Beta Engine
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Vector2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Input
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Initialize keyboard and cursor data to clean state
	void Initialize();

	// Update keyboard and cursor data
	void Update();

	// Test if key was down before and is still down
	bool CheckHeld(unsigned key) const;
	// Test if key was not down before but is down now
	bool CheckTriggered(unsigned key) const;
	// Test if key was down before but is not down now
	bool CheckReleased(unsigned key) const;

	// Test if key is currently down 
	bool IsKeyDown(unsigned key) const;
	// Test if key was down a number of frames before the current frame
	bool WasKeyDown(unsigned key, unsigned framesBefore = 1) const;

	// Get the current location of the mouse in screen coordinates
	Vector2D GetCursorPosition() const;
	// Sets the current location of the cursor this frame.
	void SetCursorPosition(const Vector2D& position);

	// Get the amount that the mouse has scrolled this frame
	float GetMouseScrollAmount() const;
	// Set the scroll amount that occurred this frame.
	void SetMouseScrollAmount(float amount);

	// Set the number of frames to store past the current frame.
	// Params:
	//   size = Number of previous frames to store (should be > 1).
	void SetBufferSize(unsigned size);

	// Retrieve the instance of the Input singleton.
	static Input& GetInstance();

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Constructor/destructor private to prevent accidental instantiation/destruction.
	Input();
	~Input();

	// Disable copy constructor and assignment operator
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	// Helper functions
	void UpdateKeyboard();
	void UpdateMouse();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Mouse information
	Vector2D mousePosition;
	long cursorPosX;
	long cursorPosY;

	long cursorDeltaX;
	long cursorDeltaY;

	float scrollAmountCurrent;
	float scrollAmountPrevious;

	// Keys data from current and previous frames.
	static const unsigned inputKeyNum;
	// Current frame is first vector, previous frames are subsequent vectors
	std::vector<std::vector<unsigned char>> inputKeyBuffer;
};

//------------------------------------------------------------------------------
