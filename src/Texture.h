#pragma once
#include <memory>
#include "../lib/glm/vec2.hpp"

class Texture
{
private:
    uint32_t m_id;
    glm::ivec2 m_size;

public:
    static std::shared_ptr<Texture> load(const char* filename);
    void bind();

public:
    Texture();
};
