#pragma once
#include <gfx_d3d/r_rendercmds.h>

enum jqWorkerType : __int32
{                                       // XREF: jqModule/r _jqWorker/r
    JQ_WORKER_GENERIC = 0x0,            // XREF: .data:jqModule bp_env_jq_module1Module/s
                                        // .data:jqModule bp_env_jq_module2Module/s ...
    JQ_WORKER_MAX     = 0x1,
    JQ_WORKER_DEFAULT = 0x0,
};

struct _jqBatch // sizeof=0x0
{                                       // XREF: jqBatch/r
};

struct __declspec(align(4)) jqBatch // sizeof=0x7C
{                                       // XREF: .data:jqBatch g_phys_task_manager_batch/r
                                        // jqAtomicQueue<jqBatch,32>::NodeType/r ...
    void *p3x_info;                     // XREF: jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+19/w
                                        // jqWorkerLoop(jqWorker *,jqBatchGroup *,bool,unsigned __int64 *)+50/w ...
    void *Input;                        // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+2E/w
                                        // jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+2E/w ...
    void *Output;                       // XREF: jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+31/w
                                        // jqWorkerLoop(jqWorker *,jqBatchGroup *,bool,unsigned __int64 *)+5C/w ...
    jqModule *Module;                   // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+39/w
                                        // R_InitWorkerCmds(void)+34/w ...
    jqBatchGroup *GroupID;              // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+3C/w
                                        // jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+34/w ...
    void *ConditionalAddress;           // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+4E/w
                                        // jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+20/w ...
    unsigned int ConditionalValue;      // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+57/w
                                        // jqAddBatch(jqModule const &,void *,void *,jqBatchGroup *,jqQueue *,void *,int)+27/w ...
    unsigned int ParamData[23];         // XREF: Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+5D/w
                                        // Sys_AddWorkerCmdInternal(jqWorkerCmd *,void *,WorkerCmdConditional *)+6F/w ...
    _jqBatch _Batch;
    // padding byte
    // padding byte
    // padding byte
};

struct jqModule // sizeof=0x18
{                                       // XREF: .data:jqModule bp_env_jq_module1Module/r
                                        // .data:jqModule bp_env_jq_module2Module/r ...
    const char *Name;                   // XREF: _dynamic_initializer_for__fx_add_markModule__+6/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+6/w ...
    jqWorkerType Type;                  // XREF: _dynamic_initializer_for__fx_add_markModule__+10/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+10/w ...
    int (__cdecl *Code)(jqBatch *);     // XREF: _dynamic_initializer_for__fx_add_markModule__+1A/w
                                        // _dynamic_initializer_for__nuge_physicsModule__+1A/w ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    jqBatchGroup Group;                 // XREF: R_FinishedFrontendWorkerCmds(void)+3/o
                                        // R_FinishedFrontendWorkerCmds(void):loc_7B97EE/o ...
};

void __cdecl phys_task_manager_init();
void __cdecl phys_task_manager_shutdown();
bool __cdecl phys_task_manager_needs_flush();
void __cdecl phys_task_manager_flush();
void __cdecl phys_task_manager_process(jqModule *module, void *input, int input_count);
