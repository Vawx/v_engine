#ifndef _SHADER_H_
#define _SHADER_H_

namespace shader
{    
    static const char* DEFAULT_VERTEX = "#version 330 core \n"
        "layout (location = 0) in vec3 aPos; \n"
        "layout (location = 1) in vec2 aTexCoord; \n"
        "out vec2 TexCoord; \n"
        "uniform mat4 transform; \n"
        "uniform mat4 view; \n"
        "uniform mat4 projection; \n"
        "void main() \n"
        "{ \n"
        "    gl_Position = projection * view * transform * vec4(aPos, 1.0); \n"
        "    TexCoord = aTexCoord; \n"
        "}";
    
    static const char* DEFAULT_FRAGMENT = "#version 330 core \n"
        "out vec4 FragColor; \n"
        "in vec2 TexCoord; \n"
        "uniform sampler2D ourTexture; \n"
        "void main() \n"
        "{ \n"
        "    FragColor = texture(ourTexture, TexCoord); \n"
        "}";
    
    static const char* DEFAULT_VERTEX_ORTHO = "#version 330 core \n"
        "layout (location = 0) in vec3 aPos; \n"
        "layout (location = 1) in vec2 aTexCoord; \n"
        "out vec2 TexCoord; \n"
        "uniform mat4 transform; \n"
        "void main() \n"
        "{ \n"
        "    gl_Position = transform * vec4(aPos, 1.0); \n"
        "    TexCoord = aTexCoord; \n"
        "}";
    
    static const char* DEFAULT_FRAGMENT_ORTHO = "#version 330 core \n"
        "out vec4 FragColor; \n"
        "in vec2 TexCoord; \n"
        "uniform sampler2D ourTexture; \n"
        "void main() \n"
        "{ \n"
        "    FragColor = texture(ourTexture, TexCoord); \n"
        "}";
    
    struct shader_info
    {
        unsigned int ShaderID;
        unsigned int VertexShader;
        unsigned int FragmentShader;
    };
    
    static shader_info Make(bool bOrtho);  
};

#endif