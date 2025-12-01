#pragma once
#include <clientscript/cscr_main.h>
#include "dobj.h"

#include <d3d9.h>
#include <flame/flame_system.h>

enum XAssetType : __int32
{                                       // XREF: XAsset/r
    ASSET_TYPE_XMODELPIECES      = 0x0,
    ASSET_TYPE_PHYSPRESET        = 0x1,
    ASSET_TYPE_PHYSCONSTRAINTS   = 0x2,
    ASSET_TYPE_DESTRUCTIBLEDEF   = 0x3,
    ASSET_TYPE_XANIMPARTS        = 0x4,
    ASSET_TYPE_XMODEL            = 0x5,
    ASSET_TYPE_MATERIAL          = 0x6,
    ASSET_TYPE_TECHNIQUE_SET     = 0x7,
    ASSET_TYPE_IMAGE             = 0x8,
    ASSET_TYPE_SOUND             = 0x9,
    ASSET_TYPE_SOUND_PATCH       = 0xA,
    ASSET_TYPE_CLIPMAP           = 0xB,
    ASSET_TYPE_CLIPMAP_PVS       = 0xC,
    ASSET_TYPE_COMWORLD          = 0xD,
    ASSET_TYPE_GAMEWORLD_SP      = 0xE,
    ASSET_TYPE_GAMEWORLD_MP      = 0xF,
    ASSET_TYPE_MAP_ENTS          = 0x10,
    ASSET_TYPE_GFXWORLD          = 0x11,
    ASSET_TYPE_LIGHT_DEF         = 0x12,
    ASSET_TYPE_UI_MAP            = 0x13,
    ASSET_TYPE_FONT              = 0x14,
    ASSET_TYPE_MENULIST          = 0x15,
    ASSET_TYPE_MENU              = 0x16,
    ASSET_TYPE_LOCALIZE_ENTRY    = 0x17,
    ASSET_TYPE_WEAPON            = 0x18,
    ASSET_TYPE_WEAPONDEF         = 0x19,
    ASSET_TYPE_WEAPON_VARIANT    = 0x1A,
    ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1B,
    ASSET_TYPE_FX                = 0x1C,
    ASSET_TYPE_IMPACT_FX         = 0x1D,
    ASSET_TYPE_AITYPE            = 0x1E,
    ASSET_TYPE_MPTYPE            = 0x1F,
    ASSET_TYPE_MPBODY            = 0x20,
    ASSET_TYPE_MPHEAD            = 0x21,
    ASSET_TYPE_CHARACTER         = 0x22,
    ASSET_TYPE_XMODELALIAS       = 0x23,
    ASSET_TYPE_RAWFILE           = 0x24,
    ASSET_TYPE_STRINGTABLE       = 0x25,
    ASSET_TYPE_PACK_INDEX        = 0x26,
    ASSET_TYPE_XGLOBALS          = 0x27,
    ASSET_TYPE_DDL               = 0x28,
    ASSET_TYPE_GLASSES           = 0x29,
    ASSET_TYPE_EMBLEMSET         = 0x2A,
    ASSET_TYPE_COUNT             = 0x2B,
    ASSET_TYPE_STRING            = 0x2B,
    ASSET_TYPE_ASSETLIST         = 0x2C,
};

union XAssetHeader // sizeof=0x4
{                                       // XREF: CG_AddVisionSetMenuItem+13/r
    struct XModelPieces *xmodelPieces;
    struct PhysPreset *physPreset;
    struct PhysConstraints *physConstraints;
    struct DestructibleDef *destructibleDef;
    struct XAnimParts *parts;
    struct XModel *model;
    struct Material *material;
    struct MaterialPixelShader *pixelShader;
    struct MaterialVertexShader *vertexShader;
    struct MaterialTechniqueSet *techniqueSet;
    struct GfxImage *image;
    struct SndBank *sound;
    struct SndPatch *soundPatch;
    struct clipMap_t *clipMap;
    struct ComWorld *comWorld;
    struct GameWorldSp *gameWorldSp;
    struct GameWorldMp *gameWorldMp;
    struct MapEnts *mapEnts;
    struct GfxWorld *gfxWorld;
    struct GfxLightDef *lightDef;
    struct Font_s *font;
    struct MenuList *menuList;
    struct menuDef_t *menu;
    struct LocalizeEntry *localize;
    struct WeaponVariantDef *weapon;
    struct SndDriverGlobals *sndDriverGlobals;
    struct FxEffectDef *fx;
    struct FxImpactTable *impactFx;
    struct RawFile *rawfile;
    struct StringTable *stringTable;
    struct PackIndex *packIndex;
    struct XGlobals *xGlobals;
    struct ddlRoot_t *ddlRoot;
    struct Glasses *glasses;
    struct TextureList *textureList;
    struct EmblemSet *emblemSet;
    void *data;
};

struct XAnimParam // sizeof=0x14
{
    char strName[16];
    float fValue;
};

union XAnimIndices // sizeof=0x4
{                                       // XREF: XAnimLoadFile(char const *,void * (*)(int),bool)+1808/w
                                        // XAnimLoadFile(char const *,void * (*)(int),bool)+1840/w ...
    unsigned __int8 *_1;
    unsigned __int16 *_2;
    void *data;
};

struct XAnimNotifyInfo // sizeof=0x8
{
    unsigned __int16 name;
    // padding byte
    // padding byte
    float time;
};

union XAnimDynamicFrames // sizeof=0x4
{                                       // XREF: XAnimCalcNonLoopEnd+9ED/w
                                        // XAnimCalcNonLoopEnd+9F3/r ...
    unsigned __int8 (*_1)[3];
    unsigned __int16 (*_2)[3];
};

union XAnimDynamicIndices // sizeof=0x2
{                                       // XREF: XAnimPartTransFrames/r
                                        // XAnimDeltaPartQuatDataFrames/r ...
    unsigned __int8 _1[1];
    unsigned __int16 _2[1];
};

struct __declspec(align(4)) XAnimPartTransFrames // sizeof=0x20
{                                       // XREF: XAnimPartTransData/r
    float mins[3];
    float size[3];
    XAnimDynamicFrames frames;
    XAnimDynamicIndices indices;
    // padding byte
    // padding byte
};

union XAnimPartTransData // sizeof=0x20
{                                       // XREF: XAnimPartTrans/r
    XAnimPartTransFrames frames;
    float frame0[3];
};

struct XAnimPartTrans // sizeof=0x24
{
    unsigned __int16 size;
    unsigned __int8 smallTrans;
    // padding byte
    XAnimPartTransData u;
};

struct __declspec(align(4)) XAnimDeltaPartQuatDataFrames // sizeof=0x8
{                                       // XREF: XAnimDeltaPartQuatData/r
    __int16 (*frames)[2];
    XAnimDynamicIndices indices;
    // padding byte
    // padding byte
};

union XAnimDeltaPartQuatData // sizeof=0x8
{                                       // XREF: XAnimDeltaPartQuat/r
    XAnimDeltaPartQuatDataFrames frames;
    __int16 frame0[2];
};

struct XAnimDeltaPartQuat // sizeof=0xC
{
    unsigned __int16 size;
    // padding byte
    // padding byte
    XAnimDeltaPartQuatData u;
};

struct XAnimDeltaPart // sizeof=0x8
{
    XAnimPartTrans *trans;
    XAnimDeltaPartQuat *quat;
};

struct XAnimParts // sizeof=0x68
{                                       // XREF: XAssetPoolEntry<XAnimParts>/r
    const char *name;
    unsigned __int16 dataByteCount;
    unsigned __int16 dataShortCount;
    unsigned __int16 dataIntCount;
    unsigned __int16 randomDataByteCount;
    unsigned __int16 randomDataIntCount;
    unsigned __int16 numframes;
    bool bLoop;
    bool bDelta;
    bool bLeftHandGripIK;
    bool bStreamable;
    unsigned int streamedFileSize;
    unsigned __int8 boneCount[10];
    unsigned __int8 notifyCount;
    unsigned __int8 assetType;
    bool isDefault;
    // padding byte
    // padding byte
    // padding byte
    unsigned int randomDataShortCount;
    unsigned int indexCount;
    float framerate;
    float frequency;
    float primedLength;
    float loopEntryTime;
    unsigned __int16 *names;
    unsigned __int8 *dataByte;
    __int16 *dataShort;
    int *dataInt;
    __int16 *randomDataShort;
    unsigned __int8 *randomDataByte;
    int *randomDataInt;
    XAnimIndices indices;
    XAnimNotifyInfo *notify;
    XAnimDeltaPart *deltaPart;
};

struct XAnimParent // sizeof=0x4
{                                       // XREF: $AE2C40205408E7677B548FCC327D21B5/r
    unsigned __int16 flags;
    unsigned __int16 children;
};

union $AE2C40205408E7677B548FCC327D21B5 // sizeof=0x4
{                                       // XREF: XAnimClearTreeGoalWeightsInternal+42/r
                                        // XAnimClearTreeGoalWeightsInternal+5F/r ...
    XAnimParts *parts;
    XAnimParent animParent;
};

