#include "Shader.h"

Shader::Shader() 
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
	uniformAmbientColor = 0;
	uniformAmbientIntesity = 0;
	uniformDiffuseIntesity = 0;
	uniformDirection = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	ComplieShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* path) 
{
	std::string content;
	std::ifstream fileStream(path, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Cant open the file %s", path);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::CreateFromFile(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexString = ReadFile(vertexPath);
	std::string fragmentString = ReadFile(fragmentPath);

	if (vertexString.empty() || fragmentString.empty()) {
		return;
	}

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	ComplieShader(vertexCode, fragmentCode);
}

void Shader::ComplieShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();
	if (!shaderID)
	{
		printf("Cant Create Shader program!");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program %s \n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program %s \n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
	uniformAmbientIntesity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
	uniformDiffuseIntesity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntesity");
	uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}

GLuint Shader::GetAmbientColorLocation()
{
	return uniformAmbientColor;
}

GLuint Shader::GetAmbientIntesityLocation()
{
	return uniformAmbientIntesity;
}

GLuint Shader::GetModelLocation()
{
	return uniformModel;
}

GLuint Shader::GetDiffuseIntesityLocation()
{
	return uniformDiffuseIntesity;
}

GLuint Shader::GetDirectionLocation()
{
	return uniformDirection;
}

GLuint Shader::GetViewLocation()
{
	return uniformView;
}

void Shader::UseShader() 
{
	if (!shaderID)
	{
		printf("No Shader!\n");
		return;
	}
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLen[1];
	codeLen[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLen);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: %s \n", result, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader() 
{
	ClearShader();
}

