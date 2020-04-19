#include "Transform.h"

Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
    : m_position(_position)
    , m_rotation(_rotation)
    , m_scale(_scale)
{
}

Transform::Transform(const Transform& _transform)
    : m_position(_transform.m_position)
    , m_rotation(_transform.m_rotation)
    , m_scale(_transform.m_scale)
{
}
