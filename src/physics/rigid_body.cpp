#include "rigid_body.h"
#include "phys_assert.h"
#include "physics_system_internal.h"
#include <tl/physics/rbc_def_generic.h>
#include <physics/phys_constraint_solver_multithreaded.h>

void rigid_body::add_force(const phys_vec3 *force)
{
    this->m_force_sum.x = this->m_force_sum.x + force->x;
    this->m_force_sum.y = this->m_force_sum.y + force->y;
    this->m_force_sum.z = this->m_force_sum.z + force->z;
    if ( fabs(this->m_force_sum.x) > 100000.0
        || fabs(this->m_force_sum.y) > 100000.0
        || fabs(this->m_force_sum.z) > 100000.0 )
    {
        phys_exec_debug_callback(this);
    }
}

void rigid_body::set_inertia(const phys_vec3 *inertia)
{
    if ( inertia->x <= 0.000001 && _tlAssert("source/rigid_body.cpp", 8, "inertia.GetX() > 0.000001f", "") )
        __debugbreak();
    if ( inertia->y <= 0.000001 && _tlAssert("source/rigid_body.cpp", 9, "inertia.GetY() > 0.000001f", "") )
        __debugbreak();
    if ( inertia->z <= 0.000001 && _tlAssert("source/rigid_body.cpp", 10, "inertia.GetZ() > 0.000001f", "") )
        __debugbreak();

    this->m_inv_inertia.x = (1.0 / inertia->x);
    this->m_inv_inertia.y = (1.0 / inertia->y);
    this->m_inv_inertia.z = (1.0 / inertia->z);
}

void rigid_body::set_mass(float mass)
{
    if ( mass <= 0.000001 && _tlAssert("source/rigid_body.cpp", 17, "mass > 0.000001f", "") )
        __debugbreak();
    this->m_inv_mass = 1.0 / mass;
}

void user_rigid_body::setPosition(const phys_mat44 *const dictator)
{
    this->m_dictator_mat.x.x = dictator->x.x;
    this->m_dictator = &this->m_dictator_mat;
    this->m_dictator_mat.x.y = dictator->x.y;
    this->m_dictator_mat.x.z = dictator->x.z;
    this->m_dictator_mat.y.x = dictator->y.x;
    this->m_dictator_mat.y.y = dictator->y.y;
    this->m_dictator_mat.y.z = dictator->y.z;
    this->m_dictator_mat.z.x = dictator->z.x;
    this->m_dictator_mat.z.y = dictator->z.y;
    this->m_dictator_mat.z.z = dictator->z.z;
    this->m_dictator_mat.w.x = dictator->w.x;
    this->m_dictator_mat.w.y = dictator->w.y;
    this->m_dictator_mat.w.z = dictator->w.z;
}

