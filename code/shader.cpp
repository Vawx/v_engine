#include "shader.h"

namespace shader
{
    static shader_info Make(bool bOrtho)
    {        
        shader_info Result = {};
        Result.VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(Result.VertexShader, 1, bOrtho ? &DEFAULT_VERTEX_ORTHO : &DEFAULT_VERTEX, nullptr);
        glCompileShader(Result.VertexShader);
        
        Result.FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(Result.FragmentShader, 1, bOrtho ? &DEFAULT_FRAGMENT_ORTHO : &DEFAULT_FRAGMENT, nullptr);
        glCompileShader(Result.FragmentShader);
        
        Result.ShaderID = glCreateProgram();
        glAttachShader(Result.ShaderID, Result.VertexShader);
        glAttachShader(Result.ShaderID, Result.FragmentShader);
        glLinkProgram(Result.ShaderID);
        
        glDeleteShader(Result.VertexShader);
        glDeleteShader(Result.FragmentShader);
        return Result;
    }
};