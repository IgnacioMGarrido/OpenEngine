#pragma once
#include <vector> 
#include <../glm/ext.hpp>
#include "Transform.h"
#include <memory>

class Vertex;
class Shader;
class Buffer;
class Primitive;
class Material;
class Mesh
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<uint16_t> m_indices;
    Buffer* m_Buffer;
    Transform m_transform;
    Material* m_material;
    glm::mat4 m_modelMatrix;
public:
    Mesh(Primitive& _primitive,const Transform& _transform = Transform(), Material* _material = nullptr);

    ~Mesh();

    void draw(std::shared_ptr<Shader> _shader) const;

    void translate(glm::vec3 _position);
    void rotate(float _degrees, glm::vec3 _axis);
    void scale(glm::vec3 _scale);

    void updateUniforms(Shader& _shader, glm::mat4 _projection, glm::mat4 _view);

    //Accessors
    inline glm::mat4& getModelMatrix() { return m_modelMatrix; };

    inline glm::vec3 getPosition() const { return m_transform.getPosition(); };
    inline glm::vec3 getRotation() const { return m_transform.getRotation(); };
    inline glm::vec3 getScale() const { return m_transform.getScale(); };

    inline const Material& getMaterial() const { return *m_material; };
    inline Material& getMaterial() { return *m_material; };

    inline void setPosition(glm::vec3 _position) { m_transform.setPosition(_position); };
    inline void setRotation(glm::vec3 _rotation) { m_transform.setRotation(_rotation); };
    inline void setScale(glm::vec3 _scale) { m_transform.setScale(_scale); };
private:
    void updateModelMatrix();
};
