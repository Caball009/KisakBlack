#include "bg_misctables.h"
#include <universal/q_shared.h>
#include <qcommon/common.h>
#include <clientscript/cscr_stringlist.h>
#include <clientscript/cscr_vm.h>
#include <client/cl_keys.h>
#include <qcommon/graph.h>

const char *s_vehicleCameraModes[6] = { "first", "chase", "view", "strafe", "horse", "oldtank" };
const char *s_vehicleBoostModes[2] = { "burst", "continuous" };
const char *s_tractionTypeNames[3] = { "TRACTION_TYPE_FRONT", "TRACTION_TYPE_BACK", "TRACTION_TYPE_ALL_WD" };
const char *s_vehicleClassNames[7] = { "4 wheel", "motorcycle", "tank", "plane", "boat", "artillery", "helicopter" };

int __cdecl VEH_ParseSpecificField(unsigned __int8 *pStruct, char *pValue, int fieldType, int fieldOffset)
{
    const char *v4; // eax
    const char *v5; // eax
    float v7; // [esp+0h] [ebp-10h]
    float v8; // [esp+4h] [ebp-Ch]
    int i; // [esp+Ch] [ebp-4h]
    int ia; // [esp+Ch] [ebp-4h]
    int ib; // [esp+Ch] [ebp-4h]
    int ic; // [esp+Ch] [ebp-4h]

    switch ( fieldType )
    {
        case 15:
            i = 0;
            break;
        case 16:
            ia = 0;
            while ( 2 )
            {
                if ( ia < 6 )
                {
                    if ( I_stricmp(pValue, s_vehicleCameraModes[ia]) )
                    {
                        ++ia;
                        continue;
                    }
                    *((_WORD *)pStruct + 54) = ia;
                }
                break;
            }
            if ( ia == 6 )
                Com_Error(ERR_DROP, "Unknown vehicle camera mode [%s]", pValue);
            return 1;
        case 17:
            ib = 0;
            while ( 2 )
            {
                if ( ib < 2 )
                {
                    if ( I_stricmp(pValue, s_vehicleBoostModes[ib]) )
                    {
                        ++ib;
                        continue;
                    }
                    *((_WORD *)pStruct + 176) = ib;
                }
                break;
            }
            if ( ib == 2 )
                Com_Error(ERR_DROP, "Unknown vehicle boost mode [%s]", pValue);
            return 1;
        case 18:
            ic = 0;
            while ( 2 )
            {
                if ( ic < 3 )
                {
                    if ( I_stricmp(pValue, s_tractionTypeNames[ic]) )
                    {
                        ++ic;
                        continue;
                    }
                    *((unsigned int *)pStruct + 1863) = ic;
                }
                break;
            }
            if ( ic == 3 )
                Com_Error(ERR_DROP, "Unknown traction type [%s]", pValue);
            return 1;
        case 19:
            v8 = atof(pValue);
            *(float *)&pStruct[fieldOffset] = v8 * 17.6;
            return 1;
        case 20:
            v7 = atof(pValue);
            *(float *)&pStruct[fieldOffset] = v7 * 0.001;
            return 1;
        case 21:
            *(unsigned int *)&pStruct[fieldOffset] = SL_FindLowercaseString(pValue, SCRIPTINSTANCE_SERVER);
            return 1;
        case 22:
            if ( I_stricmp(pValue, "axis") )
            {
                if ( I_stricmp(pValue, "allies") )
                {
                    v4 = va("unknown team '%s', should be axis or allies\n", pValue);
                    Scr_Error(v4, 0);
                }
                else
                {
                    *((unsigned int *)pStruct + 1797) = 2;
                }
            }
            else
            {
                *((unsigned int *)pStruct + 1797) = 1;
            }
            return 1;
        case 23:
            *(unsigned int *)&pStruct[fieldOffset] = Key_StringToKeynum(pValue);
            return 1;
        case 24:
            *(unsigned int *)&pStruct[fieldOffset] = (unsigned int)GraphFloat_Load(pValue);
            return 1;
        default:
            v5 = va("Bad vehicle field type %i\n", fieldType);
            if ( !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\bgame\\bg_misctables.cpp", 528, 0, v5) )
                __debugbreak();
            Com_Error(ERR_DROP, "Bad vehicle field type %i", fieldType);
            return 0;
    }
    while ( 1 )
    {
        if ( i >= 7 )
            goto LABEL_7;
        if ( !I_stricmp(pValue, s_vehicleClassNames[i]) )
            break;
        ++i;
    }
    *((_WORD *)pStruct + 32) = i;
LABEL_7:
    if ( i == 7 )
        Com_Error(ERR_DROP, "Unknown vehicle type [%s]", pValue);
    return 1;
}

