#ifndef _GL_SYS_CORE_HPP_
#define _GL_SYS_CORE_HPP_
#include <glsys.hint>
#include <shader_loader.hpp>
#include <glsys_texture.hpp>
#include <cpp_standard_lib.hpp>

#include "macro_inf.hint"

#define GLSYS_CONTINUE 1
#define GLSYS_END 0
#define EXAMPLE_WINDOW_NAME "example gl window"
class Basic_Cursor_Manager{
    public:
    virtual void cursor_program_main(double cx, double cy) = 0;
};
/*change standard type to gl type enum*/
#define SAMPLER_2D_MAX 

struct Shader_Samplers_Data{
    private:
    GLenum sampler_idx;
    public:
    inline Shader_Samplers_Data();
    inline GLenum get_now_sampler2D(GLint & dst_sampler_idx);
    inline void reset_sampler2D();
};
Shader_Samplers_Data::Shader_Samplers_Data() : sampler_idx{}{
}
GLenum Shader_Samplers_Data::get_now_sampler2D(GLint & dst_sampler_idx){
    dst_sampler_idx = sampler_idx;
    GLenum dst_sampler_id = GL_TEXTURE0 + sampler_idx++;
    return dst_sampler_id;
}

void Shader_Samplers_Data::reset_sampler2D(){sampler_idx = 0;}
class Program_Shader_Operator{
    public:
    Program_Shader_Operator(const char * vert_file_path, const char * frag_file_path, GLuint shader_var_num);
    void register_shader_var_name_id(GLuint shader_var_name_id, const char * shader_var_name);
    inline void begin_program_shader(){glUseProgram(program_shader_manager.prog_shader);sample_data.reset_sampler2D();}
    //inline void end_program_shader(){glUseProgram(0);frag_sample.reset_sampler2D(), vert_sample.reset_sampler2D();}
    inline void upload_shader_uniform_data(GLuint shader_var_name_id, float x, float y, float z){glUniform3f(prog_shader_var_ids[shader_var_name_id], x, y, z);}
    inline void upload_shader_uniform_data(GLuint shader_var_name_id, int i){glUniform1i(prog_shader_var_ids[shader_var_name_id], i);}
    inline void upload_shader_uniform_data(GLuint shader_var_name_id, float i){glUniform1f(prog_shader_var_ids[shader_var_name_id], i);}
    inline void upload_shader_uniform_data(GLuint shader_var_name_id, float x, float y){glUniform2f(prog_shader_var_ids[shader_var_name_id], x, y);}
    inline void upload_shader_uniform_data(GLuint shader_var_name_id, float * m4){glUniformMatrix4fv(prog_shader_var_ids[shader_var_name_id], 1, GL_FALSE, m4);}
    Shader_Samplers_Data sample_data;
    private:
    std::vector<GLuint> prog_shader_var_ids;

    Basic_GL_Program_Shader_Manager program_shader_manager;
};

template <GLuint tex_buffer_id>
class Texture_2D_Manager : private Gl_2D_Texture_Manager{
    public:
    Texture_2D_Manager(const char * img_file_path);
    void start_texture_2D(Program_Shader_Operator & prog_shader_ope);
};
template <GLuint tex_buffer_id>
Texture_2D_Manager<tex_buffer_id>::Texture_2D_Manager(const char * img_file_path) : Gl_2D_Texture_Manager(img_file_path){

}
template <GLuint tex_buffer_id>
void Texture_2D_Manager<tex_buffer_id>::start_texture_2D(Program_Shader_Operator & prog_shader_ope){
    GLint sampler_id_idx;
    GLenum sampler2D_id = prog_shader_ope.sample_data.get_now_sampler2D(sampler_id_idx);
    active_texture(sampler2D_id);
    start_texture();
    prog_shader_ope.upload_shader_uniform_data(tex_buffer_id, sampler_id_idx);
}
template <GLuint u2d_id, int u2d_data_width = 4>
class Emulate_Uniform_2D_Data : Gl_2D_Texture_Manager{
    public:
    Emulate_Uniform_2D_Data(int ini_size);
    void gen_emulated_u2d_data(int data_size);
    bool start_emulated_u2d_data(Program_Shader_Operator & prog_shader_ope);
    bool use_emulated_u2d_data(void * emulated_u2d, int emulated_u2d_size);
    bool use_emulated_u2d_data(void * emulated_u2d);
    
    private:
    void booked_uniform_2_data(int data_size);
    void standard_emulated_u2d_data_opt();
};
template <GLuint u2d_id, int u2d_data_width>
void Emulate_Uniform_2D_Data<u2d_id, u2d_data_width>::gen_emulated_u2d_data(int data_size){
    //if(data_size <= 0)return;

    //standard_emulated_u2d_data_opt();
    //booked_uniform_2_data(data_size);
}

template <GLuint u2d_id, int u2d_data_width>
bool Emulate_Uniform_2D_Data<u2d_id, u2d_data_width>::start_emulated_u2d_data(Program_Shader_Operator & prog_shader_ope){
    GLint sampler_idx;
    GLenum sample_id = prog_shader_ope.sample_data.get_now_sampler2D(sampler_idx);
    active_texture(sample_id);
    start_texture();
    prog_shader_ope.upload_shader_uniform_data(u2d_id, sampler_idx);
    return true;
}

template <GLuint u2d_id, int u2d_data_width>
bool Emulate_Uniform_2D_Data<u2d_id, u2d_data_width>::use_emulated_u2d_data(void * emulated_u2d, int emulated_u2d_size){
    if(!emulated_u2d)return false;
    booked_uniform_2_data(emulated_u2d_size);
    upload_text_data<float, GL_RGBA>(0, 0, u2d_data_width, tex_size, emulated_u2d);
    return true;
}

