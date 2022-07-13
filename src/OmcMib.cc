/* 
 * File:   COmcMib.cc
 * Author: wyy
 * 
 */

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "pthread.h"
#include <agent_pp/agent++.h>
#include <agent_pp/snmp_group.h>
#include <agent_pp/system_group.h>
#include <agent_pp/snmp_target_mib.h>
#include <agent_pp/snmp_notification_mib.h>
#include <agent_pp/snmp_community_mib.h>
#include <agent_pp/notification_originator.h>
#include <agent_pp/notification_log_mib.h>
#include <agent_pp/agentpp_simulation_mib.h>
#include <agent_pp/agentpp_config_mib.h>
#include <agent_pp/mib_policy.h>
#include <agent_pp/vacm.h>
#include <snmp_pp/log.h>

#include "OmcMib.h"

#define VT100_STYLE_OLD VT100_COLOR(VT100_B_BLACK,VT100_F_BLUE)
#define VT100_STYLE1_   VT100_STYLE1 VT100_UNDER_LINE

using namespace std;
static bool bTurnOnLed = false;
char* Time2String();

bool COmcMib::m_bEchoOff = true;
bool COmcMib::m_bPrcFree = true;
DWORD COmcMib::m_nComPeriod = 60;
DWORD COmcMib::m_nTicker = 0;
bool COmcMib::m_bTrigerShort = false;
bool COmcMib::m_bTrigerLong = false;
time_t COmcMib::m_nRecently = 0;
pthread_mutex_t COmcMib::m_hMibTreeSync;
bool bIsDebugOn = false;

COmcMib::COmcMib() {// : m_kpi(*this) {
    COmcMib::instance = this;
    m_pGroup = NULL;
    m_hThread = EMPTY;
    m_nTrapVersion = 2;
    m_nSnmpTimeout = 3000;
    memset(m_nComParams,0x00,32*sizeof(DWORD));
    m_nComTimeout = 100;
    m_nOff = 0;
    m_nVbx = 0;
    m_sVbx = NULL;
    m_trapDist.clear();
    memset(m_sTrapCommunity,0x00,64);
}

COmcMib::~COmcMib() {
//    m_Exit();
}

int COmcMib::m_Init(char* trapCommunity) {
    int error_code = SUCCESS_OK;
    OctetStr sysDescr("6 Harmonics OMC");
    sysDescr += AGENTPP_VERSION_STRING;
    sysDescr += "SNMP Agent";
    if (!this->add(new sysGroup(sysDescr.get_printable(), "1.3.6.1.4.1." OID_6H_S, 10))) return ERROR_AGENT_ADD_MIB_ENTRY;
    if (!this->add(new snmpGroup())) return ERROR_AGENT_ADD_MIB_ENTRY;
    if (!this->add(new snmp_target_mib())) return ERROR_AGENT_ADD_MIB_ENTRY;
    if (!this->add(new snmp_notification_mib())) return ERROR_AGENT_ADD_MIB_ENTRY;
    if ((error_code = this->m_gwsIF.m_Init()) < SUCCESS_OK) return error_code;
    if ((error_code = this->m_LoadTable()) < SUCCESS_OK) return error_code;
    m_pGroup = new arn_6h_gws_mib();
    if (!this->add(m_pGroup)) return ERROR_AGENT_ADD_MIB_ENTRY;
    if (!this->init()) return ERROR_AGENT_MIB_INIT;
    if (trapCommunity) strncpy(this->m_sTrapCommunity, trapCommunity, 63);
    MibTableRow* header = snmpTargetAddrEntry::instance->get_columns();
    if (header->get_nth(2)) {
        header->get_nth(2)->set_value(5 * SNMP_AGENT_TIMEOUT_SECOND);
    }

    this->set_notification_sender(&this->m_notification);
    pthread_mutex_init(&COmcMib::m_hMibTreeSync,NULL);
    if ((error_code = this->m_StartProcesser()) < SUCCESS_OK) return error_code;

    return SUCCESS_OK;
}

