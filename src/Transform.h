#pragma once
#include "../lib/glm/detail/type_vec3.hpp"

class Transform
{
private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

public:
    Transform(glm::vec3 _position = glm::vec3(0.f), glm::vec3 _rotation = glm::vec3(0.f), glm::vec3 _scale = glm::vec3(1.f));
    Transform(const Transform& _transform);


    //Accessors
    inline glm::vec3 getPosition() const { return m_position; };
    inline glm::vec3 getRotation() const { return m_rotation; };
    inline glm::vec3 getScale() const { return m_scale; };

    inline void setPosition(glm::vec3 _position) { m_position = _position; };
    inline void setRotation(glm::vec3 _rotation) { m_rotation = _rotation; };
    inline void setScale(glm::vec3 _scale) { m_scale = _scale; };
};