void __thiscall rigid_body::set(
                float mass,
                const phys_vec3 *inertia,
                const phys_mat44 *mat,
                const phys_vec3 *t_vel,
                const phys_vec3 *a_vel,
                int stable_min_contact_count)
{
    double v8; // st7
    double v9; // st6
    bool v10; // c0
    bool v11; // c3
    double v12; // st7
    float v13; // [esp+10h] [ebp-10h]
    float v14; // [esp+10h] [ebp-10h]
    float v15; // [esp+10h] [ebp-10h]
    float v16; // [esp+10h] [ebp-10h]
    float v17; // [esp+10h] [ebp-10h]
    float v18; // [esp+10h] [ebp-10h]
    float v19; // [esp+10h] [ebp-10h]
    float v20; // [esp+10h] [ebp-10h]
    float v21; // [esp+10h] [ebp-10h]
    float v22; // [esp+10h] [ebp-10h]
    float v23; // [esp+10h] [ebp-10h]
    float v24; // [esp+10h] [ebp-10h]
    float v25; // [esp+10h] [ebp-10h]
    float v26; // [esp+10h] [ebp-10h]
    float v27; // [esp+10h] [ebp-10h]
    float v28; // [esp+10h] [ebp-10h]
    float v29; // [esp+10h] [ebp-10h]
    float v30; // [esp+10h] [ebp-10h]

    rigid_body::set_mass(mass);
    rigid_body::set_inertia(inertia);
    this->m_mat.x.x = mat->x.x;
    this->m_mat.x.y = mat->x.y;
    this->m_mat.x.z = mat->x.z;
    this->m_mat.y.x = mat->y.x;
    this->m_mat.y.y = mat->y.y;
    this->m_mat.y.z = mat->y.z;
    this->m_mat.z.x = mat->z.x;
    this->m_mat.z.y = mat->z.y;
    this->m_mat.z.z = mat->z.z;
    this->m_mat.w.x = mat->w.x;
    this->m_mat.w.y = mat->w.y;
    this->m_mat.w.z = mat->w.z;
    v8 = 100000.0;
    v13 = fabs(this->m_mat.w.x);
    if ( v13 > 100000.0 || (v14 = fabs(this->m_mat.w.y), v14 > 100000.0) || (v15 = fabs(this->m_mat.w.z), v15 > 100000.0) )
    {
        phys_exec_debug_callback(this);
        v8 = 100000.0;
    }
    this->m_last_position.x = this->m_mat.w.x;
    this->m_last_position.y = this->m_mat.w.y;
    this->m_last_position.z = this->m_mat.w.z;
    v16 = fabs(this->m_last_position.x);
    if ( v16 > v8 || (v17 = fabs(this->m_last_position.y), v17 > v8) || (v18 = fabs(this->m_last_position.z), v18 > v8) )
    {
        phys_exec_debug_callback(this);
        v8 = 100000.0;
    }
    this->m_moved_vec.x = PHYS_ZERO_VEC.x;
    this->m_moved_vec.y = PHYS_ZERO_VEC.y;
    this->m_moved_vec.z = PHYS_ZERO_VEC.z;
    v9 = 0.0;
    this->m_smallest_lambda = 0.0;
    this->m_t_vel.x = t_vel->x;
    this->m_t_vel.y = t_vel->y;
    this->m_t_vel.z = t_vel->z;
    this->m_a_vel.x = a_vel->x;
    this->m_a_vel.y = a_vel->y;
    this->m_a_vel.z = a_vel->z;
    v19 = fabs(this->m_t_vel.x);
    if ( v19 > v8 || (v20 = fabs(this->m_t_vel.y), v20 > v8) || (v21 = fabs(this->m_t_vel.z), v21 > v8) )
    {
        phys_exec_debug_callback(this);
        v8 = 100000.0;
        v9 = 0.0;
    }
    v22 = fabs(this->m_a_vel.x);
    if ( v22 > v8 || (v23 = fabs(this->m_a_vel.y), v23 > v8) || (v24 = fabs(this->m_a_vel.z), v24 > v8) )
    {
        phys_exec_debug_callback(this);
        v8 = 100000.0;
        v9 = 0.0;
    }
    this->m_stable_min_contact_count = stable_min_contact_count;
    this->m_force_sum.x =  PHYS_ZERO_VEC.x;
    this->m_force_sum.y =  PHYS_ZERO_VEC.y;
    this->m_force_sum.z =  PHYS_ZERO_VEC.z;
    this->m_torque_sum.x = PHYS_ZERO_VEC.x;
    this->m_torque_sum.y = PHYS_ZERO_VEC.y;
    this->m_torque_sum.z = PHYS_ZERO_VEC.z;
    this->m_last_t_vel.x = this->m_t_vel.x;
    this->m_last_t_vel.y = this->m_t_vel.y;
    this->m_last_t_vel.z = this->m_t_vel.z;
    this->m_last_a_vel.x = this->m_a_vel.x;
    this->m_last_a_vel.y = this->m_a_vel.y;
    this->m_last_a_vel.z = this->m_a_vel.z;
    v25 = fabs(this->m_last_t_vel.x);
    if ( v25 > v8 || (v26 = fabs(this->m_last_t_vel.y), v26 > v8) || (v27 = fabs(this->m_last_t_vel.z), v27 > v8) )
    {
        phys_exec_debug_callback(this);
        v8 = 100000.0;
        v9 = 0.0;
    }
    v28 = fabs(this->m_last_a_vel.x);
    if ( v28 > v8
        || (v29 = fabs(this->m_last_a_vel.y), v29 > v8)
        || (v30 = fabs(this->m_last_a_vel.z), v10 = v30 < v8, v11 = v30 == v8, v12 = v9, !v10 && !v11) )
    {
        phys_exec_debug_callback(this);
        v12 = 0.0;
    }
    this->m_gravity_acc_vec.x = v12;
    this->m_gravity_acc_vec.y = -9.8000002;
    this->m_gravity_acc_vec.z = v12;
    this->m_flags = 0;
    this->m_tick = 0;
    this->m_max_delta_t = 0.033898305;
    this->m_userdata = 0;
    this->m_max_avel = 1000.0;
    this->m_largest_vel_sq = 1000.0;
    this->m_stable_energy_time = v12;
    this->m_t_drag_coef = v12;
    this->m_a_drag_coef = v12;

    if ((g_physics_system->m_flags & 1) != 0)
    {
        rbint::collision_prolog(this, g_physics_system->m_outside_sub_delta_t);
    }

    PHYS_ASSERT_ORTHONORMAL(&this->m_mat);
}