void COmcMib::m_Exit() {
    this->m_StopProcesser();
    pthread_mutex_unlock(&COmcMib::m_hMibTreeSync);
    pthread_mutex_destroy(&COmcMib::m_hMibTreeSync);
    this->m_gwsIF.m_Exit();
    if (this->m_sVbx) {
        delete [] m_sVbx;
        m_sVbx = NULL;
    }
}

bool COmcMib::m_Notify(Oid& TrapOid) {
    bool bSend = false;
    if (m_sVbx && m_nOff > 0) {
        for (int i=0; i<3; i++ ) {
            if (bSend = this->m_Notify(TrapOid, m_sVbx, m_nOff)) {
               m_nOff = 0;  //Notify OK,clear variable binding list;
               return true;
            }
        }
        m_nOff = 0; //error handle
    }
    return bSend;
}

bool COmcMib::m_Notify(Oid& TrapOid, Vbx* vbs, int len) {
    switch (this->m_nTrapVersion) {
        case 1: this->m_notification.add_v1_trap_destination(
                    this->m_trapDist, "GWS 6H V1 TRAP", "v1trap", this->m_sTrapCommunity);
            break;
        case 2: this->m_notification.add_v2_trap_destination(
                    this->m_trapDist, "GWS 6H V2 TRAP", "v2trap", this->m_sTrapCommunity);
            break;
        case 3: this->m_notification.add_v3_trap_destination(
                    this->m_trapDist, "GWS 6H", "OMC Agent", this->m_sTrapCommunity);
            break;
        default:return false;
    }
    int nError = this->notify("6 Harmonics", TrapOid, vbs, len);
    if (SNMP_ERROR_SUCCESS != nError) {
        printf("\nError on Sent SNMP Trap/Notification. Error code = %d.\n",nError);
        fflush(stdout);
        return false;
    }
    return true;
}

int COmcMib::m_LoadTable() {    //Preserv for embedded database
    int error_code = SUCCESS_OK;
    string  szSql;
    //////////////////////////////////////////////////////////////////////////////////
    //  Read configuration
    return error_code;
}

bool COmcMib::m_VbxEmpty() {
    return (0 == this->m_nOff);
}

Vbx* COmcMib::m_VbxAlloc() {
    if (m_sVbx && m_nVbx > m_nOff) {
        m_nOff ++;
        return &m_sVbx[m_nOff-1];
    } else return NULL;
}

int COmcMib::m_MaxOf(int nFirst,...) {
    va_list arg_list;
    va_start(arg_list, nFirst);
    int nMax = nFirst;
    int nCur = 0;
    while( END_OF_MAX != (nCur=va_arg(arg_list, int)) ) {
        nMax = MAX_OF(nMax,nCur);
    }
    va_end(arg_list);
    return nMax;
}

int COmcMib::m_MinOf(int nFirst,...) {
    va_list arg_list;
    va_start(arg_list, nFirst);
    int nMin = nFirst;
    int nCur = 0;
    while( END_OF_MIN != (nCur=va_arg(arg_list, int)) ) {
        nMin = MIN_OF(nMin,nCur);
    }
    va_end(arg_list);
    return nMin;
}

int COmcMib::m_StartProcesser() {
    int error_code = SUCCESS_OK;

    struct itimerval interval;
#ifdef  __ARM_ARCH_3__
#define USECS_PER_SECOND  499999;
#else   //__ARM_ARCH_3__
#define USECS_PER_SECOND  499999;
#endif  //__ARM_ARCH_3__
    interval.it_value.tv_sec = 0;
    interval.it_value.tv_usec = USECS_PER_SECOND;
    interval.it_interval.tv_sec = 0;
    interval.it_interval.tv_usec = USECS_PER_SECOND;
    signal(SIGALRM, COmcMib::m_ProcessBoard);
    setitimer(ITIMER_REAL, &interval, NULL);
    return error_code;
}

