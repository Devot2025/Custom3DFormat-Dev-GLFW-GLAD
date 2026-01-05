#include "glsys_core.hpp"


Program_Shader_Operator::Program_Shader_Operator(const char * vert_file_path,const char * frag_file_path,  GLuint shader_var_num) : program_shader_manager(vert_file_path, frag_file_path){
    prog_shader_var_ids.resize(shader_var_num);
}
void Program_Shader_Operator::register_shader_var_name_id(GLuint shader_var_name_id, const char * shader_var_name){
    prog_shader_var_ids[shader_var_name_id] = glGetUniformLocation(program_shader_manager.prog_shader, shader_var_name);
    //std::cout << shader_var_name << " " << prog_shader_var_ids[shader_var_name_id] << " " << shader_var_name_id << std::endl;
}
GLFW_Manager::GLFW_Manager(int width, int height, const char * name){
    if(!name) name = EXAMPLE_WINDOW_NAME;
    if(!glfwInit()) throw std::runtime_error(GET_TEMPLATE_ERROR_STRING("failed to glfw init"));
    glwin = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if(!glwin) throw std::runtime_error(GET_TEMPLATE_ERROR_STRING("failed to create glfw window"));
	glfwMakeContextCurrent(glwin);
    
}

GLFW_Manager::~GLFW_Manager(){
    glfwDestroyWindow(glwin);
    glfwTerminate();
}
bool GLFW_Manager::glfw_run(){
    return !glfwWindowShouldClose(glwin);
}

void GLFW_Manager::glfw_require_process(){
    glfwPollEvents();
    glfwSwapBuffers(glwin);
}



GL_Sys_Main_Manager::GL_Sys_Main_Manager(int width, int height, const char * name) : glfw_manage(width, height, name){
    ini_uint_gls_manager();
}

GL_Sys_Main_Manager::GL_Sys_Main_Manager(int width, int height, const char * name, Gl_Option_Manager & gl_opt_manager) : glfw_manage(width, height, name){
    ini_uint_gls_manager();
    gl_opt_manager.optional_main();
    if(gl_opt_manager.opt3d_check)gl_opt_manager.optional_3d_main();
}

GL_Sys_Main_Manager::GL_Sys_Main_Manager(int width, int height, const char * name, Gl_Option_Manager & gl_opt_manager, GL_Loop_Manager *& loop_manager) : glfw_manage(width, height, name){
    ini_uint_gls_manager();
    gl_opt_manager.optional_main();
    if(gl_opt_manager.opt3d_check)gl_opt_manager.optional_3d_main();
}
GL_Sys_Main_Manager::~GL_Sys_Main_Manager(){
}

void GL_Sys_Main_Manager::ini_uint_gls_manager(){
    glfw_manage.ini_gl_core();
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error(GET_TEMPLATE_ERROR_STRING("failed to load glad"));
}

int GL_Sys_Main_Manager::run_gl_loop(GL_Loop_Manager & loop_manager){
    loop_manager.glfw_sub_manager.set_glfw_manager(glfw_manage);
    
    if(!loop_manager.init_loop())return -1;

    while(glfw_manage.glfw_run()){
        if(!loop_manager.main_loop()) break;
        glfw_manage.glfw_require_process();
    }
    if(!loop_manager.end_loop()) return -1;
    return 0;
}