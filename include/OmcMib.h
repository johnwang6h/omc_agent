/* 
 * File:   COmcMib.h
 * Author: wyy
 *
 * Created on 2013-7-23 下午4:09
 */

#ifndef _COmcMib_H
#define	_COmcMib_H

#include <string>
#include "error_agent.h"
#include "arn_6h_gws_mib.h"
#include "GwsIf.h"

class COmcMib : public Mib {
private:
    pthread_t               m_hThread;
    arn_6h_gws_mib*         m_pGroup;
    int                     m_nTrapVersion;
    int                     m_nSnmpTimeout;
    DWORD                   m_nComParams[8];
    DWORD                   m_nComTimeout;
    static pthread_mutex_t  m_hMibTreeSync;
    static DWORD            m_nComPeriod;
    static DWORD            m_nTicker;
    static bool             m_bTrigerShort;
    static bool             m_bTrigerLong;
    static time_t           m_nRecently;
    char                    m_sTrapCommunity[64];
    NotificationOriginator  m_notification;
    UdpAddress              m_trapDist;
    Vbx*                    m_sVbx;
    DWORD                   m_nVbx;
    DWORD                   m_nOff;
    GwsIf                   m_gwsIF;
public:
    COmcMib();
    COmcMib(const COmcMib& orig);
    virtual ~COmcMib();
private:
    bool                    m_VbxEmpty();
    Vbx*                    m_VbxAlloc();
    int                     m_LoadTable();
    int                     m_StartProcesser();
    bool                    m_IsProcessing();
    int                     m_StopProcesser();
    static int              m_MaxOf(int nFirst,...);
    static int              m_MinOf(int nFirst,...);
    static void             m_ProcessBoard(int sig);
    static char*            m_PrintTimestamp(char* sTime);
    static COmcMib*         m_Occupy_Mib(bool infinite = false);
    static void             m_Release_Mib();
public:
    static bool             m_bEchoOff;
    static bool             m_bPrcFree;
public:
    bool                    m_Notify(Oid& TrapOid);
    bool                    m_Notify(Oid& TrapOid,Vbx* vbs,int len);
    void                    m_ProcessRequest(Request* req);
    void                    m_ProcessMibSync();
public:
    int             m_Init(char* trapCommunity = NULL);
    void            m_Exit();
};

#endif	/* _COmcMib_H */