struct XAnimEntry // sizeof=0x10
{                                       // XREF: XAnim_s/r
    unsigned __int16 bCreated;
    unsigned __int16 numAnims;
    unsigned __int16 firstParamIxPlusOne;
    unsigned __int16 paramCount;
    unsigned __int16 parent;
    // padding byte
    // padding byte
    $AE2C40205408E7677B548FCC327D21B5 ___u5;
};

struct XAnim_s // sizeof=0x28
{                                       // XREF: XAnim/r
    const char *debugName;
    unsigned int size;
    unsigned int paramSize;
    XAnimParam *params;
    const char **debugAnimNames;
    bool *wasLoggedIfMissing;
    XAnimEntry entries[1];
};

struct XAnimTree_s // sizeof=0x8
{                                       // XREF: XAnimTree/r
    XAnim_s *anims;
    unsigned __int16 children;
    __int16 inst;
};

union $C8C573B57ACA1D7542AD56C4163862EC // sizeof=0x4
{                                       // XREF: XModel/r
    unsigned __int16 *localBoneNames;
    unsigned __int16 *boneNames;
};

union $37E13A30061EC97EDA76440B3BA5E97A // sizeof=0x4
{                                       // XREF: XModel/r
    unsigned __int8 *localParentList;
    unsigned __int8 *parentList;
};

union $BF9640C0B3AB5E078C286DD9616EC22F // sizeof=0x4
{                                       // XREF: XModel/r
    __int16 *localQuats;
    __int16 *quats;
};

union $E1CD6A013C1D28F2956F4983A8D1052C // sizeof=0x4
{                                       // XREF: XModel/r
    float *localTrans;
    float *trans;
};

struct __declspec(align(4)) XBoneInfo // sizeof=0x2C
{                                       // XREF: XModelDefault/r
    float bounds[2][3];
    float offset[3];
    float radiusSquared;
    unsigned __int8 collmap;
    // padding byte
    // padding byte
    // padding byte
};

union $AD77717FA1177FEDD3D106F4B139C8DB // sizeof=0x4
{                                       // XREF: XModel/r
    XBoneInfo *localBoneInfo;
    XBoneInfo *boneInfo;
};

struct XSurfaceVertexInfo // sizeof=0x10
{                                       // XREF: XSurface/r
    __int16 vertCount[4];
    unsigned __int16 *vertsBlend;
    float *tensionData;
};

struct XSurfaceCollisionAabb // sizeof=0xC
{                                       // XREF: XSurfaceCollisionNode/r
    unsigned __int16 mins[3];
    unsigned __int16 maxs[3];
};

struct XSurfaceCollisionNode // sizeof=0x10
{
    XSurfaceCollisionAabb aabb;
    unsigned __int16 childBeginIndex;
    unsigned __int16 childCount;
};

struct XSurfaceCollisionLeaf // sizeof=0x2
{
    unsigned __int16 triangleBeginIndex;
};

struct XSurfaceCollisionTree // sizeof=0x28
{
    float trans[3];
    float scale[3];
    unsigned int nodeCount;
    XSurfaceCollisionNode *nodes;
    unsigned int leafCount;
    XSurfaceCollisionLeaf *leafs;
};

struct XRigidVertList // sizeof=0xC
{                                       // XREF: ?XModelReadSurface@@YAXPAUXModel@@PAPBEP6APAXH@ZPAUXSurface@@HPBD@Z/r
    unsigned __int16 boneOffset;        // XREF: XModelReadSurface(XModel *,uchar const * *,void * (*)(int),XSurface *,int,char const *)+28A/r
                                        // XModelReadSurface(XModel *,uchar const * *,void * (*)(int),XSurface *,int,char const *)+A3A/r
    unsigned __int16 vertCount;         // XREF: XModelReadSurface(XModel *,uchar const * *,void * (*)(int),XSurface *,int,char const *)+FDB/r
    unsigned __int16 triOffset;         // XREF: XModelReadSurface(XModel *,uchar const * *,void * (*)(int),XSurface *,int,char const *)+F8B/w
                                        // XModelReadSurface(XModel *,uchar const * *,void * (*)(int),XSurface *,int,char const *)+F9C/r
    unsigned __int16 triCount;          // XREF: XModelReadSurface(XModel *,uchar const * *,void * (*)(int),XSurface *,int,char const *)+1027/w
                                        // XModelReadSurface(XModel *,uchar const * *,void * (*)(int),XSurface *,int,char const *)+1038/r
    XSurfaceCollisionTree *collisionTree;
};

union GfxColor // sizeof=0x4
{                                       // XREF: RB_AddWaypoint+286/w
                                        // RB_AddWaypoint+2C5/r ...
    unsigned int packed;
    unsigned __int8 array[4];
};

union PackedTexCoords // sizeof=0x4
{                                       // XREF: Vec2PackTexCoords(float const * const)+120/w
                                        // Vec2PackTexCoords(float const * const)+123/r ...
    unsigned int packed;
};

union PackedUnitVec // sizeof=0x4
{                                       // XREF: FX_GenSpriteVerts+8BE/w
                                        // FX_GenSpriteVerts+986/w ...
    unsigned int packed;
    unsigned __int8 array[4];
};


struct GfxPackedVertex // sizeof=0x20
{                                       // XREF: GfxPackedVertex0/r
                                        // GfxPackedVertex1/r ...
    float xyz[3];
    float binormalSign;
    GfxColor color;                     // XREF: R_GenerateQuadStampCodeMeshVertsArray(Material *,renderQuad_t *,int,float (* const)[3])+175/o
                                        // R_GenerateQuadStampCodeMeshVertsArray(Material *,renderQuad_t *,int,float (* const)[3])+41C/o
    PackedTexCoords texCoord;
    PackedUnitVec normal;               // XREF: R_GenerateQuadStampCodeMeshVertsArray(Material *,renderQuad_t *,int,float (* const)[3])+2C3/w
    PackedUnitVec tangent;              // XREF: R_GenerateQuadStampCodeMeshVertsArray(Material *,renderQuad_t *,int,float (* const)[3])+419/w
};

struct XSurface // sizeof=0x44
{
    unsigned __int8 tileMode;
    unsigned __int8 vertListCount;
    unsigned __int16 flags;
    unsigned __int16 vertCount;
    unsigned __int16 triCount;
    unsigned __int16 baseTriIndex;
    unsigned __int16 baseVertIndex;
    unsigned __int16 *triIndices;
    XSurfaceVertexInfo vertInfo;
    GfxPackedVertex *verts0;
    IDirect3DVertexBuffer9 *vb0;
    XRigidVertList *vertList;
    IDirect3DIndexBuffer9 *indexBuffer;
    int partBits[5];
};

struct XModelLodInfo // sizeof=0x20
{                                       // XREF: XModel/r
    float dist;
    unsigned __int16 numsurfs;
    unsigned __int16 surfIndex;
    int partBits[5];
    unsigned __int8 lod;
    unsigned __int8 smcIndexPlusOne;
    unsigned __int8 smcAllocBits;
    unsigned __int8 unused;
};

struct XModelCollTri_s // sizeof=0x30
{                                       // XREF: XModelCollTri/r
    float plane[4];
    float svec[4];
    float tvec[4];
};

struct XModelCollSurf_s // sizeof=0x2C
{                                       // XREF: XModelCollSurf/r
    XModelCollTri_s *collTris;
    int numCollTris;
    float mins[3];
    float maxs[3];
    int boneIdx;
    int contents;
    int surfFlags;
};

struct XModelHighMipBounds // sizeof=0x10
{
    float center[3];
    float himipRadiusSq;
};

struct XModelStreamInfo // sizeof=0x4
{                                       // XREF: XModel/r
    XModelHighMipBounds *highMipBounds;
};

struct Collmap // sizeof=0x4
{
    PhysGeomList *geomList;
};

enum ConstraintType : __int32
{                                       // XREF: PhysConstraint/r
                                        // ?XDoll_IsXDollConstraint@@YA_NW4ConstraintType@@@Z/r
    CONSTRAINT_NONE       = 0x0,
    CONSTRAINT_POINT      = 0x1,
    CONSTRAINT_DISTANCE   = 0x2,
    CONSTRAINT_HINGE      = 0x3,
    CONSTRAINT_JOINT      = 0x4,
    CONSTRAINT_ACTUATOR   = 0x5,
    CONSTRAINT_FAKE_SHAKE = 0x6,
    CONSTRAINT_LAUNCH     = 0x7,
    CONSTRAINT_ROPE       = 0x8,
    CONSTRAINT_LIGHT      = 0x9,
    NUM_CONSTRAINT_TYPES  = 0xA,
};

enum AttachPointType : __int32
{                                       // XREF: PhysConstraint/r
                                        // PhysConstraint/r ...
    ATTACH_POINT_WORLD  = 0x0,
    ATTACH_POINT_DYNENT = 0x1,
    ATTACH_POINT_ENT    = 0x2,
    ATTACH_POINT_BONE   = 0x3,
};


