#pragma once

#include <DemonWare/bdCore/bdReference/bdReferencable.h>
#include <DemonWare/bdCore/bdSocket/bdAddr.h>
#include "bdCore/bdTiming/bdStopwatch.h"
#include <DemonWare/bdCore/bdContainers/bdQueue.h>
#include "bdCore/bdSocket/bdStreamSocket.h"
#include "bdConnection.h"
#include <DemonWare/bdCore/bdContainers/bdByteBuffer.h>
#include "bdCore/bdCrypto/bdCypher3Des.h"

struct bdTaskByteBuffer : bdByteBuffer // sizeof=0x2C
{
    unsigned __int8 *m_taskData;
    unsigned int m_taskDataSize;
    unsigned int m_validHeaderSize;
    unsigned int m_paddingSize;
};

struct bdPendingBufferTransfer : bdReferencable // sizeof=0x14
{                                       // XREF: ?sendTask@bdLobbyConnection@@UAE_NV?$bdReference@VbdTaskByteBuffer@@@@I_N@Z/r
                                        // ?sendTask@bdLobbyConnection@@UAE_NV?$bdReference@VbdTaskByteBuffer@@@@I_N@Z/r ...
    bdReference<bdByteBuffer> m_buffer;
    unsigned __int8 *m_txPtr;
    unsigned int m_txAvail;
};

struct bdLobbyConnection : bdReferencable // sizeof=0x408
{
    enum RecvState : __int32
    {                                       // XREF: bdLobbyConnection/r
        BD_READ_INIT     = 0x0,
        BD_READ_SIZE     = 0x1,
        BD_READ_ENCRYPT  = 0x2,
        BD_READ_MESSAGE  = 0x3,
        BD_READ_COMPLETE = 0x4,
    };

    typedef bdConnection::Status Status;

    bdReference<bdCommonAddr> m_addr;
    unsigned int m_maxSendMessageSize;
    unsigned int m_maxRecvMessageSize;
    bdLobbyConnection::RecvState m_recvState;
    unsigned __int8 m_msgSizeBuffer[4];
    unsigned int m_recvCount;
    unsigned __int8 m_recvEncryptType;
    // padding byte
    // padding byte
    // padding byte
    unsigned int m_messageSize;
    bdReference<bdTaskByteBuffer> m_recvMessage;
    bdReference<bdPendingBufferTransfer> m_recvTransfer;
    bdQueue<bdPendingBufferTransfer> m_outgoingBuffers;
    bdStreamSocket m_socket;
    bdLobbyConnection::Status m_status;
    bdLobbyConnectionListener *m_connectionListener;
    bdCypher3Des m_cypher;
    unsigned __int8 m_sessionKey[24];
    unsigned int m_messageCount;
    bdStopwatch m_keepAliveTimer;
    bdStopwatch m_lastReceivedTimer;
    bdStopwatch m_asyncConnectTimer;
};

struct bdLobbyConnectionListener // sizeof=0x4
{                                       // XREF: bdAuthService/r
                                        // bdLobbyService/r
    //bdLobbyConnectionListener_vtbl *__vftable;

    virtual ~bdLobbyConnectionListener();
    virtual void onConnect(bdReference<bdLobbyConnection>);
    virtual void onConnectFailed(bdReference<bdLobbyConnection>);
    virtual void onDisconnect(bdReference<bdLobbyConnection>);
};

struct bdLobbyService : bdLobbyConnectionListener // sizeof=0x118
{
    bdRemoteTaskManager *m_taskManager;
    bdProfiles *m_profiles;
    bdMessaging *m_messaging;
    bdMatchMaking *m_matchMaking;
    bdStats *m_statsManager;
    bdFriends *m_friendsManager;
    struct bdTeams *m_teamsManager;
    bdStorage *m_storageManager;
    struct bdContentUnlock *m_contentUnlockManager;
    bdTitleUtilities *m_titleUtilitiesManager;
    bdKeyArchive *m_keyArchive;
    bdCounter *m_counter;
    bdGroup *m_group;
    bdContentStreaming *m_contentStreamingManager;
    bdPooledStorage *m_pooledStorageManager;
    bdTags *m_tags;
    bdVoteRank *m_voteRankManager;
    struct bdTwitter *m_twitter;
    struct bdFacebook *m_facebook;
    struct bdLinkCode *m_linkCode;
    bdAntiCheat *m_antiCheat;
    bdDML *m_DML;
    struct bdCRUX *m_crux;
    struct bdActivityTracker *m_activityTracker;
    unsigned int m_titleID;
    bdLobbyEventHandler *m_eventHandler;
    bdReference<bdLobbyConnection> m_lobbyConnection;
    bdAuthInfo m_authInfo;
    bool m_encryptedConnection;
    // padding byte
    // padding byte
    // padding byte
    unsigned int m_errorCode;
};