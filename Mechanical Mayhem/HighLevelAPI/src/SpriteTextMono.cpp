//------------------------------------------------------------------------------
//
// File Name:	SpriteTextMono.cpp
// Author(s):	David Cohen (david.cohen)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "SpriteTextMono.h"

// Systems
#include "Transform.h"
#include <Graphics.h>
#include "Parser.h"
#include "SpriteSource.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default constructor.
SpriteTextMono::SpriteTextMono() : text(), charWidth(0.5f), horizontalAlignment(Alignment::CENTER), verticalAlignment(Alignment::CENTER)
{
}

// Constructor.
// Params:
//   text = The text to display.
SpriteTextMono::SpriteTextMono(const char* text) : text(text), charWidth(0.75f), horizontalAlignment(Alignment::CENTER), verticalAlignment(Alignment::CENTER)
{
}

// Clone the sprite, returning a dynamically allocated copy.
Component* SpriteTextMono::Clone() const
{
	return new SpriteTextMono(*this);
}

// Draw a sprite (Sprite can be textured or untextured).
void SpriteTextMono::Draw()
{
	// If there is no map, there is nothing to draw.
	if (text.c_str() == nullptr || *text.data() == '\0' || mesh == nullptr || spriteSource == nullptr)
		return;

	Vector2D translation = transform->GetTranslation();
	Vector2D scale = transform->GetScale();
	float rotation = transform->GetRotation();

	Vector2D right = Vector2D::FromAngleRadians(rotation);
	Vector2D down = Vector2D::FromAngleRadians(rotation - M_PI_F / 2.0f);

	// The position of the current character.
	Vector2D pos = 0.1875f * Vector2D(right.x * scale.x, right.y * scale.y) + 0.25f * Vector2D(down.x * scale.x, down.y * scale.y);

	Vector2D offset = Vector2D(0.0f, 0.0f);

	// Set the offset of the text based on the alignment properties (do nothing for LEFT/TOP because that is the default alignment with no offset).

	float width = GetWidth();
	float height = GetHeight();

	switch (horizontalAlignment)
	{
	case Alignment::CENTER:
		offset.x -= width / 2.0f;
		break;
	case Alignment::RIGHT:
		offset.x -= width;
		break;
	}

	switch (verticalAlignment)
	{
	case Alignment::CENTER:
		offset.y -= height / 2.0f;
		break;
	case Alignment::BOTTOM:
		offset.y -= height;
		break;
	}

	offset.y -= scale.y * 0.0625f;

	const BoundingRectangle screenWorldDimensions = Graphics::GetInstance().GetDefaultCamera().GetScreenWorldDimensions();

	// If the text would be off the screen, don't draw anything.
	if (screenWorldDimensions.bottom > translation.y + offset.y
		|| screenWorldDimensions.top < translation.y + offset.y + height
		|| screenWorldDimensions.left > translation.x + offset.x + width
		|| screenWorldDimensions.right < translation.x + offset.x)
		return;

	Graphics::GetInstance().SetSpriteBlendColor(color);

	int newlines = 0;
	for (auto it = text.begin(); it != text.end(); ++it)
	{
		// When a newline is encountered, move the sprite back on the X axis and move down 1 character on the Y axis (accounts for scale & rotation).
		if (*it == '\n')
		{
			pos = 0.1875f * Vector2D(right.x * scale.x, right.y * scale.y) + (0.25f + (++newlines * 0.5f)) * Vector2D(down.x * scale.x, down.y * scale.y);
			continue;
		}

		// Calculate the frame in the spritesheet.
		int frame = *it - 32;

		// Skip characters outside of the printable ASCII charset.
		if (frame < 0 || frame >= static_cast<int>(spriteSource->GetNumCols() * spriteSource->GetNumRows()))
			continue;

		// The frame in the font atlas is the character in the ASCII charset - 32.
		SetFrame(frame);

		// Draw the mesh.
		Sprite::Draw(pos + offset.x * right + offset.y * down);

		// Move the sprite position 1 character over on the X axis.
		pos += charWidth * 0.5f * Vector2D(right.x * scale.x, right.y * scale.y);
	}
}

// Write object data to file
// Params:
//   parser = The parser that is writing this object to a file.
void SpriteTextMono::Serialize(Parser& parser) const
{
	Sprite::Serialize(parser);

	parser.WriteVariable("charWidth", charWidth);
	unsigned uHorizontalAlignment = static_cast<unsigned>(horizontalAlignment);
	parser.WriteVariable("horizontalAlignment", uHorizontalAlignment);
	unsigned uVerticalAlignment = static_cast<unsigned>(verticalAlignment);
	parser.WriteVariable("verticalAlignment", uVerticalAlignment);
}

// Read object data from a file
// Params:
//   parser = The parser that is reading this object's data from a file.
void SpriteTextMono::Deserialize(Parser& parser)
{
	Sprite::Deserialize(parser);

	parser.ReadVariable("charWidth", charWidth);
	unsigned uHorizontalAlignment;
	parser.ReadVariable("horizontalAlignment", uHorizontalAlignment);
	horizontalAlignment = static_cast<Alignment>(uHorizontalAlignment);
	unsigned uVerticalAlignment;
	parser.ReadVariable("verticalAlignment", uVerticalAlignment);
	verticalAlignment = static_cast<Alignment>(uVerticalAlignment);
}

// Sets the string to display.
// Params:
//   text = New string to display.
void SpriteTextMono::SetText(const char* text_)
{
	text = text_;
}

// Get the current string being desplayed.
const std::string& SpriteTextMono::GetText() const
{
	return text;
}

// Gets the current horizontal alignment.
SpriteTextMono::Alignment SpriteTextMono::GetHorizontalAlignment() const
{
	return horizontalAlignment;
}

// Sets the current horizontal alignment.
void SpriteTextMono::SetHorizontalAlignment(Alignment alignment)
{
	horizontalAlignment = alignment;
}

// Gets the current vertical alignment.
SpriteTextMono::Alignment SpriteTextMono::GetVerticalAlignment() const
{
	return verticalAlignment;
}

// Sets the current vertical alignment.
void SpriteTextMono::SetVerticalAlignment(Alignment alignment)
{
	verticalAlignment = alignment;
}

// Calculates the width of the current text when displayed.
// Returns:
//   The width of the current text.
float SpriteTextMono::GetWidth() const
{
	Vector2D scale = transform->GetScale();

	// The current line's width.
	float width = 0.0f;
	// The largest width found.
	float maxWidth = width;

	for (auto it = text.begin(); it != text.end(); ++it)
	{
		// When a newline is encountered, reset the current line's width to 0.
		if (*it == '\n')
		{
			width = 0.0f;
			continue;
		}

		// Increase the current line's width by the width of a single character.
		width += charWidth * 0.5f * scale.x;

		// If the current line's width is bigger than the current largest width, overwrite it.
		maxWidth = max(maxWidth, width);
	}

	return maxWidth;
}

// Calculates the height of the current text when displayed.
// Returns:
//   The height of the current text.
float SpriteTextMono::GetHeight() const
{
	Vector2D scale = transform->GetScale();

	// Count how many newlines are in the text.
	int newlines = 0;
	for (auto it = text.begin(); it != text.end(); ++it)
	{
		if (*it == '\n')
		{
			++newlines;
		}
	}

	// Return the number of lines * the height of a single character.
	return (newlines + 1) * scale.y * 0.5f;
}

//------------------------------------------------------------------------------
