#include "Buffer.h"
#include "GL/glew.h"
#include "Shader.h"

Buffer::Buffer(std::vector<Vertex> &_vertices, std::vector<uint16_t> _indices)
    : m_vertices(_vertices)
    , m_indices(_indices)
{
    glGenBuffers(2, m_ids.data());

    glBindBuffer(GL_ARRAY_BUFFER, m_ids[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ids[1]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

    m_numIndices = m_indices.size();
}

Buffer::~Buffer()
{

}

void Buffer::draw(const Shader& _shader) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ids[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ids[1]);

    _shader.setupAttributes();

    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, nullptr);
}
