#pragma once
#include "../glm/glm.hpp"
class Vertex
{
public:
    glm::vec3 m_vertexPosition;
    glm::vec3 m_vertexColor;

public:
    Vertex(glm::vec3 _vertexPosition, glm::vec3 _vertexColor);
};
