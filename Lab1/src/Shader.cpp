#include "Shader.h"

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

Shader::~Shader()
{
	for (auto itr = m_shaders.begin(); itr != m_shaders.end(); itr++) 
	{
		for (GLuint& shader : itr->second._shaders)
		{ 
			glDetachShader(m_program, shader);
			glDeleteShader(shader);
		}
	}

	glDeleteProgram(m_program);
}

void Shader::InitProgram(const std::string& filename)
{
	m_program = glCreateProgram();
}

void Shader::InitShaders(const std::string& filename)
{
	InitProgram(filename);

	m_program = glCreateProgram(); // maybe move to constructor once hash tables are sorted

	m_shaders[filename] = 
		S_VertAndFrag {{CreateShader(LoadShader("..\\res\\" + filename + ".vert"), GL_VERTEX_SHADER),
						CreateShader(LoadShader("..\\res\\" + filename + ".frag"), GL_FRAGMENT_SHADER)}};

	for (unsigned int i = 0; i <= m_shaders.size(); i++)
	{
		glAttachShader(m_program, m_shaders[filename]._shaders[i]);
	}

	//pre hash table
	//-------------
	/*shaders[0] = CreateShader(LoadShader("..\\res\\" + filename + ".vert"), GL_VERTEX_SHADER);
	//shaders[1] = CreateShader(LoadShader("..\\res\\" + filename + ".frag"), GL_FRAGMENT_SHADER);
	//for (GLuint& shader : shaders)
	{
		glAttachShader(program, shader);
	}*/
	//-------------

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

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const glm::mat4& objTransform, const Camera& camera)
{
	mvp = camera.GetViewProjection() * objTransform;
	glUniformMatrix4fv(u_locations["u_transform"], 1, GLU_FALSE, &mvp[0][0]); // update transform uniform
	
	glm::vec4 lightPosMVP = mvp * lightPos;
	glUniform3f(u_locations["u_lighting"], lightPosMVP.x, lightPosMVP.y, lightPosMVP.z);

	/*glm::mat4 model = transform.GetModelMatrix();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &model[0][0]);*/
}

// read shaders from a text file
std::string Shader::LoadShader(const std::string& fileName)
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

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool programValid, const std::string& errorMessage)
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

GLuint Shader::CreateShader(const std::string& shaderSrc, GLuint shaderType)
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

//GLint Shader::GetShader(const std::string& shaderName)
//{
//	//std::string locations = u_locations.find(name);
//	//checks if shader exists
//	//true - return shader
//	//false - create new shader
//	if (m_shaders.find(shaderName) != m_shaders.end())
//	{
//		return m_shaders[shaderName];
//	}
//
//
//	/*GLint location = glGetUniformLocation(program, m_shaders.c_str());
//	m_shaders[name] = location;
//	return location;*/
//
//
//}

// activate all the shaders in m_shaders hash table
//void Shader::ActivateShaders()
//{
//
//}

// checks uniform locations hashmap to see if uniform location has 
// already been retrieved to prevent multiple calls to the GPU
GLint Shader::GetUniformLocation(const std::string& name)
{
	//std::string locations = u_locations.find(name);

	// if uniform exists
	if(u_locations.find(name) != u_locations.end())
	{
		return u_locations[name];
	}

	GLint location = glGetUniformLocation(m_program, name.c_str());

	u_locations[name] = location;

	return location;
}

//void Shader::SetLightingUniform(const std::string& name, const Camera& camera)
//{
//	glm::mat4 mvp = camera.GetViewProjection();
//	GLfloat lightPos[] = { 0.0f, 0.0f, -1.0f };
//	//GLfloat lightPos[] = { mvp, mvp.y, mvp.z };
//	GLfloat lightPosX = 0.0f;
//	GLfloat lightPosY = 0.0f;
//	GLfloat lightPosZ = -1.0f;
//
//	glUseProgram(program);
//
//	glUniform3f(u_locations[name], lightPosX, lightPosY, lightPosZ);
//	//glUniform3fv(u_locations[name], 1, lightPos);
//
//	/*if (u_locations[name] == -1)
//	{
//		std::cout << "Uniform 'lighting' not found in shader program" << std::endl;
//	}*/
//
//	GLenum error = glGetError();
//
//	if (error != GL_NO_ERROR)
//	{
//		std::cout << "Error setting uniform value: " << error << std::endl;
//	}
//}