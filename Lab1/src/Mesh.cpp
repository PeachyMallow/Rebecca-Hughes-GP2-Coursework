#include "Mesh.h"

//Mesh::Mesh(/*Vertex* vertices, unsigned int numVertices*/)
//{
	//this->drawCount = numVertices;

	//std::vector<glm::vec3> positions; //position data
	//std::vector<glm::vec2> textCoords; //texture coordinate data

	// not been moved to Init/InitModel or LoadModel, but is it needed if using push_back? or would it be better than a for loop?
	/*positions.reserve(numVertices);
	textCoords.reserve(numVertices);*/

	// below for loop in Init()
	//stores vertex data in lists
	/*for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].pos);
		textCoords.push_back(vertices[i].textureCoord);
	}*/


	//glGenVertexArrays(1, &vertexArrayObject); // generates one vertex & sets the location to store it
	//glBindVertexArray(vertexArrayObject); // bind the vertex array object to be able to work with it
	
	//glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); // generate buffers based on our array of data
	
	//first buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); // bind the buffer specifying the type of data (array in this case) to work on the buffer in specified position
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW); // moves data to GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	//glEnableVertexAttribArray(0); // tell OpenGL how many attributes there are in our object
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // tell OpenGL how to read the above array (can be used to combine into single buffer as well - Week 3 on Collaborate)

	//second buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); 
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW);
	
	//two below not in InitModel
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	

	//glBindVertexArray(0); // unbind VAO
//}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject); // deletes the arrays
}

void Mesh::Init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	InitModel(model);

}

void Mesh::LoadModel(const std::string& fileName)
{
	IndexedModel model = OBJModel("..\\res\\models\\" + fileName + ".obj").ToIndexedModel(); // load model from file
	InitModel(model); // initialise the new model
}

void Mesh::InitModel(const IndexedModel& model)
{
	drawCount = model.indices.size();

	glGenVertexArrays(1, &vertexArrayObject); //generate a vertex array and store it in the VAO
	glBindVertexArray(vertexArrayObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	
	//MIGHT NEED TO CHANGE STRIDE BELOW CHERNO STRUCT?
	// index, size(3 floats), type, normalized, stride(amount of bytes between each vertex), 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our VAO

}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject); // bind the array
	
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, drawCount); // draw the array - draw mode, start pos, where to end draw
	
	glBindVertexArray(0); // unbind the array
}