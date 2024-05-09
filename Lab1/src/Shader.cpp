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
	for (GLuint& shader : shaders)
	{
		glDetachShader(program, shader);
		glDeleteShader(shader);
	}

	glDeleteProgram(program);
}

void Shader::SetUp(const std::string& filename)
{
	program = glCreateProgram();

	shaders[0] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER);

	for (GLuint& shader : shaders)
	{
		glAttachShader(program, shader);
	}

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");


	glLinkProgram(program); // creates exe that will run on the GPU shaders
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	glValidateProgram(program); // check the entire program is valid
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}

void Shader::Bind()
{
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);


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

// check for errors
void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}

	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
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

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1] = { nullptr }; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1] = { 0 };
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

