
#include <string>
#include <syslog.h>
#include "GwsIf.h"


/////////////////////////////////////////////////////////////////////////////////////////
//The implementations of these functions can be overrided, but don't touch the prototypes
/////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_ENABLE_GWSAPI_SYS     1
#define DEBUG_ENABLE_GWSAPI_BB      1
#define DEBUG_ENABLE_GWSAPI_ASSOC   1
#define DEBUG_ENABLE_GWSAPI_UHF     1

static void TrimLeft(string& s,char c) {
    const char* str = s.data();
    int n,nSize = s.size();
    for (n = 0; n < nSize; n ++) {
        if (c != str[n]) {
            s = s.substr(n,nSize);
            return;
        }
    }
}

static void SplitStringByChar(string& s,string& s_target,char seperator) {
    int     n = -1;
    
    s_target = s.substr(0,(n = s.find_first_of(seperator)));
    if (n > 0) {
        s = s.substr(n+1,s.size());
        TrimLeft(s,seperator);
    }
}

static long static_cpu_busy = 0;
static long static_cpu_total = 0;
static long Calculate_usage_CPU() {
    FILE*   fp = fopen("/proc/stat","r");
    if (fp) {
        long    usage = 0;
        char    buff[1024];
        memset (buff,0x00,1024);
        while (fgets(buff,1023,fp)) {
            if (strstr(buff,"cpu") >= buff) {
                string  s = buff;
                string  s_cpu;
                string  s_user,s_nice,s_system,s_idel,s_iowait,s_irq,s_softirq;
                long    n_user,n_nice,n_system,n_idel,n_iowait,n_irq,n_softirq;
                long    n_busy = -1,n_total;

                SplitStringByChar(s,s_cpu       ,' ');
                SplitStringByChar(s,s_user      ,' ');
                SplitStringByChar(s,s_nice      ,' ');
                SplitStringByChar(s,s_system    ,' ');
                SplitStringByChar(s,s_idel      ,' ');
                SplitStringByChar(s,s_iowait    ,' ');
                SplitStringByChar(s,s_irq       ,' ');
                SplitStringByChar(s,s_softirq   ,' ');
                sscanf(s_user.data()    ,"%d",&n_user);
                sscanf(s_nice.data()    ,"%d",&n_nice);
                sscanf(s_system.data()  ,"%d",&n_system);
                sscanf(s_idel.data()    ,"%d",&n_idel);
                sscanf(s_iowait.data()  ,"%d",&n_iowait);
                sscanf(s_irq.data()     ,"%d",&n_irq);
                sscanf(s_softirq.data() ,"%d",&n_softirq);
                n_busy = n_user + n_nice + n_system + n_iowait + n_irq + n_softirq;
                n_total = n_busy + n_idel;
                if (static_cpu_busy > 0 && static_cpu_total > 0) {
                    int delta = n_total - static_cpu_total;
                    if (delta >= 100) {
                        usage = 100 * (n_busy - static_cpu_busy) / delta;
                        static_cpu_busy     = n_busy;
                        static_cpu_total    = n_total;
                    }
                } else {
                    static_cpu_busy     = n_busy;
                    static_cpu_total    = n_total;
                }
                break;
            }
        }
        fclose(fp);
        return usage;
    }
    return -1;
}

#define MEM_INFO_TOTAL  "MemTotal:"
#define MEM_INFO_FREE   "MemFree:"

static long Calculate_usage_Mem() {
    FILE* fp = fopen("/proc/meminfo", "r");
    if (fp) {
        long usage = 0, n_total = -1, n_free = -1;
        char buff[1024];
        memset(buff, 0x00, 1024);
        while (fgets(buff, 1023, fp)) {
            string s = buff;
            string s_keyword, s_total, s_free;
            if (strstr(buff, MEM_INFO_TOTAL) >= buff) {
                //printf("%s\n",buff);
                SplitStringByChar(s, s_keyword, ' ');
                SplitStringByChar(s, s_total, ' ');
                if (!s_total.empty()) {
                    sscanf(s_total.data(), "%d", &n_total);
                } else {
                    n_total = 0; //error happened
                }
            } else if (strstr(buff, MEM_INFO_FREE) >= buff) {
                //printf("%s\n",buff);
                SplitStringByChar(s, s_keyword, ' ');
                SplitStringByChar(s, s_free, ' ');
                if (!s_free.empty()) {
                    sscanf(s_free.data(), "%d", &n_free);
                } else {
                    n_free = 0; //error happened
                }
            }
            if (-1 == n_total || -1 == n_free) {
                continue; //both free and total are needed
            }
            if (0 == n_total || 0 == n_free) {
                fclose(fp);
                return 0; //error happened
            }
            if (n_total > 0 && n_free > 0) {
                usage = (100 * (n_total - n_free) / n_total);
            }
            break;
        }
        fclose(fp);
        return usage;
    }
    return -1;
}