struct PhysConstraint // sizeof=0xA8
{                                       // XREF: PhysConstraints/r
    unsigned __int16 targetname;
    // padding byte
    // padding byte
    ConstraintType type;
    AttachPointType attach_point_type1;
    int target_index1;
    unsigned __int16 target_ent1;
    // padding byte
    // padding byte
    const char *target_bone1;
    AttachPointType attach_point_type2;
    int target_index2;
    unsigned __int16 target_ent2;
    // padding byte
    // padding byte
    const char *target_bone2;
    float offset[3];
    float pos[3];
    float pos2[3];
    float dir[3];
    int flags;
    int timeout;
    int min_health;
    int max_health;
    float distance;
    float damp;
    float power;
    float scale[3];
    float spin_scale;
    float minAngle;
    float maxAngle;
    struct Material *material;
    int constraintHandle;
    int rope_index;
    int centity_num[4];
};

struct PhysConstraints // sizeof=0xA88
{                                       // XREF: XAssetPoolEntry<PhysConstraints>/r
    const char *name;
    unsigned int count;
    PhysConstraint data[16];
};


struct XModel // sizeof=0xFC
{                                       // XREF: XAssetPoolEntry<XModel>/r
    const char *name;
    unsigned __int8 numBones;
    unsigned __int8 numRootBones;
    unsigned __int8 numsurfs;
    unsigned __int8 lodRampType;
    $C8C573B57ACA1D7542AD56C4163862EC ___u5;
    $37E13A30061EC97EDA76440B3BA5E97A ___u6;
    $BF9640C0B3AB5E078C286DD9616EC22F ___u7;
    $E1CD6A013C1D28F2956F4983A8D1052C ___u8;
    unsigned __int8 *partClassification;
    DObjAnimMat *baseMat;
    XSurface *surfs;
    struct Material **materialHandles;
    XModelLodInfo lodInfo[4];
    unsigned __int8 lodDistAutoGenerated;
    // padding byte
    // padding byte
    // padding byte
    XModelCollSurf_s *collSurfs;
    int numCollSurfs;
    int contents;
    $AD77717FA1177FEDD3D106F4B139C8DB ___u18;
    float radius;
    float mins[3];
    float maxs[3];
    __int16 numLods;
    __int16 collLod;
    XModelStreamInfo streamInfo;
    int memUsage;
    int flags;
    bool bad;
    // padding byte
    // padding byte
    // padding byte
    PhysPreset *physPreset;
    unsigned __int8 numCollmaps;
    // padding byte
    // padding byte
    // padding byte
    Collmap *collmaps;
    PhysConstraints *physConstraints;
};

struct XModelNameMap // sizeof=0x4
{                                       // XREF: ?XAnimResetAnimMap@@YAXPBUDObj@@I@Z/r
    unsigned __int16 name;              // XREF: XAnimResetAnimMap(DObj const *,uint)+10/w
    unsigned __int16 index;
};


struct XAnimSimpleRotPos // sizeof=0x18
{                                       // XREF: ?XAnimCalcDelta@@YAXPAUDObj@@IQAM1_N@Z/r
    float rot[2];                       // XREF: XAnimCalcDelta(DObj *,uint,float * const,float * const,bool)+13B/r
    float posWeight;                    // XREF: XAnimGetRelDelta(XAnim_s const *,uint,float * const,float * const,float,float)+97/w
    float pos[3];                       // XREF: XAnimCalcDelta(DObj *,uint,float * const,float * const,bool)+19C/r
};

struct XAnimClientNotifyList // sizeof=0x604
{                                       // XREF: ?CG_UpdateViewWeaponAnim@@YAXHH@Z/r
    unsigned __int8 m_clientNotifyMemory[1536];
    int m_numNotifies;
};

struct __declspec(align(4)) XAnimState // sizeof=0x20
{                                       // XREF: XAnimInfo/r
                                        // ?DObjInitServerTime@@YAXPAUDObj@@M@Z/r ...
    float currentAnimTime;              // XREF: XAnimInit(void)+6A/w
                                        // XAnimGetTime(XAnimTree_s const *,uint)+ED/r ...
    float oldTime;                      // XREF: XAnimInit(void)+70/w
    __int16 cycleCount;                 // XREF: XAnimInit(void)+76/w
                                        // DObjInitServerTime(DObj *,float)+5C/w ...
    __int16 oldCycleCount;
    float goalTime;                     // XREF: XAnimInit(void)+7C/w
    float goalWeight;                   // XREF: XAnimInit(void)+82/w
                                        // XAnimSetCompleteGoalWeightNode+9A/r ...
    float weight;                       // XREF: XAnimInit(void)+88/w
                                        // XAnimGetWeight(XAnimTree_s const *,uint)+ED/r
    float rate;                         // XREF: XAnimInit(void)+8E/w
                                        // XAnimSetAnimRate(XAnimTree_s *,uint,float)+12B/w
    bool instantWeightChange;           // XREF: XAnimInit(void)+94/w
    // padding byte
    // padding byte
    // padding byte
};

struct __declspec(align(4)) XAnimInfo // sizeof=0x40
{                                       // XREF: .data:g_xAnimInfo/r
                                        // XAnimInfoArray/r
    unsigned __int16 notifyChild;
    __int16 notifyIndex;
    unsigned __int16 notifyName;
    unsigned __int16 notifyType;
    unsigned __int16 prev;              // XREF: XAnimInit(void)+3E/w
                                        // XAnimFreeInfo+269/w ...
    unsigned __int16 next;              // XREF: XAnimInit(void)+5F/w
                                        // XAnimGetInfoIndex_r+7A/r ...
    unsigned __int16 children;          // XREF: XAnimResetTime+16/r
                                        // XAnimCloneInitTime+DC/r ...
    unsigned __int16 parent;            // XREF: XAnimClearTreeGoalWeightsInternal+55/r
                                        // XAnimClearGoalWeightKnobInternal+9F/r ...
    unsigned __int16 animIndex;         // XREF: XAnimGetInfoIndex_r+BC/r
                                        // XAnimClearTreeGoalWeightsInternal+F2/r ...
    unsigned __int16 animToModel;       // XREF: XAnimClearTreeGoalWeightsInternal+31/r
                                        // XAnimClearGoalWeightKnobInternal+1D8/r
    $AE2C40205408E7677B548FCC327D21B5 ___u10;
                                        // XREF: XAnimClearTreeGoalWeightsInternal+42/r
                                        // XAnimClearTreeGoalWeightsInternal+5F/r ...
    XAnimState state;                   // XREF: XAnimInit(void)+6A/w
                                        // XAnimInit(void)+70/w ...
    XAnimParts *streamedParts;
    unsigned __int16 streamedAnimToModel;
    // padding byte
    // padding byte
};

struct XAnimServerNotify // sizeof=0xC
{                                       // XREF: ?G_DObjUpdateServerTime@@YAXPAUgentity_s@@HP6AXXZ@Z/r
    unsigned __int16 entNum;            // XREF: G_DObjUpdateServerTime(gentity_s *,int,void (*)(void))+DE/r
    unsigned __int16 notifyName;        // XREF: G_DObjUpdateServerTime(gentity_s *,int,void (*)(void))+CA/r
    unsigned __int16 notetrackName;     // XREF: G_DObjUpdateServerTime(gentity_s *,int,void (*)(void))+AE/r
    // padding byte
    // padding byte
    float fPercentTime;
};

struct XAnimServerNotifyList // sizeof=0xC
{                                       // XREF: ?G_DObjUpdateServerTime@@YAXPAUgentity_s@@HP6AXXZ@Z/r
    XAnimServerNotify *pList;           // XREF: G_DObjUpdateServerTime(gentity_s *,int,void (*)(void))+41/w
    int iNumElements;                   // XREF: G_DObjUpdateServerTime(gentity_s *,int,void (*)(void))+4B/w
    int iCurrentElement;                // XREF: G_DObjUpdateServerTime(gentity_s *,int,void (*)(void))+44/w
                                        // G_DObjUpdateServerTime(gentity_s *,int,void (*)(void))+9E/r
};

struct XAnimDeltaInfo // sizeof=0x4
{                                       // XREF: ?XAnimCalcDelta@@YAXPAUDObj@@IQAM1_N@Z/r
                                        // XAnimCalcDeltaTree/r ...
    bool bClear;                        // XREF: XAnimCalcDelta(DObj *,uint,float * const,float * const,bool):loc_7F186B/w
                                        // XAnimCalcDelta(DObj *,uint,float * const,float * const,bool)+121/r ...
    bool bNormQuat;                     // XREF: XAnimCalcDelta(DObj *,uint,float * const,float * const,bool)+10F/w
                                        // XAnimCalcDeltaTree+3A1/w ...
    bool bAbs;                          // XREF: XAnimCalcDelta(DObj *,uint,float * const,float * const,bool)+113/w
                                        // XAnimCalcDeltaTree+125/r ...
    bool bUseGoalWeight;                // XREF: XAnimCalcDelta(DObj *,uint,float * const,float * const,bool)+11A/w
                                        // XAnimCalcDeltaTree+1F1/r ...
};

struct XAnimTime // sizeof=0xC
{                                       // XREF: XAnimCalcParts_unsigned_char_/r
    float time;
    float frameFrac;                    // XREF: XAnimCalcParts_unsigned_char_+29E/w
    int frameIndex;                     // XREF: XAnimCalcParts_unsigned_char_+28E/r
};

