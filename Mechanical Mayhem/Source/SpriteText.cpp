//------------------------------------------------------------------------------
//
// File Name:	SpriteText.cpp
// Author(s):	David Cohen (david.cohen)
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

#include "SpriteText.h"

#include <Color.h>
#include <Vector2D.h>

// Systems
#include <Mesh.h>
#include <MeshFactory.h>
#include <SpriteSource.h>
#include <Graphics.h>
#include <GameObject.h>
#include <Texture.h>

// Components
#include <Transform.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a new sprite object.
SpriteText::SpriteText(std::string text) : Component("SpriteText"), text(text), columns(12), rows(8),
horizontalAlignment(Alignment::LEFT), verticalAlignment(Alignment::TOP), texture(nullptr), spriteSource(nullptr),
mesh(nullptr), color(Colors::White)
{

}

SpriteText::~SpriteText()
{
	delete mesh;
	delete spriteSource;
	delete texture;
}

Component* SpriteText::Clone() const
{
	return new SpriteText(*this);
}

void SpriteText::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));

	// Load the font atlas texture.
	texture = Texture::CreateTextureFromFile("Code New Roman.png");

	// Setup the font atlas sprite source.
	spriteSource = new SpriteSource(columns, rows, texture);

	// Create a new quad mesh for the sprite.
	mesh = MeshFactory::GetInstance().CreateQuadMesh(Vector2D(1.0f / columns, 1.0f / rows), Vector2D(0.5f, 0.5f));
}

// Draw a sprite (Sprite can be textured or untextured).
void SpriteText::Draw()
{
	// Exit if there is no mesh or sprite source.
	if (mesh == nullptr || spriteSource == nullptr)
	{
		return;
	}

	float rotation = transform->GetRotation();
	Vector2D scale = transform->GetScale();

	Vector2D right = Vector2D::FromAngleRadians(rotation);
	Vector2D down = Vector2D::FromAngleRadians(rotation - M_PI_F / 2.0f);

	// The position of the current character.
	Vector2D pos = Vector2D(down.x * scale.x, down.y * scale.y) * 0.25f + Vector2D(right.x * scale.x, right.y * scale.y) * 0.1875;

	Vector2D offset = Vector2D(0.0f, 0.0f);

	// Set the offset of the text based on the alignment properties (do nothing for LEFT/TOP because that is the default alignment with no offset).

	switch (horizontalAlignment)
	{
	case Alignment::CENTER:
		offset.x -= GetWidth() / 2.0f;
		break;
	case Alignment::RIGHT:
		offset.x -= GetWidth();
		break;
	}

	switch (verticalAlignment)
	{
	case Alignment::CENTER:
		offset.y -= GetHeight() / 2.0f;
		break;
	case Alignment::BOTTOM:
		offset.y -= GetHeight();
		break;
	}

	Graphics::GetInstance().SetSpriteBlendColor(color);

	int newlines = 0;
	for (auto iter = text.begin(); iter < text.end(); iter++)
	{
		// When a newline is encountered, move the sprite back on the X axis and move down 1 character on the Y axis (accounts for scale & rotation).
		if (*iter == '\n')
		{
			pos = Vector2D(down.x * scale.x, down.y * scale.y) * 0.5f * (++newlines + 0.5f) + Vector2D(right.x * scale.x, right.y * scale.y) * 0.1875;
			continue;
		}

		// Get the UV of the current character and set the current texture.
		Vector2D uv;
		spriteSource->GetUV(*iter - 32, uv);
		spriteSource->GetTexture()->Use(uv);

		// Set the translation & scale for the mesh.
		Graphics::GetInstance().SetTransform(transform->GetTranslation() + pos + offset.x * right + offset.y * down, scale, rotation);

		// Draw the mesh.
		mesh->Draw();

		// Move the sprite position 1 character over on the X axis.
		pos += Vector2D(right.x * scale.x, right.y * scale.y) * 0.3125f;
	}

	Graphics::GetInstance().SetSpriteBlendColor(Colors::White);
}

// Sets the string to display.
// Params:
//   text = New string to display.
void SpriteText::SetText(const std::string& text_)
{
	text = text_;
}

// Get the current string being desplayed.
std::string SpriteText::GetText() const
{
	return text;
}

// Set a sprite's transparency (between 0.0f and 1.0f).
// Params:
//   alpha = New value for the sprite's 'alpha' value.
void SpriteText::SetAlpha(float alpha)
{
	color.a = alpha;
}

// Get the current value for a sprite's transparency.
float SpriteText::GetAlpha() const
{
	return color.a;
}

// Set the blend color for the specified sprite.
// Params:
//	 color = A new color for the sprite.
void SpriteText::SetColor(Color color_)
{
	color = color_;
}

// Retrieves the blend color for the sprite.
const Color& SpriteText::GetColor() const
{
	return color;
}

// Gets the current horizontal alignment.
SpriteText::Alignment SpriteText::GetHorizontalAlignment() const
{
	return horizontalAlignment;
}

// Sets the current horizontal alignment.
void SpriteText::SetHorizontalAlignment(Alignment alignment)
{
	horizontalAlignment = alignment;
}

// Gets the current vertical alignment.
SpriteText::Alignment SpriteText::GetVerticalAlignment() const
{
	return verticalAlignment;
}

// Sets the current vertical alignment.
void SpriteText::SetVerticalAlignment(Alignment alignment)
{
	verticalAlignment = alignment;
}

// Calculates the width of the current text when displayed.
// Returns:
//   The width of the current text.
float SpriteText::GetWidth() const
{
	Vector2D scale = transform->GetScale();

	// The current line's width.
	float width = 0.0f;
	// The largest width found.
	float maxWidth = width;

	for (auto iter = text.begin(); iter < text.end(); iter++)
	{
		// When a newline is encountered, reset the current line's width to 0.
		if (*iter == '\n')
		{
			width = 0.0f;
			continue;
		}

		// Increase the current line's width by the width of a single character.
		width += scale.x * 0.3125f;

		// If the current line's width is bigger than the current largest width, overwrite it.
		maxWidth = max(maxWidth, width);
	}

	return maxWidth;
}

// Calculates the height of the current text when displayed.
// Returns:
//   The height of the current text.
float SpriteText::GetHeight() const
{
	Vector2D scale = transform->GetScale();

	// Count how many newlines are in the text.
	int newlines = 0;
	for (auto iter = text.begin(); iter < text.end(); iter++)
	{
		if (*iter == '\n')
		{
			++newlines;
		}
	}

	// Return the number of lines * the height of a single character.
	return (newlines + 1) * scale.y * 0.5f;
}

//------------------------------------------------------------------------------