void __thiscall rigid_body::add_force(
                const phys_vec3 *force,
                const phys_vec3 *point,
                float torque_mult)
{
    double v6; // st7
    float v7; // [esp-30h] [ebp-3Ch]
    float v8; // [esp-2Ch] [ebp-38h]
    float v9; // [esp-28h] [ebp-34h]
    float v10; // [esp-20h] [ebp-2Ch]
    float v11; // [esp-20h] [ebp-2Ch]
    float v12; // [esp-1Ch] [ebp-28h]
    float v13; // [esp-1Ch] [ebp-28h]
    float v14; // [esp-18h] [ebp-24h]
    float v15; // [esp-18h] [ebp-24h]
    float v16; // [esp-4h] [ebp-10h]
    float v17; // [esp-4h] [ebp-10h]
    float v18; // [esp-4h] [ebp-10h]
    float v19; // [esp-4h] [ebp-10h]
    float v20; // [esp-4h] [ebp-10h]
    float v21; // [esp-4h] [ebp-10h]

    this->m_force_sum.x = this->m_force_sum.x + force->x;
    this->m_force_sum.y = this->m_force_sum.y + force->y;
    this->m_force_sum.z = this->m_force_sum.z + force->z;
    v10 = point->x - this->m_mat.w.x;
    v12 = point->y - this->m_mat.w.y;
    v14 = point->z - this->m_mat.w.z;
    v7 = force->z * v12 - force->y * v14;
    v8 = v14 * force->x - force->z * v10;
    v9 = v10 * force->y - v12 * force->x;
    v11 = v7 * torque_mult;
    v13 = v8 * torque_mult;
    v15 = torque_mult * v9;
    this->m_torque_sum.x = this->m_torque_sum.x + v11;
    this->m_torque_sum.y = v13 + this->m_torque_sum.y;
    this->m_torque_sum.z = this->m_torque_sum.z + v15;
    v6 = 100000.0;
    v16 = fabs(this->m_force_sum.x);
    if ( v16 > 100000.0
        || (v17 = fabs(this->m_force_sum.y), v17 > 100000.0)
        || (v18 = fabs(this->m_force_sum.z), v18 > 100000.0) )
    {
        phys_exec_debug_callback(this);
        v6 = 100000.0;
    }
    v19 = fabs(this->m_torque_sum.x);
    if ( v19 > v6 || (v20 = fabs(this->m_torque_sum.y), v20 > v6) || (v21 = fabs(this->m_torque_sum.z), v6 < v21) )
        phys_exec_debug_callback(this);
}

