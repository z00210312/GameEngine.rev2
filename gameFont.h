#pragma once
#include <iostream>
#include <map>
#include "GLSL.h"

#include <ft2build.h>
#include FT_FREETYPE_H
class gameFont
{
private:
	// Properties
	float m_width, m_height;

	// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		GLuint m_textureID;   // ID handle of the glyph texture
		glm::ivec2 m_size;    // Size of glyph
		glm::ivec2 m_bearing;  // Offset from baseline to left/top of glyph
		GLuint m_advance;    // Horizontal offset to advance to next glyph
	};

	std::map<GLchar, Character> m_characters;
	GLuint _VAO, _VBO;
	GLSL* m_fontshader;
public:
	gameFont(float _width, float _height);
	~gameFont();

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};

