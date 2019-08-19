#pragma once
#include "Vertex.h"
#include <math.h>
#include <cstddef>
#include <iostream>

class spriteObj
{
private:
	float m_x, m_y, m_width, m_height, m_posu, m_posv, m_uvWidth, m_uvHeight;
	GLuint m_vboID;
	bool m_activate;
	GLubyte m_defaultColor[4];
public:
	spriteObj();
	~spriteObj();

	// get current class
	spriteObj* getThis();

	// xy coordinates
	float getVexPosx();
	float getVexPosy();
	float getVexWidth();
	float getVexHeight();

	// uv coordinates
	float getVexPosu();
	float getVexPosv();
	float getVexUVWidth();
	float getVexUVHeight();

	// utilities
	void spriteActivate();
	void spriteDeactivate();

	void setSprite(float x, float y, float width, float height, float u, float v, float uv_width, float uv_height);
	void setSpriteUV(float u, float v, float uv_width, float uv_height);
	void setSpriteColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void drawSprite();
	bool isActivate() const;
	bool isCollision(float x, float y, float width, float height) const;
private:
	void setVertexValues();
	void setVertexPointers();
};