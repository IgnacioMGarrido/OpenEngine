#pragma once
#include <memory>

class Texture;
class Shader;
class Material
{

private:
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Shader> m_shader;

public:
    Material(const std::shared_ptr<Texture> tex = nullptr,const std::shared_ptr<Shader> shader = nullptr);

    void prepare();

    inline const std::shared_ptr<Shader>& getShader() const { return m_shader; };

    inline std::shared_ptr<Shader>& getShader() { return m_shader; };

    inline void setShader(const std::shared_ptr<Shader>& shader) { m_shader = shader; };

    inline const std::shared_ptr<Texture>& getTexture() const { return m_texture; };

    inline void setTexture(const std::shared_ptr<Texture>& tex) { m_texture = tex; };

};
