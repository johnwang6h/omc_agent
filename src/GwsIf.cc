/* 
 * File:   GwsIf.cc
 * Author: wyy
 * 
 * Created on 2015年6月12日, 上午8:31
 */
#include <string>
#include "GwsIf.h"

#define INTERFACE_GWSMAN
#undef  INTERFACE_GWSMAN
#define WYY_DEBUG_UHF(var,fmt)  if (var) printf("%s = " fmt "\n",#var,var)

GwsIf::GwsIf() {
//    m_nQid = 0;
//    m_nKpi = 0;
//    m_pKpi = NULL;
}

GwsIf::GwsIf(const GwsIf& orig) {
}

GwsIf::~GwsIf() {
}

int GwsIf::m_Init() {
//    if ((m_pKpi = ConnectShm(&m_nKpi)) == NULL) return ERROR_AGENT_CONNECT_SHMEM;
//    if ((m_nQid = OpenMessageQueue(0)) < 0) {
//        CloseShm(m_pKpi);
//        return ERROR_AGENT_CONNECT_MEG_Q;
//    }
    m_report_gws_uhf = false;
    m_report_gws_bb = false;
    return SUCCESS_OK;   //error = 0
}

int GwsIf::m_Exit() {
//    if (m_pKpi) CloseShm(m_pKpi);
}

#define SPLIT_ASSOC_STRING(s,s_target,seperator)  do {\
    int     n = -1;\
    s_target = s.substr(0,(n = s.find_first_of(seperator)));\
    if (n > 0) s = s.substr(n+1,s.size()); else return;\
} while (0)

void GwsIf::m_ParseAssocString(char* assoc,string& mac,int& rssi,int& nf,int& snr,
        int& rxRate, int& txRate, int& qload, int& rxMcs, int& txMcs, string& online) {
    double          rx_fRate = 0.0f, tx_fRate = 0.0f;
//    unsigned int    nHour = 0, nMinute = 0, nSecond = 0;
    string  s = assoc;
    string  s_sig,s_na,s_mcs,s_rate,s_queue,s_online,s_rx_tpt,s_tx_tpt;
    time_t  current = time(&current);
    
//    printf("[%lu]   %s\n",current,assoc);
    SPLIT_ASSOC_STRING(s,mac,'|');
    SPLIT_ASSOC_STRING(s,s_sig,'|');
    SPLIT_ASSOC_STRING(s,s_na,'|');
    SPLIT_ASSOC_STRING(s,s_mcs,'|');
    SPLIT_ASSOC_STRING(s,s_rate,'|');
    SPLIT_ASSOC_STRING(s,s_queue,'|');
    SPLIT_ASSOC_STRING(s,s_online,'|');
    SPLIT_ASSOC_STRING(s,s_rx_tpt,'|');
    s_tx_tpt = s;
    
    string  s_signal,s_noise,s_snr;
    SPLIT_ASSOC_STRING(s_sig,s_signal,'/');
    SPLIT_ASSOC_STRING(s_sig,s_noise,'/');
    s_snr = s_sig;
    string  s_rx_mcs,s_tx_mcs;
    SPLIT_ASSOC_STRING(s_mcs,s_rx_mcs,'/');
    s_tx_mcs = s_mcs;
    string  s_rx_rate,s_tx_rate;
    SPLIT_ASSOC_STRING(s_rate,s_rx_rate,'/');
    s_tx_rate = s_rate;
//    string  s_hour,s_minute,s_second;
//    SPLIT_ASSOC_STRING(s_online,s_hour,':');
//    SPLIT_ASSOC_STRING(s_online,s_minute,':');
//    s_second = s_online;
    
    sscanf(s_signal.data()  ,"%d",&rssi);
    sscanf(s_noise.data()   ,"%d",&nf);
    sscanf(s_snr.data()     ,"%d",&snr);
    sscanf(s_rx_mcs.data()  ,"%d",&rxMcs);
    sscanf(s_tx_mcs.data()  ,"%d",&txMcs);
    sscanf(s_rx_rate.data() ,"%lf",&rx_fRate);
    sscanf(s_tx_rate.data() ,"%lf",&tx_fRate);
    sscanf(s_queue.data()   ,"%d",&qload);
    rxRate = rx_fRate * 1000;
    txRate = tx_fRate * 1000;
//    sscanf(s_hour.data()    ,"%d",&nHour);
//    sscanf(s_minute.data()  ,"%d",&nMinute);
//    sscanf(s_second.data()  ,"%d",&nSecond);
//    online = nHour * 3600 + nMinute * 60 + nSecond;
    online = s_online;
}

