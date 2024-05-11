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

	glBindAttribLocation(program, 0, "v_pos");
	glBindAttribLocation(program, 1, "v_texCoord");
	glBindAttribLocation(program, 2, "v_normals");


	glLinkProgram(program); // creates exe that will run on the GPU shaders
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	glValidateProgram(program); // check the entire program is valid
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[U_TRANSFORM] = glGetUniformLocation(program, "transform");
	uniforms[U_LIGHTING] = glGetUniformLocation(program, "lighting");
}

void Shader::Bind()
{
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[U_TRANSFORM], 1, GLU_FALSE, &mvp[0][0]);
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

	if (shaderID == 0) //if == 0 shader no created
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