int COmcMib::m_StopProcesser() {
    struct itimerval interval;

    interval.it_value.tv_sec = 0;
    interval.it_value.tv_usec = 0;
    interval.it_interval.tv_sec = 0;
    interval.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &interval, NULL);
    printf("\nExit OK\n");
    return 0;
}

bool COmcMib::m_IsProcessing() {
    return ( EMPTY != this->m_hThread);
}

char* COmcMib::m_PrintTimestamp(char* sTime) {
#if 0
    struct timeval  itvl;
    struct timezone zone;

    gettimeofday(&itvl,&zone);
    unsigned long       nDay = (unsigned long)itvl.tv_sec/86400;
    unsigned long       nHour = (unsigned long)(itvl.tv_sec%86400)/3600;
    unsigned long       nMinute = (unsigned long)(itvl.tv_sec%3600)/60;
    unsigned long       nSecond = (unsigned long)itvl.tv_sec%60;
    TC4(m_bEchoOff)( VT100_GOTO("1","10")
            "[ %d:%02d:%02d.%d(ms) ]\n"
            VT100_GOTO("79","1"),
            nHour,nMinute,nSecond,itvl.tv_usec/1000);
#endif
    return NULL;
}

COmcMib* COmcMib::m_Occupy_Mib(bool infinite) {
    if (infinite) {
        pthread_mutex_lock(&COmcMib::m_hMibTreeSync);
        return ((COmcMib*) (COmcMib::instance));
    } else {
        struct timespec timer;
        timer.tv_sec = 0;
        timer.tv_nsec = 20 * 1000;  //20 ms
        if (0 == pthread_mutex_timedlock(&COmcMib::m_hMibTreeSync,&timer))
            return ((COmcMib*) (COmcMib::instance));
    }
    return NULL;
}

void COmcMib::m_Release_Mib() {
    pthread_mutex_unlock(&COmcMib::m_hMibTreeSync);
}

void COmcMib::m_ProcessBoard(int sig) {
    COmcMib*    mib = NULL;

    if (mib = COmcMib::m_Occupy_Mib()) {    //infinite
        m_nTicker ++;
        if (0 == (m_nTicker % 4)) {
            if (!m_bTrigerShort) m_bTrigerShort = true;
        }
        if (0 == (m_nTicker % 10)) {
            if (!m_bTrigerLong) m_bTrigerLong = true;
        }
//        printf("> [%d] short=%d,long=%d\n",COmcMib::m_nTicker,COmcMib::m_bTrigerShort,COmcMib::m_bTrigerLong);
//        fflush(stdout);
        COmcMib::m_Release_Mib();
    }
}

void COmcMib::m_ProcessRequest(Request* req) {
    COmcMib*    mib = NULL;

    if (mib = COmcMib::m_Occupy_Mib()) {
        this->process_request(req);
        mib->m_gwsIF.m_SetGwsUHF(req);   //commit the new values
        COmcMib::m_Release_Mib();
    }        
}

void COmcMib::m_ProcessMibSync() {
    COmcMib*    mib = NULL;

    if (mib = COmcMib::m_Occupy_Mib()) {
        if (COmcMib::m_bTrigerShort) {
            COmcMib::m_bTrigerShort = false;
            mib->m_gwsIF.m_UpdateSystem(true);  //update CPU usage only
            mib->m_gwsIF.m_UpdateAssocTable(VAR_INSTANCE(assocCount),VAR_INSTANCE(assocEntry));
        }
        if (COmcMib::m_bTrigerLong) {
            COmcMib::m_bTrigerLong = false;
            mib->m_gwsIF.m_UpdateSystem(false);
            mib->m_gwsIF.m_UpdateBBInfo();
            mib->m_gwsIF.m_UpdateGwsUHF();
        }
        COmcMib::m_Release_Mib();
    }
}
