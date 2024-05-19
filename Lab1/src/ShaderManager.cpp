#include "ShaderManager.h"

ShaderManager::~ShaderManager()
{
	for (GLuint& shader : shaders)
	{
		glDetachShader(m_program, shader);
		glDeleteShader(shader);
	}

	glDeleteProgram(m_program);
}

void ShaderManager::InitShaders(const std::string& filename)
{
	m_program = glCreateProgram();

	shaders[0] = CreateShader(LoadShader("..\\res\\shaders\\" + filename + ".vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader("..\\res\\shaders\\" + filename + ".frag"), GL_FRAGMENT_SHADER);
	
	for (GLuint& shader : shaders)
	{
		glAttachShader(m_program, shader);
	}

	glBindAttribLocation(m_program, 0, "vertexPos");
	glBindAttribLocation(m_program, 1, "vertexTexCoord");
	glBindAttribLocation(m_program, 2, "vertexNormals");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	GetUniformLocation("u_transform");
	GetUniformLocation("u_lighting");
}

GLuint ShaderManager::CreateShader(const std::string& shaderSrc, GLuint shaderType)
{
	GLuint shaderID = glCreateShader(shaderType);

	if (shaderID == 0)
	{
		std::cerr << "Error shader type creation failed " << shaderType << std::endl;
	}

	const GLchar* source[1] = { nullptr };
	source[0] = shaderSrc.c_str();

	GLint lengths[1] = { 0 };
	lengths[0] = shaderSrc.length();

	glShaderSource(shaderID, 1, &source[0], &lengths[0]);
	glCompileShader(shaderID);

	CheckShaderError(shaderID, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shaderID;
}

// read shaders from a text file
std::string ShaderManager::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}

	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void ShaderManager::CheckShaderError(const GLuint shader, const GLuint flag, const bool programValid, const std::string& errorMessage)
{
	GLint result = 0;
	GLchar error[1024] = { 0 };

	if (programValid)
	{
		glGetProgramiv(shader, flag, &result);
	}

	else
	{
		glGetShaderiv(shader, flag, &result);
	}

	if (result == GL_FALSE)
	{
		if (programValid)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}

		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << " : " << error << "'" << std::endl;
	}
}

// checks uniform locations hashmap to see if uniform location has 
// already been retrieved to prevent multiple calls to the GPU
const GLint ShaderManager::GetUniformLocation(const std::string& name)
{
	// if uniform exists
	if (u_locations.find(name) != u_locations.end())
	{
		return u_locations[name];
	}

	// if uniform doesn't exist, then create uniform
	GLint location = glGetUniformLocation(m_program, name.c_str());
	u_locations[name] = location;
	return location;
}

void ShaderManager::Bind()
{
	glUseProgram(m_program);
}

void ShaderManager::UpdateUniforms(const glm::mat4& objTransform, const Camera& camera)
{
	mvp = camera.GetMVPMatrix() * objTransform;
	glUniformMatrix4fv(u_locations["u_transform"], 1, GLU_FALSE, &mvp[0][0]);

	// light pos is the camera
	glm::vec4 lightPosVP = (objTransform * glm::vec4(camera.GetCameraPos(), 1.0f) * glm::vec4(-1.0f, -1.0f, 1.0f, -1.0f));
	glUniform3f(u_locations["u_lighting"], lightPosVP.x, lightPosVP.y, lightPosVP.z);
}