int GwsIf::m_Get_CPU_Info(long& nCPU) {
    nCPU = Calculate_usage_CPU();       //it's not from API now
}

int GwsIf::m_Get_System_Info(   string&         sVersion,
                                string&         sBanner,
                                string&         sHostname,
                                string&         sUptime,
                                string&         sModuleType,
                                string&         sModuleSN,
                                long&           nMemory,
                                ETH_IF_TABLE&   ifTable,
                                VLAN_TABLE&     vlanTable) {  //return error code
//    time_t  curr_time = time(&curr_time);
	ERROR_CODE    err_code = 0;
    static char str_version[64];
    static char str_uptime[128];
    static char str_hostname[128];
    static char str_banner[64];
    static char str_type[64];
    static char str_sn[64];

    memset (str_version,0x00,64);
    memset (str_uptime,0x00,128);
    memset (str_hostname,0x00,128);
    memset (str_banner,0x00,64);
    memset (str_type,0x00,64);
    memset (str_sn,0x00,64);
#if DEBUG_ENABLE_GWSAPI_SYS
    gethostname(str_hostname,127);
    sHostname = str_hostname;


    if (get_uptime(str_uptime))        	sUptime = str_uptime;
    if (get_api_verion(str_version))    sVersion = str_version;
    if (get_banner(str_banner))         sBanner = str_banner;
    if (get_module_type(str_type))      sModuleType = str_type;
    if (get_module_sn(str_sn))          sModuleSN = str_sn;
    nMemory = Calculate_usage_Mem();	//it's not from API now
#endif  //DEBUG_ENABLE_GWSAPI
//    for (int nIf = 0; nIf < MAX_ETH_IF; nIf ++) {
//        char*   sIfName     = get_if_name();
//        char*   sIpAddr     = get_if_ip();
//        char*   sSubnet     = get_if_subnet();
//        char*   sGateway    = get_if_gateway();
//        char*   sMacAddr    = get_if_mac_address();
//        char*   sBrLan      = get_if_br_lan();
//        char*   sDNS        = get_if_dns();
//        if (sIfName && sIpAddr && sSubnet && sGateway && sMacAddr) {
//            ifTable.m_Ifs[nIf].m_sIf_Name       = sIfName;
//            ifTable.m_Ifs[nIf].m_sIf_Address    = sIpAddr;
//            ifTable.m_Ifs[nIf].m_sIf_Subnet     = sSubnet;
//            ifTable.m_Ifs[nIf].m_sIf_Gateway    = sGateway;
//            ifTable.m_Ifs[nIf].m_sIf_MacAdd     = sMacAddr;
//            ifTable.m_Ifs[nIf].m_sIf_BrLan      = sBrLan;
//            ifTable.m_Ifs[nIf].m_sIf_DNS        = sDNS;
//            if (ifTable.m_Ifs[nIf].m_sIf_Name.empty()) {    //end of if table
//            ifTable.m_nIf_Count = nIf;
//            break;
//            }
//        } else {    //end of if table
//            ifTable.m_nIf_Count = nIf;
//            break;
//        }
//    }
//    
//    vlanTable.m_nVlan_Count = 1;
//    vlanTable.m_Vlans[0].m_vlan_id = 1;
//    vlanTable.m_Vlans[0].m_vlan_name = "br-lan";

    memset (&ifTable    ,0x00,sizeof(ETH_IF_TABLE));
    memset (&vlanTable  ,0x00,sizeof(VLAN_TABLE));
#if DEBUG_ENABLE_GWSAPI_SYS
    if (err_code = get_if_table(&ifTable)) goto label_return;

    if (err_code = get_vlan_table(&vlanTable)) goto label_return;
#endif  //DEBUG_ENABLE_GWSAPI
    
label_return:
    return err_code;
}

