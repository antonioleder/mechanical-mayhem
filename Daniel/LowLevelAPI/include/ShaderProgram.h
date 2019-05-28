//------------------------------------------------------------------------------
//
// File Name:	ShaderProgram.h
// Author(s):	Jeremy Kings
// Project:		Beta Engine
// Course:		WANIC VGP2
//
// Copyright © 2018-2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <map>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Vector2D;
struct Vector3D;
class Color;
class Matrix2D;
struct Matrix3D;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ShaderProgram
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Destructor
	~ShaderProgram();

	// Set this as the active shader program
	void Use() const;

	// Set values of uniform variables
	void SetUniform(const std::string& name, int value) const;
	void SetUniform(const std::string& name, float value) const;
	void SetUniform(const std::string& name, bool value) const;
	void SetUniform(const std::string& name, const Vector2D& value) const;
	void SetUniform(const std::string& name, const Vector3D& value) const;
	void SetUniform(const std::string& name, const Color& value) const;
	void SetUniform(const std::string& name, const Matrix2D& value) const;
	void SetUniform(const std::string& name, const Matrix3D& value) const;
	
	// Set values of uniform arrays
	void SetUniform(const std::string& name, std::vector<int>& values) const;
	void SetUniform(const std::string& name, std::vector<float>& values) const;
	void SetUniform(const std::string& name, std::vector<Vector2D>& values) const;
	void SetUniform(const std::string& name, std::vector<Vector3D>& values) const;
	void SetUniform(const std::string& name, std::vector<Color>& values) const;

	// Operators
	bool operator==(const ShaderProgram& other) const;

	// Attempt to load a shader program from a file.
	// Params:
	//   vertexShaderFile = The file name of the vertex shader.
	//   pixelShaderFile = The file name of the pixel shader.
	// Returns:
	//   A valid program if successful, nullptr if unsuccessful.
	static ShaderProgram* CreateProgramFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	// The current relative path for loading shaders.
	static std::string shaderPath;

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Deleted functions
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;

	// Constructor
	// Params:
	//   id = The program id returned by OpenGL during shader creation.
	//   vertexShader = The file name of the vertex shader.
	//   pixelShader = The file name of the pixel shader.
	ShaderProgram(unsigned id, const std::string& vertexShader, const std::string& pixelShader);

	// Getting IDs of shader variables
	int GetUniformLocation(const std::string& name) const;
	int GetAttributeLocation(const std::string& name) const;

	// Loads shaders into OpenGL from strings/files
	static bool AddShaderFromString(unsigned program, const std::string& source, int glType);
	static bool AddShaderFromFile(unsigned program, const std::string& filename, int glType);

	// Reads contents from a file into a string
	static std::string ReadFromFile(const std::string& filename);

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Variables
	unsigned id;
	std::string vertexShader;
	std::string pixelShader;

	// Store locations for faster lookup
	mutable std::map<std::string, int> uniformLocations;
	mutable std::map<std::string, int> attributeLocations;
};

//------------------------------------------------------------------------------
