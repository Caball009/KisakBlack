#include "rb_stream.h"

#include <cstring>

StreamBackendGlob streamBackendGlob;

void __cdecl RB_StreamInit()
{
    memset((unsigned __int8 *)&streamBackendGlob, 0, 0x210u);
    memset((unsigned __int8 *)&streamBackendGlob.maxLodBiasDirty[4], 0, 0x210u);
}

