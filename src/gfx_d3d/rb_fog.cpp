#include "rb_fog.h"
#include "r_dvars.h"
#include "r_scene.h"

void    R_SetFrameFog(GfxCmdBufInput *input, const GfxViewInfo *viewInfo)
{
    const GfxBackEndData *v1; // ebp
    long double v2; // [esp+18h] [ebp-84h]
    long double v3; // [esp+18h] [ebp-84h]
    long double v4; // [esp+18h] [ebp-84h]
    long double v5; // [esp+18h] [ebp-84h]
    long double v6; // [esp+18h] [ebp-84h]
    long double v7; // [esp+18h] [ebp-84h]
    float v8; // [esp+2Ch] [ebp-70h]
    float v9; // [esp+30h] [ebp-6Ch]
    float v10; // [esp+3Ch] [ebp-60h] BYREF
    float parms2[4]; // [esp+40h] [ebp-5Ch] BYREF
    float fog_maxDensity; // [esp+50h] [ebp-4Ch]
    float fog_density; // [esp+54h] [ebp-48h]
    float viewerZ; // [esp+58h] [ebp-44h] BYREF
    float fogColorVec[4]; // [esp+5Ch] [ebp-40h]
    float v16; // [esp+6Ch] [ebp-30h] BYREF
    float parms[4]; // [esp+70h] [ebp-2Ch]
    float endAng; // [esp+80h] [ebp-1Ch]
    float v19; // [esp+84h] [ebp-18h]
    float startAng; // [esp+88h] [ebp-14h]
    float v21; // [esp+8Ch] [ebp-10h]
    GfxFog *slopeAng; // [esp+90h] [ebp-Ch]
    GfxBackEndData *data; // [esp+94h] [ebp-8h]
    //const GfxBackEndData *da; // [esp+98h] [ebp-4h]
    //int field_1; // [esp+9Ch] [ebp+0h]

    //da = v1;
    //field_1 = args->field_1;
    if (r_fog->current.enabled)
    {
        data = (GfxBackEndData*)input->data;

        iassert(data);

        slopeAng = &data->fogSettings;
        R_SetInputCodeConstantFromVec4(input, 0x3Du, data->fogSettings.sunFogColor);
        R_SetInputCodeConstantFromVec4(input, 0x3Cu, data->fogSettings.sunFogDir);
        v21 = 1.0e7f;
        startAng = data->fogSettings.sunFogStartAng * 0.017453292;
        //__libm_sse2_cos(v2);
        startAng = cos(startAng);
        v19 = startAng;
        endAng = data->fogSettings.sunFogEndAng * 0.017453292;
        //__libm_sse2_cos(v3);
        endAng = cos(endAng);
        parms[3] = endAng;
        if ((float)(startAng - endAng) != 0.0)
            v21 = 1.0 / (float)(v19 - parms[3]);
        v16 = (-(parms[3])) * v21;
        parms[0] = v21;
        parms[1] = 0.0f;
        parms[2] = 0.0f;
        R_SetInputCodeConstantFromVec4(input, 0x3Bu, &v16);
        //LODWORD(fogColorVec[3]) = slopeAng->color;
        viewerZ = slopeAng->color[0];
        fogColorVec[0] = slopeAng->color[1];
        fogColorVec[1] = slopeAng->color[2];
        fogColorVec[2] = slopeAng->color[3];
        R_SetInputCodeConstantFromVec4(input, 0x3Au, &viewerZ);
        fog_density = viewInfo->cullViewInfo.viewParms.origin[2] - slopeAng->baseHeight;
        fog_maxDensity = slopeAng->density;
        parms2[3] = slopeAng->maxDensity;
        if (fog_maxDensity == 0.0)
        {
            R_SetInputCodeConstant(input, 0x38u, 0.0, 0.0, 0.0, 0.0);
            R_SetInputCodeConstant(input, 0x39u, 0.0, 0.0, 0.0, 0.0);
        }
        //else
        //{
        //    memset(parms2, 0, 12);
        //    if (parms2[3] > (float)(100.0 * fog_maxDensity))
        //        parms2[3] = 100.0 * fog_maxDensity;
        //    if (fog_maxDensity > parms2[3])
        //        parms2[3] = fog_maxDensity;
        //    __libm_sse2_log(v4);
        //    __libm_sse2_log(v5);
        //    v9 = (float)(fog_maxDensity / parms2[3]) - (float)((float)(slopeAng->heightDensity * fog_density) * (float)2.0);
        //    v16 = v9;
        //    if (v9 >= 0.0)
        //    {
        //        v8 = v9 + 1.0;
        //    }
        //    else
        //    {
        //        __libm_sse2_exp(v6);
        //        v8 = v9;
        //    }
        //    v10 = v8;
        //    parms[0] = -(parms2[3]);
        //    parms[1] = fog_maxDensity * slopeAng->fogStart;
        //    __libm_sse2_log(v6);
        //    parms[2] = (-(slopeAng->heightDensity)) * 2.0f;
        //    if (slopeAng->heightDensity > 0.0)
        //    {
        //        __libm_sse2_log(v7);
        //        parms[0] = parms[0] * (float)2.0;
        //    }
        //    R_SetInputCodeConstantFromVec4(input, 0x38u, &v16);
        //    R_SetInputCodeConstantFromVec4(input, 0x39u, &v10);
        //}
        // aislop (log/exp sse aids)
        else
        {
            float logRatio;
            float log2;

            memset(parms2, 0, 12);

            if (parms2[3] > (float)(100.0 * fog_maxDensity))
                parms2[3] = (float)(100.0 * fog_maxDensity);
            if (fog_maxDensity > parms2[3])
                parms2[3] = fog_maxDensity;

            /* log(fog_density / parms2[3]) */
            logRatio = logf(fog_density / parms2[3]);

            /* log(2.0) */
            log2 = logf(2.0f);

            v9 = logRatio - (float)((float)(slopeAng->heightDensity * fog_density) * log2);
            v16 = v9;

            if (v9 < 0.0f)
                v8 = expf(v9);
            else
                v8 = v9 + 1.0f;

            v10 = v8;

            parms[0] = -parms2[3];
            parms[1] = fog_maxDensity * slopeAng->fogStart;
            parms[2] = -slopeAng->heightDensity * log2;

            if (slopeAng->heightDensity > 0.0f)
                parms[0] *= log2;

            R_SetInputCodeConstantFromVec4(input, 0x38u, &v16);
            R_SetInputCodeConstantFromVec4(input, 0x39u, &v10);
        }
    }
    else
    {
        R_SetInputCodeConstant(input, 0x38u, 0.0, 0.0, 0.0, 0.0);
        R_SetInputCodeConstant(input, 0x39u, 0.0, 0.0, 0.0, 0.0);
    }
}

