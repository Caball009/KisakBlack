#pragma once

#include <universal/dvar.h>

enum TerrainFireSource : __int32
{                                       // XREF: ?GetFoliageBurnRadius@@YAMW4TerrainFireSource@@@Z/r
                                        // ?CG_SetFireToWall@@YAXHQAMPAHHW4TerrainFireSource@@@Z/r ...
    TFS_DEFAULT      = 0x0,
    TFS_FLAMETHROWER = 0x1,
};

struct FM_ACTIVECELL_DATA // sizeof=0x1C
{                                       // XREF: .data:FM_ACTIVECELL_DATA * g_FM_ActiveCells/r
    float pos[3];
    bool is_active;                     // XREF: CG_UpdateFire(int)+3C/r
                                        // CG_UpdateFire(int)+60/w ...
    // padding byte
    // padding byte
    // padding byte
    int endtime;                        // XREF: CG_UpdateFire(int)+52/r
                                        // CG_SetFireToTerrain(float * const,float,int,int,float,int *,int,TerrainFireSource)+26B/w ...
    int fireStarterClientNum;
    int weaponUsed;
};

void __cdecl BG_Flame_RegisterDvars();
void __cdecl BG_InitFire();
void __cdecl BG_ShutdownFire();
void __cdecl BG_ResetFire();
bool __cdecl TerrainScorch_AllowSurfacesCallback(int surfIndex);
void __cdecl TerrainScorch(float *loresCellPos, bool instant);
unsigned __int16 __cdecl HalfFromFloat(float floatIn);
double __cdecl FloatFromHalf(unsigned __int16 halfIn);
void __cdecl CG_UpdateFire(int localClientNum);
void __cdecl CG_RenderFire();
double __cdecl GetFoliageBurnRadius(TerrainFireSource fireSrc);
void __cdecl CG_SetFireToWall(int localClientNum, float *pos, int *models, int models_count, TerrainFireSource fireSrc);
void __cdecl CG_SetFireToTerrain(
                float *pos,
                float radius,
                int fireStarterClientNum,
                int weaponUsed,
                float pSpread,
                int *models,
                int models_count,
                TerrainFireSource fireSrc);
void __cdecl AddBurnCell(float *pos);
void __cdecl SetTerrainScorchInitialState();
void __cdecl Sync_VisualBurn_To_FM_State();
//void __cdecl MemFile_WriteInt(MemoryFile *memFile, int value);
void __cdecl CG_GenerateFireSounds(int localClientNum);

extern const dvar_t *fire_audio_repeat_duration;
extern const dvar_t *fire_audio_random_max_duration;
extern const dvar_t *fire_world_damage_duration;
extern const dvar_t *fire_burn_time;
extern const dvar_t *fire_world_damage;
extern const dvar_t *fire_world_damage_rate;
extern const dvar_t *fire_debug;