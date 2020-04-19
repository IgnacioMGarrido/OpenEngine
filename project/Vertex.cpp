#include "Vertex.h"

Vertex::Vertex(glm::vec3 _vertexPosition, glm::vec3 _vertexColor, glm::vec2 _texCords)
    : m_vertexPosition(_vertexPosition)
    , m_vertexColor(_vertexColor)
    , m_texCoords(_texCords)
{
}