//#define    UPDATE_ASSOC_TABLE(table,typePTR,row,col,value)  \
//    do {\
//        Vbx vb = ((typePTR) table.get(col,row))->get_value();\
//        vb.set_value(value);\
//    } while (0)

void GwsIf::m_FlushAssocCount(int nAssocList,assocCount& countAssoc) {
    Vbx countValue = countAssoc.get_value();
    countValue.set_value(nAssocList);
    countAssoc.set_value(countValue);
}

int GwsIf::m_FlushIfnameTable(ETH_IF_INFO& ifInfo,int instance,ifnameEntry& table) {
    if (instance >= 0 && strlen(ifInfo.m_sIf_Name) > 0) {
        MibTableRow*    row = NULL;
        DWORD id[1]     = {instance};        
        Oidx Oid(id, 1);
//            table.start_synch();
        if ((row = table.find_index(Oid)) == NULL) {
            row = table.add_row(Oid);
        }
        if (row) {
            table.set_row(row, instance + 1,
                    ifInfo.m_sIf_Name,
                    ifInfo.m_sIf_BrLan,
                    ifInfo.m_sIf_Address,
                    ifInfo.m_sIf_Subnet,
                    ifInfo.m_sIf_MacAdd,
                    ifInfo.m_sIf_Gateway,
                    ifInfo.m_sIf_DNS);
        }
//            table.end_synch();
    }
}