int GwsIf::m_Get_BB_Info(   string& sFirmware,
                            string& sMac,
                            string& sSSID,
                            string& sMode,
                            string& sEncryption,
                            long&   nTxPwr,
                            long&   nSignal,
                            long&   nNoise,
                            long&   nBandWidth,
                            long&   nFixedMCS) {    //return error code
    long    err_code    = 0;
    static char    s_firmware[STRSIZE];
    static char    s_mac_addr[STRSIZE];
    static char    s_ssid[STRSIZE];
    static char    s_mode[STRSIZE];
    static char    s_encrypt[STRSIZE];
    
    memset (s_firmware,0x00,STRSIZE);
    memset (s_mac_addr,0x00,STRSIZE);
    memset (s_ssid,0x00,STRSIZE);
    memset (s_mode,0x00,STRSIZE);
    memset (s_encrypt,0x00,STRSIZE);
#if DEBUG_ENABLE_GWSAPI_BB
    if (get_bb_firmware(s_firmware))    sFirmware   = s_firmware;
    //if (get_bb_mac_address(s_mac_addr))  sMac        = s_mac_addr;
    if (get_mac_address(s_mac_addr,"wlan0"))  sMac     = s_mac_addr;
    if (get_bb_ssid(s_ssid))            sSSID       = s_ssid;
    if (get_bb_mode(s_mode))            sMode       = s_mode;
    if (get_bb_encryption(s_encrypt))   sEncryption = s_encrypt;

    if (-1 == get_bb_tx_power(&nTxPwr))     err_code = -10;
    if (-1 == get_bb_signal(&nSignal))      err_code = -11;
    if (-1 == get_bb_noise(&nNoise))        err_code = -12;
    if (-1 == get_bb_fixed_mcs(&nFixedMCS)) err_code = -13;
    if (-1 == get_bb_bandwidth(&nBandWidth)) err_code = -14;
#endif  //DEBUG_ENABLE_GWSAPI
#if (0)
    { //for debugging 2015-12-4
        syslog(4,"---------------- m_Get_BB_Info() -------------------\n");
        syslog(4,"wifi firmware   from gwsapi : %s\n",s_firmware);
       // get_mac_address(s_mac_addr,"wlan0");
        syslog(4,"wifi mac_addr    from gwsapi : %s\n",s_mac_addr);
        syslog(4,"wifi ssid       from gwsapi : %s\n",s_ssid);
        syslog(4,"wifi mode       from gwsapi : %s\n",s_mode);
        syslog(4,"wifi encrypt    from gwsapi : %s\n",s_encrypt);
        syslog(4,"wifi power      from gwsapi : %d\n",nTxPwr);
        syslog(4,"wifi signal     from gwsapi : %d\n",nSignal);
        syslog(4,"wifi noise      from gwsapi : %d\n",nNoise);
        syslog(4,"wifi bandwidth  from gwsapi : %d\n",nBandWidth);
        syslog(4,"wifi fixed MCS  from gwsapi : %d\n",nFixedMCS);
        syslog(4,"-------------error code = %d\n",err_code);
   } //for debugging 2015-12-4
#endif
    return err_code;
}

int GwsIf::m_Get_AssocTable(ASSOC_TABLE& table)
{
	long    err_code    = 0;
    memset (&table,0x00,sizeof(ASSOC_TABLE));
#if DEBUG_ENABLE_GWSAPI_ASSOC
    err_code = get_assoc_table(&table);
#endif  //DEBUG_ENABLE_GWSAPI
#if 0
    int i =0;
	for(i=0;i<table.m_nAssoc;i++)
	{
		printf("m_Get_AssocTable nosie=%d\n",table.m_Assocs[i].m_noise);
		printf("m_Get_AssocTable rssi=%d\n",table.m_Assocs[i].m_rssi);
		printf("m_Get_AssocTable snr=%d\n",table.m_Assocs[i].m_snr);
		printf("m_Get_AssocTable m_rx_mcs=%d\n",table.m_Assocs[i].m_rx_mcs);
		printf("m_Get_AssocTable m_rx_rate=%d\n",table.m_Assocs[i].m_rx_rate);
		printf("m_Get_AssocTable m_tx_mcs=%d\n",table.m_Assocs[i].m_tx_mcs);
		printf("m_Get_AssocTable m_tx_rate=%d\n",table.m_Assocs[i].m_tx_rate);
		printf("m_Get_AssocTable m_mac_add=%s\n",table.m_Assocs[i].m_mac_add);
	}
#endif
    return err_code;
}

