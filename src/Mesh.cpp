#include "Mesh.h"
#include "../project/Buffer.h"
#include "../project/Shader.h"
#include "Primitives.h"
#include "Material.h"

Mesh::Mesh(Primitive& _primitive, const Transform& _transform, Material* _material)
    : m_transform(_transform)
    , m_material(_material)
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

    updateModelMatrix();
}

Mesh::~Mesh()
{
    //delete m_Buffer;
    //delete m_indices;
    //delete m_vertices;
}

void Mesh::draw(std::shared_ptr<Shader> _shader) const
{
    m_material->prepare();
    m_Buffer->draw(_shader);
}

void Mesh::translate(glm::vec3 _position)
{
   // m_modelMatrix = glm::translate(m_modelMatrix, _position);
    m_transform.setPosition(_position);
}

void Mesh::rotate(float _degrees, glm::vec3 _axis)
{
   // m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(_degrees), _axis);
    m_transform.setRotation(_degrees * _axis);
}

void Mesh::scale(glm::vec3 _scale)
{
    m_transform.setScale(m_transform.getScale() + _scale);
   // m_modelMatrix = glm::scale(m_modelMatrix, _scale);
}

void Mesh::updateModelMatrix()
{
   m_modelMatrix = glm::translate(glm::mat4(1.f), m_transform.getPosition());
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.getRotation().x), glm::vec3(1, 0, 0));
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.getRotation().y), glm::vec3(0, 1, 0));
   m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_transform.getRotation().z), glm::vec3(0, 0, 1));
   m_modelMatrix = glm::scale(m_modelMatrix, m_transform.getScale());
}

void Mesh::updateUniforms(Shader& _shader, glm::mat4 _projection, glm::mat4 _view)
{
    updateModelMatrix();
    _shader.setMatrix(_shader.getLocation("mvp"), _projection * _view * getModelMatrix());
}

