#include "ShaderManager.h"

//Shader::Shader(const std::string& filename)
//	: program(0), shaders{ NUM_SHADERS }, uniforms{ NUM_UNIFORMS }
//{
//	program = glCreateProgram();
//
//	shaders[0] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER);
//	shaders[1] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER);
//	
//	for (GLuint& shader : shaders)
//	{
//		glAttachShader(program, shader);
//	}
//
//	glBindAttribLocation(program, 0, "position");
//	glBindAttribLocation(program, 1, "texCoord");
//	
//
//	glLinkProgram(program); // creates exe that will run on the GPU shaders
//	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed");
//
//	glValidateProgram(program); // check the entire program is valid
//	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");
//
//	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
//}

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
	m_program = glCreateProgram(); // maybe move to constructor once hash tables are sorted

	shaders[0] = CreateShader(LoadShader("..\\res\\shaders\\" + filename + ".vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader("..\\res\\shaders\\" + filename + ".frag"), GL_FRAGMENT_SHADER);
	
	for (GLuint& shader : shaders)
	{
		glAttachShader(m_program, shader);
	}

	glBindAttribLocation(m_program, 0, "vertexPos");
	glBindAttribLocation(m_program, 1, "vertexTexCoord");
	glBindAttribLocation(m_program, 2, "vertexNormals");

	glLinkProgram(m_program); // creates exe that will run on the GPU shaders
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	glValidateProgram(m_program); // check the entire program is valid
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	GetUniformLocation("u_transform");
	GetUniformLocation("u_lighting");
}

GLuint ShaderManager::CreateShader(const std::string& shaderSrc, GLuint shaderType)
{
	GLuint shaderID = glCreateShader(shaderType); //create shader based on specified type

	if (shaderID == 0) //if == 0 shader not created
		std::cerr << "Error shader type creation failed " << shaderType << std::endl;

	const GLchar* source[1] = { nullptr }; //convert strings into list of c-strings    DEPENDANT ON FUTURE WORK COULD MAKE NOT ARRAYS if so make string source in glShaderSource a ref
	source[0] = shaderSrc.c_str();

	GLint lengths[1] = { 0 }; // const? 
	lengths[0] = shaderSrc.length();

	glShaderSource(shaderID, 1, &source[0], &lengths[0]); //send source code to opengl
	glCompileShader(shaderID); //get open gl to compile shader code

	CheckShaderError(shaderID, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

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

	GLint location = glGetUniformLocation(m_program, name.c_str());

	u_locations[name] = location;

	return location;
}

void ShaderManager::Bind()
{
	glUseProgram(m_program);
}

void ShaderManager::SetLightPos(const Camera& camera)
{
	lightPos = glm::vec4(camera.GetCameraPos(), 1.0f);
}

// update light uniform with lights position to object
// made x & y axes negative so light pos looks like it's coming from the camera
void ShaderManager::UpdateLight(const glm::mat4& objTransform, const Camera& camera)        // could use camera instead of 'lightPos', could move to Update below 
{
	glm::vec4 lightPosVP = (objTransform * lightPos * glm::vec4(-1.0f, -1.0f, 1.0f, -1.0f));

	glUniform3f(u_locations["u_lighting"], lightPosVP.x, lightPosVP.y, lightPosVP.z);
}

void ShaderManager::Update(const glm::mat4& objTransform, const Camera& camera)
{
	mvp = camera.GetMVPMatrix() * objTransform;
	glUniformMatrix4fv(u_locations["u_transform"], 1, GLU_FALSE, &mvp[0][0]); // update transform uniform
}