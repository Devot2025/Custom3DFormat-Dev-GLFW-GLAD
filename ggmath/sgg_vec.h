#ifndef _SGG_VEC_H_
#define _SGG_VEC_H_
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "c_header_helper.hint"
#define EPS 1e-8f
#define sgg_vec_si_strap static inline
/**
 * 0 1 2 3
 * 4 5 6 7
 * 8 9 10 11
 * 12 13 14 15
*/

#define INSERT_ROW_MAT4(mat4, idx, m1, m2, m3, m4)\
     mat4->m[idx * 4 + 0] = m1,\
     mat4->m[idx * 4 + 1] = m2, \
     mat4->m[idx * 4 + 2] = m3, \
     mat4->m[idx * 4 + 3] = m4 
#define INSERT_COL_MAT4(mat4, idx, m1, m2, m3, m4)\
    mat4->m[idx + 0 * 4] = m1,\
    mat4->m[idx + 1 * 4] = m2,\
    mat4->m[idx + 2 * 4] = m3,\
    mat4->m[idx + 3 * 4] = m4

typedef struct SGG_Vector2{ float x; float y;}SGG_Vector2;
typedef struct SGG_Vector3{ float x; float y; float z;}SGG_Vector3;
typedef struct SGG_Vector4{ float x; float y; float z; float w;}SGG_Vector4;

typedef struct SGG_Mat3{float m[3 * 3];}SGG_Mat3;
typedef struct SGG_Mat4{float m[4 * 4];}SGG_Mat4;
_EXTERN_C_BEGIN_

sgg_vec_si_strap float get_maxf(float a, float b){return a > b ? a : b;}
sgg_vec_si_strap float get_minf(float a, float b){return a < b ? a : b;}

sgg_vec_si_strap size_t get_maxu(size_t a, size_t b){return a > b ? a : b;}
sgg_vec_si_strap size_t get_minu(size_t a, size_t b){return a < b ? a : b;}
sgg_vec_si_strap size_t sgg_clampu(size_t v, size_t min, size_t max){
    return get_minu(get_maxu(v, min), max);
}
sgg_vec_si_strap float sgg_clampf(float v, float min, float max){
    return get_minf(get_maxf(v, min), max);
}

sgg_vec_si_strap void set_f_array_to_vec3(float ** vec3, float x, float y, float z, int next_pos){
    (*vec3)[0] = x; (*vec3)[1] = y; (*vec3)[2] = z;
    (*vec3) += 3 + next_pos;
}
sgg_vec_si_strap float sgg_lerp(float sx, float ex, float t){
    /* V = S * (1 - t) + E * t */
    return sx * (1.0f - t) + ex * t;
}

sgg_vec_si_strap void sgg_lerp_vector3(SGG_Vector3 * dv, SGG_Vector3 * sv, SGG_Vector3 * ev, float t){
    float lx = sgg_lerp(sv->x, ev->x, t);
    float ly = sgg_lerp(sv->y, ev->y, t);
    float lz = sgg_lerp(sv->z, ev->z, t);
    dv->x = lx;
    dv->y = ly;
    dv->z = lz;
}
sgg_vec_si_strap void sgg_lerp_vector4(SGG_Vector4 * dv, SGG_Vector4 * sv, SGG_Vector4 * ev, float t){
    float lx = sgg_lerp(sv->x, ev->x, t);
    float ly = sgg_lerp(sv->y, ev->y, t);
    float lz = sgg_lerp(sv->z, ev->z, t);
    float lw = sgg_lerp(sv->w, ev->w, t);
    dv->x = lx;
    dv->y = ly;
    dv->z = lz;
    dv->w = lw;
}

void sgg_trs_mat4(SGG_Mat4 * dst, SGG_Vector4 * rot, SGG_Vector3 * pos, SGG_Vector3 * scale);
bool sgg_equal_vector1(float a, float b);
bool sgg_equal_vector2(SGG_Vector2 * a, SGG_Vector2 * b);
bool sgg_equal_vector3(SGG_Vector3 * a, SGG_Vector3 * b);
bool sgg_equal_vector4(SGG_Vector4 * a, SGG_Vector4 * b);
float sgg_dot_vector4(SGG_Vector4 * a, SGG_Vector4 * b);
void sgg_neg_vector4(SGG_Vector4 * a);
void sgg_swap(float *a, float *b);
void sgg_identity(SGG_Mat4* dst);
float calc_radius(float degree);
void cross_vector3(SGG_Vector3 * dst_vec, const SGG_Vector3 * src_1, const SGG_Vector3 * src_2);
void normalize_vector3(SGG_Vector3 * dst_vec3);
void normalize_vector4(SGG_Vector4 * dst_vec4);