enum weapClass_t : __int32
{                                       // XREF: WeaponDef/r
                                        // ?BG_GetWeaponClassName@@YAPBDW4weapClass_t@@@Z/r
    WEAPCLASS_RIFLE          = 0x0,
    WEAPCLASS_MG             = 0x1,
    WEAPCLASS_SMG            = 0x2,
    WEAPCLASS_SPREAD         = 0x3,
    WEAPCLASS_PISTOL         = 0x4,
    WEAPCLASS_GRENADE        = 0x5,
    WEAPCLASS_ROCKETLAUNCHER = 0x6,
    WEAPCLASS_TURRET         = 0x7,
    WEAPCLASS_NON_PLAYER     = 0x8,
    WEAPCLASS_GAS            = 0x9,
    WEAPCLASS_ITEM           = 0xA,
    WEAPCLASS_MELEE          = 0xB,
    WEAPCLASS_KILLSTREAK_ALT_STORED_WEAPON = 0xC,
    WEAPCLASS_NUM            = 0xD,
};

enum PenetrateType : __int32
{                                       // XREF: WeaponDef/r
    PENETRATE_TYPE_NONE   = 0x0,
    PENETRATE_TYPE_SMALL  = 0x1,
    PENETRATE_TYPE_MEDIUM = 0x2,
    PENETRATE_TYPE_LARGE  = 0x3,
    PENETRATE_TYPE_COUNT  = 0x4,
};

enum ImpactType : __int32
{                                       // XREF: WeaponDef/r
    IMPACT_TYPE_NONE            = 0x0,
    IMPACT_TYPE_BULLET_SMALL    = 0x1,
    IMPACT_TYPE_BULLET_LARGE    = 0x2,
    IMPACT_TYPE_BULLET_AP       = 0x3,
    IMPACT_TYPE_BULLET_XTREME   = 0x4,
    IMPACT_TYPE_SHOTGUN         = 0x5,
    IMPACT_TYPE_GRENADE_BOUNCE  = 0x6,
    IMPACT_TYPE_GRENADE_EXPLODE = 0x7,
    IMPACT_TYPE_RIFLE_GRENADE   = 0x8,
    IMPACT_TYPE_ROCKET_EXPLODE  = 0x9,
    IMPACT_TYPE_ROCKET_EXPLODE_XTREME = 0xA,
    IMPACT_TYPE_PROJECTILE_DUD  = 0xB,
    IMPACT_TYPE_MORTAR_SHELL    = 0xC,
    IMPACT_TYPE_TANK_SHELL      = 0xD,
    IMPACT_TYPE_BOLT            = 0xE,
    IMPACT_TYPE_BLADE           = 0xF,
    IMPACT_TYPE_COUNT           = 0x10,
};

enum weapFireType_t : __int32
{                                       // XREF: WeaponDef/r
                                        // ?CG_UpdateMinigunTags@@YAXPAUcg_s@@PAUcentity_s@@PBUDObj@@QAH@Z/r
    WEAPON_FIRETYPE_FULLAUTO   = 0x0,
    WEAPON_FIRETYPE_SINGLESHOT = 0x1,
    WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
    WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
    WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
    WEAPON_FIRETYPE_STACKED    = 0x5,
    WEAPON_FIRETYPE_MINIGUN    = 0x6,
    WEAPON_FIRETYPECOUNT       = 0x7,
};

enum weapClipType_t : __int32
{                                       // XREF: WeaponDef/r
    WEAPON_CLIPTYPE_BOTTOM = 0x0,
    WEAPON_CLIPTYPE_TOP    = 0x1,
    WEAPON_CLIPTYPE_LEFT   = 0x2,
    WEAPON_CLIPTYPE_DP28   = 0x3,
    WEAPON_CLIPTYPE_PTRS   = 0x4,
    WEAPON_CLIPTYPE_LMG    = 0x5,
    WEAPON_CLIPTYPECOUNT   = 0x6,
};

enum OffhandClass : __int32
{                                       // XREF: WeaponDef/r
                                        // ?CG_OwnerDraw@@YAXHUrectDef_s@@MMMMHHHHQAMPAUMaterial@@@Z/r ...
    OFFHAND_CLASS_NONE          = 0x0,
    OFFHAND_CLASS_FRAG_GRENADE  = 0x1,
    OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
    OFFHAND_CLASS_FLASH_GRENADE = 0x3,
    OFFHAND_CLASS_GEAR          = 0x4,
    OFFHAND_CLASS_COUNT         = 0x5,
};

enum weapStance_t : __int32
{                                       // XREF: WeaponDef/r
    WEAPSTANCE_STAND = 0x0,
    WEAPSTANCE_DUCK  = 0x1,
    WEAPSTANCE_PRONE = 0x2,
    WEAPSTANCE_NUM   = 0x3,
};

enum OffhandSlot : __int32
{                                       // XREF: WeaponDef/r
                                        // Bot_UpdateGrenadeThrow/r ...
    OFFHAND_SLOT_NONE             = 0x0,
    OFFHAND_SLOT_LETHAL_GRENADE   = 0x1,
    OFFHAND_SLOT_TACTICAL_GRENADE = 0x2,
    OFFHAND_SLOT_EQUIPMENT        = 0x3,
    OFFHAND_SLOT_SPECIFIC_USE     = 0x4,
    OFFHAND_SLOT_COUNT            = 0x5,
};

enum activeReticleType_t : __int32
{                                       // XREF: WeaponDef/r
    VEH_ACTIVE_RETICLE_NONE  = 0x0,
    VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
    VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
    VEH_ACTIVE_RETICLE_COUNT = 0x3,
};

enum weaponIconRatioType_t : __int32
{                                       // XREF: WeaponDef/r
                                        // WeaponDef/r ...
    WEAPON_ICON_RATIO_1TO1  = 0x0,
    WEAPON_ICON_RATIO_2TO1  = 0x1,
    WEAPON_ICON_RATIO_4TO1  = 0x2,
    WEAPON_ICON_RATIO_COUNT = 0x3,
};

enum ammoCounterClipType_t : __int32
{                                       // XREF: WeaponDef/r
    AMMO_COUNTER_CLIP_NONE          = 0x0,
    AMMO_COUNTER_CLIP_MAGAZINE      = 0x1,
    AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
    AMMO_COUNTER_CLIP_SHOTGUN       = 0x3,
    AMMO_COUNTER_CLIP_ROCKET        = 0x4,
    AMMO_COUNTER_CLIP_BELTFED       = 0x5,
    AMMO_COUNTER_CLIP_ALTWEAPON     = 0x6,
    AMMO_COUNTER_CLIP_COUNT         = 0x7,
};

enum weapOverlayReticle_t : __int32
{                                       // XREF: WeaponDef/r
    WEAPOVERLAYRETICLE_NONE      = 0x0,
    WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
    WEAPOVERLAYRETICLE_NUM       = 0x2,
};

enum weapProjExposion_t : __int32
{                                       // XREF: WeaponDef/r
    WEAPPROJEXP_GRENADE    = 0x0,
    WEAPPROJEXP_ROCKET     = 0x1,
    WEAPPROJEXP_FLASHBANG  = 0x2,
    WEAPPROJEXP_NONE       = 0x3,
    WEAPPROJEXP_DUD        = 0x4,
    WEAPPROJEXP_SMOKE      = 0x5,
    WEAPPROJEXP_HEAVY      = 0x6,
    WEAPPROJEXP_FIRE       = 0x7,
    WEAPPROJEXP_NAPALMBLOB = 0x8,
    WEAPPROJEXP_BOLT       = 0x9,
    WEAPPROJEXP_NUM        = 0xA,
};

enum WeapOverlayInteface_t : __int32
{                                       // XREF: WeaponDef/r
    WEAPOVERLAYINTERFACE_NONE        = 0x0,
    WEAPOVERLAYINTERFACE_JAVELIN     = 0x1,
    WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
    WEAPOVERLAYINTERFACECOUNT        = 0x3,
};

enum WeapStickinessType : __int32
{                                       // XREF: WeaponDef/r
    WEAPSTICKINESS_NONE             = 0x0,
    WEAPSTICKINESS_ALL              = 0x1,
    WEAPSTICKINESS_ALL_NO_SENTIENTS = 0x2,
    WEAPSTICKINESS_GROUND           = 0x3,
    WEAPSTICKINESS_GROUND_WITH_YAW  = 0x4,
    WEAPSTICKINESS_FLESH            = 0x5,
    WEAPSTICKINESS_COUNT            = 0x6,
};

enum WeapRotateType : __int32
{                                       // XREF: WeaponDef/r
                                        // ?G_InitGrenadeMovement@@YAXPAUgentity_s@@QBM1HW4WeapRotateType@@@Z/r
    WEAPROTATE_GRENADE_ROTATE  = 0x0,
    WEAPROTATE_BLADE_ROTATE    = 0x1,
    WEAPROTATE_CYLINDER_ROTATE = 0x2,
    WEAPROTATE_COUNT           = 0x3,
};

