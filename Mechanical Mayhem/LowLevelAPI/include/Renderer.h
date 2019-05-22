//------------------------------------------------------------------------------
//
// File Name:	Renderer.h
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

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class PostEffect;
class ShaderProgram;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Renderer
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Ctors/Dtors
	Renderer();
	~Renderer();

	// Methods
	void Init();
	void FrameStart();
	void FrameEnd();

	// Get the default shader (usually for the purposes of setting uniforms)
	const ShaderProgram& GetDefaultShader() const;

	// Sets the dimensions that the renderer will use to construct its framebuffer.
	void SetDimensions(unsigned width, unsigned height);

	// Adds a post-processing effect. Effects are applied sequentially,
	// starting with the first that was added.
	// Params:
	//   effect =  The effect to add to the current list of effects.
	void PushEffect(PostEffect& effect);

	// Removes the most recently added effect.
	void PopEffect();

	// Removes a specific effect.
	void RemoveEffect(const PostEffect& effect);

	// Removes all effects that are currently active.
	void ClearEffects();

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	void ApplyEffects();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Shader indices
	ShaderProgram* defaultShader;
	ShaderProgram* bufferToScreenShader;

	// Viewport dimensions
	unsigned width;
	unsigned height;

	// Framebuffer Data
	unsigned frameBuffer;
	unsigned quadVertexBuffer;
	unsigned quadVertexArray;
	unsigned diffuseTexture0;
	unsigned diffuseTexture1;

	// Post-processing effects
	std::vector<PostEffect*> effects;
};

//------------------------------------------------------------------------------