void __thiscall user_rigid_body::set(const phys_mat44 *const dictator)
{
    double v3; // st7
    float dictatora; // [esp+14h] [ebp+8h]
    float dictatorb; // [esp+14h] [ebp+8h]
    float dictatorc; // [esp+14h] [ebp+8h]
    float dictatord; // [esp+14h] [ebp+8h]
    float dictatore; // [esp+14h] [ebp+8h]
    float dictatorf; // [esp+14h] [ebp+8h]

    if ( dictator )
    {
        //phys_mat44::operator=(&this->m_mat, dictator);
        this->m_mat = dictator;
        this->m_dictator = dictator;
    }
    else
    {
        this->m_dictator = &this->m_mat;
    }
    v3 = 100000.0;
    dictatora = fabs(this->m_mat.w.x);
    if ( dictatora > 100000.0
        || (dictatorb = fabs(this->m_mat.w.y), dictatorb > 100000.0)
        || (dictatorc = fabs(this->m_mat.w.z), dictatorc > 100000.0) )
    {
        phys_exec_debug_callback(this);
        v3 = 100000.0;
    }
    this->m_last_position.x = this->m_mat.w.x;
    this->m_last_position.y = this->m_mat.w.y;
    this->m_last_position.z = this->m_mat.w.z;
    dictatord = fabs(this->m_last_position.x);
    if ( dictatord > v3
        || (dictatore = fabs(this->m_last_position.y), dictatore > v3)
        || (dictatorf = fabs(this->m_last_position.z), v3 < dictatorf) )
    {
        phys_exec_debug_callback(this);
    }
    this->m_moved_vec.x = PHYS_ZERO_VEC.x;
    this->m_moved_vec.y = PHYS_ZERO_VEC.y;
    this->m_moved_vec.z = PHYS_ZERO_VEC.z;
    this->m_flags = 0;
    this->m_smallest_lambda = 0.0;
    this->m_inv_mass = 0.0;
    this->m_inv_inertia.x = PHYS_ZERO_VEC.x;
    this->m_inv_inertia.y = PHYS_ZERO_VEC.y;
    this->m_inv_inertia.z = PHYS_ZERO_VEC.z;
    this->m_t_vel.x = PHYS_ZERO_VEC.x;
    this->m_t_vel.y = PHYS_ZERO_VEC.y;
    this->m_t_vel.z = PHYS_ZERO_VEC.z;
    this->m_a_vel.x = PHYS_ZERO_VEC.x;
    this->m_a_vel.y = PHYS_ZERO_VEC.y;
    this->m_a_vel.z = PHYS_ZERO_VEC.z;
    this->m_last_t_vel.x = PHYS_ZERO_VEC.x;
    this->m_last_t_vel.y = PHYS_ZERO_VEC.y;
    this->m_last_t_vel.z = PHYS_ZERO_VEC.z;
    this->m_last_a_vel.x = PHYS_ZERO_VEC.x;
    this->m_last_a_vel.y = PHYS_ZERO_VEC.y;
    this->m_last_a_vel.z = PHYS_ZERO_VEC.z;
    this->m_gravity_acc_vec.x = PHYS_ZERO_VEC.x;
    this->m_gravity_acc_vec.y = PHYS_ZERO_VEC.y;
    this->m_gravity_acc_vec.z = PHYS_ZERO_VEC.z;
    this->m_flags |= 0x20u;
    this->m_max_delta_t = 0.033898305;
    this->m_node = 0;
    this->m_userdata = 0;
    if ( (g_physics_system->m_flags & 1) != 0 )
        rbint::collision_prolog(this, g_physics_system->m_outside_sub_delta_t);
}

void environment_rigid_body::set()
{
    float v2; // [esp+4h] [ebp-4h]
    float v3; // [esp+4h] [ebp-4h]
    float v4; // [esp+4h] [ebp-4h]

    this->m_inv_mass = 0.0;
    this->m_flags = 0;
    this->m_inv_inertia.x = PHYS_ZERO_VEC.x;
    this->m_inv_inertia.y = PHYS_ZERO_VEC.y;
    this->m_inv_inertia.z = PHYS_ZERO_VEC.z;
    SetIdentity(&this->m_mat);
    this->m_last_position.x = this->m_mat.w.x;
    this->m_last_position.y = this->m_mat.w.y;
    this->m_last_position.z = this->m_mat.w.z;
    v2 = fabs(this->m_last_position.x);
    if ( v2 > 100000.0
        || (v3 = fabs(this->m_last_position.y), v3 > 100000.0)
        || (v4 = fabs(this->m_last_position.z), v4 > 100000.0) )
    {
        phys_exec_debug_callback(this);
    }
    this->m_moved_vec.x = PHYS_ZERO_VEC.x;
    this->m_moved_vec.y = PHYS_ZERO_VEC.y;
    this->m_moved_vec.z = PHYS_ZERO_VEC.z;
    this->m_smallest_lambda = 0.0;
    this->m_t_vel.x = PHYS_ZERO_VEC.x;
    this->m_t_vel.y = PHYS_ZERO_VEC.y;
    this->m_t_vel.z = PHYS_ZERO_VEC.z;
    this->m_a_vel.x = PHYS_ZERO_VEC.x;
    this->m_a_vel.y = PHYS_ZERO_VEC.y;
    this->m_a_vel.z = PHYS_ZERO_VEC.z;
    this->m_last_t_vel.x = PHYS_ZERO_VEC.x;
    this->m_last_t_vel.y = PHYS_ZERO_VEC.y;
    this->m_last_t_vel.z = PHYS_ZERO_VEC.z;
    this->m_last_a_vel.x = PHYS_ZERO_VEC.x;
    this->m_last_a_vel.y = PHYS_ZERO_VEC.y;
    this->m_last_a_vel.z = PHYS_ZERO_VEC.z;
    this->m_gravity_acc_vec.x = PHYS_ZERO_VEC.x;
    this->m_gravity_acc_vec.y = PHYS_ZERO_VEC.y;
    this->m_gravity_acc_vec.z = PHYS_ZERO_VEC.z;
    this->m_flags |= 0x10u;
    this->m_max_delta_t = 0.033898305;
    this->m_node = 0;
    this->m_userdata = 0;
}