enum guidedMissileType_t : __int32
{                                       // XREF: WeaponDef/r
    MISSILE_GUIDANCE_NONE       = 0x0,
    MISSILE_GUIDANCE_SIDEWINDER = 0x1,
    MISSILE_GUIDANCE_HELLFIRE   = 0x2,
    MISSILE_GUIDANCE_JAVELIN    = 0x3,
    MISSILE_GUIDANCE_BALLISTIC  = 0x4,
    MISSILE_GUIDANCE_WIREGUIDED = 0x5,
    MISSILE_GUIDANCE_TVGUIDED   = 0x6,
    MISSILE_GUIDANCE_COUNT      = 0x7,
};

struct WeaponDef // sizeof=0x808
{                                       // XREF: WeaponFullDef/r
    const char *szOverlayName;
    XModel **gunXModel;
    XModel *handXModel;
    const char *szModeName;
    unsigned __int16 *notetrackSoundMapKeys;
    unsigned __int16 *notetrackSoundMapValues;
    int playerAnimType;
    weapType_t weapType;
    weapClass_t weapClass;
    PenetrateType penetrateType;
    ImpactType impactType;
    weapInventoryType_t inventoryType;
    weapFireType_t fireType;
    weapClipType_t clipType;
    int itemIndex;
    const char *parentWeaponName;
    int iJamFireTime;
    int tracerFrequency;
    float tracerWidth;
    float tracerLength;
    int overheatWeapon;
    float overheatRate;
    float cooldownRate;
    float overheatEndVal;
    bool coolWhileFiring;
    bool fuelTankWeapon;
    // padding byte
    // padding byte
    int iTankLifeTime;
    OffhandClass offhandClass;
    OffhandSlot offhandSlot;
    weapStance_t stance;
    const FxEffectDef *viewFlashEffect;
    const FxEffectDef *worldFlashEffect;
    const char *pickupSound;
    const char *pickupSoundPlayer;
    const char *ammoPickupSound;
    const char *ammoPickupSoundPlayer;
    const char *projectileSound;
    const char *pullbackSound;
    const char *pullbackSoundPlayer;
    const char *fireSound;
    const char *fireSoundPlayer;
    const char *fireLoopSound;
    const char *fireLoopSoundPlayer;
    const char *fireLoopEndSound;
    const char *fireLoopEndSoundPlayer;
    const char *fireStopSound;
    const char *fireStopSoundPlayer;
    const char *fireLastSound;
    const char *fireLastSoundPlayer;
    const char *emptyFireSound;
    const char *emptyFireSoundPlayer;
    const char *crackSound;
    const char *whizbySound;
    const char *meleeSwipeSound;
    const char *meleeSwipeSoundPlayer;
    const char *meleeHitSound;
    const char *meleeMissSound;
    const char *rechamberSound;
    const char *rechamberSoundPlayer;
    const char *reloadSound;
    const char *reloadSoundPlayer;
    const char *reloadEmptySound;
    const char *reloadEmptySoundPlayer;
    const char *reloadStartSound;
    const char *reloadStartSoundPlayer;
    const char *reloadEndSound;
    const char *reloadEndSoundPlayer;
    const char *rotateLoopSound;
    const char *rotateLoopSoundPlayer;
    const char *deploySound;
    const char *deploySoundPlayer;
    const char *finishDeploySound;
    const char *finishDeploySoundPlayer;
    const char *breakdownSound;
    const char *breakdownSoundPlayer;
    const char *finishBreakdownSound;
    const char *finishBreakdownSoundPlayer;
    const char *detonateSound;
    const char *detonateSoundPlayer;
    const char *nightVisionWearSound;
    const char *nightVisionWearSoundPlayer;
    const char *nightVisionRemoveSound;
    const char *nightVisionRemoveSoundPlayer;
    const char *altSwitchSound;
    const char *altSwitchSoundPlayer;
    const char *raiseSound;
    const char *raiseSoundPlayer;
    const char *firstRaiseSound;
    const char *firstRaiseSoundPlayer;
    const char *putawaySound;
    const char *putawaySoundPlayer;
    const char *overheatSound;
    const char *overheatSoundPlayer;
    const char *adsZoomSound;
    const char **bounceSound;
    const char *standMountedWeapdef;
    const char *crouchMountedWeapdef;
    const char *proneMountedWeapdef;
    int standMountedIndex;
    int crouchMountedIndex;
    int proneMountedIndex;
    const FxEffectDef *viewShellEjectEffect;
    const FxEffectDef *worldShellEjectEffect;
    const FxEffectDef *viewLastShotEjectEffect;
    const FxEffectDef *worldLastShotEjectEffect;
    Material *reticleCenter;
    Material *reticleSide;
    int iReticleCenterSize;
    int iReticleSideSize;
    int iReticleMinOfs;
    activeReticleType_t activeReticleType;
    float vStandMove[3];
    float vStandRot[3];
    float vDuckedOfs[3];
    float vDuckedMove[3];
    float vDuckedSprintOfs[3];
    float vDuckedSprintRot[3];
    float vDuckedSprintBob[2];
    float fDuckedSprintCycleScale;
    float vSprintOfs[3];
    float vSprintRot[3];
    float vSprintBob[2];
    float fSprintCycleScale;
    float vLowReadyOfs[3];
    float vLowReadyRot[3];
    float vDtpOfs[3];
    float vDtpRot[3];
    float vDtpBob[2];
    float fDtpCycleScale;
    float vMantleOfs[3];
    float vMantleRot[3];
    float vSlideOfs[3];
    float vSlideRot[3];
    float vDuckedRot[3];
    float vProneOfs[3];
    float vProneMove[3];
    float vProneRot[3];
    float vStrafeMove[3];
    float vStrafeRot[3];
    float fPosMoveRate;
    float fPosProneMoveRate;
    float fStandMoveMinSpeed;
    float fDuckedMoveMinSpeed;
    float fProneMoveMinSpeed;
    float fPosRotRate;
    float fPosProneRotRate;
    float fStandRotMinSpeed;
    float fDuckedRotMinSpeed;
    float fProneRotMinSpeed;
    XModel **worldModel;
    XModel *worldClipModel;
    XModel *rocketModel;
    XModel *mountedModel;
    XModel *additionalMeleeModel;
    Material *hudIcon;
    weaponIconRatioType_t hudIconRatio;
    Material *indicatorIcon;
    weaponIconRatioType_t indicatorIconRatio;
    Material *ammoCounterIcon;
    weaponIconRatioType_t ammoCounterIconRatio;
    ammoCounterClipType_t ammoCounterClip;
    int iStartAmmo;
    int iHeatIndex;
    int iMaxAmmo;
    int shotCount;
    const char *szSharedAmmoCapName;
    int iSharedAmmoCapIndex;
    int iSharedAmmoCap;
    bool unlimitedAmmo;
    bool ammoCountClipRelative;
    // padding byte
    // padding byte
    int damage;
    float damageDuration;
    float damageInterval;
    int playerDamage;
    int iMeleeDamage;
    int iDamageType;
    unsigned __int16 explosionTag;
    // padding byte
    // padding byte
    int iFireDelay;
    int iMeleeDelay;
    int meleeChargeDelay;
    int iDetonateDelay;
    int iSpinUpTime;
    int iSpinDownTime;
    float spinRate;
    const char *spinLoopSound;
    const char *spinLoopSoundPlayer;
    const char *startSpinSound;
    const char *startSpinSoundPlayer;
    const char *stopSpinSound;
    const char *stopSpinSoundPlayer;
    int iFireTime;
    int iLastFireTime;
    int iRechamberTime;
    int iRechamberBoltTime;
    int iHoldFireTime;
    int iDetonateTime;
    int iMeleeTime;
    int meleeChargeTime;
    int iReloadTimeRight;
    int iReloadTimeLeft;
    int reloadShowRocketTime;
    int iReloadEmptyTimeLeft;
    int iReloadAddTime;
    int iReloadEmptyAddTime;
    int iReloadQuickAddTime;
    int iReloadQuickEmptyAddTime;
    int iReloadStartTime;
    int iReloadStartAddTime;
    int iReloadEndTime;
    int iDropTime;
    int iRaiseTime;
    int iAltDropTime;
    int quickDropTime;
    int quickRaiseTime;
    int iFirstRaiseTime;
    int iEmptyRaiseTime;
    int iEmptyDropTime;
    int sprintInTime;
    int sprintLoopTime;
    int sprintOutTime;
    int lowReadyInTime;
    int lowReadyLoopTime;
    int lowReadyOutTime;
    int contFireInTime;
    int contFireLoopTime;
    int contFireOutTime;
    int dtpInTime;
    int dtpLoopTime;
    int dtpOutTime;
    int slideInTime;
    int deployTime;
    int breakdownTime;
    int nightVisionWearTime;
    int nightVisionWearTimeFadeOutEnd;
    int nightVisionWearTimePowerUp;
    int nightVisionRemoveTime;
    int nightVisionRemoveTimePowerDown;
    int nightVisionRemoveTimeFadeInStart;
    int fuseTime;
    int aiFuseTime;
    int lockOnRadius;
    int lockOnSpeed;
    bool requireLockonToFire;
    bool noAdsWhenMagEmpty;
    bool avoidDropCleanup;
    // padding byte
    unsigned int stackFire;
    float stackFireSpread;
    float stackFireAccuracyDecay;
    const char *stackSound;
    float autoAimRange;
    float aimAssistRange;
    bool mountableWeapon;
    // padding byte
    // padding byte
    // padding byte
    float aimPadding;
    float enemyCrosshairRange;
    bool crosshairColorChange;
    // padding byte
    // padding byte
    // padding byte
    float moveSpeedScale;
    float adsMoveSpeedScale;
    float sprintDurationScale;
    weapOverlayReticle_t overlayReticle;
    WeapOverlayInteface_t overlayInterface;
    float overlayWidth;
    float overlayHeight;
    float fAdsBobFactor;
    float fAdsViewBobMult;
    float fHipSpreadStandMin;
    float fHipSpreadDuckedMin;
    float fHipSpreadProneMin;
    float hipSpreadStandMax;
    float hipSpreadDuckedMax;
    float hipSpreadProneMax;
    float fHipSpreadDecayRate;
    float fHipSpreadFireAdd;
    float fHipSpreadTurnAdd;
    float fHipSpreadMoveAdd;
    float fHipSpreadDuckedDecay;
    float fHipSpreadProneDecay;
    float fHipReticleSidePos;
    float fAdsIdleAmount;
    float fHipIdleAmount;
    float adsIdleSpeed;
    float hipIdleSpeed;
    float fIdleCrouchFactor;
    float fIdleProneFactor;
    float fGunMaxPitch;
    float fGunMaxYaw;
    float swayMaxAngle;
    float swayLerpSpeed;
    float swayPitchScale;
    float swayYawScale;
    float swayHorizScale;
    float swayVertScale;
    float swayShellShockScale;
    float adsSwayMaxAngle;
    float adsSwayLerpSpeed;
    float adsSwayPitchScale;
    float adsSwayYawScale;
    bool sharedAmmo;
    bool bRifleBullet;
    bool armorPiercing;
    bool bBoltAction;
    bool bUseAltTagFlash;
    bool bUseAntiLagRewind;
    bool bIsCarriedKillstreakWeapon;
    bool aimDownSight;
    bool bRechamberWhileAds;
    bool bReloadWhileAds;
    // padding byte
    // padding byte
    float adsViewErrorMin;
    float adsViewErrorMax;
    bool bCookOffHold;
    bool bClipOnly;
    bool bCanUseInVehicle;
    bool bNoDropsOrRaises;
    bool adsFireOnly;
    bool cancelAutoHolsterWhenEmpty;
    bool suppressAmmoReserveDisplay;
    bool laserSightDuringNightvision;
    bool bHideThirdPerson;
    bool bHasBayonet;
    bool bDualWield;
    bool bExplodeOnGround;
    bool bThrowBack;
    bool bRetrievable;
    bool bDieOnRespawn;
    bool bNoThirdPersonDropsOrRaises;
    bool bContinuousFire;
    bool bNoPing;
    bool bForceBounce;
    bool bUseDroppedModelAsStowed;
    bool bNoQuickDropWhenEmpty;
    bool bKeepCrosshairWhenADS;
    bool bUseOnlyAltWeaoponHideTagsInAltMode;
    // padding byte
    Material *killIcon;
    weaponIconRatioType_t killIconRatio;
    bool flipKillIcon;
    bool bNoPartialReload;
    bool bSegmentedReload;
    bool bNoADSAutoReload;
    int iReloadAmmoAdd;
    int iReloadStartAdd;
    const char *szSpawnedGrenadeWeaponName;
    const char *szDualWieldWeaponName;
    unsigned int dualWieldWeaponIndex;
    int iDropAmmoMin;
    int iDropAmmoMax;
    int iDropClipAmmoMin;
    int iDropClipAmmoMax;
    bool blocksProne;
    bool bShowIndicator;
    // padding byte
    // padding byte
    int isRollingGrenade;
    int iExplosionRadius;
    int iExplosionRadiusMin;
    int iIndicatorRadius;
    int iExplosionInnerDamage;
    int iExplosionOuterDamage;
    float damageConeAngle;
    int iProjectileSpeed;
    int iProjectileSpeedUp;
    int iProjectileSpeedRelativeUp;
    int iProjectileSpeedForward;
    int iProjectileActivateDist;
    float projLifetime;
    float timeToAccelerate;
    float projectileCurvature;
    XModel *projectileModel;
    weapProjExposion_t projExplosion;
    const FxEffectDef *projExplosionEffect;
    bool projExplosionEffectForceNormalUp;
    // padding byte
    // padding byte
    // padding byte
    const FxEffectDef *projExplosionEffect2;
    bool projExplosionEffect2ForceNormalUp;
    // padding byte
    // padding byte
    // padding byte
    const FxEffectDef *projExplosionEffect3;
    bool projExplosionEffect3ForceNormalUp;
    // padding byte
    // padding byte
    // padding byte
    const FxEffectDef *projExplosionEffect4;
    bool projExplosionEffect4ForceNormalUp;
    // padding byte
    // padding byte
    // padding byte
    const FxEffectDef *projExplosionEffect5;
    bool projExplosionEffect5ForceNormalUp;
    // padding byte
    // padding byte
    // padding byte
    const FxEffectDef *projDudEffect;
    const char *projExplosionSound;
    const char *projDudSound;
    const char *mortarShellSound;
    const char *tankShellSound;
    bool bProjImpactExplode;
    bool bBulletImpactExplode;
    // padding byte
    // padding byte
    WeapStickinessType stickiness;
    WeapRotateType rotateType;
    bool plantable;
    bool hasDetonator;
    bool timedDetonation;
    bool bNoCrumpleMissile;
    bool rotate;
    bool bKeepRolling;
    bool holdButtonToThrow;
    bool offhandHoldIsCancelable;
    bool freezeMovementWhenFiring;
    // padding byte
    // padding byte
    // padding byte
    float lowAmmoWarningThreshold;
    float meleeChargeRange;
    bool bUseAsMelee;
    bool isCameraSensor;
    bool isAcousticSensor;
    // padding byte
    float *parallelBounce;
    float *perpendicularBounce;
    const FxEffectDef *projTrailEffect;
    float vProjectileColor[3];
    guidedMissileType_t guidedMissileType;
    float maxSteeringAccel;
    int projIgnitionDelay;
    const FxEffectDef *projIgnitionEffect;
    const char *projIgnitionSound;
    float fAdsAimPitch;
    float fAdsCrosshairInFrac;
    float fAdsCrosshairOutFrac;
    int adsGunKickReducedKickBullets;
    float adsGunKickReducedKickPercent;
    float fAdsGunKickPitchMin;
    float fAdsGunKickPitchMax;
    float fAdsGunKickYawMin;
    float fAdsGunKickYawMax;
    float fAdsGunKickAccel;
    float fAdsGunKickSpeedMax;
    float fAdsGunKickSpeedDecay;
    float fAdsGunKickStaticDecay;
    float fAdsViewKickPitchMin;
    float fAdsViewKickPitchMax;
    float fAdsViewKickYawMin;
    float fAdsViewKickYawMax;
    float fAdsViewScatterMin;
    float fAdsViewScatterMax;
    float fAdsSpread;
    int hipGunKickReducedKickBullets;
    float hipGunKickReducedKickPercent;
    float fHipGunKickPitchMin;
    float fHipGunKickPitchMax;
    float fHipGunKickYawMin;
    float fHipGunKickYawMax;
    float fHipGunKickAccel;
    float fHipGunKickSpeedMax;
    float fHipGunKickSpeedDecay;
    float fHipGunKickStaticDecay;
    float fHipViewKickPitchMin;
    float fHipViewKickPitchMax;
    float fHipViewKickYawMin;
    float fHipViewKickYawMax;
    float fHipViewScatterMin;
    float fHipViewScatterMax;
    float fightDist;
    float maxDist;
    const char *accuracyGraphName[2];
    float (*accuracyGraphKnots[2])[2];
    float (*originalAccuracyGraphKnots[2])[2];
    int accuracyGraphKnotCount[2];
    int originalAccuracyGraphKnotCount[2];
    int iPositionReloadTransTime;
    float leftArc;
    float rightArc;
    float topArc;
    float bottomArc;
    float accuracy;
    float aiSpread;
    float playerSpread;
    float minTurnSpeed[2];
    float maxTurnSpeed[2];
    float pitchConvergenceTime;
    float yawConvergenceTime;
    float suppressTime;
    float maxRange;
    float fAnimHorRotateInc;
    float fPlayerPositionDist;
    const char *szUseHintString;
    const char *dropHintString;
    int iUseHintStringIndex;
    int dropHintStringIndex;
    float horizViewJitter;
    float vertViewJitter;
    const char *szScript;
    int minDamage;
    int minPlayerDamage;
    float fMaxDamageRange;
    float fMinDamageRange;
    float destabilizationRateTime;
    float destabilizationCurvatureMax;
    int destabilizeDistance;
    float *locationDamageMultipliers;
    const char *fireRumble;
    const char *meleeImpactRumble;
    const char *reloadRumble;
    float adsDofStart;
    float adsDofEnd;
    float hipDofStart;
    float hipDofEnd;
    float scanSpeed;
    float scanAccel;
    int scanPauseTime;
    const char *flameTableFirstPerson;
    const char *flameTableThirdPerson;
    flameTable *flameTableFirstPersonPtr;
    flameTable *flameTableThirdPersonPtr;
    const FxEffectDef *tagFx_preparationEffect;
    const FxEffectDef *tagFlash_preparationEffect;
    bool doGibbing;
    // padding byte
    // padding byte
    // padding byte
    float maxGibDistance;
};

