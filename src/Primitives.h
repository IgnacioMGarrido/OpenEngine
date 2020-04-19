#pragma once


#include<vector>
#include "../project/Vertex.h"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

public:
	Primitive() {}
	virtual ~Primitive() {}

	//Functions
	void set(const Vertex* vertices,
		const unsigned nrOfVertices,
		const uint16_t* indices,
		const unsigned nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}

	inline Vertex* getVertices() { return this->vertices.data(); }
	inline uint16_t* getIndices() { return this->indices.data(); }
	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->indices.size(); }
};

class Triangle : public Primitive
{
public:
	Triangle()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			Vertex(glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f)),//		glm::vec3(0.f, 0.f, 1.f),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f)),//		glm::vec3(0.f, 0.f, 1.f),
			Vertex(glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f))//,		glm::vec3(0.f, 0.f, 1.f),
		};
		unsigned nrOfVertices = 3;//sizeof(vertices) / sizeof(Vertex);

		uint16_t indices[] =
		{
			0, 1, 2	//Triangle 1
		};
		unsigned int nrOfIndices = 3;//sizeof(indices) / sizeof(uint32_t);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Quad : public Primitive
{
public:
	Quad()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			Vertex(glm::vec3(-0.5f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f)),//		glm::vec3(0.f, 0.f, 1.f)),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f)),//		glm::vec3(0.f, 0.f, 1.f)),
			Vertex(glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)),//		glm::vec3(0.f, 0.f, 1.f)),
			Vertex(glm::vec3(0.5f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f))//,		glm::vec3(0.f, 0.f, 1.f))
		};
		unsigned nrOfVertices = 4;

		uint16_t indices[] =
		{
			0, 1, 2,	//Triangle 1
			0, 2, 3		//Triangle 2
		};
		unsigned int nrOfIndices = 6;

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Pyramid : public Primitive
{
public:
	Pyramid()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			//Triangle front
			Vertex(glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f)),		//glm::vec3(0.f, 0.f, 1.f),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f)),	//	glm::vec3(0.f, 0.f, 1.f),
			Vertex(glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)),//		glm::vec3(0.f, 0.f, 1.f),

			//Triangle left
			Vertex(glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),	glm::vec2(0.5f, 1.f)),//		glm::vec3(-1.f, 0.f, 0.f),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f)),//		glm::vec3(-1.f, 0.f, 0.f),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)),//		glm::vec3(-1.f, 0.f, 0.f),

			//Triangle back
			Vertex(glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f)),//		glm::vec3(0.f, 0.f, -1.f),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f)),//		glm::vec3(0.f, 0.f, -1.f),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)),//		glm::vec3(0.f, 0.f, -1.f),

			//Triangles right
			Vertex(glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f)),//		glm::vec3(1.f, 0.f, 0.f),
			Vertex(glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f)),//		glm::vec3(1.f, 0.f, 0.f),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f))//,		glm::vec3(1.f, 0.f, 0.f)
		};
		unsigned int nrOfVertices = 12;

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
};

class Cube : public Primitive
{
public:
	Cube()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f)),//		glm::vec3(0.f, 0.f, 1.f),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f)),//		glm::vec3(0.f, 0.f, 1.f),
			Vertex(glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)),//		glm::vec3(0.f, 0.f, 1.f),
			Vertex(glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f)),//		glm::vec3(0.f, 0.f, 1.f),
																											   
			Vertex(glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f)),//		glm::vec3(0.f, 0.f, -1.f),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f)),//		glm::vec3(0.f, 0.f, -1.f),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f)),//		glm::vec3(0.f, 0.f, -1.f),
			Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f))//,		glm::vec3(0.f, 0.f, -1.f)
		};
		unsigned nrOfVertices = 8;//sizeof(vertices) / sizeof(Vertex);

		uint16_t indices[] =
		{
			0, 1, 2,
			0, 2, 3,

			7, 6, 1,
			7, 1, 0,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4
		};
		unsigned int nrOfIndices = 24;//sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};