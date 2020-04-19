#pragma once
#include <cstdint>
#include "Vertex.h"
#include <array>
#include <vector>
class Shader;
class Buffer
{
    std::array<uint32_t, 2> m_ids{};
    std::vector<Vertex> &m_vertices;

    std::vector<uint16_t> m_indices{};
    size_t m_numIndices;

public:
    Buffer(std::vector<Vertex>& _vertices, std::vector<uint16_t> _indices);
    ~Buffer();
    void draw(const Shader& _shader) const;
};

