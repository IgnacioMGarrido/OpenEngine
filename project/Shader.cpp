#include "Shader.h"

#include <iosfwd>
#include <string>
#include <fstream>
#include <sstream>
#include "../glm/gtc/type_ptr.hpp"
#include "Vertex.h"

Shader::Shader(const char* _vertexLocation, const char* _fragmentLocation)
    : m_sVertex(readString(_vertexLocation))
    , m_sFragment(readString(_fragmentLocation))
    , m_sError(nullptr)
    , m_iPosLoc(-1)
{

    m_uVertexID = glCreateShader(GL_VERTEX_SHADER);
    m_uFragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(m_uVertexID, 1, &m_sVertex, nullptr);
    glShaderSource(m_uFragmentID, 1, &m_sFragment, nullptr);

    GLint retCode;
    glCompileShader(m_uVertexID);
    glGetShaderiv(m_uVertexID, GL_COMPILE_STATUS, &retCode);
    if (retCode == GL_FALSE)
    {
        char errorLog[1024];
        glGetShaderInfoLog(m_uVertexID, sizeof(errorLog), nullptr, errorLog);
        m_sError = errorLog;
        glDeleteShader(m_uVertexID);
        return;
    }

    glCompileShader(m_uFragmentID);
    glGetShaderiv(m_uFragmentID, GL_COMPILE_STATUS, &retCode);
    if (retCode == GL_FALSE)
    {
        char errorLog[1024];
        glGetShaderInfoLog(m_uFragmentID, sizeof(errorLog), nullptr, errorLog);
        m_sError = errorLog;
        glDeleteShader(m_uFragmentID);
        return;
    }


    m_uProgramID = glCreateProgram();
    glAttachShader(m_uProgramID, m_uVertexID);
    glAttachShader(m_uProgramID, m_uFragmentID);


    glLinkProgram(m_uProgramID);
    glGetProgramiv(m_uProgramID, GL_LINK_STATUS, &retCode);
    if (retCode == GL_FALSE)
    {
        char errorLog[1024];
        glGetProgramInfoLog(m_uProgramID, sizeof(errorLog), nullptr, errorLog);
        m_sError = errorLog;
        glDeleteProgram(m_uProgramID);
        return;
    }

    glDetachShader(m_uProgramID, m_uVertexID);
    glDetachShader(m_uProgramID, m_uFragmentID);

    m_iPosLoc = glGetAttribLocation(m_uProgramID, "vpos");
    m_iColorLoc = glGetAttribLocation(m_uProgramID, "vcolor");
    m_iTexCoordLoc = glGetAttribLocation(m_uProgramID, "vtex");

    glDeleteShader(m_uVertexID);
    glDeleteShader(m_uFragmentID);
    
 
}

Shader::~Shader()
{

    glDeleteProgram(m_uProgramID);

}

void Shader::use() const
{

    glUseProgram(m_uProgramID);
}

void Shader::setupAttributes() const
{
    //comprobar cada uno para cada atributo
    if (m_iPosLoc != -1) 
    {
        glEnableVertexAttribArray(m_iPosLoc);
        glVertexAttribPointer(m_iPosLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_vertexPosition)));
    }

    if (m_iColorLoc != -1)
    {
        glEnableVertexAttribArray(m_iColorLoc);
        glVertexAttribPointer(m_iColorLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_vertexColor)));
    }

    if (m_iTexCoordLoc != -1)
    {
        glEnableVertexAttribArray(m_iTexCoordLoc);
        glVertexAttribPointer(m_iTexCoordLoc, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_texCoords)));
    }

}

void Shader::setInt(int _loc, int _val)
{
    if (_loc != -1)
    {
        glUniform1i(_loc, _val);
    }
}

void Shader::setFloat(int _loc, float _val)
{
    if (_loc != -1)
    {
        glUniform1f(_loc, _val);
    }
}

void Shader::setVec2(int _loc, const glm::vec2& _vec)
{
    if(_loc != -1)
    {
        glUniform2f(_loc, _vec.x, _vec.y);
    }
}

void Shader::setVec3(int _loc, const glm::vec3& _vec)
{
    if (_loc != -1)
    {
        glUniform3f(_loc, _vec.x, _vec.y, _vec.z);
    }
}

void Shader::setVec4(int _loc, const glm::vec4& _vec)
{
    if (_loc != -1)
    {
        glUniform4f(_loc, _vec.x, _vec.y, _vec.z, _vec.w);
    }
}

void Shader::setMatrix(int _loc, const glm::mat4& _matrix)
{
    if (_loc != -1)
    {
        glUniformMatrix4fv(_loc, 1, GL_FALSE, glm::value_ptr(_matrix));
    }
}

const char* Shader::readString(const std::string& _sName)
{
    std::ifstream istream(_sName.c_str(), std::ios_base::binary);
    std::stringstream sstream;
    sstream << istream.rdbuf();

    std::string str = sstream.str();
    char* chr = _strdup(str.c_str());

    return chr;
}
