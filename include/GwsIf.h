/* 
 * File:   GwsIf.h
 * Author: wyy
 *
 * Created on 2015年6月12日, 上午8:31
 */

#ifndef GWSIF_H
#define	GWSIF_H

//#include "shmem.h"
#include "arn_6h_gws_mib.h"
//#include "gwsapi.h"
#include "../../../package/gwsapi.h"

#define COL_STA_INDEX           -1
#define COL_STA_ROW_STATUS      0
#define COL_STA_MAC_ADDR        1
#define COL_STA_SIGNAL          2
#define COL_STA_NOISE           3
#define COL_STA_SNR             4
#define COL_STA_RX_RATE         5
#define COL_STA_TX_RATE         6
#define COL_STA_QUEUE_LOAD      7
#define COL_STA_RX_MCS          8
#define COL_STA_TX_MCS          9

#define COL_ROUTE_INDEX         -1
#define COL_ROUTE_ROW_STATUS    0
#define COL_ROUTE_DESTINATION   1
#define COL_ROUTE_NEXT_HOP      2
#define COL_ROUTE_METRIC        3
#define COL_ROUTE_FLAGS         4
#define COL_ROUTE_EXP_TIME      5

using namespace std;

#define VAR_INSTANCE(var)       (*var::instance)
#define GET_VBX(var,value)      do { VAR_INSTANCE(var).get_value().get_value(value); } while (0)
#define SET_VBX(var,type,value) do { VAR_INSTANCE(var).replace_value(new type(value)); } while (0)

class GwsIf {
public:
    GwsIf();
    GwsIf(const GwsIf& orig);
    virtual ~GwsIf();
private:
//    int         m_nQid;
//    int         m_nKpi;
//    P_GWS_KPI   m_pKpi;
    bool        m_report_gws_uhf;
    bool        m_report_gws_bb;
private:
    void m_ParseAssocString(char* assoc,string& mac,int& rssi,int& nf,int& snr,
                    int& rxRate, int& txRate, int& qload, int& rxMcs, int& txMcs, string& online);
    void    m_FlushAssocCount(int nAssocList,assocCount& countAssoc);
    int     m_FlushAssocTable(char* assoc_string,int instance,assocEntry& table);
    int     m_FlushIfnameTable(ETH_IF_INFO& ifInfo,int instance,ifnameEntry& table);
public:
    int m_Init();
    int m_Exit();
    void m_UpdateSystem(bool cpu_only);
    void m_UpdateBBInfo();
    void m_UpdateGwsUHF();
    int m_UpdateAssocTable(assocCount& countAssoc,assocEntry& table);
public:
    int m_SetGwsUHF(Request* req);
/////////////////////////////////////////////////////////////////////////////////////
private:
    int m_Get_System_Info(  string&         sVersion,
                            string&         sBanner,
                            string&         sHostname,
                            string&         sUptime,
                            string&         sModuleType,
                            string&         sModuleSN,
                            long&           nMemory,
                            ETH_IF_TABLE&   ifTable,
                            VLAN_TABLE&     vlanTable);     //return error code
    int m_Get_CPU_Info(     long&           nCPU);
    int m_Get_GPS_Info(     long&           nLongitude,
                            long&           nLatitude,
                            long&           nSpeed);
    int m_Get_UHF_Info(     string&         sFirmware,
                            string&         sBoardSN,
                            long&           nChannel,
                            long&           nRegion,
                            long&           nTemperature,
                            long&           nAgcMode,
                            long&           nIfOut,
                            long&           nTxPower,
                            long&           nRxGain,
                            long&           nTxOnOff,
                            long&           nRxOnOff,
                            long&           nTxCal,
                            long&           nRxCal,
                            long&           nStatus);       //return error code
    int m_Get_BB_Info(      string&         sFirmware,
                            string&         sMac,
                            string&         sSSID,
                            string&         sMode,
                            string&         sEncryption,
                            long&           nTxPwr,
                            long&           nSignal,
                            long&           nNoise,
                            long&           nBandWidth,
                            long&           nFixedMCS);     //return error code
    int m_Get_AssocTable(   ASSOC_TABLE&    assocTable);    //return error code
};

#endif	/* GWSIF_H */

