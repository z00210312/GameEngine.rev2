#include "textureObj.h"

textureObj::textureObj()
{
	_vboID = 0;
	TexWidth = 0;
	TexHeight = 0;
}

textureObj::~textureObj()
{
	for (std::map<const char*, GLuint>::iterator it = newMap.begin(); it != newMap.end(); ++it) {
		glDeleteBuffers(1, &it->second);
	}
	newMap.clear();
	infoMap.clear();
	//glDeleteBuffers(1, &_vboID);
	_vboID = 0;
}

GLuint textureObj::getTexID()
{
	return _vboID;
}

unsigned long textureObj::getTexWidth()
{
	return TexWidth;
}

unsigned long textureObj::getTexHeight()
{
	return TexHeight;
}

GLuint textureObj::setPNGTextureID(const char * filePath)
{
	/*
	if (_vboID != 0) {
	std::cout << "setting PNG texture error" << std::endl;
	}
	*/
	std::map<const char*, GLuint>::iterator it = newMap.find(filePath);
	if (it == newMap.end()) {
		_vboID = imageloader.loadPNGTexture(filePath, TexWidth, TexHeight);
		newMap.insert(std::pair<const char*, GLuint>(filePath, _vboID));
		infoMap.insert(std::pair<GLuint, TexInfo>(_vboID, { TexWidth ,TexHeight }));
	}
	else {
		_vboID = it->second;
		TexWidth = infoMap.find(_vboID)->second.width;
		TexHeight = infoMap.find(_vboID)->second.height;
	}
	return _vboID;
}

GLuint textureObj::setDDSTextureID(const char * filePath)
{
	/*
	if (_vboID != 0) {
	std::cout << "setting PNG texture error" << std::endl;
	}
	_vboID = imageloader.loadDDSTexture("test.dds", TexWidth, TexHeight);
	*/
	std::map<const char*, GLuint>::iterator it = newMap.find(filePath);
	if (it == newMap.end()) {
		_vboID = imageloader.loadDDSTexture("test.dds", TexWidth, TexHeight);
		newMap.insert(std::pair<const char*, GLuint>(filePath, _vboID));
	}
	else {
		_vboID = it->second;
	}
	return _vboID;
}

void textureObj::enable(GLint colorProgramID, GLuint texID)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	//glBindTexture(GL_TEXTURE_2D, textureID2);
	glUniform1i(colorProgramID, 0);

	glGenerateMipmap(GL_TEXTURE_2D);
}

void textureObj::disable()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