struct WeaponVariantDef // sizeof=0xE4
{                                       // XREF: XAssetPoolEntry<WeaponVariantDef>/r
    const char *szInternalName;
    int iVariantCount;
    WeaponDef *weapDef;
    const char *szDisplayName;
    const char **szXAnims;
    const char *szAltWeaponName;
    unsigned __int16 *hideTags;
    unsigned int altWeaponIndex;
    int iClipSize;
    int iReloadTime;
    int iReloadEmptyTime;
    int iReloadQuickTime;
    int iReloadQuickEmptyTime;
    int iAdsTransInTime;
    int iAdsTransOutTime;
    int iAltRaiseTime;
    const char *szAmmoName;
    int iAmmoIndex;
    const char *szClipName;
    int iClipIndex;
    float fAimAssistRangeAds;
    float fAdsSwayHorizScale;
    float fAdsSwayVertScale;
    float fAdsViewKickCenterSpeed;
    float fHipViewKickCenterSpeed;
    float fAdsZoomFov1;
    float fAdsZoomFov2;
    float fAdsZoomFov3;
    float fAdsZoomInFrac;
    float fAdsZoomOutFrac;
    float fOverlayAlphaScale;
    float fOOPosAnimLength[2];
    bool bSilenced;
    bool bDualMag;
    bool bFullMetalJacket;
    bool bHollowPoint;
    bool bRapidFire;
    // padding byte
    // padding byte
    // padding byte
    Material *overlayMaterial;
    Material *overlayMaterialLowRes;
    Material *dpadIcon;
    weaponIconRatioType_t dpadIconRatio;
    float ikLeftHandOffset[3];
    float ikLeftHandRotation[3];
    float ikLeftHandProneOffset[3];
    float ikLeftHandProneRotation[3];
    float ikLeftHandUiViewerOffset[3];
    float ikLeftHandUiViewerRotation[3];
};