int GwsIf::m_FlushAssocTable(char* assoc_string,int instance,assocEntry& table) {
    string  s_mac;
    int     rssi,nf,snr,qload,rxRate,txRate,rxMcs,txMcs;
    string  s_online;

    if (instance >= 0 && assoc_string && assoc_string[0]) {
        time_t          current = time(&current);
        MibTableRow*    row = NULL;
        DWORD id[1]     = {instance};        
        Oidx Oid(id, 1);
//            table.start_synch();
        if ((row = table.find_index(Oid)) == NULL) {
            row = table.add_row(Oid);
            if (0) printf("[%lu]   add_row\n",current);
        }
        if (row) {
            m_ParseAssocString(assoc_string, s_mac, rssi, nf, snr, rxRate, txRate, qload, rxMcs, txMcs, s_online);
            char*   str_mac = s_mac.empty() ? (char*)"" : (char*) s_mac.data();
            char*   str_online = s_online.empty() ? (char*)"" : (char*) s_online.data();
            if (1) {    //for debugging
                printf("[%lu]   set_row(instance = %d,mac = %s,rssi = %lu,nf = %lu,snr = %lu,"
                        "rx_rate = %lu,tx_rate = %lu, queue = %lu,rxMCS = %lu,txMCS = %lu,online = %lu)\n",
                        current,instance + 1, str_mac, rssi, nf, snr, rxRate, txRate, qload, rxMcs, txMcs, str_online);
            }
            table.set_row(row, instance + 1, str_mac, rssi, nf, snr, rxRate, txRate, qload, rxMcs, txMcs, str_online);
        }
//            table.end_synch();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//  Following functions can be overridded for other platforms
//////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Following is basic system info
////////////////////////////////////////////////////////////////////////////////
void GwsIf::m_UpdateSystem(bool cpu_only) {
    long            nCPU,nMemory,nLongitude,nLatitude,nSpeed;
    string          sUptime,sVersion,sBanner,sHostname,sModuleType,sModuleSN;
    ETH_IF_TABLE    ifTable;
    VLAN_TABLE      vlanTable;
    char            str_hostname0[128];
    char*           sOldHostname = str_hostname0;

    if (0 == m_Get_CPU_Info(nCPU))
        SET_VBX(usageCPU    ,SnmpInt32,nCPU);

    if (cpu_only) return;
    if (0 == m_Get_System_Info(sVersion,sBanner,sHostname,sUptime,
                sModuleType,sModuleSN,nMemory,ifTable,vlanTable)) {
        for (int i = 0; i < ifTable.m_nIf_Count; i ++) {            
            m_FlushIfnameTable(ifTable.m_Ifs[i],i,VAR_INSTANCE(ifnameEntry));
        }
    }
    GET_VBX(hostname    ,sOldHostname);
    if (!sHostname.empty() && 0 != sHostname.compare(sOldHostname)) {
        SET_VBX(hostname,OctetStr,sHostname.data());
    }
    if (!sUptime.empty())       SET_VBX(upTime      ,OctetStr   ,sUptime.data());
    if (!sVersion.empty())      SET_VBX(bbFirmware  ,OctetStr   ,sVersion.data());
    if (!sBanner.empty())       SET_VBX(banner      ,OctetStr   ,sBanner.data());
    if (!sModuleType.empty())   SET_VBX(moduleType  ,OctetStr   ,sModuleType.data());
    if (!sModuleSN.empty())     SET_VBX(moduleSN    ,OctetStr   ,sModuleSN.data());
    SET_VBX(usageMem    ,SnmpInt32,nMemory);
    if (0 == m_Get_GPS_Info(nLongitude, nLatitude, nSpeed)) {
        SET_VBX(gpsLongitude, SnmpInt32, nLongitude);
        SET_VBX(gpsLatitude , SnmpInt32, nLatitude);
        SET_VBX(gpsSpeed    , SnmpInt32, nSpeed);
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Following is WIFI part
////////////////////////////////////////////////////////////////////////////////
void GwsIf::m_UpdateBBInfo() {
#ifdef INTERFACE_GWSMAN
    char    bb_ssid[64],bb_meshid[64],s_encrypt[32],s_mode[16];
    long    bb_encrypt,bb_mode,bb_fixed_mcs;
    if (!m_report_gws_bb) { //report MAC address only once
        char    bb_mac[18];
        
        memset (bb_mac,0x00,18);
        RW_KPI_STR(m_nKpi,bb_mac,m_pKpi->m_wifi.m_sBSSID);
        SET_VBX(bbMacAddress,OctetStr,bb_mac);
        m_report_gws_bb = true;
    }
    RW_KPI_STR(m_nKpi,bb_ssid,m_pKpi->m_wifi.m_sSSID);
    RW_KPI_STR(m_nKpi,bb_meshid,m_pKpi->m_wifi.m_sSSID);
    RW_KPI_STR(m_nKpi,s_encrypt,m_pKpi->m_wifi.m_sEncryption);
    RW_KPI_STR(m_nKpi,s_mode,m_pKpi->m_wifi.m_sMode);
    if (0 == strcmp("Master",s_mode)) {
        bb_mode = 2;
    } else if (0 == strcmp("Client",s_mode)) {
        bb_mode = 1;
    } else bb_mode = 0; //Mesh Point
    if (strcasestr(s_encrypt,"WPA")) {
        bb_encrypt = 1;
    } else if (strcasestr(s_encrypt,"PASSWORD")) {
        bb_encrypt = 2;
    } else bb_encrypt = 0;
    if (bb_mode) SET_VBX(bbSSID,OctetStr,bb_ssid);
    else SET_VBX(bbMESHID,OctetStr,bb_meshid);    
    SET_VBX(bbEncryption,SnmpInt32,bb_encrypt);
    SET_VBX(bbOptMode,SnmpInt32,bb_mode);
    RW_KPI_VAR(m_nKpi,tx_pwr,m_pKpi->m_wifi.m_nTxPower);
    RW_KPI_VAR(m_nKpi,signal,m_pKpi->m_wifi.m_nSignal);
    RW_KPI_VAR(m_nKpi,noise,m_pKpi->m_wifi.m_nNoise);
    SET_VBX(bbTxPower   ,SnmpInt32,tx_pwr);
    SET_VBX(bbSignal    ,SnmpInt32,signal);
    SET_VBX(bbNoise     ,SnmpInt32,noise);
#else
    string  s_firmware,s_mac,s_ssid,s_encrypt,s_mode;
    long    bb_encrypt,bb_mode,bb_tx_pwr,bb_signal,bb_noise,bb_bw,bb_fixed;
    if (0 == m_Get_BB_Info(s_firmware,s_mac,s_ssid,s_mode,s_encrypt,bb_tx_pwr,bb_signal,bb_noise,bb_bw,bb_fixed)) {
        SET_VBX(bbFirmware  ,OctetStr   ,s_firmware.data());
        SET_VBX(bbMacAddress,OctetStr   ,s_mac.data());
#if 1
        if (0 == s_mode.compare("car"))              bb_mode = 2;
		else if (0 == s_mode.compare("ear"))         bb_mode = 1;
		else                                            bb_mode = 0; //Mesh Point
#else
        if (0 == s_mode.compare("Master"))              bb_mode = 2;
        else if (0 == s_mode.compare("Client"))         bb_mode = 1;
        else                                            bb_mode = 0; //Mesh Point
#endif
        if (strcasestr(s_encrypt.c_str(),"PASSWORD"))   bb_encrypt = 2;
        else if (strcasestr(s_encrypt.c_str(),"WPA"))   bb_encrypt = 1;
        else                                            bb_encrypt = 0;
        if (bb_mode)    SET_VBX(bbSSID  ,OctetStr,s_ssid.data());
        else            SET_VBX(bbMESHID,OctetStr,s_ssid.data());    
        SET_VBX(bbEncryption,SnmpInt32,bb_encrypt);
        SET_VBX(bbOptMode   ,SnmpInt32,bb_mode);
        SET_VBX(bbTxPower   ,Gauge32,bb_tx_pwr);
        SET_VBX(bbSignal    ,SnmpInt32,bb_signal);
        SET_VBX(bbNoise     ,SnmpInt32,bb_noise);
        SET_VBX(bbBandwidth ,SnmpInt32,bb_bw);
        SET_VBX(bbFixedMCS  ,SnmpInt32,bb_fixed);
    }
#endif
}

int GwsIf::m_UpdateAssocTable(assocCount& countAssoc,assocEntry& table) {
#ifdef INTERFACE_GWSMAN
    int     nAssocList = 0;
    char    assoc_string[IW_LIST_MAXSIZE];
    
    if (NULL == m_pKpi) return -1;

    RW_KPI_VAR(m_nKpi,nAssocList,m_pKpi->m_assoc_list.m_nLine);
    m_FlushAssocCount(nAssocList,countAssoc);
    
    for (int n = 0; n < nAssocList && n < IW_LIST_MAXLINE; n ++) {
        memset(assoc_string,0x00,IW_LIST_MAXSIZE);
        RW_KPI_STR(m_nKpi,assoc_string,(char*) m_pKpi->m_assoc_list.m_value[n]);
        m_FlushAssocTable(assoc_string,n,table);
    }
//    if (!table.is_empty()) table.clear();
    return 0;
#else
    ASSOC_TABLE asTab;
    if (0 == m_Get_AssocTable(asTab)) {
    	m_FlushAssocCount(asTab.m_nAssoc,countAssoc);
        for (int n = 0; n < asTab.m_nAssoc && n < MAX_ASSOC; n ++) {
            time_t          current = time(&current);
            MibTableRow*    row = NULL;
            DWORD id[1]     = {n};        
            Oidx Oid(id, 1);
            if ((row = table.find_index(Oid)) == NULL) {
                row = table.add_row(Oid);
            }
            if (row) {
                table.set_row(row, n + 1,
                        asTab.m_Assocs[n].m_mac_add,
                        asTab.m_Assocs[n].m_rssi,
                        asTab.m_Assocs[n].m_noise,
                        asTab.m_Assocs[n].m_snr,
                        asTab.m_Assocs[n].m_rx_rate,
                        asTab.m_Assocs[n].m_tx_rate,
                        asTab.m_Assocs[n].m_queu_load,
                        asTab.m_Assocs[n].m_rx_mcs,
                        asTab.m_Assocs[n].m_tx_mcs,
                        asTab.m_Assocs[n].m_online_time);
            }
        }
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
//  Following is GWS_RADIO part
////////////////////////////////////////////////////////////////////////////////
void GwsIf::m_UpdateGwsUHF() {    
#ifdef INTERFACE_GWSMAN
    int temperature,uhf_region,uhf_channel,uhf_tx,uhf_tx_power,uhf_tx_cal,uhf_rx,uhf_rx_gain,uhf_rx_cal;
    if (!m_report_gws_uhf) {    //just update once
        char    radio_firmware[32];
        int     board_sn,agc_mode,if_out;
        
        RW_KPI_STR(m_nKpi,radio_firmware,m_pKpi->m_radio.m_sFirmware);
        RW_KPI_VAR(m_nKpi,board_sn,m_pKpi->m_radio.m_nBoardSNO);
        RW_KPI_VAR(m_nKpi,agc_mode,m_pKpi->m_radio.m_nAGCMode);
        RW_KPI_VAR(m_nKpi,if_out,m_pKpi->m_radio.m_nIFOUT);
        SET_VBX(radioFirmware,OctetStr,radio_firmware);
        SET_VBX(radioBoardSN,SnmpInt32,board_sn);
        SET_VBX(radioAgcMode,SnmpInt32,agc_mode);
        SET_VBX(radioIfout,SnmpInt32,if_out);
        m_report_gws_uhf = true;
    }

    RW_KPI_VAR(m_nKpi,temperature,m_pKpi->m_radio.m_nTemp);
    RW_KPI_VAR(m_nKpi,uhf_region,m_pKpi->m_radio.m_nRegion);
    RW_KPI_VAR(m_nKpi,uhf_channel,m_pKpi->m_radio.m_nChanNo);
    RW_KPI_VAR(m_nKpi,uhf_tx,m_pKpi->m_radio.m_bTX);
    RW_KPI_VAR(m_nKpi,uhf_tx_power,m_pKpi->m_radio.m_nCurTxPwr);
    RW_KPI_VAR(m_nKpi,uhf_tx_cal,m_pKpi->m_radio.m_bTXCal);
    RW_KPI_VAR(m_nKpi,uhf_rx,m_pKpi->m_radio.m_bRX);
    RW_KPI_VAR(m_nKpi,uhf_rx_gain,m_pKpi->m_radio.m_nRXGain);
    RW_KPI_VAR(m_nKpi,uhf_rx_cal,m_pKpi->m_radio.m_bRXCal);
    SET_VBX(radioTemperature,SnmpInt32,temperature);
    SET_VBX(uhfRegion,SnmpInt32,uhf_region);
    SET_VBX(uhfChannel,Gauge32,uhf_channel);
    SET_VBX(uhfTxOnOff,SnmpInt32,uhf_tx);
    SET_VBX(uhfTxPower,SnmpInt32,uhf_tx_power);
    SET_VBX(uhfTxAutoCal,SnmpInt32,uhf_tx_cal);
    SET_VBX(uhfRxOnOff,SnmpInt32,uhf_rx);
    SET_VBX(uhfRxGain,SnmpInt32,uhf_rx_gain);
    SET_VBX(uhfRxAutoCal,SnmpInt32,uhf_rx_cal);
    WYY_DEBUG_UHF(uhf_channel,"%d");
#else   //INTERFACE_MW_API
    string  sFirmware,sBoardSN;
    long    nChannel,nRegion,nTemperature,nAgcMode,nIfOut;
    long    nTxPower,nRxGain,nTxOnOff,nRxOnOff,nTxCal,nRxCal,nStatus;
    if (0 == m_Get_UHF_Info(sFirmware,sBoardSN,nChannel,nRegion,nTemperature,nAgcMode,
                    nIfOut,nTxPower,nRxGain,nTxOnOff,nRxOnOff,nTxCal,nRxCal,nStatus)) {
        SET_VBX(radioFirmware   ,OctetStr   ,sFirmware.data());
        SET_VBX(radioBoardSN    ,OctetStr   ,sBoardSN.data());
        SET_VBX(uhfChannel      ,Gauge32    ,nChannel);
        SET_VBX(uhfRegion       ,SnmpInt32  ,nRegion);
        SET_VBX(radioTemperature,SnmpInt32  ,nTemperature);
        SET_VBX(radioAgcMode    ,SnmpInt32  ,nAgcMode);
        SET_VBX(radioIfout      ,SnmpInt32  ,nIfOut);
        SET_VBX(uhfTxPower      ,Gauge32    ,nTxPower);
        SET_VBX(uhfRxGain       ,Gauge32    ,nRxGain);
        SET_VBX(uhfTxOnOff      ,SnmpInt32  ,nTxOnOff);
        SET_VBX(uhfRxOnOff      ,SnmpInt32  ,nRxOnOff);
        SET_VBX(uhfTxAutoCal    ,SnmpInt32  ,nTxCal);
        SET_VBX(uhfRxAutoCal    ,SnmpInt32  ,nRxCal);
        SET_VBX(radioStatus     ,SnmpInt32  ,nStatus);
    }
#endif  //#if (INTERFACE_GWSMAN == true)
}

int GwsIf::m_SetGwsUHF(Request* req) {
    if (!req) return -1;    //For SNMP_SET request only
    if (sNMP_PDU_SET != req->get_type()) return 0;

    static bool     bInitOid;
    static string   szOID_uhf_txonoff;
    static string   szOID_uhf_txpower;
    static string   szOID_uhf_channel;
    string          szOID_req = req->get_oid(0).get_printable();
    unsigned long   nValue = 0;
    
    if (bInitOid == false) {
        bInitOid = true;
        Oidx oid_uhf_txonoff = VAR_INSTANCE(uhfTxOnOff).get_oid();
        Oidx oid_uhf_txpower = VAR_INSTANCE(uhfTxPower).get_oid();
        Oidx oid_uhf_channel = VAR_INSTANCE(uhfChannel).get_oid();
        szOID_uhf_txonoff   = oid_uhf_txonoff.get_printable();
        szOID_uhf_txpower   = oid_uhf_txpower.get_printable();
        szOID_uhf_channel   = oid_uhf_channel.get_printable();
    }
//    printf("omc_agent : %s(%d) SET %s = %u\n", __func__, __LINE__, szOID_req.data(), nValue);
//    printf("omc_agent : %s(%d) txpower = %s\n", __func__, __LINE__, szOID_uhf_txpower.data());
//    printf("omc_agent : %s(%d) channel = %s\n", __func__, __LINE__, szOID_uhf_channel.data());
    if (szOID_req == szOID_uhf_txpower) {
        req->get_value(0).get_value(nValue);
        if (0 <= nValue && nValue < 50) {
		char sTxPower[16];
		memset (sTxPower, 0x00, 16);
		snprintf (sTxPower, 15, "%d", nValue);
		set_radio_txpower(sTxPower);
                syslog(4, "omc_agent : set_radio_txpower(%d)\n", nValue);
                return 1;
        }
    } else if (szOID_req == szOID_uhf_channel) {
        req->get_value(0).get_value(nValue);
        if (14 <= nValue && nValue <= 60) {
		char sChannel[16];
		memset (sChannel, 0x00, 16);
		snprintf (sChannel, 15, "%d", nValue);
		set_uhf_channel(sChannel);
                syslog(4, "omc_agent : set_uhf_channel(%d)\n", nValue);
                return 1;
        }
    } else if (szOID_req == szOID_uhf_txonoff) {
        req->get_value(0).get_value(nValue);
        //set_uhf_onoff(!!(nValue) ? "1", "0");
        syslog(4, "omc_agent : set_uhf_onoff(%d)\n", nValue);
        return 1;
    }
    return 0;
}