void assignment_vector2_vector2(SGG_Vector2 * vec2, const SGG_Vector2 * a_vec2);
void assignment_vector2_xyz(SGG_Vector2 * vec2, float ax, float ay);
void assignment_vector2(SGG_Vector2 * vec2, const float ass_vec);

void add_vector2_vector2(SGG_Vector2 * vec2, const SGG_Vector2 * a_vec2);
void add_vector2_xyz(SGG_Vector2 * vec2, float ax, float ay);
void add_vector2(SGG_Vector2 * vec2, const float add_vec);

void sub_vector2_vector2(SGG_Vector2 * vec2, const SGG_Vector2 * a_vec2);
void sub_vector2_xyz(SGG_Vector2 * vec2, float ax, float ay);
void sub_vector2(SGG_Vector2 * vec2, const float sub_vec);

void mul_vector2_vector2(SGG_Vector2 * vec2, const SGG_Vector2 * a_vec2);
void mul_vector2_xyz(SGG_Vector2 * vec2, float ax, float ay);
void mul_vector2(SGG_Vector2 * vec2, const float mul_vec);

void div_vector2_vector2(SGG_Vector2 * vec2, const SGG_Vector2 * a_vec2);
void div_vector2_xyz(SGG_Vector2 * vec2, float ax, float ay);
void div_vector2(SGG_Vector2 * vec2, const float div_vec);


void assignment_vector3_vector3(SGG_Vector3 * vec3, const SGG_Vector3 * a_vec3);
void assignment_vector3_xyz(SGG_Vector3 * vec3, float ax, float ay, float az);
void assignment_vector3(SGG_Vector3 * vec3, const float ass_vec);

void add_vector3_vector3(SGG_Vector3 * vec3, const SGG_Vector3 * a_vec3);
void add_vector3_xyz(SGG_Vector3 * vec3, float ax, float ay, float az);
void add_vector3(SGG_Vector3 * vec3, const float add_vec);

void sub_vector3_vector3(SGG_Vector3 * vec3, const SGG_Vector3 * a_vec3);
void sub_vector3_xyz(SGG_Vector3 * vec3, float ax, float ay, float az);
void sub_vector3(SGG_Vector3 * vec3, const float sub_vec);

void mul_vector3_vector3(SGG_Vector3 * vec3, const SGG_Vector3 * a_vec3);
void mul_vector3_xyz(SGG_Vector3 * vec3, float ax, float ay, float az);
void mul_vector3(SGG_Vector3 * vec3, const float mul_vec);

void div_vector3_vector3(SGG_Vector3 * vec3, const SGG_Vector3 * a_vec3);
void div_vector3_xyz(SGG_Vector3 * vec3, float ax, float ay, float az);
void div_vector3(SGG_Vector3 * vec3, const float div_vec);
void mul_vector4(SGG_Vector4 * vec4, const float mul_vec);
void assignment_vector4(SGG_Vector4 * vec4, const float ass_vec);
void assignment_mat4(SGG_Mat4 * dst, float x);
void mul_mat4_vector4(SGG_Vector4 *dst, SGG_Mat4 *a, SGG_Vector4 * b);
void mul_mat4_mat4(SGG_Mat4 *dst, SGG_Mat4 *a, SGG_Mat4 *b);

void cross_sgg_vector3(SGG_Vector3 * vec3, const SGG_Vector3 * src_a, const SGG_Vector3 * src_b);
void sgg_perspective(SGG_Mat4 * dst_per, float vertical_rad, float aspect, float near, float far);
void sgg_lookAt(SGG_Mat4 * dst_mat4, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
void sgg_ortho(SGG_Mat4 * dst_mat, float left, float right, float bottom, float top, float far_z, float near_z);
void sgg_inverse(SGG_Mat4 * dst_mat4);
void sgg_quads_matrix(float * q_mat, float left, float right, float bottom, float top);
void sgg_cube_matrix(float * c_mat, float left, float right, float bottom, float top, float near, float far, int next_pos);
void sgg_sphere_matrix(float * sph_mat, float stack_count, float sector_count, float radius, uint32_t attr_num);
_EXTERN_C_END_
#endif
