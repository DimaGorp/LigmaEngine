#pragma once
#include <vector>
#include <glad/glad.h>
class Shader{
    private:
        unsigned int um_id;
        unsigned int um_programID;
        static std::vector<unsigned int&> shaders;
        const char* m_shaderProgram;
    public:
    enum ESHADERTYPE{
        VERTEX  =  GL_VERTEX_SHADER,
        FRAGMENT  =GL_FRAGMENT_SHADER
    };
    Shader(unsigned int& id, const char * shaderProgram,const ESHADERTYPE& type);

    bool GenerateProgram();

};