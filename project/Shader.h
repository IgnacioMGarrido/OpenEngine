#pragma once

//#include "../lib/glm/mat4x2.hpp"
#include "GL/glew.h"
#include "../glm/glm.hpp"
#include <cstdint>
#include <string>

//#include <xstring>

class Shader
{
private:
    GLuint m_uProgramID;
    const char* m_sVertex;
    const char* m_sFragment;
    mutable char* m_sError;

    GLuint m_uVertexID;
    GLuint m_uFragmentID;
    GLuint m_iPosLoc;
    GLuint m_iColorLoc;
    GLuint m_iTexCoordLoc;

public:
    Shader(const char* _vertexLocation, const char* _fragmentLocation);
    ~Shader();

    void use() const;
    void setupAttributes() const;

    void setInt(int _loc, int _val);
    void setFloat(int _loc, float _val);
    void setVec2(int _loc, const glm::vec2& _vec);
    void setVec3(int _loc, const glm::vec3& _vec);
    void setVec4(int _loc, const glm::vec4& _vec);
    void setMatrix(int _loc, const glm::mat4& _matrix);

    inline uint32_t getId() const { return m_uProgramID; };
    inline char* getError() const { return m_sError; };
    inline int getLocation(const char* _sName) const { return glGetUniformLocation(m_uProgramID, _sName); };
private:
    const char* readString(const std::string& filename);

};