unsigned int rigid_body::is_user_rigid_body()
{
    return this->m_flags & 0x20;
}

void rigid_body::adjust_col_moved_vec(float lambda)
{
    double v3; // st7
    float v4; // [esp-30h] [ebp-3Ch]
    float v5; // [esp-2Ch] [ebp-38h]
    float v6; // [esp-28h] [ebp-34h]
    float v7; // [esp-20h] [ebp-2Ch]
    float v8; // [esp-1Ch] [ebp-28h]
    float v9; // [esp-18h] [ebp-24h]
    float v10; // [esp-4h] [ebp-10h]
    float v11; // [esp-4h] [ebp-10h]
    float v12; // [esp-4h] [ebp-10h]
    float v13; // [esp-4h] [ebp-10h]
    float v14; // [esp-4h] [ebp-10h]
    float v15; // [esp-4h] [ebp-10h]
    float v16; // [esp-4h] [ebp-10h]

    v7 = this->m_moved_vec.x * lambda;
    v8 = this->m_moved_vec.y * lambda;
    v9 = this->m_moved_vec.z * lambda;
    v4 = this->m_mat.w.x + v7;
    v5 = this->m_mat.w.y + v8;
    v6 = this->m_mat.w.z + v9;
    this->m_mat.w.x = v4;
    this->m_mat.w.y = v5;
    this->m_mat.w.z = v6;
    v10 = 1.0 - lambda;
    this->m_moved_vec.x = v10 * this->m_moved_vec.x;
    this->m_moved_vec.y = this->m_moved_vec.y * v10;
    this->m_moved_vec.z = v10 * this->m_moved_vec.z;
    v3 = 100000.0;
    v11 = fabs(this->m_moved_vec.x);
    if (v11 > 100000.0
        || (v12 = fabs(this->m_moved_vec.y), v12 > 100000.0)
        || (v13 = fabs(this->m_moved_vec.z), v13 > 100000.0))
    {
        phys_exec_debug_callback(this);
        v3 = 100000.0;
    }
    v14 = fabs(this->m_mat.w.x);
    if (v14 > v3 || (v15 = fabs(this->m_mat.w.y), v15 > v3) || (v16 = fabs(this->m_mat.w.z), v3 < v16))
        phys_exec_debug_callback(this);
}

void rigid_body_constraint_point::setup_constaint(struct pulse_sum_constraint_solver *phys, float delta_t)
{
    rigid_body *b2; // edi
    phys_vec3 b1_r; // [esp+20h] [ebp-3Ch] BYREF
    phys_vec3 b2_r; // [esp+30h] [ebp-2Ch] BYREF
    rigid_body *b1; // [esp+4Ch] [ebp-10h]
    void *retaddr; // [esp+5Ch] [ebp+0h]

    b2 = this->b2;
    phys_multiply(&b2_r, &b2->m_mat, &this->m_b2_r_loc);
    b1 = this->b1;
    phys_multiply(&b1_r, &b1->m_mat, &this->m_b1_r_loc);

    //pulse_sum_constraint_solver::create_point(
        phys->create_point(
        b1,
        &b1_r,
        b2,
        &b2_r,
        (pulse_sum_cache*)this->m_ps_cache_list,
        delta_t,
        this->m_spring_enabled,
        this->m_spring_k,
        this->m_damp_k);
}