int __cdecl XAnimTreeSize();
bool __cdecl XAnimTreeHasInfo(const XAnimTree_s *tree);
void __cdecl XAnimInit();
void __cdecl XAnimShutdown();
void __cdecl XAnimFree(XAnimParts *parts, scriptInstance_t inst);
unsigned __int8 *__cdecl Hunk_AllocXAnimPrecache(unsigned int size);
XAnimParts *__cdecl XAnimPrecache(char *name, void *(__cdecl *Alloc)(int));
XAnimParts *__cdecl XAnimFindData_LoadObj(char *name, void *(__cdecl *Alloc)(int));
XAnimParts *__cdecl XAnimFindData_FastFile(const char *name);
XAnimParts *__cdecl XAnimClone(XAnimParts *fromParts, void *(__cdecl *Alloc)(int));
void __cdecl XAnimCreate(XAnim_s *anims, unsigned int animIndex, char *name);
void __cdecl XAnimBlend(
        XAnim_s *anims,
        unsigned int animIndex,
        const char *name,
        unsigned int children,
        unsigned int num,
        unsigned int flags);
bool __cdecl IsNodeAdditive(const XAnimEntry *node);
bool __cdecl IsLeafNode(const XAnimEntry *anim);
void __cdecl XAnimSetParamValue(XAnim_s *anims, unsigned int paramIndex, char *strParamName, float paramValue);
void __cdecl XAnimSetValueSection(
        XAnim_s *anims,
        unsigned int animIndex,
        __int16 iFirstValueIndex,
        unsigned __int16 iValueCount);
XAnim_s *__cdecl XAnimCreateAnims(const char *debugName, int size, void *(__cdecl *Alloc)(int));
XAnim_s *__cdecl XAnimCreateAnimsWithValues(
        const char *debugName,
        int size,
        unsigned int iTotalValueCount,
        void *(__cdecl *Alloc)(int));
void __cdecl XAnimFreeList(XAnim_s *anims);
XAnimTree_s *__cdecl XAnimCreateTree(XAnim_s *anims, void *(__cdecl *Alloc)(int));
void __cdecl XAnimFreeTree(
        XAnimTree_s *tree,
        void (__cdecl *Free)(void *, int, scriptInstance_t),
        scriptInstance_t inst);
XAnim_s *__cdecl XAnimGetAnims(const XAnimTree_s *tree);
void __cdecl XAnimInitModelMap(XModel *const *models, unsigned int numModels, XModelNameMap *modelMap);
unsigned int __cdecl XAnimGetAnimMap(const XAnimParts *parts, const XModelNameMap *modelMap);
void __cdecl XAnimCalcRelDeltaParts(
        const XAnimParts *parts,
        float weightScale,
        float time1,
        float time2,
        XAnimSimpleRotPos *rotPos,
        int quatIndex);
void __cdecl TransformToQuatRefFrame(const float *rot, float *trans);
void __cdecl XAnimCalcAbsDeltaParts(const XAnimParts *parts, float weightScale, float time, XAnimSimpleRotPos *rotPos);
void __cdecl XAnimAddClientNotify(unsigned int notetrackName, float frac, unsigned int notifyType);
void __cdecl AddSignalToNoteList(XAnimClientNotifyList *pList, const struct ClientNotifyData *ourNote);
void __cdecl XAnimAddClientNotifyNamed(unsigned int notetrackName, float frac, unsigned int notifyName);
void  XAnimResetAnimMap(const DObj *obj, unsigned int infoIndex);
void __cdecl XAnimResetAnimMap_r(XModelNameMap *modelMap, unsigned int infoIndex);
void __cdecl XAnimResetAnimMapLeaf(const XModelNameMap *modelMap, unsigned int infoIndex);
double __cdecl XAnimGetLength(const XAnim_s *anims, unsigned int animIndex);
int __cdecl XAnimGetFrameCount(const XAnim_s *anims, unsigned int animIndex);
int __cdecl XAnimGetLengthMsec(const XAnim_s *anims, unsigned int anim);
unsigned int __cdecl XAnimGetInfoIndex(const XAnimTree_s *tree, unsigned int animIndex);
unsigned int __cdecl XAnimGetInfoIndex_r(unsigned int animIndex, unsigned int infoIndex);
double __cdecl XAnimGetTime(const XAnimTree_s *tree, unsigned int animIndex);
double __cdecl XAnimGetWeight(const XAnimTree_s *tree, unsigned int animIndex);
bool __cdecl XAnimHasFinished(const XAnimTree_s *tree, unsigned int animIndex);
int __cdecl XAnimGetNumChildren(const XAnim_s *anims, unsigned int animIndex);
unsigned int __cdecl XAnimGetChildAt(const XAnim_s *anims, unsigned int animIndex, unsigned int childIndex);
const char *__cdecl XAnimGetAnimName(const XAnim_s *anims, unsigned int animIndex);
char *__cdecl XAnimGetAnimDebugName(const XAnim_s *anims, unsigned int animIndex);
unsigned int __cdecl XAnimGetAnimTreeSize(const XAnim_s *anims);
void __cdecl XAnimInitInfo(XAnimInfo *info);
void __cdecl XAnimUpdateOldTime(
        DObj *obj,
        unsigned int infoIndex,
        XAnimState *syncState,
        float dtime,
        bool parentHasWeight,
        bool *childHasTimeForParent);
unsigned int __cdecl XAnimInitTime(XAnimTree_s *tree, unsigned int infoIndex, float goalTime, int cmdIndex);
void __cdecl XAnimResetTime(unsigned int infoIndex);
void __cdecl XAnimResetTimeInternal(unsigned int infoIndex);
unsigned int __cdecl XAnimCloneInitTime(
        XAnimTree_s *tree,
        unsigned int infoIndex,
        unsigned int parentIndex,
        int cmdIndex);
void __cdecl DObjInitServerTime(DObj *obj, float dtime);
void __cdecl DObjUpdateClientInfo(DObj *obj, float dtime, int notifyFlags);
void __cdecl XAnimUpdateTimeAndNotetrack(const DObj *obj, unsigned int infoIndex, float dtime, int notifyFlags);
void __cdecl XAnimCheckFreeInfo(XAnimTree_s *tree, unsigned int infoIndex, int hasWeight);
void __cdecl XAnimFreeInfo(XAnimTree_s *tree, unsigned int infoIndex);
void __cdecl XAnimClearServerNotify(XAnimInfo *info, scriptInstance_t inst);
double __cdecl XAnimGetAverageRateFrequency(const XAnimTree_s *tree, unsigned int infoIndex);
void __cdecl XAnimUpdateTimeAndNotetrackLeaf(
        const DObj *obj,
        const XAnimParts *parts,
        unsigned int infoIndex,
        float dtime,
        char notifyFlags);
void __cdecl XAnimProcessClientNotify(XAnimInfo *info, float dtime);
signed int __cdecl XAnimGetNextNotifyIndex(const XAnimParts *parts, float time);
double __cdecl XAnimGetNotifyFracLeaf(const XAnimState *state, const XAnimState *nextState, float time, float dtime);
void __cdecl XAnimUpdateTimeAndNotetrackSyncSubTree(
        const DObj *obj,
        unsigned int infoIndex,
        float dtime,
        int notifyFlags);
