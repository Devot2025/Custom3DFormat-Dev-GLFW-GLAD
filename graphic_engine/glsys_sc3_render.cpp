#include "glsys_sc3_render.hpp"


Glsys_Sc3_Render::Glsys_Sc3_Render(const char * sc3_path) : anim_time{}{
    Speed_Charm_3D_Main * sc3_main = change_fbx_speed_charm_3d(sc3_path, 1.0f);
    for(size_t i = 0; i < sc3_main->meshes_num; ++i){
        sc3_vp[i].gen_vp();
        sc3_vp[i].set_up_vp_buffer_on_gpu<Speed_Charm_3D_Mesh_Attr>(0, sc3_main->sc_meshes[i].mesh_attr, sc3_main->sc_meshes[i].attr_num);
        sc3_vp[i].set_up_vp_buffer_shader_attribute_memory(0, 3, 8, 0);
        sc3_vp[i].set_up_vp_buffer_shader_attribute_memory(1, 3, 8, 3);
        if(sc3_main->sc_meshes[i].skin_attr){
            sc3_vp[i].set_up_vp_buffer_on_gpu(1, sc3_main->sc_meshes[i].skin_attr, sc3_main->sc_meshes[i].attr_num);
            sc3_vp[i].set_up_vp_buffer_shader_attribute_memory_int<sc_ushort, Speed_Charm_3D_Skin_Attr>(4, 4, 1, sizeof(sc_ubyte) * 4);
            sc3_vp[i].set_up_vp_buffer_shader_attribute_memory<sc_ubyte, Speed_Charm_3D_Skin_Attr, GL_TRUE>(5, 4, 1, 0);
        }
        sc3_vp[i].set_up_vp_ebo_on_gpu(2, sc3_main->sc_meshes[i].indices, sc3_main->sc_meshes[i].ind_num);
    }
    sc_run_main = sc3_main;
}

void Glsys_Sc3_Render::update_sc3_anim_bones(sc_uint anim_id, float delta_time){
    start_animation_speed_charm_3d_bone(sc_run_main, anim_id, &anim_time, delta_time);
    start_speed_charm_3d_bones_hierarchy(sc_run_main);
}
Glsys_Sc3_Render::~Glsys_Sc3_Render(){
    delete_speed_charm_3d_main(&sc_run_main);
}