void rigid_body_constraint_point::epilog_vel_constaint(float __formal)
{
    this->m_stress = this->m_ps_cache_list[1].m_pulse_sum * this->m_ps_cache_list[1].m_pulse_sum
        + this->m_ps_cache_list[0].m_pulse_sum * this->m_ps_cache_list[0].m_pulse_sum
        + this->m_ps_cache_list[2].m_pulse_sum * this->m_ps_cache_list[2].m_pulse_sum;
}

void rigid_body_constraint_point::set(const phys_vec3 *b1_r_loc, const phys_vec3 *b2_r_loc)
{
    this->m_b1_r_loc.x = b1_r_loc->x;
    this->m_b1_r_loc.y = b1_r_loc->y;
    this->m_b1_r_loc.z = b1_r_loc->z;

    this->m_b2_r_loc.x = b2_r_loc->x;
    this->m_b2_r_loc.y = b2_r_loc->y;
    this->m_b2_r_loc.z = b2_r_loc->z;
}

void rigid_body_constraint_distance::setup_constraint(struct pulse_sum_constraint_solver *psys, float delta_t)
{
    if (!(m_flags & 1))
        return;

    // Debug-style assertions preserved logically
    iassert(m_min_distance >= 0.0f);
    iassert(m_max_distance >= m_min_distance);

    rigid_body *b1 = this->b1;
    rigid_body *b2 = this->b2;

    phys_vec3 b1_local, b2_local;
    phys_multiply(&b1_local, &b1->m_mat, &m_b1_r_loc);
    phys_multiply(&b2_local, &b2->m_mat, &m_b2_r_loc);

    phys_vec3 b1_pt = b1->m_mat.w + b1_local;
    phys_vec3 b2_pt = b2->m_mat.w + b2_local;

    phys_vec3 delta = b2_pt - b1_pt;
    float dist_sq = phys_dot(&delta, &delta);

    if (dist_sq < 1e-6f)
        return;

    float dist = sqrtf(dist_sq);
    phys_vec3 normal = delta * (1.0f / dist);

    /* ===============================
       MAX DISTANCE CONSTRAINT
    =============================== */

    //pulse_sum_normal *max_n = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
    pulse_sum_normal *max_n = psys->create_pulse_sum_normal();

    phys_vec3 neg_normal = -normal;

    //pulse_sum_normal::set(
    max_n->set(
        b1,
        &b1_pt,
        b2,
        &b2_pt,
        &neg_normal,
        m_ps_cache_list,
        &PHYS_ZERO_VEC);

    max_n->m_pulse_sum_min = -10000000.0f;
    max_n->m_pulse_sum_max = 0.0f;

    float pos_adjust = -m_max_distance;

    //pulse_sum_normal::setup_vel_uni_standard_pos_adjust(
    max_n->setup_vel_uni_standard_pos_adjust(
        delta_t,
        pos_adjust,
        1700.0f);

    max_n->m_right_side += m_max_distance_vel;

    /* ===============================
       MIN DISTANCE CONSTRAINT
    =============================== */

    if (m_min_distance > 0.01f)
    {
        //pulse_sum_normal *min_n = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
        pulse_sum_normal *min_n = psys->create_pulse_sum_normal();

        //pulse_sum_normal::set(
            min_n->set(
            b1,
            &b1_pt,
            b2,
            &b2_pt,
            &normal,
            &m_ps_cache_list[1],
            &PHYS_ZERO_VEC);

        min_n->m_pulse_sum_min = -10000000.0f;
        min_n->m_pulse_sum_max = 0.0f;

        min_n->setup_vel_uni_standard_pos_adjust(
            delta_t,
            m_min_distance,
            1700.0f);
    }

    /* ===============================
       DAMPING (simplified but faithful)
    =============================== */

    if (m_damp_coef > 0.00001f)
    {
        float min_band = m_max_distance - 0.1f;
        float max_band = m_max_distance + 0.1f;

        if (dist >= min_band && dist <= max_band)
        {
            phys_vec3 rel_vel;
            //pulse_sum_normal::get_relative_velocity(max_n, this, &rel_vel);
            max_n->get_relative_velocity(&rel_vel);

            float proj = phys_dot(&rel_vel, &normal);
            phys_vec3 tangential = rel_vel - normal * proj;

            float mag = Abs((const float*)&tangential);

            if (mag > 0.0001f)
            {
                tangential *= (1.0f / mag);

                //pulse_sum_normal *damp = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
                pulse_sum_normal *damp = psys->create_pulse_sum_normal();

                //pulse_sum_normal::set(
                    damp->set(
                    b1,
                    &b1_pt,
                    b2,
                    &b2_pt,
                    &tangential,
                    &m_ps_cache_list[2],
                    &PHYS_ZERO_VEC);

                float cfm = 1.0f / (m_damp_coef * delta_t);

                damp->m_right_side = 0.0f;
                damp->m_big_dirt = 0.0f;
                damp->m_cfm = cfm;
                damp->m_denom += cfm;
                damp->m_pulse_sum_min = -10000000.0f;
                damp->m_pulse_sum_max = 10000000.0f;
            }
        }
    }
}


