#ifndef _GLSYS_STANDARD_OBJ_ELE_HPP_
#define _GLSYS_STANDARD_OBJ_ELE_HPP_

#include <ggmath/sgg_vec.hpp>

#include "glsys_core.hpp"
#include <glsys_vertex_package.hpp>
template <GLuint static_check_id>
static inline void use_static_check(Program_Shader_Operator & prog_shader_ope, int static_check){
    prog_shader_ope.upload_shader_uniform_data(static_check_id, static_check);
}
template <GLuint color_id>
class Object_Color_Manager{
    public:
    SGG_Vector3 color;
    Object_Color_Manager();
    SGG_Vector3 & operator () (float vec_a);
    SGG_Vector3 & operator () (float vec_x, float vec_y, float vec_z);
    void use_obj_color(Program_Shader_Operator & prog_shader_ope);
};

template <GLuint color_id>
SGG_Vector3 & Object_Color_Manager<color_id>::operator()(float vec_x, float vec_y, float vec_z){
    assignment_vector(color, vec_x, vec_y, vec_z);
    return color;
}
template <GLuint color_id>
SGG_Vector3 & Object_Color_Manager<color_id>::operator()(float vec_a){
    assignment_vector(color, vec_a);
    return color;
}
template <GLuint color_id>
Object_Color_Manager<color_id>::Object_Color_Manager(){
    assignment_vector(color, 1.0f);
}
template <GLuint color_id>
void Object_Color_Manager<color_id>::use_obj_color(Program_Shader_Operator & prog_shader_ope){
    prog_shader_ope.upload_shader_uniform_data(color_id, color.x, color.y, color.z);
}

template <GLuint pos_id>
class Object_Pos_Manager{
    public:
    SGG_Vector3 pos;
    SGG_Vector3 & operator () (float vec_a);
    SGG_Vector3 & operator () (float vec_x, float vec_y, float vec_z);
    Object_Pos_Manager();
    void use_obj_pos(Program_Shader_Operator & prog_shader_ope);
};

template <GLuint pos_id>
SGG_Vector3 & Object_Pos_Manager<pos_id>::operator()(float vec_a){
    assignment_vector(pos, vec_a);
    return pos;
}

template <GLuint pos_id>
SGG_Vector3 & Object_Pos_Manager<pos_id>::operator()(float vec_x, float vec_y, float vec_z){
    pos.x = vec_x;
    pos.y = vec_y;
    pos.z = vec_z;
    return pos;
}
template <GLuint pos_id>
Object_Pos_Manager<pos_id>::Object_Pos_Manager(){
    assignment_vector3(&pos, 0.0f);
}
template <GLuint pos_id>
void Object_Pos_Manager<pos_id>::use_obj_pos(Program_Shader_Operator & prog_shader_ope){
    prog_shader_ope.upload_shader_uniform_data(pos_id, pos.x, pos.y, pos.z);
}

template <GLuint color_id, GLuint pos_id>
class Object_Light_3D{
    public:
    Object_Pos_Manager<pos_id> pos_manager;
    Object_Color_Manager<color_id> color_manager;
    void use_light(Program_Shader_Operator & prog_shader_ope);
};
template <GLuint color_id, GLuint pos_id>
void Object_Light_3D<color_id, pos_id>::use_light(Program_Shader_Operator & prog_shader_ope){
    pos_manager.use_obj_pos(prog_shader_ope);
    color_manager.use_obj_color(prog_shader_ope);
}
template <GLuint Color_Id, GLuint Pos_Id>
class Object_Quads{
    public:

    Object_Pos_Manager<Pos_Id> pos;
    Object_Color_Manager<Color_Id> color;
    void set_color(float red, float blue, float green);
    void set_pos(float x, float y);
    Object_Quads(float left, float right, float bottom, float top);
    Basic_Gl_Vertex_Package<1, GL_STATIC_DRAW> quads_vp;
    void start_quads(Program_Shader_Operator & prog_shader_ope);
};

template <GLuint Color_Id, GLuint Pos_Id>
void Object_Quads<Color_Id, Pos_Id>::set_color(float red, float blue, float green){
    assignment_vector(color.color, red, blue, green);
}
template <GLuint Color_Id, GLuint Pos_Id>
void Object_Quads<Color_Id, Pos_Id>::set_pos(float x, float y){
    assignment_vector(pos.pos, x, y, 0.0f);
}
template <GLuint Color_Id, GLuint Pos_Id>
Object_Quads<Color_Id, Pos_Id>::Object_Quads(float left, float right, float bottom, float top){
    float quads_vertices[] = {
        left, top, 0.0f, 1.0f,
        left, bottom, 0.0f, 0.0f,
        right, top, 1.0f, 1.0f,
        right, top, 1.0f, 1.0f,
        left, bottom, 0.0f, 0.0f,
        right, bottom, 1.0f, 0.0f
    };
    quads_vp.gen_vp();
    quads_vp.set_up_vp_buffer_on_gpu(0, quads_vertices, 24);
    quads_vp.set_up_vp_buffer_shader_attribute_memory(0, 4, 4, 0);
}
template <GLuint Color_Id, GLuint Pos_Id>
void Object_Quads<Color_Id, Pos_Id>::start_quads(Program_Shader_Operator & prog_shader_ope){
    color.use_obj_color(prog_shader_ope);
    pos.use_obj_pos(prog_shader_ope);
    quads_vp.start_vp();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
class Basic_Vp_Object{
    public:
    Basic_Gl_Vertex_Package<2, GL_DYNAMIC_DRAW> vp;
};

class Basic_Cube_Vp_Object : public Basic_Vp_Object{
    public:
    Basic_Cube_Vp_Object();
};

class Basic_N_Cube_Vp_Object : public Basic_Vp_Object{
    public:
    Basic_N_Cube_Vp_Object(float cube_size = 1.0f);
    Basic_N_Cube_Vp_Object(float left, float right, float bottom, float top, float near, float far);
    void render_object();
};
class Basic_Quads_Vp_Object : public Basic_Vp_Object{
    public:
    Basic_Quads_Vp_Object();
};
class Basic_Sphere_Vp_Object : public Basic_Vp_Object{
    public:
    Basic_Sphere_Vp_Object(uint32_t sph_longitude_count = 36, uint32_t sph_latitude_counts = 18, float radius = 10.0f);
    Basic_Sphere_Vp_Object(uint32_t sph_longitude_count, uint32_t sph_latitude_counts, float radius, float x, float y, float z);
    inline void render_sphere();
    private:
    void build_sphere_vertex(std::vector<float> & dst_vertices, uint32_t sector_count, uint32_t stack_count, float radius, float x, float y, float z);
    void build_sphere_indices(std::vector<GLuint> & dst_indices, uint32_t sector_count, uint32_t stack_count);
};
void Basic_Sphere_Vp_Object::render_sphere(){
    vp.e_draw();
}
#endif