int GwsIf::m_Get_UHF_Info(  string& sFirmware,
                            string& sBoardSN,
                            long&   nChannel,
                            long&   nRegion,
                            long&   nTemp,
                            long&   nAgcMode,
                            long&   nIfOut,
                            long&   nTxPower,
                            long&   nRxGain,
                            long&   nTxOnOff,
                            long&   nRxOnOff,
                            long&   nTxCal,
                            long&   nRxCal,
                            long&   nStatus) {    //return error code
    long    err_code    = 0;
    static char    s_firmware[STRSIZE];
    static char    s_board_sn[STRSIZE];

    memset (s_firmware,0x00,STRSIZE);
    memset (s_board_sn,0x00,STRSIZE);
    
#if DEBUG_ENABLE_GWSAPI_UHF
    if (get_radio_firmware(s_firmware)) sFirmware   = s_firmware;
    if (get_radio_board_sn(s_board_sn)) sBoardSN    = s_board_sn;
    if (-1 == get_uhf_channel(&nChannel))       err_code = -20;
    if (-1 == get_uhf_region(&nRegion))         err_code = -21;
    if (-1 == get_radio_temperature(&nTemp))    err_code = -22;
    if (-1 == get_radio_agc_mode(&nAgcMode))    err_code = -23;
    if (-1 == get_radio_ifout(&nIfOut))         err_code = -24;
    if (-1 == get_uhf_txpower(&nTxPower))       err_code = -25;
    if (-1 == get_uhf_rxgain(&nRxGain))         err_code = -26;
    if (-1 == get_uhf_tx_on_off(&nTxOnOff))     err_code = -27;
    if (-1 == get_uhf_tx_auto_cal(&nTxCal))     err_code = -28;

    if (-1 == get_uhf_rx_on_off(&nRxOnOff))     err_code = -29;
    if (-1 == get_uhf_rx_auto_cal(&nRxCal))     err_code = -30;

    if (-1 == get_radio_status(&nStatus))       err_code = -31;
#endif  //DEBUG_ENABLE_GWSAPI
#if (0)
    { //for debugging 2015-12-4
        syslog(4,"---------------- m_Get_UHF_Info() -------------------\n");
        syslog(4,"firmware    from gwsapi : %s\n",s_firmware);
        syslog(4,"board sn    from gwsapi : %s\n",s_board_sn);
        syslog(4,"channel     from gwsapi : %d\n",nChannel);
        syslog(4,"region      from gwsapi : %d\n",nRegion);
        syslog(4,"temperature from gwsapi : %d\n",nTemp);
        syslog(4,"agcmode     from gwsapi : %d\n",nAgcMode);
        syslog(4,"ifout       from gwsapi : %d\n",nIfOut);
        syslog(4,"txpower     from gwsapi : %d\n",nTxPower);
        syslog(4,"rxgain      from gwsapi : %d\n",nRxGain);
        syslog(4,"txcal       from gwsapi : %d\n",nTxCal);
        syslog(4,"txOnOff     from gwsapi : %d\n",nTxOnOff);
        syslog(4,"rxcal       from gwsapi : %d\n",nRxCal);
        syslog(4,"rxOnOff     from gwsapi : %d\n",nRxOnOff);

        syslog(4,"nStatus     from gwsapi : %d\n",nStatus);

        syslog(4,"-------------error code = %d\n",err_code);

    } //for debugging 2015-12-4
#endif
    return err_code;
}

//The following functions should be implemented in libgwsapi, please remove them after that
//long get_if_table(ETH_IF_TABLE* table)      { return 0; }
//long get_vlan_table(VLAN_TABLE* table)      { return 0; }
//long get_assoc_table(ASSOC_TABLE* table)    { return 0; }
//char* get_bb_ssid()                         { return "GWS_20151106"; }
//char* get_bb_encryption()                   { return "none"; }
//char* get_bb_mode()                         { return "Mesh Point"; }
#define GPS_F2N(f)  (f >= 0 ? (long)(f * 1000000 + 0.5) : (long)(f * 1000000 - 0.5))
int GwsIf::m_Get_GPS_Info(long& nLongitude, long& nLatitude, long& nSpeed) {
    char    s_longitude[128] = {0}, s_latitude[128] = {0}, s_speed[128] = {0};
    double  fLongitude = 0.0, fLatitude = 0.0, fSpeed = 0.0;
    
    if (!get_gps_longitude(s_longitude))    return -32;
    if (!get_gps_latitude(s_latitude))      return -33;
    if (!get_gps_speed(s_speed))            return -34;
    sscanf(s_longitude, "%lf", &fLongitude);    nLongitude = GPS_F2N(fLongitude);
    sscanf(s_latitude, "%lf", &fLatitude);      nLatitude = GPS_F2N(fLatitude);
    sscanf(s_speed, "%lf", &fSpeed);            nSpeed = GPS_F2N(fSpeed);
    return 0;
}

