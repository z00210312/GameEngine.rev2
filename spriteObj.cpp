#include "spriteObj.h"

spriteObj::spriteObj()
{
	m_defaultColor[0] = 255;
	m_defaultColor[1] = 255;
	m_defaultColor[2] = 255;
	m_defaultColor[3] = 255;
	m_activate = true;
}

spriteObj::~spriteObj()
{
	glDeleteBuffers(1, &m_vboID);
	m_vboID = 0;
}

spriteObj * spriteObj::getThis()
{
	return this;
}

float spriteObj::getVexPosx()
{
	return m_x;
}

float spriteObj::getVexPosy()
{
	return m_y;
}

float spriteObj::getVexWidth()
{
	return m_width;
}

float spriteObj::getVexHeight()
{
	return m_height;
}

float spriteObj::getVexPosu()
{
	return m_posu;
}

float spriteObj::getVexPosv()
{
	return m_posv;
}

float spriteObj::getVexUVWidth()
{
	return m_uvWidth;
}

float spriteObj::getVexUVHeight()
{
	return m_uvHeight;
}

void spriteObj::spriteActivate()
{
	m_activate = true;
}

void spriteObj::spriteDeactivate()
{
	m_activate = false;
}

void spriteObj::setSprite(float x, float y, float width, float height, float u, float v, float uv_width, float uv_height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_posu = u;
	m_posv = v;
	m_uvWidth = uv_width;
	m_uvHeight = uv_height;

	if (m_vboID == 0) {
		glGenBuffers(1, &m_vboID);
	}
}

void spriteObj::setSpriteUV(float u, float v, float uv_width, float uv_height)
{
	m_posu = u;
	m_posv = v;
	m_uvWidth = uv_width;
	m_uvHeight = uv_height;
}

void spriteObj::setSpriteColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	this->m_defaultColor[0] = r;
	this->m_defaultColor[1] = g;
	this->m_defaultColor[2] = b;
	this->m_defaultColor[3] = a;
}

void spriteObj::drawSprite()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	setVertexValues();
	setVertexPointers();

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool spriteObj::isActivate() const
{
	return m_activate;
}

bool spriteObj::isCollision(float x, float y, float width, float height) const
{
	if (std::floor((x + width) * 1000 + 0.1) / 1000 > std::floor(m_x * 1000 + 0.1) / 1000 && std::floor((x) * 1000 + 0.1) / 1000 < std::floor((m_x + m_width) * 1000 + 0.1) / 1000) {
		/////////////
		// if y is in the range
		/////////////
		if (std::floor((y + height) * 1000 + 0.1) / 1000 > std::floor(m_y * 1000 + 0.1) / 1000 && std::floor((y) * 1000 + 0.1) / 1000 < std::floor((m_y + m_height) * 1000 + 0.1) / 1000) {
			/*
			std::cout << "isCollision()" << std::endl;
			std::cout << "--------------------------" << std::endl;
			*/
			//it->~spriteObj();
			//numSprite.erase(it);
			return true;
		}
	}
	return false;
}

void spriteObj::setVertexValues()
{
	Vertex vertexData[4];
	//Top-left
	vertexData[0].position.x = m_x;
	vertexData[0].position.y = m_y + m_height;
	vertexData[0].uv.u = m_posu;
	vertexData[0].uv.v = m_posv;
	vertexData[0].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };
	//Top-right
	vertexData[1].position.x = m_x + m_width;
	vertexData[1].position.y = m_y + m_height;
	vertexData[1].uv.u = m_uvWidth;
	vertexData[1].uv.v = m_posv;
	vertexData[1].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };
	//Bottom-right
	vertexData[2].position.x = m_x + m_width;
	vertexData[2].position.y = m_y;
	vertexData[2].uv.u = m_uvWidth;
	vertexData[2].uv.v = m_uvHeight;
	vertexData[2].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };
	//Bottom-left
	vertexData[3].position.x = m_x;
	vertexData[3].position.y = m_y;
	vertexData[3].uv.u = m_posu;
	vertexData[3].uv.v = m_uvHeight;
	vertexData[3].color = { m_defaultColor[0],m_defaultColor[1],m_defaultColor[2],m_defaultColor[3] };

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

void spriteObj::setVertexPointers()
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
}
