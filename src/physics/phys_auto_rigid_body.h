#pragma once
#include "rigid_body.h"

struct centity_s;

struct auto_rigid_body // sizeof=0x1C
{
    user_rigid_body *rb;
    const centity_s *cent;
    int frame_count;
    auto_rigid_body *next;
    phys_inplace_avl_tree_node<auto_rigid_body> m_avl_node_info;
};

void __cdecl auto_rigid_body::add(const centity_s *cent, gjk_physics_collision_visitor *collision_visitor, int mask);
void __cdecl auto_rigid_body::remove_ent(const centity_s *cent);
user_rigid_body *__cdecl auto_rigid_body::ent_has_auto_rigid_body(const centity_s *cent);
void    auto_rigid_body::update(auto_rigid_body *a1@<ebp>);

void __thiscall tlAtomicReadWriteMutex::WriteLock(tlAtomicReadWriteMutex *this);
void __thiscall tlAtomicReadWriteMutex::ReadLock(tlAtomicReadWriteMutex *this);
void __thiscall tlAtomicReadWriteMutex::WriteUnlock(tlAtomicReadWriteMutex *this);
void __cdecl fixup_wheel_constraints_arb(auto_rigid_body *arb);
auto_rigid_body *__thiscall phys_simple_allocator<auto_rigid_body>::allocate(
                phys_simple_allocator<auto_rigid_body> *this);
void __thiscall phys_simple_allocator<auto_rigid_body>::free(
                phys_simple_allocator<auto_rigid_body> *this,
                auto_rigid_body *slot);
