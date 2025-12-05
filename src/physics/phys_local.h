#pragma once
#include <universal/assertive.h>

struct phys_vec2 // sizeof=0x8
{                                                                             // XREF: contact_manifold_mesh_point/r
                                                                                // phys_contact_manifold_process::bridge/r ...
        float x;                                                        // XREF: phys_contact_manifold::generate_convex_poly_internal(void)+59/w
                                                                                // phys_contact_manifold::generate_convex_poly_internal(void)+70/w ...
        float y;                                                        // XREF: phys_contact_manifold::generate_convex_poly_internal(void)+68/w
                                                                                // phys_contact_manifold::generate_convex_poly_internal(void)+7C/w ...
};

struct phys_vec3 // sizeof=0x10
{                                                                             // XREF: .data:PHYS_X_VEC/r
        float x;                                                        // XREF: gjkcc_info::update_cg(float const * const,float const * const,bool)+1F2/r
        float y;                                                        // XREF: gjkcc_info::update_cg(float const * const,float const * const,bool)+209/r
        float z;                                                        // XREF: gjkcc_info::update_cg(float const * const,float const * const,bool)+221/r
        float w;                                                        // XREF: standard_query::query(broad_phase_environment_query_input const &,broad_phase_environement_query_results *)+440/r

        inline phys_vec3& operator*=(float d)
        {
            this->x = this->x * d;
            this->y = this->y * d;
            this->z = d * this->z;

            return *this;
        }

        inline phys_vec3& operator+=(const phys_vec3 *v)
        {
            this->x = this->x + v->x;
            this->y = this->y + v->y;
            this->z = this->z + v->z;
            return *this;
        }

        inline phys_vec3& operator-=(const phys_vec3 *v)
        {
            this->x = this->x - v->x;
            this->y = this->y - v->y;
            this->z = this->z - v->z;
            return *this;
        }

        inline phys_vec3& operator/=(const float d)
        {
            float d_inv; // [esp+8h] [ebp+8h]

            d_inv = 1.0 / d;
            this->x = this->x * d_inv;
            this->y = this->y * d_inv;
            this->z = d_inv * this->z;
            return *this;
        }

        inline phys_vec3 & operator=(const phys_vec3 *v)
        {
            this->x = v->x;
            this->y = v->y;
            this->z = v->z;
            return *this;
        }

        inline float * operator[](unsigned int i)
        {
            iassert(i >= 0 && i < 3);
            return (float *)this + i;
        }

        //inline const float * operator[](unsigned int i)
        //{
        //    iassert(i >= 0 && i < 3);
        //    return (const float *)this + i;
        //}
};

struct phys_mat44 // sizeof=0x40
{                                                                             // XREF: .data:PHYS_IDENTITY_MATRIX/r
    phys_mat44(
        const phys_vec3 *x_,
        const phys_vec3 *y_,
        const phys_vec3 *z_,
        const phys_vec3 *w_)
    {
        this->x = *x_;
        this->y = *y_;
        this->z = *z_;
        this->w = *w_;
    }

    void fix_w_column()
    {
        this->x.w = 0.0f;
        this->y.w = 0.0f;
        this->z.w = 0.0f;
        this->w.w = 1.0f;
    }

    phys_mat44& operator=(const phys_mat44 *that)
    {
            this->x.x = that->x.x;
            this->x.y = that->x.y;
            this->x.z = that->x.z;
            this->y.x = that->y.x;
            this->y.y = that->y.y;
            this->y.z = that->y.z;
            this->z.x = that->z.x;
            this->z.y = that->z.y;
            this->z.z = that->z.z;
            this->w.x = that->w.x;
            this->w.y = that->w.y;
            this->w.z = that->w.z;
            return *this;
    }
                                                                            // .data:PHYS_IDENTITY_MATRIX_0/r ...
    phys_vec3 x;                                                // XREF: gjk_cylinder_t::get_feature(phys_contact_manifold *)+63/r
    // gjk_cylinder_t::get_feature(phys_contact_manifold *)+70/r ...
    phys_vec3 y;                                                // XREF: gjk_cylinder_t::get_feature(phys_contact_manifold *)+95/o
    // SetIdentity(phys_mat44 &)+20/r ...
    phys_vec3 z;                                                // XREF: gjk_cylinder_t::get_feature(phys_contact_manifold *):loc_834A44/o
    // SetIdentity(phys_mat44 &)+3B/r ...
    phys_vec3 w;                                                // XREF: phys_calc_world_aabb(phys_vec3 const &,phys_vec3 const &,phys_mat44 const &,phys_vec3 *,phys_vec3 *)+10/w
    // create_obb_gjk_geom(float const (* const)[3],float const * const,float const * const,int,gjk_collision_visitor *)+10/w ...
};

template <typename T>
struct phys_link_list_base//<pulse_sum_node> // sizeof=0x4
{                                                                             // XREF: pulse_sum_node/r
        //pulse_sum_node *m_next_link;
        T *m_next_link;
};