void rigid_body_constraint_hinge::set(
    const phys_vec3 *b1_r_loc,
    const phys_vec3 *b2_r_loc,
    const phys_vec3 *b1_axis_loc,
    const phys_vec3 *b2_axis_loc,
    const phys_vec3 *b1_ref_loc,
    const phys_vec3 *b2_ref_loc,
    float theta_min,
    float theta_max,
    float damp_k)
{
    m_flags = 0;

    // Anchor points
    m_b1_r_loc = *b1_r_loc;
    m_b2_r_loc = *b2_r_loc;

    // Unit axes
    m_b1_axis_loc = *phys_Unitize(&m_b1_axis_loc, b1_axis_loc);
    m_b2_axis_loc = *phys_Unitize(&m_b2_axis_loc, b2_axis_loc);

    // Reference direction on body1
    m_b1_ref_loc = *phys_Unitize(&m_b1_ref_loc, b1_ref_loc);

    // Build orthonormal basis around hinge axis (body1)
    m_b1_a1_loc = *construct_orth_ud(&m_b1_a1_loc, &m_b1_axis_loc);

    // a2 = axis × a1
    m_b1_a2_loc.x = m_b1_axis_loc.y * m_b1_a1_loc.z - m_b1_axis_loc.z * m_b1_a1_loc.y;
    m_b1_a2_loc.y = m_b1_a1_loc.x * m_b1_axis_loc.z - m_b1_a1_loc.z * m_b1_axis_loc.x;
    m_b1_a2_loc.z = m_b1_a1_loc.y * m_b1_axis_loc.x - m_b1_a1_loc.x * m_b1_axis_loc.y;

    phys_mat44 rot;

    // Min limit
    make_rotate(&rot, &m_b2_axis_loc, theta_min, 1000.0f);
    phys_vec3 tmp = *phys_multiply(&tmp, &rot, b2_ref_loc);
    m_b2_ref_min_loc = *phys_Unitize(&m_b2_ref_min_loc, &tmp);

    // Max limit
    make_rotate(&rot, &m_b2_axis_loc, theta_max, 1000.0f);
    tmp = *phys_multiply(&tmp, &rot, b2_ref_loc);
    m_b2_ref_max_loc = *phys_Unitize(&m_b2_ref_max_loc, &tmp);

    m_damp_k = damp_k;

    // Debug validation (matches original asserts)
    PHYS_ASSERT_UNIT(&m_b1_axis_loc);
    PHYS_ASSERT_UNIT(&m_b2_axis_loc);
    PHYS_ASSERT_UNIT(&m_b1_ref_loc);
    PHYS_ASSERT_UNIT(&m_b1_a1_loc);
    PHYS_ASSERT_UNIT(&m_b1_a2_loc);
    PHYS_ASSERT_UNIT(&m_b2_ref_min_loc);
    PHYS_ASSERT_UNIT(&m_b2_ref_max_loc);

    PHYS_ASSERT_ORTHOGONAL(&m_b1_axis_loc, &m_b1_ref_loc);
    PHYS_ASSERT_ORTHOGONAL(&m_b1_a1_loc, &m_b1_a2_loc);
}

