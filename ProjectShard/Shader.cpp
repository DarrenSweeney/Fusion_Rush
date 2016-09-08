#include "Shader.h"

void Shader::LoadShader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath)
{
	std::string vertexCode, fragmentCode, geometryCode;
	std::ifstream vShaderFile, fShaderFile, gShaderFile;

	// Ensure ifstream can thorw exceptions
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	if (geometryPath)
		gShaderFile.exceptions(std::ifstream::badbit);

	// Check if the file exsists
	std::ifstream infile(vertexPath);
	if (!infile.good())
	{
		std::cout << "ERROR::SHADER::VERTEX_SHADER_NOT_FOUND" << std::endl;
		return;
	}
	infile = std::ifstream(fragmentPath);
	if (!infile.good())
	{
		std::cout << "ERROR::SHADER::FRAGMENT_SHADER_NOT_FOUND" << std::endl;
		return;
	}
	if (geometryPath != NULL)
	{
		infile = std::ifstream(geometryPath);
		if (!infile.good())
		{
			std::cout << "ERROR::SHADER::GEOMETRY_SHADER_NOT_FOUND" << std::endl;
			return;
		}
	}

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		if (geometryPath != NULL)
			gShaderFile.open(geometryPath);

		std::stringstream vShaderStream, fShaderStream, gShaderStream;
		// Read file's buffer contents into steam
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		if (geometryPath != NULL)
			gShaderStream << gShaderFile.rdbuf();

		// Cose file handlers
		vShaderFile.close();
		fShaderFile.close();
		if (geometryPath != NULL)
			gShaderFile.close();

		// Convert stream in GLchar array
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		if (geometryPath != NULL)
			geometryCode = gShaderStream.str();

		std::cout << "SHADER_LOADED: " << vertexPath << "\n " << fragmentPath << "\n" << (geometryPath != NULL ? geometryPath : "") << std::endl;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = (geometryPath != NULL ? geometryCode.c_str() : NULL);

	Compile(vShaderCode, fShaderCode, gShaderCode != NULL ? gShaderCode : NULL);
}

void Shader::Compile(const GLchar *vShaderCode, const GLchar *fShaderCode, const GLchar *gShaderCode)
{
	GLint result;
	const int logLength = 512;
	GLchar infoLog[logLength];

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geometryShader = NULL;
	if(gShaderCode != NULL)
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

	// Compile vertex shader
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	// Check vertex shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMILATION_FAILED" << std::endl;
		return;
	}

	// Compile fragment shader
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	// Check fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMILATION_FAILED" << std::endl;
	}

	if (gShaderCode != NULL)
	{
		// Compile vertex shader
		glShaderSource(geometryShader, 1, &gShaderCode, NULL);
		glCompileShader(geometryShader);

		// Check vertex shader
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::GEOMETRY::COMILATION_FAILED" << std::endl;
		}
	}

	// Linking the shader program
	Program = glCreateProgram();
	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragmentShader);
	if(gShaderCode != NULL)
		glAttachShader(Program, geometryShader);
	glLinkProgram(Program);

	glGetProgramiv(Program, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING_FAILED" << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if(gShaderCode != NULL)
		glDeleteShader(geometryShader);
}

void Shader::Use()
{
	glUseProgram(Program);
}