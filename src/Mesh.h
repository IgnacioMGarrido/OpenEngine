#pragma once
#include <vector> 
#include <../glm/ext.hpp>

class Vertex;
class Shader;
class Buffer;

struct Transform
{
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

class Mesh
{
private:
    std::vector<Vertex>* m_vertices;
    std::vector<uint16_t>* m_indices;
    Buffer* m_Buffer;

    Transform m_transform;
    glm::mat4 m_modelMatrix;
public:
    Mesh(std::vector<Vertex>& _vertices, std::vector<uint16_t>& _indices);

    ~Mesh();

    void draw(const Shader& _shader) const;

private:
    void initModelMatrix();
};
