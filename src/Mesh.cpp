#include "Mesh.h"
#include "../project/Buffer.h"
#include "../project/Shader.h"
#include "../project/Vertex.h"

Mesh::Mesh(std::vector<Vertex>& _vertices, std::vector<uint16_t>& _indices)
    : m_vertices(&_vertices)
    , m_indices(&_indices)
    , m_Buffer(new Buffer(*m_vertices, *m_indices))
{
    m_transform.m_position = glm::vec3(0.f);
    m_transform.m_rotation = glm::vec3(0.f);
    m_transform.m_scale = glm::vec3(1.f);
}

Mesh::~Mesh()
{
    delete m_Buffer;
    delete m_vertices;
    delete m_indices;
}

void Mesh::draw(const Shader& _shader) const
{
    m_Buffer->draw(_shader);
}

void Mesh::initModelMatrix()
{
    m_modelMatrix = glm::translate(m_modelMatrix, m_transform.m_position);
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.m_rotation.x), glm::vec3(1, 0, 0));
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.m_rotation.y), glm::vec3(0, 1, 0));
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.m_rotation.z), glm::vec3(0, 0, 1));
   m_modelMatrix = glm::scale(m_modelMatrix, m_transform.m_scale);
}
