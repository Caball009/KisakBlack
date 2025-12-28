#pragma once
#include <xanim/dobj.h>
#include <xanim/xanim.h>

struct ViewModelHand // sizeof=0x8
{                                       // XREF: ViewModelInfo/r
    int iPrevAnim;
    int iHandAnimIndex;
};

struct ViewModelInfo // sizeof=0x34
{
    DObj *viewModelDObj;
    int hasAnimTree;
    struct XAnimTree_s *tree;
    XAnim_s *anims;
    unsigned int partBits[5];
    ViewModelHand hand[2];
};

extern ViewModelInfo *cg_viewModelArray;

inline ViewModelInfo *__cdecl CG_GetLocalClientViewModelInfo(int localClientNum)
{
    if (localClientNum
        && !Assert_MyHandler(
            "c:\\projects_pc\\cod\\codsrc\\src\\cgame\\../cgame/cg_local.h",
            236,
            0,
            "%s\n\t(localClientNum) = %i",
            "(localClientNum == 0)",
            localClientNum))
    {
        __debugbreak();
    }
    return cg_viewModelArray;
}