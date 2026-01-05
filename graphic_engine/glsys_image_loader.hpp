
#ifndef _GLSYS_IMAGE_LOADER_HPP_
#define _GLSYS_IMAGE_LOADER_HPP_

//#include <stb_link_helper.h>
#include <stb_image.h>
#include <cpp_standard_lib.hpp>
#include "macro_inf.hint"

enum class Image_Api_Type{
    EC_IMAGE_API_STBI,
    EC_IMAGE_API_SCI,
};

class Basic_Image_Loader{
    public:
    
    Basic_Image_Loader(const char * img_path);
    ~Basic_Image_Loader();
    inline const uint8_t * get_img_buffer(){return img_buffer;}
    int width;
    int height;
    private:
    uint8_t * img_buffer = nullptr;
};

class Basic_GL_Image_Loaders{
    public:
    Basic_GL_Image_Loaders(const char * img_path, Image_Api_Type img_api_type);
};
#endif // _GLSYS_IMAGE_LOADER_HPP_