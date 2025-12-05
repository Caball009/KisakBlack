#pragma once

#include <physics/rigid_body.h>

struct __declspec(align(16)) rigid_body_constraint_custom_path : rigid_body_constraint // sizeof=0x80
{                                       // XREF: phys_free_list<rigid_body_constraint_custom_path>::T_internal/r
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    phys_mat44 m_path_mat;
    phys_vec3 b1_r_loc;
    user_rigid_body *m_urb;
    pulse_sum_cache m_list_psc[4];
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct gentity_s;

void    path_constraint_update(rigid_body_constraint_custom_path *vpc, gentity_s *veh);
rigid_body_constraint_custom_path * path_constraint_create(gentity_s *veh);
void __cdecl path_constraint_destroy(rigid_body_constraint_custom_path *vpc);