template <typename T>
struct phys_simple_link_list//<contact_point_info> // sizeof=0x4
{                                                                             // XREF: rigid_body_constraint_contact/r
                                                                                // rigid_body_constraint_contact/r
        //contact_point_info *m_first;
        T *m_first;
};

char *__cdecl PMM_ALLOC(unsigned int size, unsigned int alignment);
void __cdecl PMM_VALIDATE(char *ptr, unsigned int size, unsigned int alignment);
void __cdecl PMM_FREE(unsigned __int8 *ptr, unsigned int size, unsigned int alignment);

template <typename T>
struct phys_simple_allocator//<phys_heap_gjk_cache_system_avl_tree::phys_gjk_cache_info_internal> // sizeof=0x4
{                                                                             // XREF: phys_heap_gjk_cache_system_avl_tree/r
        int m_count;

        T *allocate()
        {
                char *slot; // [esp+18h] [ebp-4h]

                slot = PMM_ALLOC(sizeof(T), sizeof(T) % 16 == 0 ? 16 : 4);
                if (!slot)
                        return 0;
                ++this->m_count;
                return (T*)slot;
        }

        void free(T *slot)
        {
                if (slot)
                {
                        PMM_VALIDATE((char *)slot, sizeof(T), sizeof(T) % 16 == 0 ? 16 : 4);
                        --this->m_count;
                        PMM_FREE((unsigned __int8 *)slot, sizeof(T), sizeof(T) % 16 == 0 ? 16 : 4);
                }
        }
};

//gjk_aabb_t *__thiscall phys_simple_allocator<gjk_aabb_t>::allocate(phys_simple_allocator<gjk_aabb_t> *this);
//gjk_obb_t *__thiscall phys_simple_allocator<gjk_obb_t>::allocate(phys_simple_allocator<gjk_obb_t> *this);
//gjk_brush_t *__thiscall phys_simple_allocator<gjk_brush_t>::allocate(phys_simple_allocator<gjk_brush_t> *this);
//void __thiscall phys_simple_allocator<gjk_brush_t>::free(phys_simple_allocator<gjk_brush_t> *this, gjk_brush_t *slot);
//gjk_partition_t *__thiscall phys_simple_allocator<gjk_partition_t>::allocate(
//        phys_simple_allocator<gjk_partition_t> *this);
//void __thiscall phys_simple_allocator<gjk_partition_t>::free(
//        phys_simple_allocator<gjk_partition_t> *this,
//        gjk_partition_t *slot);
//gjk_double_sphere_t *__thiscall phys_simple_allocator<gjk_double_sphere_t>::allocate(
//        phys_simple_allocator<gjk_double_sphere_t> *this);
//void __thiscall phys_simple_allocator<gjk_double_sphere_t>::free(
//        phys_simple_allocator<gjk_double_sphere_t> *this,
//        gjk_double_sphere_t *slot);
//gjk_cylinder_t *__thiscall phys_simple_allocator<gjk_cylinder_t>::allocate(phys_simple_allocator<gjk_cylinder_t> *this);
//void __thiscall phys_simple_allocator<gjk_cylinder_t>::free(
//        phys_simple_allocator<gjk_cylinder_t> *this,
//        gjk_cylinder_t *slot);
//gjk_polygon_cylinder_t *__thiscall phys_simple_allocator<gjk_polygon_cylinder_t>::allocate(
//        phys_simple_allocator<gjk_polygon_cylinder_t> *this);
//void __thiscall phys_simple_allocator<gjk_polygon_cylinder_t>::free(
//        phys_simple_allocator<gjk_polygon_cylinder_t> *this,
//        gjk_polygon_cylinder_t *slot);

struct phys_memory_heap // sizeof=0x10
{                                                                             // XREF: phys_contact_manifold_process/r
        char *m_buffer_start;
        char *m_buffer_end;
        char *m_buffer_cur;
        char *m_user_start;

        //char *phys_memory_heap::fast_allocate(phys_memory_heap *this, int size, const char *error_msg);
        char *fast_allocate(int size, const char *error_msg);
};

template <typename T, int SIZE>
struct __declspec(align(16)) phys_static_array
{
    char m_buffer[sizeof(T) * SIZE];
    T *const m_slot_array;
    int m_alloc_count;

private:
    bool is_member(T *data)
    {
        return (data >= this->m_slot_array && data < &this->m_slot_array[this->m_alloc_count]);
    }
public:

    phys_static_array()
    {
        m_slot_array = &m_buffer;
        m_alloc_count = 0;
    }

    T *operator[](int i)
    {
        iassert(i >= 0 && i < m_alloc_count);
        return &this->m_slot_array[i];
    }

    T *add(int no_error, const char *error_msg)
    {
        if (m_alloc_count < 512)
        {
            return &this->m_slot_array[m_alloc_count++];
        }
        else
        {
            if (!no_error)
            {
                tlFatal(error_msg);
            }
            return NULL;
        }
    }

    T *back()
    {
        iassert(m_alloc_count > 0);

        return &this->m_slot_array[m_alloc_count - 1];
    }

