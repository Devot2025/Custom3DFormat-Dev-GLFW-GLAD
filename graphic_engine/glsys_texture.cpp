
#include "glsys_texture.hpp"

Basic_Gl_Texture::Basic_Gl_Texture() : tex_id{}, tex_size{} {
    glGenTextures(1, &tex_id);
}
Basic_Gl_Texture::~Basic_Gl_Texture(){
    glDeleteTextures(1, &tex_id);
}
Basic_Gl_2D_Texture::Basic_Gl_2D_Texture(){
    start_texture();
}
Glsys_Texture::Glsys_Texture(){

}

Glsys_Texture::~Glsys_Texture(){

}

Gl_2D_Texture_Manager::Gl_2D_Texture_Manager(const char * img_path){
    Basic_Image_Loader image_loader(img_path);
    upload_text_data<GLubyte, GL_RGBA>(image_loader.width, image_loader.height, image_loader.get_img_buffer());
    start_mipmap();
}
Gl_2D_Texture_Manager::Gl_2D_Texture_Manager(){
    
}