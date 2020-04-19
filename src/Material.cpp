#include "Material.h"

Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader)
    : m_texture(tex)
    , m_shader(shader)
{
}

void Material::prepare()
{
}
