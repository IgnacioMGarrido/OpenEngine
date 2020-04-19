#include "Mesh.h"
#include "../project/Buffer.h"
#include "../project/Shader.h"
#include "Primitives.h"
#include "../project/Vertex.h"

Mesh::Mesh(Primitive& _primitive)
{

    for (int i = 0; i < _primitive.getNrOfVertices(); ++i)
    {
        m_vertices.push_back(_primitive.getVertices()[i]);
    }
    for (int i = 0; i < _primitive.getNrOfIndices(); ++i)
    {
        m_indices.push_back(_primitive.getIndices()[i]);
    }

    m_Buffer = new Buffer(m_vertices, m_indices);

    m_transform.m_position = glm::vec3(0.f);
    m_transform.m_rotation = glm::vec3(0.f);
    m_transform.m_scale = glm::vec3(1.f);
    initModelMatrix();
}

Mesh::~Mesh()
{
    //delete m_Buffer;
    //delete m_indices;
    //delete m_vertices;
}

void Mesh::draw(const Shader& _shader) const
{
    m_Buffer->draw(_shader);
}

void Mesh::translate(glm::vec3 _position)
{
    m_modelMatrix = glm::translate(glm::mat4(), _position);
}

void Mesh::rotate(float _degrees, glm::vec3 _axis)
{
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(_degrees), _axis);
}

void Mesh::scale(glm::vec3 _scale)
{
    m_modelMatrix = glm::scale(m_modelMatrix, _scale);
}

void Mesh::initModelMatrix()
{
   m_modelMatrix = glm::translate(m_modelMatrix, m_transform.m_position);
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.m_rotation.x), glm::vec3(1, 0, 0));
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.m_rotation.y), glm::vec3(0, 1, 0));
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.m_rotation.z), glm::vec3(0, 0, 1));
   m_modelMatrix = glm::scale(m_modelMatrix, m_transform.m_scale);
}

void Mesh::updateUniforms(Shader& _shader, glm::mat4 _projection, glm::mat4 _view)
{
    _shader.setMatrix(_shader.getLocation("mvp"), _projection * _view * getModelMatrix());
}

