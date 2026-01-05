
#ifndef _GLSYS_TEXTURE_HPP_
#define _GLSYS_TEXTURE_HPP_
#include <glsys.hint>
#include <glsys_type.hint>
#include <glsys_image_loader.hpp>

inline void gl_texture_max_base_level(GLenum tex_target, GLenum parameter_1, GLenum paramater_2){
    glTexParameteri(tex_target, GL_TEXTURE_BASE_LEVEL, parameter_1);
    glTexParameteri(tex_target, GL_TEXTURE_MAX_LEVEL, paramater_2);
}
inline void gl_texture_wrap_methods(GLenum tex_target, GLenum parameter_1, GLenum parameter_2){
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_S, parameter_1);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_T, parameter_2);
}
inline void gl_texture_wrap_methods(GLenum tex_target, GLenum parameter_1){
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_S, parameter_1);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_T, parameter_1);
}

inline void gl_texture_filter_method(GLenum tex_target, GLenum parameter_1, GLenum parameter_2){
    glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, parameter_1);
    glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, parameter_2);
}

inline void gl_texture_filter_method(GLenum tex_target, GLenum parameter_1){
    glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, parameter_1);
    glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, parameter_1);
}
inline void gl_texture_parameter(GLenum tex_target, GLenum paramater_type, float * parameter){
    glTexParameterfv(tex_target, paramater_type, parameter);
}
inline void gl_texture_re_wrap_method(GLenum tex_target){gl_texture_wrap_methods(tex_target, GL_REPEAT);}
inline void gl_texture_clamp_border_wrap_method(GLenum tex_target){gl_texture_wrap_methods(tex_target, GL_CLAMP_TO_BORDER);}
inline void gl_texture_clamp_edge_wrap_method(GLenum tex_target){gl_texture_wrap_methods(tex_target, GL_CLAMP_TO_EDGE);}
inline void gl_texture_mipmap_liner_filter_method(GLenum tex_target){gl_texture_filter_method(tex_target, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);}
inline void gl_texture_liner_filter_method(GLenum tex_target){gl_texture_filter_method(tex_target, GL_LINEAR);}
inline void gl_texture_near_filter_method(GLenum tex_target){gl_texture_filter_method(tex_target, GL_NEAREST);}
inline void gl_texture_mex_base_method(GLenum tex_target){gl_texture_max_base_level(tex_target, 0, 0);}
inline void unpack_pixel_store(GLint i){glPixelStorei(GL_UNPACK_ALIGNMENT, i);}
template <GLenum Tex_Target>
inline void gl_start_mipmap(){
    glGenerateMipmap(Tex_Target);
}
class Basic_Gl_Texture{
    protected:
	GLuint tex_id;
	public:
	int tex_size;
	Basic_Gl_Texture();
	~Basic_Gl_Texture();
	virtual inline void start_texture(){}
    virtual inline void wrap_texture_method(GLenum param_1 = GL_REPEAT){}
    virtual inline void filter_texture_method(){}
    virtual inline void start_mipmap(){}
    virtual inline void upload_text_data(GLint tx, GLint ty, GLint tw, GLint th, const void * tex_buffer){}
    inline void active_texture(GLenum active_tex_num){glActiveTexture(active_tex_num);}
};

class Basic_Gl_2D_Texture : public Basic_Gl_Texture{
    public:
    Basic_Gl_2D_Texture();
    inline void re_wrap_texture_method(){gl_texture_re_wrap_method(GL_TEXTURE_2D);}
    inline void clamp_border_wrap_texture_method(){gl_texture_clamp_border_wrap_method(GL_TEXTURE_2D);}
    inline void clamp_edge_wrap_texture_method(){gl_texture_clamp_edge_wrap_method(GL_TEXTURE_2D);}
    inline void mipmap_line_filter_texture_method(){gl_texture_mipmap_liner_filter_method(GL_TEXTURE_2D);}
    inline void line_filter_texture_method(){gl_texture_liner_filter_method(GL_TEXTURE_2D);}
    inline void near_filter_texture_method(){gl_texture_near_filter_method(GL_TEXTURE_2D);}
    inline void max_base_level(){gl_texture_mex_base_method(GL_TEXTURE_2D);}
    inline void tex_border_color_parameter(float * parameter){gl_texture_parameter(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, parameter);}
    inline void set_tex_to_frame(GLenum frame_type, GLenum attachment){
        glFramebufferTexture2D(frame_type, attachment, GL_TEXTURE_2D, tex_id, 0);
    }
    inline void start_mipmap()override{
        gl_start_mipmap<GL_TEXTURE_2D>();
    }
    inline void start_texture()override{
        glBindTexture(GL_TEXTURE_2D, tex_id);
    }
    template <typename Tex_Type = GLubyte, GLenum Tex_Format = GL_RED>
    inline void upload_text_data(GLint tx, GLint ty, GLint tw, GLint th, const void * tex_buffer){
        glTexSubImage2D(GL_TEXTURE_2D, 0, tx, ty, tw, th, Tex_Format, fix_gl_type<Tex_Type>(), tex_buffer);
    }
    template <typename Tex_Type = GLubyte, GLenum Tex_Format = GL_RED, GLenum Tex_Format_1 = Tex_Format>
    inline void upload_text_data(GLint tw, GLint th, const void * tex_buffer){
        glTexImage2D(GL_TEXTURE_2D, 0, Tex_Format, tw, th, 0, Tex_Format_1, fix_gl_type<Tex_Type>(), tex_buffer);
    }
    
};
class Gl_2D_Texture_Manager : public Basic_Gl_2D_Texture{
    public:
    Gl_2D_Texture_Manager(const char * img_path);
    Gl_2D_Texture_Manager();
};

class Glsys_Texture{
    public:
    Glsys_Texture();
    ~Glsys_Texture();

};


#endif // _GLSYS_TEXTURE_HPP_

