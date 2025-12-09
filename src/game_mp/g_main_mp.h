#pragma once

#include <game/teams.h>
#include <universal/q_shared.h>
#include <demo/demo_common.h>
#include "g_scr_main_mp.h"
#include <bgame/bg_public.h>

enum sessionState_t : __int32
{                                       // XREF: clientSession_t/r
    SESS_STATE_PLAYING      = 0x0,
    SESS_STATE_DEAD         = 0x1,
    SESS_STATE_SPECTATOR    = 0x2,
    SESS_STATE_INTERMISSION = 0x3,
};

enum clientConnected_t : __int32
{                                       // XREF: clientSession_t/r
    CON_DISCONNECTED = 0x0,
    CON_CONNECTING   = 0x1,
    CON_CONNECTED    = 0x2,
};

struct playerTeamState_t // sizeof=0x4
{                                       // XREF: clientSession_t/r
    int location;
};

struct __declspec(align(8)) clientSession_t // sizeof=0x1F0
{                                       // XREF: gclient_s/r
                                        // ?ClientSpawn@@YAXPAUgentity_s@@QBM1@Z/r
    sessionState_t sessionState;
    int forceSpectatorClient;
    int killCamEntity;
    int killCamTargetEntity;
    int archiveTime;
    unsigned int scriptPersId;
    clientConnected_t connected;
    usercmd_s cmd;
    usercmd_s oldcmd;
    int localClient;
    int predictItemPickup;
    char newnetname[32];
    int maxHealth;
    int enterTime;
    playerTeamState_t teamState;
    int voteCount;
    int teamVoteCount;
    float moveSpeedScaleMultiplier;
    int viewmodelIndex;
    int noSpectate;
    int teamInfo;
    clientState_s cs;
    int psOffsetTime;
    int scoreboardColumnCache[18];
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct trigger_info_t // sizeof=0xC
{                                       // XREF: level_locals_t/r
                                        // level_locals_t/r ...
    unsigned __int16 entnum;
    unsigned __int16 otherEntnum;
    int useCount;
    int otherUseCount;
};

struct gclient_s // sizeof=0x29E0
{                                       // XREF: .data:g_clients/r
                                        // gclient_t/r
    gclient_s();

