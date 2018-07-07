#include "image.h"

namespace image
{
    static image_info Load(const char* Path)
    {
        image_info Result = {};
        
        glGenTextures(1, &Result.TextureID);
        glBindTexture(GL_TEXTURE_2D, Result.TextureID);
        
        // Set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // Flip vertically
        stbi_set_flip_vertically_on_load(true);  
                
        // Load Texture file into Data
        Result.Data = stbi_load(Path, &Result.Width, &Result.Height, &Result.NumberChannels, 0);
        if(!Result.Data)
        {
            SDL_Log("Failed to load image at %s. \n", Path);
        }
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Result.Width, Result.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Result.Data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        return Result;
    }
};