void __cdecl XAnimUpdateInfoSync(
        const DObj *obj,
        unsigned int infoIndex,
        int notifyFlags,
        XAnimState *syncState,
        float dtime);
void __cdecl XAnimProcessServerNotify(const DObj *obj, XAnimInfo *info, float time);
XAnimParts *__cdecl XAnimGetPartsForNotify(const XAnimTree_s *tree, XAnimInfo *info);
void __cdecl NotifyServerNotetrack(
        const DObj *obj,
        unsigned int notifyName,
        unsigned int notetrackName,
        float fPercentage);
void __cdecl DObjClearServerNotifies();
void __cdecl DObjSetServerNotifies(XAnimServerNotifyList *pNotifyList);
void __cdecl DObjClearClientNotifies();
void __cdecl DObjSetClientNotifies(XAnimClientNotifyList *pNotifyList);
const XAnimClientNotifyList *__cdecl DObjGetClientNotifies();
void __cdecl DObjUpdateServerInfo(DObj *obj, float dtime, int notifyFlags);
void __cdecl DObjDisplayAnimToBuffer(const DObj *obj, const char *header, char *buffer, int bufferSize);
void __cdecl XAnimDisplay(
        const XAnimTree_s *tree,
        unsigned int infoIndex,
        int depth,
        char *buffer,
        int bufferSize,
        int *bufferPos);
void __cdecl DObjDisplayAnim(const DObj *obj, const char *header);
void __cdecl XAnimCalcDelta(DObj *obj, unsigned int animIndex, float *rot, float *trans, bool bUseGoalWeight);
void __cdecl XAnimCalcDeltaTree(
        const DObj *obj,
        unsigned int infoIndex,
        float weightScale,
        XAnimDeltaInfo deltaInfo,
        XAnimSimpleRotPos *rotPos);
void __cdecl XAnimCalcAbsDelta(DObj *obj, unsigned int animIndex, float *rot, float *trans);
void __cdecl XAnimGetRelDelta(
        const XAnim_s *anims,
        unsigned int animIndex,
        float *rot,
        float *trans,
        float time1,
        float time2);
void __cdecl XAnimGetAbsDelta(const XAnim_s *anims, unsigned int animIndex, float *rot, float *trans, float time);
unsigned int __cdecl XAnimAllocInfoWithParent(
        XAnimTree_s *tree,
        unsigned __int16 animToModel,
        unsigned int animIndex,
        unsigned int parentInfoIndex,
        int after);
unsigned int  XAnimAllocInfoIndex(DObj *obj,
        unsigned int animIndex,
        int after,
        int cmdIndex);
unsigned int __cdecl XAnimEnsureGoalWeightParent(DObj *obj, unsigned int animIndex, int cmdIndex);
void __cdecl XAnimClearGoalWeight(
        XAnimTree_s *tree,
        unsigned int animIndex,
        float blendTime,
        unsigned __int16 cmdIndex);
void __cdecl XAnimClearGoalWeightInternal(
        XAnimTree_s *tree,
        unsigned int infoIndex,
        float blendTime,
        int forceBlendTime,
        unsigned __int16 cmdIndex);
void __cdecl XAnimClearTreeGoalWeightsInternal(
        XAnimTree_s *tree,
        unsigned int infoIndex,
        float blendTime,
        int forceBlendTime,
        int cmdIndex);
void __cdecl XAnimClearTreeGoalWeights(XAnimTree_s *tree, unsigned int animIndex, float blendTime, int cmdIndex);
void __cdecl XAnimClearTreeGoalWeightsStrict(XAnimTree_s *tree, unsigned int animIndex, float blendTime, int cmdIndex);
int __cdecl XAnimSetCompleteGoalWeightKnob(
        DObj *obj,
        unsigned int animIndex,
        float goalWeight,
        float goalTime,
        float rate,
        unsigned int notifyName,
        unsigned int notifyType,
        int bRestart,
        int cmdIndex);
void __cdecl XAnimClearGoalWeightKnobInternal(
        XAnimTree_s *tree,
        unsigned int infoIndex,
        float goalWeight,
        float goalTime,
        unsigned __int16 cmdIndex);
int __cdecl XAnimSetCompleteGoalWeightNode(
        XAnimTree_s *tree,
        unsigned int infoIndex,
        float goalWeight,
        float goalTime,
        float rate,
        unsigned int notifyName,
        unsigned int notifyType,
        unsigned __int16 cmdIndex);
int __cdecl XAnimSetGoalWeightKnobAll(
        DObj *obj,
        unsigned int animIndex,
        unsigned int rootIndex,
        float goalWeight,
        float goalTime,
        float rate,
        unsigned int notifyName,
        unsigned int notifyType,
        int bRestart,
        int cmdIndex);
int __cdecl XAnimSetCompleteGoalWeightKnobAll(
        DObj *obj,
        unsigned int animIndex,
        unsigned int rootIndex,
        float goalWeight,
        float goalTime,
        float rate,
        unsigned int notifyName,
        unsigned int notifyType,
        int bRestart,
        int cmdIndex);
int __cdecl XAnimSetGoalWeightKnob(
        DObj *obj,
        unsigned int animIndex,
        float goalWeight,
        float goalTime,
        float rate,
        unsigned int notifyName,
        unsigned int notifyType,
        int bRestart,
        int cmdIndex);
void __cdecl XAnimClearTree(XAnimTree_s *tree);
int __cdecl XAnimSetGoalWeightNode(
        XAnimTree_s *tree,
        unsigned int infoIndex,
        float goalWeight,
        float goalTime,
        float rate,
        unsigned int notifyName,
        unsigned int notifyType,
        unsigned __int16 cmdIndex);
unsigned int __cdecl XAnimGetDescendantWithGreatestWeight(const XAnimTree_s *tree, unsigned int infoIndex);
void __cdecl  XAnimSetupSyncNodes(XAnim_s *anims);
void __cdecl XAnimSetupSyncNodes_r(XAnim_s *anims, unsigned int animIndex, int parFlags);
bool __cdecl XAnimHasTime(const XAnim_s *anims, unsigned int animIndex);
bool __cdecl XAnimIsPrimitive(XAnim_s *anims, unsigned int animIndex);
void __cdecl XAnimSetTime(XAnimTree_s *tree, unsigned int animIndex, float time, unsigned __int16 cmdIndex);
unsigned int __cdecl XAnimRestart(XAnimTree_s *tree, unsigned int infoIndex, float goalTime, int cmdIndex);
int __cdecl XAnimSetGoalWeight(
        DObj *obj,
        unsigned int animIndex,
        float goalWeight,
        float goalTime,
        float rate,
        unsigned int notifyName,
        unsigned int notifyType,
        int bRestart,
        int cmdIndex);
void __cdecl XAnimSetAnimRate(XAnimTree_s *tree, unsigned int animIndex, float rate);
bool __cdecl XAnimIsLooped(const XAnim_s *anims, unsigned int animIndex);
unsigned __int8 __cdecl XAnimGetBoneCount(const XAnim_s *anims, unsigned int animIndex);
int __cdecl XAnimHasBone(const XAnim_s *anims, unsigned int animIndex, unsigned __int16 boneName);
bool __cdecl XAnimIsClientNode(const XAnim_s *anims, unsigned int animIndex);
bool __cdecl XAnimIsClientNode(XAnimTree_s *tree, unsigned int animIndex);
char __cdecl XAnimNotetrackExists(const XAnim_s *anims, unsigned int animIndex, unsigned int name);
void __cdecl XAnimAddNotetrackTimesToScriptArray(const XAnim_s *anims, unsigned int animIndex, unsigned int name);
int __cdecl XAnimSetCompleteGoalWeight(
        DObj *obj,
        unsigned int animIndex,
        float goalWeight,
        float goalTime,
        float rate,
        unsigned int notifyName,
        unsigned int notifyType,
        int bRestart,
        int cmdIndex);
void __cdecl XAnimCloneAnimInfo(XAnimTree_s *toTree, const XAnimInfo *from, XAnimInfo *to);
void __cdecl XAnimCloneAnimTree(const XAnimTree_s *from, XAnimTree_s *to);
void __cdecl XAnimCloneAnimTree_r(
        const XAnimTree_s *from,
        XAnimTree_s *to,
        unsigned int fromInfoIndex,
        unsigned int toInfoParentIndex);
XAnimInfo *__cdecl GetAnimInfo(int infoIndex);
char __cdecl XAnimGetParamValue(const XAnim_s *anims, unsigned int animIndex, const char *paramName, float *outValue);
bool __cdecl XAnimGetParamValue(XAnimTree_s *tree, unsigned int animIndex, const char *paramName, float *outValue);
bool __cdecl XAnimGetParamValueTree(
        const XAnim_s *anims,
        unsigned int animIndex,
        const char *paramName,
        float *outValue);
//void __thiscall bitarray<160>::setBit(bitarray<160> *this, unsigned int pos);
void __cdecl XAnim_SetTime(float time, int frameCount, XAnimTime *animTime);
