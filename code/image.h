#ifndef _IMAGE_H_
#define _IMAGE_H_

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace image
{    
    struct image_info
    {
        int Width;
        int Height;
        int NumberChannels;
        char* FilePath;
        unsigned int TextureID;
        
        unsigned char* Data;
    };
    
    static image_info Load(const char* Path);
};

#endif