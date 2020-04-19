#include "Texture.h"
#include "../lib/stb_image.h"
#include "GL/glew.h"

std::shared_ptr<Texture> Texture::load(const char* filename)
{
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();

    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(filename, &texture->m_size.x, &texture->m_size.y, nullptr, 4); //Obtenemos array de bytes con los datos de una imagen
    if (image)
    {
        glGenTextures(1, &texture->m_id); //Generacion Textura
        glBindTexture(GL_TEXTURE_2D, texture->m_id); //Activacion
        texture->bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Tipo filtrado si se dibuja mas pequeña: trilinear
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Tipo filtrado si se dibuja mas grande: interpolacion
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Coordenada mapeado horizontal fuera rango 0,1
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Coordenada mapeado vertical fuera rango 0,1

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->m_size.x, texture->m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); //Carga imagen

        glGenerateMipmap(GL_TEXTURE_2D); //Mipmap

        stbi_image_free(image); //Elimina el buffer generado por stbi_load
    }

    return texture;
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

Texture::Texture()
    : m_id(0)
    , m_size(glm::ivec2(0))
{
}
