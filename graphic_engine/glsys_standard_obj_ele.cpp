#include "glsys_standard_obj_ele.hpp"
Basic_Quads_Vp_Object::Basic_Quads_Vp_Object(){
    float quads[12];
    sgg_quads_matrix(quads, -1.0f, 1.0f, -1.0f, 1.0f);
    vp.gen_vp();
    vp.set_up_vp_buffer_on_gpu(0, quads, 12);
    vp.set_up_vp_buffer_shader_attribute_memory(0, 2, 2, 0);
}

Basic_Cube_Vp_Object::Basic_Cube_Vp_Object(){
    float cube[108];
    sgg_cube_matrix(cube, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 0);
    vp.gen_vp();
    vp.set_up_vp_buffer_on_gpu(0, cube, 108);
    vp.set_up_vp_buffer_shader_attribute_memory(0, 3, 3, 0);

}
Basic_N_Cube_Vp_Object::Basic_N_Cube_Vp_Object(float cube_size){
    float n_cube[216];
    sgg_cube_matrix(n_cube, -cube_size, cube_size, -cube_size, cube_size, -cube_size, cube_size, 3);
    const int stride = 6;
    const int triangle_count = 12;

    for (unsigned t = 0; t < triangle_count; ++t) {

        float* v0 = n_cube + (t * 3 + 0) * stride;
        float* v1 = n_cube + (t * 3 + 1) * stride;
        float* v2 = n_cube + (t * 3 + 2) * stride;

        float p0[3] = { v0[0], v0[1], v0[2] };
        float p1[3] = { v1[0], v1[1], v1[2] };
        float p2[3] = { v2[0], v2[1], v2[2] };

        float e1[3] = { p1[0]-p0[0], p1[1]-p0[1], p1[2]-p0[2] };
        float e2[3] = { p2[0]-p0[0], p2[1]-p0[1], p2[2]-p0[2] };
        float n[3] = {
            e1[1]*e2[2] - e1[2]*e2[1],
            e1[2]*e2[0] - e1[0]*e2[2],
            e1[0]*e2[1] - e1[1]*e2[0]
        };
        
        
        float len = sqrtf(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
        n[0] /= len; n[1] /= len; n[2] /= len;

        for (int k = 0; k < 3; ++k) {
            float* v = n_cube + (t * 3 + k) * stride;
            v[3] = n[0];
            v[4] = n[1];
            v[5] = n[2];
        }
    }
    vp.gen_vp();
    vp.set_up_vp_buffer_on_gpu(0, n_cube, 216);
    vp.set_up_vp_buffer_shader_attribute_memory(0, 3, 6, 0);
    vp.set_up_vp_buffer_shader_attribute_memory(1, 3, 6, 3);
}
void buildCubeLRBTF(float L, float R,
                    float B, float T,
                    float N, float F,
                    std::vector<float>& out)
{
    out.clear();
    out.reserve(36 * 6); // 36 vertices, 6 floats each

    auto push = [&](float x, float y, float z, float nx, float ny, float nz){
        out.push_back(x);
        out.push_back(y);
        out.push_back(z);
        out.push_back(nx);
        out.push_back(ny);
        out.push_back(nz);
    };

    // ========== 上面 (0, +1, 0) ==========
    push(L,T,N, 0,1,0);
    push(R,T,N, 0,1,0);
    push(R,T,F, 0,1,0);
    push(L,T,N, 0,1,0);
    push(R,T,F, 0,1,0);
    push(L,T,F, 0,1,0);

    // ========== 下面 (0, -1, 0) ==========
    push(L,B,N, 0,-1,0);
    push(R,B,F, 0,-1,0);
    push(R,B,N, 0,-1,0);
    push(L,B,N, 0,-1,0);
    push(L,B,F, 0,-1,0);
    push(R,B,F, 0,-1,0);

    // ========== 前面 near (0, 0, -1) ==========
    push(L,B,N, 0,0,-1);
    push(R,T,N, 0,0,-1);
    push(R,B,N, 0,0,-1);
    push(L,B,N, 0,0,-1);
    push(L,T,N, 0,0,-1);
    push(R,T,N, 0,0,-1);

    // ========== 背面 far (0, 0, +1) ==========
    push(L,B,F, 0,0,1);
    push(R,B,F, 0,0,1);
    push(R,T,F, 0,0,1);
    push(L,B,F, 0,0,1);
    push(R,T,F, 0,0,1);
    push(L,T,F, 0,0,1);

    // ========== 左面 (-1, 0, 0) ==========
    push(L,B,N, -1,0,0);
    push(L,B,F, -1,0,0);
    push(L,T,F, -1,0,0);
    push(L,B,N, -1,0,0);
    push(L,T,F, -1,0,0);
    push(L,T,N, -1,0,0);

    // ========== 右面 (+1, 0, 0) ==========
    push(R,B,N, 1,0,0);
    push(R,T,F, 1,0,0);
    push(R,B,F, 1,0,0);
    push(R,B,N, 1,0,0);
    push(R,T,N, 1,0,0);
    push(R,T,F, 1,0,0);
}

Basic_N_Cube_Vp_Object::Basic_N_Cube_Vp_Object(float left, float right, float bottom, float top, float near, float far){
    float n_cube[216];
    sgg_cube_matrix(n_cube, left, right, bottom, top, near, far, 3);
    const int stride = 6;
    const int triangle_count = 12;

    for (unsigned t = 0; t < triangle_count; ++t) {

        float* v0 = n_cube + (t * 3 + 0) * stride;
        float* v1 = n_cube + (t * 3 + 1) * stride;
        float* v2 = n_cube + (t * 3 + 2) * stride;

        float p0[3] = { v0[0], v0[1], v0[2] };
        float p1[3] = { v1[0], v1[1], v1[2] };
        float p2[3] = { v2[0], v2[1], v2[2] };

        float e1[3] = { p1[0]-p0[0], p1[1]-p0[1], p1[2]-p0[2] };
        float e2[3] = { p2[0]-p0[0], p2[1]-p0[1], p2[2]-p0[2] };
        float n[3] = {
            e1[1]*e2[2] - e1[2]*e2[1],
            e1[2]*e2[0] - e1[0]*e2[2],
            e1[0]*e2[1] - e1[1]*e2[0]
        };
        float len = sqrtf(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
        n[0] /= len; n[1] /= len; n[2] /= len;

        for (int k = 0; k < 3; ++k) {
            float* v = n_cube + (t * 3 + k) * stride;
            v[3] = n[0];
            v[4] = n[1];
            v[5] = n[2];
        }
    }
    std::vector<float> test;
    buildCubeLRBTF(left, right, bottom, top, near, far, test);
    vp.gen_vp();
    vp.set_up_vp_buffer_on_gpu(0, test.data(), test.size());
    vp.set_up_vp_buffer_shader_attribute_memory(0, 3, 6, 0);
    vp.set_up_vp_buffer_shader_attribute_memory(1, 3, 6, 3);
}

void Basic_N_Cube_Vp_Object::render_object(){
    vp.start_normal_draw();
}
Basic_Sphere_Vp_Object::Basic_Sphere_Vp_Object(uint32_t sph_longitude_count, uint32_t sph_latitude_counts, float radius, float x, float y, float z){
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    build_sphere_vertex(vertices, sph_longitude_count, sph_latitude_counts, radius, x, y, z);
    build_sphere_indices(indices, sph_longitude_count, sph_latitude_counts);
    vp.gen_vp();
    vp.set_up_vp_buffer_on_gpu(0, vertices.data(), vertices.size());
    vp.set_up_vp_buffer_shader_attribute_memory(0, 3, 6, 0);
    vp.set_up_vp_buffer_shader_attribute_memory(1, 3, 6, 3);
    vp.set_up_vp_ebo_on_gpu(1, indices.data(), indices.size());
}
Basic_Sphere_Vp_Object::Basic_Sphere_Vp_Object(uint32_t sph_longitude_count, uint32_t sph_latitude_counts, float radius){
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    build_sphere_vertex(vertices, sph_longitude_count, sph_latitude_counts, radius, 0.0f, 0.0f, 0.0f);
    build_sphere_indices(indices, sph_longitude_count, sph_latitude_counts);
    vp.gen_vp();
    vp.set_up_vp_buffer_on_gpu(0, vertices.data(), vertices.size());
    vp.set_up_vp_buffer_shader_attribute_memory(0, 3, 6, 0);
    vp.set_up_vp_buffer_shader_attribute_memory(1, 3, 6, 3);
    vp.set_up_vp_ebo_on_gpu(1, indices.data(), indices.size());
}
void Basic_Sphere_Vp_Object::build_sphere_vertex(std::vector<float> & dst_vertices, uint32_t sector_count, uint32_t stack_count, float radius, float x, float y, float z){
    SGG_Vector3 pos;
    SGG_Vector3 norm;
    float length_inv = 1.0f / radius;
    float sector_step = 2.0f * M_PI / sector_count;
    float stack_step = M_PI / stack_count;
    for(uint32_t i = 0; i <= stack_count; ++i){
        float stack_angle = M_PI / 2.0f - i * stack_step;
        float xy = radius * cos(stack_angle);
        pos.z = radius * sin(stack_angle);    
        for(uint32_t j = 0; j <= sector_count; ++j){
            float sector_angle = j * sector_step;
            pos.x = xy * cos(sector_angle);
            pos.y = xy * sin(sector_angle);
            SGG_Vector3 a_pos = pos;
            add_vector3_xyz(&a_pos, x, y, z);
            dst_vertices.push_back(a_pos.x);
            dst_vertices.push_back(a_pos.y);
            dst_vertices.push_back(a_pos.z);
            norm = pos * length_inv;
            dst_vertices.push_back(norm.x);
            dst_vertices.push_back(norm.y);
            dst_vertices.push_back(norm.z);
        }
    }
}
void Basic_Sphere_Vp_Object::build_sphere_indices(std::vector<GLuint> & dst_indices, uint32_t sector_count, uint32_t stack_count){
        
    for (int i = 0; i < stack_count; ++i) {
        int k1 = i * (sector_count + 1);
        int k2 = k1 + sector_count + 1;
        for (int j = 0; j < sector_count; ++j, ++k1, ++k2) {
            if (i != 0) {
                dst_indices.push_back(k1);
                dst_indices.push_back(k2);
                dst_indices.push_back(k1 + 1);
            }
            if (i != (stack_count - 1)) {
                dst_indices.push_back(k1 + 1);
                dst_indices.push_back(k2);
                dst_indices.push_back(k2 + 1);
            }
        }
    }
}
