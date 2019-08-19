#pragma once
#include "glew.h"
#include "glfw3.h"
#include "glm/matrix.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
class GLSL
{
private:
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentSharderID;
	int m_numAttributes;
	glm::mat4 m_inputMatrix;
public:
	GLSL();
	~GLSL();

	void setGLSL(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath, const std::string& attributeShaderFilePath);
	GLint getUniformLocation(const std::string& uniformName);

	void setOrthoMatrix(const float& left, const float& right, const float& bottom, const float& top, const float& zNear, const float& zFar);
	void setScaleMatrix(glm::vec3 scale);
	void setTranslateMatrix(const float& x, const float& y, const float& z);
	void setRotateMatrix(const float& degree, const float &x, const float &y, const float &z);
	void setColorAndEffect(const float& colorr, const float& colorg, const float& colorb, const float& colora, const float& lightx, const float& lighty, const float& lightz);

	void enable();
	void disable();

	GLuint getProgramID() { return m_programID; };
private:
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void addAttribute(const std::string& attributeName);
	void linkShaders();
	std::string getFileString(const std::string& filePath);
};

