#pragma once
#include "picoPNG.h"
#include "glew.h"
#include "glfw3.h"
#include "gli/gli.hpp"
#include "gli/texture.hpp"
#include "gli/load.hpp"
#include "gli/type.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

//#include <gli/texture2d.hpp>
//#include <gli/convert.hpp>
//#include <gli/generate_mipmaps.hpp>

class imageLoader
{
public:
	imageLoader();
	~imageLoader();
private:
	void loadPNGFile(std::vector<unsigned char>& fileBuffer, const std::string& filename, std::vector<unsigned char>& imageBuffer, unsigned long &width, unsigned long &height);
public:
	GLuint loadPNGTexture(const std::string& filename, unsigned long &width, unsigned long &height);
	GLuint loadDDSTexture(const std::string& filename, unsigned long &width, unsigned long &height);
};