template <GLuint u2d_id, int u2d_data_width>
bool Emulate_Uniform_2D_Data<u2d_id, u2d_data_width>::use_emulated_u2d_data(void * emulated_u2d){
    if(!emulated_u2d)return false;
    upload_text_data<float, GL_RGBA>(0, 0, u2d_data_width, tex_size, emulated_u2d);
    return true;
}
template <GLuint u2d_id, int u2d_data_width>
Emulate_Uniform_2D_Data<u2d_id, u2d_data_width>::Emulate_Uniform_2D_Data(int ini_size){
    if(ini_size <= 0)ini_size = 64;
    standard_emulated_u2d_data_opt();
    booked_uniform_2_data(ini_size);
}
template <GLuint u2d_id, int u2d_data_width>
void Emulate_Uniform_2D_Data<u2d_id, u2d_data_width>::booked_uniform_2_data(int data_size){
    if(tex_size == data_size) return;
    upload_text_data<float, GL_RGBA32F, GL_RGBA>(u2d_data_width, data_size, nullptr);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, u2d_data_width, data_size, 0, GL_RGBA, GL_FLOAT, nullptr);
    tex_size = data_size;   
}
template <GLuint u2d_id, int u2d_data_width>
void Emulate_Uniform_2D_Data<u2d_id, u2d_data_width>::standard_emulated_u2d_data_opt(){
    near_filter_texture_method();
    clamp_edge_wrap_texture_method();
    max_base_level();
}

class Basic_GLFW_Manager{
    protected:
    GLFWwindow * glwin = nullptr;
    Program_Shader_Operator * now_prog_shader_ope;
    static inline Basic_Cursor_Manager * cursor_manager;
    static inline void glfw_cursor_program_call_back(GLFWwindow * tool_glwin, double x, double y){
        cursor_manager->cursor_program_main(x,y);
    }
    public:
    inline void set_cursor_basic_cursor(Basic_Cursor_Manager & src_cursor_manager){
        cursor_manager = &src_cursor_manager;
        glfw_cursor_program_start();
    }
    inline void glfw_cursor_program_start(){
		glfwSetCursorPosCallback(glwin, glfw_cursor_program_call_back);
    }
    inline bool gl_sys_push_key(int key){return glfwGetKey(glwin, key) == GLFW_PRESS;}
    inline bool gl_sys_push_mouse(int mouse_button){return glfwGetMouseButton(glwin, mouse_button) == GLFW_PRESS;}
	inline void get_render_cursor_pos(double & dst_cursor_x, double& dst_cursor_y)const {glfwGetCursorPos(glwin, &dst_cursor_x, &dst_cursor_y);}
    inline void set_now_prog_shader(Program_Shader_Operator &prog_shader_ope){now_prog_shader_ope = &prog_shader_ope;}
    inline const Program_Shader_Operator & get_prog_shader(){return *now_prog_shader_ope;}
};
class GLFW_Manager : public Basic_GLFW_Manager{
    public:
    explicit GLFW_Manager(int width, int height, const char * name);
    glsys_si_strap void ini_gl_core();
    inline const GLFWwindow * get_glwin();
    bool glfw_run();
    void glfw_require_process();
    ~GLFW_Manager();
};

void GLFW_Manager::ini_gl_core(){

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
const GLFWwindow * GLFW_Manager::get_glwin(){
    return glwin;
}
class GL_Sys_Sub_Manager{
    public:
    inline void begin_3D_mode(){glEnable(GL_DEPTH_TEST);}
    inline void begin_3D_mask_mode(){glDepthMask(GL_TRUE);}
    inline void end_3D_mask_mode(){glDepthMask(GL_FALSE);}
    inline void end_3D_mode(){glDisable(GL_DEPTH_TEST);}
    inline GLint force_end(){
        if(glfw_manager->gl_sys_push_key(GLFW_KEY_LEFT_CONTROL)){
            if(glfw_manager->gl_sys_push_key(GLFW_KEY_C)){
                return GLSYS_END;
            }
        }
        return GLSYS_CONTINUE;
    }
    inline void render_base_color(GLclampf red, GLclampf green, GLclampf blue){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(red, green, blue, 1.0f);
    }
    inline void set_glfw_manager(GLFW_Manager & src_glfw_manager){ glfw_manager = &src_glfw_manager;}
    Basic_GLFW_Manager * glfw_manager;
};
class Gl_Option_Manager{
    public:
    virtual void optional_main() = 0;
    bool opt3d_check = false;
    inline void optional_3d_main();
    protected:
    inline void render_option(GLenum option);
    inline void zbuffer_option();
};
void Gl_Option_Manager::optional_3d_main(){
    zbuffer_option();
}
void Gl_Option_Manager::render_option(GLenum option){
    glEnable(option);
}
void Gl_Option_Manager::zbuffer_option(){
    render_option(GL_DEPTH_TEST);
}
class GL_Loop_Manager{
    public:
    virtual int init_loop() = 0;
    virtual int main_loop() = 0;
    virtual int end_loop() = 0;
    GL_Sys_Sub_Manager glfw_sub_manager;
};
class GL_Sys_Main_Manager{
    public:
    GLFW_Manager glfw_manage;
    explicit GL_Sys_Main_Manager(int width, int height, const char * name);
    GL_Sys_Main_Manager(int width, int height, const char * name, Gl_Option_Manager & gl_opt_manager);
    GL_Sys_Main_Manager(int width, int height, const char * name, Gl_Option_Manager & gl_opt_manager, GL_Loop_Manager *& loop_manager);
    ~GL_Sys_Main_Manager();
    int run_gl_loop(GL_Loop_Manager & loop_manager);
    private:

	void ini_gl_core();
    void ini_uint_gls_manager();
};

#endif