    T *get_list_head()
    {
        iassert(m_alloc_count > 0);

        return this->m_slot_array;
    }

    void remove_slow(T *data)
    {
        iassert(is_member(data));

        *data = &this->m_slot_array[--this->m_alloc_count];
    }
};


#define PTR_LIST_SIZE 256

// whoever wrote this class is a crackhead
template <typename T>
struct phys_free_list
{
public:
    struct T_internal_base
    {
        T_internal_base *m_prev_T_internal;
        T_internal_base *m_next_T_internal;
    };
    static_assert(sizeof(T_internal_base) == 8);

    struct __declspec(align(16)) T_internal : T_internal_base
    {
        T m_data;
        int m_ptr_list_index;
    };

    T_internal_base m_dummy_head;

    int m_list_count;
    int m_list_count_high_water;

    T *m_ptr_list[PTR_LIST_SIZE];
    int m_ptr_list_count;

public:

    void debug_add(phys_free_list<NitrousVehicle>::T_internal *T_i)
    {
        int m_list_count; // [esp+0h] [ebp-10h]

        if (this->m_list_count_high_water <= this->m_list_count)
            m_list_count = this->m_list_count;
        else
            m_list_count = this->m_list_count_high_water;
        this->m_list_count_high_water = m_list_count;
        if (this->m_ptr_list_count >= PTR_LIST_SIZE)
        {
            T_i->m_ptr_list_index = -1;
        }
        else
        {
            T_i->m_ptr_list_index = this->m_ptr_list_count;
            this->m_ptr_list[this->m_ptr_list_count++] = &T_i->m_data;
        }
    }

    T *add(int no_error, const char *error_msg)
    {
        T_internal *ptr;

        ptr = (T_internal *)PMM_ALLOC(sizeof(T), sizeof(T) % 16 == 0 ? 16 : 4);

        if (ptr)
        {
            new (&ptr->m_data) T();
            ptr->m_prev_T_internal = &this->m_dummy_head;
            ptr->m_next_T_internal = this->m_dummy_head.m_next_T_internal;
            this->m_dummy_head.m_next_T_internal->m_prev_T_internal = ptr;
            this->m_dummy_head.m_next_T_internal = ptr;
            
            m_list_count++;

            debug_add(ptr);

            return &ptr->m_data;
        }
        else
        {
            iassert(no_error);
            return NULL;
        }
    }

    void debug_remove(T_internal *T_i)
    {
        if (T_i->m_ptr_list_index != -1)
        {
            iassert(T_i->m_ptr_list_index >= 0 && T_i->m_ptr_list_index < PTR_LIST_SIZE);
            iassert(m_ptr_list[T_i->m_ptr_list_index] == &T_i->m_data);

            this->m_ptr_list[--this->m_ptr_list_count][1].m_wheel_state[0].m_state = T_i->m_ptr_list_index;
            this->m_ptr_list[T_i->m_ptr_list_index] = this->m_ptr_list[this->m_ptr_list_count];
        }
    }

    void remove(T_internal *data)
    {
        T_internal_base *next; // [esp+14h] [ebp-8h]
        T_internal_base *prev; // [esp+18h] [ebp-4h]

        iassert(data);

        --this->m_list_count;
        debug_remove(data);
        next = data->m_next_T_internal;
        prev = data->m_prev_T_internal;
        prev->m_next_T_internal = next;
        next->m_prev_T_internal = prev;
        PMM_FREE((unsigned __int8 *)data, sizeof(T), sizeof(T) % 16 == 0 ? 16 : 4);
    }

    void remove(T *data_)
    {
        if (data_)
        {
            PMM_VALIDATE((char *)data_ - (sizeof(T) % 16 == 0 ? 16 : 8), sizeof(T), (sizeof(T) % 16 == 0 ? 16 : 4));
            remove((T_internal*)((char *)data_ - (sizeof(T) % 16 == 0 ? 16 : 8)));
        }
    }
};


// oh fuck yes, in the compiler this is slurped into every file and duplicated 68 times
static const phys_vec3 PHYS_X_VEC = { 1.0f, 0.0f, 0.0f, 0.0f };
static const phys_vec3 PHYS_Y_VEC = { 0.0f, 1.0f, 0.0f, 0.0f };
static const phys_vec3 PHYS_Z_VEC = { 0.0f, 0.0f, 1.0f, 0.0f };

static const phys_vec3 PHYS_ZERO_VEC = { 0.0f, 0.0f, 0.0f, 0.0f };

static const phys_mat44 PHYS_IDENTITY_MATRIX =
{
        .x = PHYS_X_VEC,
        .y = PHYS_Y_VEC,
        .z = PHYS_Z_VEC,

        .w = { PHYS_ZERO_VEC }
};

static const float PHYS_PI = 3.1415927f;
static const float PHYS_PI_TIMES_2 = 6.2831855f;
static const float PHYS_PI_OVER_2 = 1.5707964f;

#define PHYS_ALIGNOF(type) alignof(type)
