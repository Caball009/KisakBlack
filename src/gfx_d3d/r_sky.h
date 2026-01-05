#pragma once

#include "r_image.h"

struct sunflare_t // sizeof=0x60
{                                       // XREF: GfxWorld/r
    bool hasValidData;
    // padding byte
    // padding byte
    // padding byte
    Material *spriteMaterial;
    Material *flareMaterial;
    float spriteSize;
    float flareMinSize;
    float flareMinDot;
    float flareMaxSize;
    float flareMaxDot;
    float flareMaxAlpha;
    int flareFadeInTime;
    int flareFadeOutTime;
    float blindMinDot;
    float blindMaxDot;
    float blindMaxDarken;
    int blindFadeInTime;
    int blindFadeOutTime;
    float glareMinDot;
    float glareMaxDot;
    float glareMaxLighten;
    int glareFadeInTime;
    int glareFadeOutTime;
    float sunFxPosition[3];
};

void __cdecl R_RegisterSunDvars();
void __cdecl R_SetSunFromDvars(sunflare_t *sun);
void __cdecl R_LoadSunThroughDvars(const char *sunName, sunflare_t *sun);
unsigned int __cdecl R_GetSunDvarCount();
void __cdecl R_Cmd_LoadSun();
void __cdecl R_Cmd_SaveSun();
void __cdecl R_SaveSunFromDvars(const char *sunName);
void __cdecl R_FlushSun();
