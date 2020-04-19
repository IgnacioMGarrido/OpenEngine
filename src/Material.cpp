#include "Material.h"
#include "../project/Shader.h"
#include "Texture.h"
Material::Material(const std::shared_ptr<Texture> tex, const std::shared_ptr<Shader> shader)
    : m_texture(tex)
    , m_shader(shader)
{
}

void Material::prepare()
{
    m_shader->use();

    if (m_texture)
        m_texture->bind();
    m_shader->setInt(m_shader->getLocation("texSampler"), 0);

}
