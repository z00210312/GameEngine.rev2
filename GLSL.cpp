#include "GLSL.h"

GLSL::GLSL() : m_programID(0), m_vertexShaderID(0), m_fragmentSharderID(0), m_numAttributes(0)
{
}

GLSL::~GLSL()
{
	if (m_programID != 0) {
		glDeleteProgram(m_programID);
	}
}

void GLSL::setGLSL(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilePath, const std::string& attributeShaderFilePath)
{
	if (m_programID != 0) {
		glDeleteProgram(m_programID);
	}
	m_programID = glCreateProgram();
	compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
	addAttribute(attributeShaderFilePath);
	linkShaders();
}

void GLSL::enable()
{
	glUseProgram(m_programID);
	for (int i = 0; i < m_numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSL::disable()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLSL::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0) {
		std::cout << "vertex error" << std::endl;
	}
	std::string tempstring = getFileString(vertexShaderFilePath);
	const char* contentsPtr = tempstring.c_str();
	glShaderSource(m_vertexShaderID, 1, &contentsPtr, nullptr);
	glCompileShader(m_vertexShaderID);

	GLint success = 0;
	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		std::cout << "vertex compile error" << std::endl;
		GLint maxLength = 0;
		glGetShaderiv(m_vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(m_vertexShaderID, maxLength, &maxLength, &errorLog[0]);

		std::cout << &(errorLog[0]) << std::endl;
		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(m_vertexShaderID); // Don't leak the shader.
		return;
	}

	m_fragmentSharderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentSharderID == 0) {
		std::cout << "fragment error" << std::endl;
	}
	tempstring = getFileString(fragmentShaderFilePath);
	contentsPtr = tempstring.c_str();
	glShaderSource(m_fragmentSharderID, 1, &contentsPtr, nullptr);
	glCompileShader(m_fragmentSharderID);

	success = 0;
	glGetShaderiv(m_fragmentSharderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		std::cout << "fragment compile error" << std::endl;
		GLint maxLength = 0;
		glGetShaderiv(m_fragmentSharderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(m_fragmentSharderID, maxLength, &maxLength, &errorLog[0]);

		std::cout << &(errorLog[0]) << std::endl;
		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(m_fragmentSharderID); // Don't leak the shader.
		return;
	}
}

//void  GLSL::addAttribute(const std::string & attributeName)
void GLSL::addAttribute(const std::string & attributeShaderFilePath)
{
	std::string tempstring = getFileString(attributeShaderFilePath);
	std::string attrString;
	std::size_t found;
	std::size_t start = 0;
	found = tempstring.find('\n', start);
	while (found != std::string::npos) {
		attrString = tempstring.substr(start, found - start);
		glBindAttribLocation(m_programID, m_numAttributes++, attrString.c_str());
		start = found + 1;
		found = tempstring.find('\n', start);
	}
	//glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

void GLSL::linkShaders()
{
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentSharderID);

	glLinkProgram(m_programID);
	glValidateProgram(m_programID);

	glDetachShader(m_programID, m_fragmentSharderID);
	glDetachShader(m_programID, m_vertexShaderID);
	glDeleteShader(m_fragmentSharderID);
	glDeleteShader(m_vertexShaderID);
}

std::string GLSL::getFileString(const std::string& filePath)
{
	std::ifstream inputfile(filePath);
	std::string fileStr = "";
	std::string line;
	while (std::getline(inputfile, line)) {
		fileStr += line + "\n";
	}
	inputfile.close();
	return fileStr;
}

GLint GLSL::getUniformLocation(const std::string & uniformName)
{
	GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		std::cout << "glUniform location Error" << std::endl;
	}
	return location;
}

void GLSL::setOrthoMatrix(const float& left, const float& right, const float& bottom, const float& top, const float& zNear, const float& zFar)
{
	glm::mat4 matrix = glm::ortho(left, right, bottom, top, zNear, zFar);
	//glm::mat4 testing = glm::ortho(-2.0f, 1.5f, -2.0f, 1.5f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "ortho"), 1, GL_FALSE, &matrix[0][0]);
}

void GLSL::setScaleMatrix(glm::vec3 scale)
{
	glm::mat4 matrix = glm::scale(glm::mat4(1.0f), scale);
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "scale"), 1, GL_FALSE, &matrix[0][0]);
}

void GLSL::setTranslateMatrix(const float& x, const float& y, const float& z)
{
	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "trans"), 1, GL_FALSE, &matrix[0][0]);
}

void GLSL::setRotateMatrix(const float & degree, const float & x, const float & y, const float & z)
{
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), degree, glm::vec3(x, y, z));
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "rotate"), 1, GL_FALSE, &matrix[0][0]);
}

void GLSL::setColorAndEffect(const float& colorr, const float& colorg, const float& colorb, const float& colora, const float& lightx, const float& lighty, const float& lightz)
{
	glUniform4f(glGetUniformLocation(m_programID, "colour"), colorr, colorg, colorb, colora);
	glUniform3f(glGetUniformLocation(m_programID, "light_pos"), lightx, lighty, lightz);
}

