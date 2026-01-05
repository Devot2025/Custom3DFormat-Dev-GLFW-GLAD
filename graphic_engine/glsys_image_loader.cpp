
#include "glsys_image_loader.hpp"


Basic_Image_Loader::Basic_Image_Loader(const char * img_path){
    int channel;
    img_buffer = stbi_load(img_path, &width, &height, &channel, 4);
    if(!img_buffer){
        std::string buffer_error = GET_TEMPLATE_ERROR_STRING("Failed to loading ");
        buffer_error += img_path;
        buffer_error += " file.";
        throw std::runtime_error(buffer_error);
    }

}

Basic_Image_Loader::~Basic_Image_Loader(){
    stbi_image_free(img_buffer);
}

Basic_GL_Image_Loaders::Basic_GL_Image_Loaders(const char * img_path, Image_Api_Type img_api_type){
    if(img_api_type == Image_Api_Type::EC_IMAGE_API_SCI){
        
    }   
}