#pragma once
#include "imageLoader.h"
#include <map>

class textureObj
{
private:
	GLuint _vboID;
	unsigned long TexWidth, TexHeight;
	imageLoader imageloader;
	std::map<const char*, GLuint> newMap;
	struct TexInfo {
		unsigned long width;
		unsigned long height;
	}texInfo;
	std::map<GLuint, TexInfo> infoMap;
public:
	textureObj();
	~textureObj();

	GLuint getTexID();
	unsigned long getTexWidth();
	unsigned long getTexHeight();

	GLuint setPNGTextureID(const char* filePath);
	GLuint setDDSTextureID(const char* filePath);

	void enable(GLint colorProgramID, GLuint texID);
	void disable();
};