void rigid_body_constraint_hinge::setup_constraint(
    pulse_sum_constraint_solver *psys,
    float delta_t)
{
    // Anchor point constraint (unless disabled)
    if (!(m_flags & 0x10))
    {
        phys_vec3 world_b2_r;
        phys_vec3 world_b1_r;

        phys_multiply(&world_b2_r, &b2->m_mat, &m_b2_r_loc);
        phys_multiply(&world_b1_r, &b1->m_mat, &m_b1_r_loc);

        //pulse_sum_constraint_solver::create_point(
            psys->create_point(
            b1,
            &world_b1_r,
            b2,
            &world_b2_r,
            m_ps_cache,
            delta_t,
            0,
            0.0f,
            0.0f);
    }

    // Transform hinge axes to world space
    phys_vec3 b1_axis_w, b2_axis_w;
    phys_vec3 b1_a1_w, b1_a2_w;

    phys_multiply(&b1_axis_w, &b1->m_mat, &m_b1_axis_loc);
    phys_multiply(&b2_axis_w, &b2->m_mat, &m_b2_axis_loc);
    phys_multiply(&b1_a2_w, &b1->m_mat, &m_b1_a2_loc);
    phys_multiply(&b1_a1_w, &b1->m_mat, &m_b1_a1_loc);

    //pulse_sum_constraint_solver::create_hinge(
        psys->create_hinge(
        b1,
        &b1_axis_w,
        b2,
        &b2_axis_w,
        &b1_a1_w,
        &b1_a2_w,
        &m_ps_cache[4],
        delta_t);

    // Angular damping
    if (m_damp_k > 1e-5f)
    {
        //auto *ang = pulse_sum_constraint_solver::create_pulse_sum_angular(
        auto *ang = psys->create_pulse_sum_angular(
            b1,
            &PHYS_ZERO_VEC,
            b2,
            &PHYS_ZERO_VEC,
            &b2_axis_w,
            &m_ps_cache[3]);

        float limit = delta_t * m_damp_k;

        ang->m_right_side = 0.0f;
        ang->m_big_dirt = 0.0f;
        ang->m_cfm = 0.0f;
        ang->m_pulse_sum_min = -limit;
        ang->m_pulse_sum_max = limit;
    }

    // --- Limit handling (preserved logic) ---

    phys_vec3 b1_ref_w, b2_ref_min_w, b2_ref_max_w;

    phys_multiply(&b1_ref_w, &b1->m_mat, &m_b1_ref_loc);
    phys_multiply(&b2_ref_min_w, &b2->m_mat, &m_b2_ref_min_loc);
    phys_multiply(&b2_ref_max_w, &b2->m_mat, &m_b2_ref_max_loc);

    // Original flag evaluation logic preserved
    // (Condensed for readability but functionally identical)

    float dot_min = b1_ref_w.x * b2_ref_min_w.x +
        b1_ref_w.y * b2_ref_min_w.y +
        b1_ref_w.z * b2_ref_min_w.z;

    float dot_max = b1_ref_w.x * b2_ref_max_w.x +
        b1_ref_w.y * b2_ref_max_w.y +
        b1_ref_w.z * b2_ref_max_w.z;

    if (dot_max > dot_min)
        m_flags = (m_flags & ~3u) | 2;
    else
        m_flags = (m_flags | 1u) & ~2u;

    // Lower limit constraint
    if (m_flags & 1)
    {
        phys_vec3 neg = -b1_ref_w;

        //auto *ang = pulse_sum_constraint_solver::create_pulse_sum_angular(
        auto *ang = psys->create_pulse_sum_angular(
            b1,
            &b1_ref_w,
            b2,
            &b2_ref_min_w,
            &neg,
            &m_ps_cache[6]);

        ang->m_pulse_sum_min = -10000000.0f;
        ang->m_pulse_sum_max = 0.0f;
        //pulse_sum_angular::setup_vel_uni_standard(ang, delta_t, 5.0f);
        ang->setup_vel_uni_standard(delta_t, 5.0f);
    }

    // Upper limit constraint
    if (m_flags & 2)
    {
        //auto *ang = pulse_sum_constraint_solver::create_pulse_sum_angular(
        auto *ang = psys->create_pulse_sum_angular(
            b1,
            &b1_ref_w,
            b2,
            &b2_ref_max_w,
            &b1_ref_w,
            &m_ps_cache[7]);

        ang->m_pulse_sum_min = -10000000.0f;
        ang->m_pulse_sum_max = 0.0f;
        //pulse_sum_angular::setup_vel_uni_standard(ang, delta_t, 5.0f);
        ang->setup_vel_uni_standard(delta_t, 5.0f);
    }
}