    playerState_s ps;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    clientSession_t sess;
    int spectatorClient;
    int flags;
    int lastCmdTime;
    bitarray<51> button_bits;
    bitarray<51> oldbutton_bits;
    bitarray<51> latched_button_bits;
    bitarray<51> button_bitsSinceLastFrame;
    float fGunPitch;
    float fGunYaw;
    int damage_blood;
    float damage_from[3];
    int damage_fromWorld;
    int inactivityTime;
    int inactivityWarning;
    int lastVoiceTime;
    int outWaterTime;
    int switchSeatTime;
    float currentAimSpreadScale;
    int dropWeaponTime;
    int sniperRifleFiredTime;
    float sniperRifleMuzzleYaw;
    int PCSpecialPickedUpCount;
    bool prevLinkAnglesSet;
    // padding byte
    // padding byte
    // padding byte
    float prevLinkedInvQuat[4];
    float linkAnglesFrac;
    bool linkAnglesLocked;
    // padding byte
    // padding byte
    // padding byte
    float linkAnglesMinClamp[2];
    float linkAnglesMaxClamp[2];
    bool link_rotationMovesEyePos;
    // padding byte
    EntHandle useHoldEntity;
    // padding byte
    // padding byte
    int useHoldTime;
    int useButtonDone;
    int iLastCompassPlayerInfoEnt;
    int compassPingTime;
    int damageTime;
    float v_dmg_roll;
    float v_dmg_pitch;
    float swayViewAngles[3];
    float swayOffset[3];
    float swayAngles[3];
    float baseAngles[3];
    float baseOrigin[3];
    float recoilAngles[3];
    float fLastIdleFactor;
    int weapIdleTime;
    float recoilSpeed[3];
    int lastServerTime;
    int lastSpawnTime;
    unsigned int lastWeapon;
    bool previouslyFiring;
    bool previouslyUsingNightVision;
    bool previouslyBeganWeaponRaise;
    bool previouslySprinting;
    unsigned int hasSpyplane;
    unsigned int hasSatellite;
    int revive;
    int reviveTime;
    int disallowVehicleUsage;
    int lastStand;
    int lastStandTime;
};

struct __declspec(align(64)) level_locals_t // sizeof=0x3880
{                                       // XREF: .data:level_locals_t level/r
    struct gclient_s *clients;                 // XREF: MatchRecordMovement(void)+133/r
                                        // MatchRecordMovement(void)+149/r ...
    gentity_s *gentities;               // XREF: ClientEndFrame(gentity_s *)+C61/r
                                        // ClientEndFrame(gentity_s *)+C87/r ...
    int gentitySize;
    int num_entities;                   // XREF: Cmd_EntityCount_f(gentity_s *):loc_612A72/r
                                        // G_FreeEntities(bool)+2E/r ...
    gentity_s *firstFreeEnt;            // XREF: DrawEntityCounts+B7/r
                                        // G_FreeEntities(bool)+12A/w ...
    gentity_s *lastFreeEnt;             // XREF: G_FreeEntities(bool)+134/w
                                        // G_InitGame(int,int,int,int,int)+649/w ...
    struct scr_vehicle_s *vehicles;            // XREF: G_RunFrameForEntity+34E/r
                                        // G_InitScrVehicles(void):loc_66C758/w
    gentity_s *firstFreeActor;
    gentity_s *lastFreeActor;
    int num_actors;
    struct sentient_s *sentients;              // XREF: G_InitGame(int,int,int,int,int)+5DA/w
                                        // turret_findBestTarget+165/r ...
    struct actor_s *actors;                    // XREF: G_FreeEntities(bool):loc_626429/r
                                        // G_FreeEntities(bool)+A3/r ...
    int actorCorpseCount;               // XREF: G_InitGame(int,int,int,int,int)+325/w
                                        // G_InitGame(int,int,int,int,int)+32A/r ...
    struct TurretInfo *turrets;                // XREF: G_InitTurrets(void):loc_69F71E/w
    int logFile;                        // XREF: G_InitGame(int,int,int,int,int)+1E9/o
                                        // G_InitGame(int,int,int,int,int)+204/o ...
    int initializing;                   // XREF: Cmd_Give_f(gentity_s *)+2E4/w
                                        // Cmd_Give_f(gentity_s *)+31A/w ...
    int clientIsSpawning;               // XREF: ClientSpawn(gentity_s *,float const * const,float const * const):loc_6017D0/w
                                        // ClientSpawn(gentity_s *,float const * const,float const * const)+973/w ...
    int maxclients;                     // XREF: MatchRecordMovement(void)+62/r
                                        // MatchRecordMovement(void)+183/r ...
    objective_t objectives[32];         // XREF: G_UpdateObjectiveToClients(void)+BD/o
                                        // G_InitObjectives(void)+22/o ...
    int objectivesClientMask[32][2];    // XREF: G_UpdateObjectiveToClients(void)+FB/r
                                        // Scr_Objective_Add+75/w ...
    int framenum;                       // XREF: G_RunFrame(int)+22/r
                                        // G_RunFrame(int)+2A/w ...
    int time;                           // XREF: GenerateBinaryMatchSummary+34/r
                                        // GenerateBinaryBreadcrumbData+32/r ...
    int previousTime;                   // XREF: G_RunFrame(int)+35/w
                                        // G_RunFrame(int)+49/r ...
    int frametime;                      // XREF: G_PlayerController(gentity_s const *,int * const):loc_5FCBD0/r
                                        // G_RunFrame(int)+4F/w ...
    int startTime;                      // XREF: G_InitGame(int,int,int,int,int)+1B4/w
                                        // GScr_getStartTime+5/r
    SpawnVar spawnVar;                  // XREF: G_SpawnItem(gentity_s *,gitem_s const *)+360/r
                                        // G_CallSpawn(SpawnVar *):loc_684549/r ...
    EntHandle droppedWeaponCue[32];
    int savepersist;                    // XREF: G_GetSavePersist(void)+3/r
                                        // G_SetSavePersist(int)+6/w ...
    float fFogOpaqueDist;               // XREF: G_setfog(char const *)+1C/w
                                        // G_setfog(char const *)+AF/w ...
    float fFogOpaqueDistSqrd;           // XREF: G_setfog(char const *)+2C/w
                                        // G_setfog(char const *)+C7/w ...
    int bPlayerIgnoreRadiusDamage;      // XREF: G_RadiusDamage(float const * const,gentity_s *,gentity_s *,float,float,float,float,float * const,gentity_s *,int,int)+15B/r
                                        // GScr_RadiusDamageInternal+ED/w ...
    int bPlayerIgnoreRadiusDamageLatched;
                                        // XREF: GScr_RadiusDamageInternal:loc_651777/r
                                        // GScr_SetPlayerIgnoreRadiusDamage+F/w
    int currentEntityThink;             // XREF: G_InitGame(int,int,int,int,int)+BD/w
                                        // G_RunFrame(int)+711/r ...
    int registerWeapons;                // XREF: SaveRegisteredWeapons(void)+2E/w
                                        // G_RegisterWeapon(uint)+55/w ...
    int bRegisterItems;                 // XREF: SaveRegisteredItems(void)+13/w
                                        // G_RegisterWeapon(uint)+4B/w ...
    cached_tag_mat_t cachedTagMat;      // XREF: GScr_GetTagOrigin(scr_entref_t)+34/o
                                        // GScr_GetTagOrigin(scr_entref_t)+4B/o ...
    cached_tag_mat_t cachedEntTargetTagMat;
    trigger_info_t pendingTriggerList[256]; // XREF: G_RunFrame(int)+385/o
                                        // G_Trigger(gentity_s *,gentity_s *)+B6/o
    trigger_info_t currentTriggerList[256]; // XREF: G_RunFrame(int)+38A/o
                                        // G_RunFrame(int)+3E9/o ...
    int pendingTriggerListSize;         // XREF: G_RunFrame(int):loc_62B69B/r
                                        // G_RunFrame(int)+397/r ...
    int currentTriggerListSize;         // XREF: G_RunFrame(int)+34C/r
                                        // G_RunFrame(int)+39D/w ...
    int openScriptIOFileHandles[1];     // XREF: G_InitGame(int,int,int,int,int)+2D2/w
                                        // G_ShutdownGame(int)+18A/r ...
    char *openScriptIOFileBuffers[1];   // XREF: G_InitGame(int,int,int,int,int)+2E3/w
                                        // G_ShutdownGame(int)+15A/r ...
    com_parse_mark_t currentScriptIOLineMark[1];
                                        // XREF: G_InitGame(int,int,int,int,int)+2F9/o
                                        // GScr_OpenFile+1B8/w ...
    int scriptPrintChannel;             // XREF: G_InitGame(int,int,int,int,int)+C7/w
                                        // GScr_printChannelSet:loc_641EB0/r ...
    float compassMapUpperLeft[2];       // XREF: GetWorldLocation+29/r
                                        // GetWorldLocation+3B/r ...
    float compassMapWorldSize[2];       // XREF: GetWorldLocation+4D/r
                                        // GetWorldLocation+BE/r ...
    float compassNorth[2];              // XREF: GetWorldLocation+5A/r
                                        // GetWorldLocation+67/r ...
    int finished;                       // XREF: GScr_MapRestart+4/r
                                        // GScr_MapRestart+D/r ...
    int manualNameChange;               // XREF: ClientUserinfoChanged(int)+12B/r
                                        // GScr_SetClientNameMode+23/w ...
    unsigned __int16 modelMap[512];
    int numConnectedClients;            // XREF: Cmd_CallVote_f(gentity_s *):loc_611955/r
                                        // CalculateRanks(void)+6/w ...
    int sortedClients[32];              // XREF: CalculateRanks(void)+5A/w
                                        // CalculateRanks(void)+C1/o ...
    int bUpdateScoresForIntermission;   // XREF: CalculateRanks(void):loc_629FEB/w
                                        // GScr_SetTeamScore:loc_654E53/w
    int numVotingClients;               // XREF: CalculateRanks(void)+10/w
                                        // CalculateRanks(void)+A0/r ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    MatchState matchState;              // XREF: G_GetMatchState(void)+3/o
                                        // G_PopulateMatchState+3/w ...
    int teamScores[4];                  // XREF: SaveTeamScores(void):loc_5AAA1E/r
                                        // SaveTeamScores(void)+26/r ...
    int lastTeammateHealthTime;         // XREF: CheckTeamStatus(void)+B/r
                                        // CheckTeamStatus(void)+1B/w
    unsigned int teamHasSpyplane[4];    // XREF: ClientEndFrame(gentity_s *)+68D/r
                                        // G_GetNonPVSPlayerInfo(gentity_s *,float * const,int)+54/r ...
    unsigned int teamHasSatellite[4];   // XREF: ClientEndFrame(gentity_s *)+656/r
                                        // G_GetNonPVSPlayerInfo(gentity_s *,float * const,int)+35/r ...
    char voteString[1024];              // XREF: Cmd_CallVote_f(gentity_s *)+39D/o
                                        // Cmd_CallVote_f(gentity_s *)+568/o ...
    char voteDisplayString[1024];       // XREF: Cmd_CallVote_f(gentity_s *)+5C1/o
                                        // Cmd_CallVote_f(gentity_s *)+5E1/o ...
    int voteTime;                       // XREF: Cmd_CallVote_f(gentity_s *)+B0/r
                                        // Cmd_CallVote_f(gentity_s *)+BF4/w ...
    int voteExecuteTime;                // XREF: Cmd_CallVote_f(gentity_s *):loc_611C7A/r
                                        // Cmd_CallVote_f(gentity_s *)+393/w ...
    int voteYes;                        // XREF: Cmd_CallVote_f(gentity_s *)+BFA/w
                                        // Cmd_CallVote_f(gentity_s *)+CC8/r ...
    int voteNo;                         // XREF: Cmd_CallVote_f(gentity_s *)+C04/w
                                        // Cmd_CallVote_f(gentity_s *)+CE7/r ...
    int currentActorClone;              // XREF: G_SpawnActorClone(void)+6/r
                                        // G_SpawnActorClone(void)+1D/r ...
    int iSearchFrame;                   // XREF: Path_AStarAlgorithm_CustomSearchInfo_FindCloseNode_:loc_90E0E9/r
                                        // Path_AStarAlgorithm_CustomSearchInfo_FindCloseNode_+E2/w ...
    int currentPlayerClone;             // XREF: G_SpawnPlayerClone(void)+6/r
                                        // G_SpawnPlayerClone(void)+1D/r ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

int __cdecl G_GetTime();
void __cdecl G_RegisterConnectPaths();
bool __cdecl G_OnlyConnectingPaths();
void __cdecl G_RegisterRegisterToolDvars();
int __cdecl G_GetSavePersist();
void __cdecl G_SetSavePersist(int savepersist);
double __cdecl G_GetFogOpaqueDistSqrd();
int __cdecl G_GetClientScore(unsigned int clientNum);
int __cdecl G_GetClientKills(unsigned int clientNum);
int __cdecl G_GetClientAssists(unsigned int clientNum);
int __cdecl G_GetClientRank(unsigned int clientNum);
int __cdecl G_GetClientPrestige(unsigned int clientNum);
team_t __cdecl G_GetClientTeam(unsigned int clientNum);
int __cdecl G_GetClientDeaths(unsigned int clientNum);
int __cdecl G_GetClientArchiveTime(unsigned int clientNum);
void __cdecl G_SetClientArchiveTime(unsigned int clientNum, int time);
MatchState *__cdecl G_GetMatchState();
clientState_s *__cdecl G_GetClientState(unsigned int clientNum);
gclient_s *__cdecl G_GetPlayerState(unsigned int clientNum);
int __cdecl G_GetClientSize();
void __cdecl G_FreeEntities(bool clearTargets);
unsigned __int8 *__cdecl Hunk_AllocXAnimServer(unsigned int size);
bool __cdecl G_ExitAfterConnectPaths();
bool __cdecl G_ExitAfterToolComplete();
bool __cdecl G_ExitOnComError(int code);
int __cdecl G_IsServerGameSystem(int clientNum);
unsigned __int16 __cdecl G_GetWeaponAttachBone(clientInfo_t *ci, weapType_t weapType, weapInventoryType_t invType);
void G_FreeAnimTreeInstances();
void __cdecl    G_InitGame(int levelTime, int randomSeed, int restart, int registerDvars);
void G_RegisterDvars();
void __cdecl G_CreateDObj(
                DObjModel_s *dobjModels,
                unsigned __int16 numModels,
                XAnimTree_s *tree,
                unsigned int handle,
                int unusedLocalClientNum);
DObj *__cdecl G_GetDObj(unsigned int handle, int unusedLocalClientNum);
void __cdecl G_SafeDObjFree(unsigned int handle, int unusedLocalClientNum);
XAnim_s *G_LoadAnimTreeInstances();
unsigned __int8 *__cdecl Hunk_AllocActorXAnimServer(unsigned int size);
void G_PrintAllFastFileErrors();
void __cdecl G_PrintFastFileErrors(char *fastfile);
unsigned __int16 __cdecl G_AttachWeapon(DObjModel_s *dobjModels, unsigned __int16 numModels, clientInfo_t *ci);
void __cdecl G_ShutdownGame(int freeScripts);
void __cdecl CalculateRanks();
int __cdecl SortRanks(int *a, int *b);
void __cdecl ExitLevel();
void G_LogPrintf(const char *fmt, ...);
void __cdecl CheckVote();
void __cdecl G_UpdateObjectiveToClients();
void __cdecl G_UpdateHudElemsToClients();
void __cdecl G_RunThink(gentity_s *ent);
void __cdecl DebugDumpAnims();
void __cdecl G_XAnimUpdateEnt(gentity_s *ent);
void __cdecl ScriptPump();
void __cdecl ShowEntityInfo();
void __cdecl G_UpdateIKPlayerClipTerrainTimeout(gentity_s *ent);
void __cdecl G_UpdateIKDisableTerrainMappingTimeout(gentity_s *ent);
void __cdecl G_UpdateTimedDamage(gentity_s *ent);
void __cdecl G_DebugTimedDamage();
void __cdecl G_UpdateClientLinkInfo(gentity_s *ent);
bool __cdecl ResolveParentClientMask(const gentity_s *entChild, gentity_s *entParent);
void    G_RunFrame(int levelTime);
void __cdecl G_ClientDoPerFrameNotifies(gentity_s *ent);
bool __cdecl DoPerFrameNotify(
                gentity_s *ent,
                bool isCurrently,
                bool wasPreviously,
                unsigned __int16 begin,
                unsigned __int16 end);
void __cdecl G_UpdateIKCulling(gentity_s *ent);
void __cdecl G_RunFrameForEntity(gentity_s *ent);
void    G_UpdateWeapons( gentity_s *ent);
int G_PopulateMatchState();
bool __cdecl G_IsEntWalkable(int localClientNum, int entityNum);
bool __cdecl G_GetEntityOriginAngles(int localClientNum, int entityNum, float *origin, float *angles);
void __cdecl G_EntityLinkFromPMove(unsigned int entityNum, int parentEntityNum, int tagName);
void __cdecl G_AddDebugString(const float *xyz, const float *color, float scale, char *pszText, int duration);
//gclient_s *__thiscall gclient_s::gclient_s(gclient_s *this);
void __cdecl G_SafeDObjFree(gentity_s *ent);

extern level_locals_t level;

extern gentity_s g_entities[MAX_GENTITIES];