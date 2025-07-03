#include "Shader/Shader.hpp"

Shader::Shader(unsigned int& id, const char * shaderProgram,const ESHADERTYPE& type){
    auto it = std::find(shaders.begin(),shaders.end(),id);
    if(*it == id){
        static_assert("COMPILE SHADER ERROR: ID ALREADY EXISTS");
    }else{
        um_id = id;
        m_shaderProgram = shaderProgram;
        glCreateShader(type);
        glShaderSource(id, 1, &shaderProgram, NULL);
        glCompileShader(id);
        shaders.push_back(id);
    }
   
}