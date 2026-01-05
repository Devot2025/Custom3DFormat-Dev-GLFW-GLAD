
#ifndef _GLSYS_SC3_RENDER_HPP_
#define _GLSYS_SC3_RENDER_HPP_
#include <glsys_core.hpp>
#include <glsys_vertex_package.hpp>
#include <sc3_loader/speed_charm_3d.h>
#include <sc3_loader/fbx_to_speed_charm_3d.h>
class Glsys_Sc3_Render{
    public:
    protected:
    float anim_time;
    std::vector<Basic_Gl_Vertex_Package<3, GL_STATIC_DRAW>> sc3_vp;
    Speed_Charm_3D_Main * sc_run_main;
    public:
    Glsys_Sc3_Render(const char * sc3_path);
    void update_sc3_anim_bones(sc_uint anim_id, float delta_time);
    ~Glsys_Sc3_Render();
};
template <GLuint u2d_id>
class Glsys_Sc3_Render_Manager : public Glsys_Sc3_Render{
    Emulate_Uniform_2D_Data<u2d_id> bone_emulate_u2d;
    void render_sc3_main(Program_Shader_Operator & prog_shader_ope);
};
template <GLuint u2d_id>
void Glsys_Sc3_Render_Manager<u2d_id>::render_sc3_main(Program_Shader_Operator & prog_shader_ope){
    bone_emulate_u2d.start_emulated_u2d_data(prog_shader_ope);
    for(sc_size i = 0; i < sc3_vp.size(); ++i){
        std::vector<SGG_Mat4> sgg_mat4(sc_run_main->sc_meshes[i].mesh_bone_map_num);
        for(sc_size j = 0; j < sc_run_main->sc_meshes[i].mesh_bone_map_num; ++j){
            start_build_bones_speed_charm_3d(sc_run_main, &sc_run_main->sc_bones[j], &sgg_mat4.data()[j]);
        }
        bone_emulate_u2d.use_emulated_u2d_data(sgg_mat4.data(), sgg_mat4.size());
        sc3_vp[i].e_draw();
    }
}

#endif // _GLSYS_SC3_RENDER_HPP_

