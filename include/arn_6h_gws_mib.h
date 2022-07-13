//
// AgentGen Standard v1.5  Copyright (C) Frank Fock, All rights reserved
// Not for use in a commercial environment
//


#ifndef _arn_6h_gws_mib_h
#define _arn_6h_gws_mib_h


#include <mib.h>

#include <snmp_textual_conventions.h>
#include <notification_originator.h>
#include <log.h>
#include "agent.h"


#define oidTitle                         "1.3.6.1.4.1.46002.2.1.1.0"
#define oidBanner                        "1.3.6.1.4.1.46002.2.1.2.0"
#define oidHostname                      "1.3.6.1.4.1.46002.2.1.3.0"
#define oidOwnerContact                  "1.3.6.1.4.1.46002.2.1.5.0"
#define oidUpTime                        "1.3.6.1.4.1.46002.2.1.6.0"
#define oidModuleType                    "1.3.6.1.4.1.46002.2.1.7.0"
#define oidModuleSN                      "1.3.6.1.4.1.46002.2.1.8.0"
#define oidIfnameTable                   "1.3.6.1.4.1.46002.2.3.1"
#define oidIfnameEntry                   "1.3.6.1.4.1.46002.2.3.1.1"
#define oidIfnameIndex                   "1.3.6.1.4.1.46002.2.3.1.1.1"
#define colIfnameIndex                   "1"
#define oidIfnameRowStatus               "1.3.6.1.4.1.46002.2.3.1.1.2"
#define colIfnameRowStatus               "2"
#define oidIfnameName                    "1.3.6.1.4.1.46002.2.3.1.1.3"
#define colIfnameName                    "3"
#define oidIfnameBrLan                   "1.3.6.1.4.1.46002.2.3.1.1.4"
#define colIfnameBrLan                   "4"
#define oidIfnameIP                      "1.3.6.1.4.1.46002.2.3.1.1.5"
#define colIfnameIP                      "5"
#define oidIfnameSubnet                  "1.3.6.1.4.1.46002.2.3.1.1.6"
#define colIfnameSubnet                  "6"
#define oidIfnameMacAddress              "1.3.6.1.4.1.46002.2.3.1.1.7"
#define colIfnameMacAddress              "7"
#define oidIfnameGateway                 "1.3.6.1.4.1.46002.2.3.1.1.8"
#define colIfnameGateway                 "8"
#define oidIfnameDNS                     "1.3.6.1.4.1.46002.2.3.1.1.9"
#define colIfnameDNS                     "9"
#define oidVlanTable                     "1.3.6.1.4.1.46002.2.3.3"
#define oidVlanEntry                     "1.3.6.1.4.1.46002.2.3.3.1"
#define oidVlanIndex                     "1.3.6.1.4.1.46002.2.3.3.1.1"
#define colVlanIndex                     "1"
#define oidVlanRowStatus                 "1.3.6.1.4.1.46002.2.3.3.1.2"
#define colVlanRowStatus                 "2"
#define oidVlanID                        "1.3.6.1.4.1.46002.2.3.3.1.3"
#define colVlanID                        "3"
#define oidVlanIfname                    "1.3.6.1.4.1.46002.2.3.3.1.4"
#define colVlanIfname                    "4"
#define oidRadioFirmware                 "1.3.6.1.4.1.46002.2.4.1.1.0"
#define oidRadioBoardSN                  "1.3.6.1.4.1.46002.2.4.1.2.0"
#define oidRadioTemperature              "1.3.6.1.4.1.46002.2.4.1.3.0"
#define oidRadioAgcMode                  "1.3.6.1.4.1.46002.2.4.1.5.0"
#define oidRadioIfout                    "1.3.6.1.4.1.46002.2.4.1.6.0"
#define oidRadioStatus                   "1.3.6.1.4.1.46002.2.4.1.7.0"
#define oidBbFirmware                    "1.3.6.1.4.1.46002.2.4.2.1.0"
#define oidBbFixedMCS                    "1.3.6.1.4.1.46002.2.4.2.2.0"
#define oidBbMacAddress                  "1.3.6.1.4.1.46002.2.4.2.3.0"
#define oidBbTxPower                     "1.3.6.1.4.1.46002.2.4.2.4.0"
#define oidBbSignal                      "1.3.6.1.4.1.46002.2.4.2.5.0"
#define oidBbNoise                       "1.3.6.1.4.1.46002.2.4.2.6.0"
#define oidBbBandwidth                   "1.3.6.1.4.1.46002.2.4.2.7.0"
#define oidBbHandover                    "1.3.6.1.4.1.46002.2.4.2.8.0"
#define oidBbStatus                      "1.3.6.1.4.1.46002.2.4.2.9.0"
#define oidAssocCount                    "1.3.6.1.4.1.46002.2.4.2.11.0"
#define oidAssocTable                    "1.3.6.1.4.1.46002.2.4.2.12"
#define oidAssocEntry                    "1.3.6.1.4.1.46002.2.4.2.12.1"
#define oidStaIndex                      "1.3.6.1.4.1.46002.2.4.2.12.1.1"
#define colStaIndex                      "1"
#define oidStaRowStatus                  "1.3.6.1.4.1.46002.2.4.2.12.1.2"
#define colStaRowStatus                  "2"
#define oidStaMacAddress                 "1.3.6.1.4.1.46002.2.4.2.12.1.3"
#define colStaMacAddress                 "3"
#define oidStaSignal                     "1.3.6.1.4.1.46002.2.4.2.12.1.4"
#define colStaSignal                     "4"
#define oidStaNoise                      "1.3.6.1.4.1.46002.2.4.2.12.1.5"
#define colStaNoise                      "5"
#define oidStaSNR                        "1.3.6.1.4.1.46002.2.4.2.12.1.6"
#define colStaSNR                        "6"
#define oidStaRxRate                     "1.3.6.1.4.1.46002.2.4.2.12.1.7"
#define colStaRxRate                     "7"
#define oidStaTxRate                     "1.3.6.1.4.1.46002.2.4.2.12.1.8"
#define colStaTxRate                     "8"
#define oidStaQLoad                      "1.3.6.1.4.1.46002.2.4.2.12.1.9"
#define colStaQLoad                      "9"
#define oidStaRxMcs                      "1.3.6.1.4.1.46002.2.4.2.12.1.10"
#define colStaRxMcs                      "10"
#define oidStaTxMcs                      "1.3.6.1.4.1.46002.2.4.2.12.1.11"
#define colStaTxMcs                      "11"
#define oidStaOnlineTime                 "1.3.6.1.4.1.46002.2.4.2.12.1.12"
#define colStaOnlineTime                 "12"
#define oidRouteTable                    "1.3.6.1.4.1.46002.2.4.2.13"
#define oidRouteEntry                    "1.3.6.1.4.1.46002.2.4.2.13.1"
#define oidRouteIndex                    "1.3.6.1.4.1.46002.2.4.2.13.1.1"
#define colRouteIndex                    "1"
#define oidRouteRowStatus                "1.3.6.1.4.1.46002.2.4.2.13.1.2"
#define colRouteRowStatus                "2"
#define oidRouteDestination              "1.3.6.1.4.1.46002.2.4.2.13.1.3"
#define colRouteDestination              "3"
#define oidRouteNextHop                  "1.3.6.1.4.1.46002.2.4.2.13.1.4"
#define colRouteNextHop                  "4"
#define oidRouteMetric                   "1.3.6.1.4.1.46002.2.4.2.13.1.5"
#define colRouteMetric                   "5"
#define oidRouteFlags                    "1.3.6.1.4.1.46002.2.4.2.13.1.6"
#define colRouteFlags                    "6"
#define oidRouteExpiredTime              "1.3.6.1.4.1.46002.2.4.2.13.1.7"
#define colRouteExpiredTime              "7"
#define oidBbSSID                        "1.3.6.1.4.1.46002.2.4.3.2.0"
#define oidBbMESHID                      "1.3.6.1.4.1.46002.2.4.3.3.0"
#define oidBbEncryption                  "1.3.6.1.4.1.46002.2.4.3.4.0"
#define oidBbProtocol                    "1.3.6.1.4.1.46002.2.4.3.5.0"
#define oidBbHT20                        "1.3.6.1.4.1.46002.2.4.3.6.0"
#define oidBbHT20SGI                     "1.3.6.1.4.1.46002.2.4.3.7.0"
#define oidBbOptMode                     "1.3.6.1.4.1.46002.2.4.3.8.0"
#define oidUhfRegion                     "1.3.6.1.4.1.46002.2.4.3.9.0"
#define oidUhfChannel                    "1.3.6.1.4.1.46002.2.4.3.10.0"
#define oidUhfTxOnOff                    "1.3.6.1.4.1.46002.2.4.3.11.1.0"
#define oidUhfTxPower                    "1.3.6.1.4.1.46002.2.4.3.11.2.0"
#define oidUhfTxAutoCal                  "1.3.6.1.4.1.46002.2.4.3.11.3.0"
#define oidUhfRxOnOff                    "1.3.6.1.4.1.46002.2.4.3.12.1.0"
#define oidUhfRxGain                     "1.3.6.1.4.1.46002.2.4.3.12.2.0"
#define oidUhfRxAutoCal                  "1.3.6.1.4.1.46002.2.4.3.12.3.0"
#define oidScanChannel                   "1.3.6.1.4.1.46002.2.4.4.1.0"
#define oidScanTimer                     "1.3.6.1.4.1.46002.2.4.4.2.0"
#define oidScanTrigger                   "1.3.6.1.4.1.46002.2.4.4.3.0"
#define oidGpsLongitude                  "1.3.6.1.4.1.46002.2.6.1.1.0"
#define oidGpsLatitude                   "1.3.6.1.4.1.46002.2.6.1.2.0"
#define oidGpsSpeed                      "1.3.6.1.4.1.46002.2.6.1.3.0"
#define oidGpsStatus                     "1.3.6.1.4.1.46002.2.6.2.0"
#define oidDlThroughput                  "1.3.6.1.4.1.46002.2.7.1.1.0"
#define oidUlThroughput                  "1.3.6.1.4.1.46002.2.7.2.1.0"
#define oidUsageCPU                      "1.3.6.1.4.1.46002.2.7.3.0"
#define oidUsageMem                      "1.3.6.1.4.1.46002.2.7.4.0"
#define oidHwBoardEvent                  "1.3.6.1.4.1.46002.2.8"
#define oidSwKeyParameters               "1.3.6.1.4.1.46002.2.10"


//--AgentGen BEGIN=_INCLUDE
//--AgentGen END


/**
 *  title
 *
 * "BTS name"
 */


class title: public SnmpDisplayString {

public:
	title();
	virtual ~title();

	static title* instance;

	virtual void       	get_request(Request*, int);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=title
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  banner
 *
 * "Percentage of CPU usage."
 */


class banner: public SnmpDisplayString {

public:
	banner();
	virtual ~banner();

	static banner* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=banner
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  hostname
 *
 * "GWS hostname"
 */


class hostname: public SnmpDisplayString {

public:
	hostname();
	virtual ~hostname();

	static hostname* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=hostname
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  ownerContact
 *
 * "Geo-location coordinates for database countries"
 */


class ownerContact: public SnmpDisplayString {

public:
	ownerContact();
	virtual ~ownerContact();

	static ownerContact* instance;

	virtual void       	get_request(Request*, int);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=ownerContact
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  upTime
 *
 * "Escaped seconds since the device power on."
 */


class upTime: public SnmpDisplayString {

public:
	upTime();
	virtual ~upTime();

	static upTime* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=upTime
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  moduleType
 *
 * "CAR/EAR/CPE"
 */


class moduleType: public SnmpDisplayString {

public:
	moduleType();
	virtual ~moduleType();

	static moduleType* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=moduleType
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  moduleSN
 *
 * "Firmware version."
 */


class moduleSN: public SnmpDisplayString {

public:
	moduleSN();
	virtual ~moduleSN();

	static moduleSN* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=moduleSN
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  ifnameRowStatus
 *
 * "Column Description"
 */


class ifnameRowStatus: public snmpRowStatus {

public:
	ifnameRowStatus(const Oidx&);
	virtual ~ifnameRowStatus();

	virtual MibEntryPtr	clone();
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);

//--AgentGen BEGIN=ifnameRowStatus
//--AgentGen END
};


/**
 *  ifnameName
 *
 * "Description"
 */


class ifnameName: public SnmpDisplayString {

public:
	ifnameName(const Oidx&);
	virtual ~ifnameName();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=ifnameName
//--AgentGen END
};


/**
 *  ifnameBrLan
 *
 * "Column Description"
 */


class ifnameBrLan: public SnmpDisplayString {

public:
	ifnameBrLan(const Oidx&);
	virtual ~ifnameBrLan();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=ifnameBrLan
//--AgentGen END
};


/**
 *  ifnameIP
 *
 * "Column Description"
 */


class ifnameIP: public MibLeaf {

public:
	ifnameIP(const Oidx&);
	virtual ~ifnameIP();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=ifnameIP
//--AgentGen END
};


/**
 *  ifnameSubnet
 *
 * "Column Description"
 */


class ifnameSubnet: public MibLeaf {

public:
	ifnameSubnet(const Oidx&);
	virtual ~ifnameSubnet();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=ifnameSubnet
//--AgentGen END
};


/**
 *  ifnameMacAddress
 *
 * "Column Description"
 */


class ifnameMacAddress: public MibLeaf {

public:
	ifnameMacAddress(const Oidx&);
	virtual ~ifnameMacAddress();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=ifnameMacAddress
//--AgentGen END
};


/**
 *  ifnameGateway
 *
 * "Column Description"
 */


class ifnameGateway: public MibLeaf {

public:
	ifnameGateway(const Oidx&);
	virtual ~ifnameGateway();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=ifnameGateway
//--AgentGen END
};


/**
 *  ifnameDNS
 *
 * "Description"
 */


class ifnameDNS: public MibLeaf {

public:
	ifnameDNS(const Oidx&);
	virtual ~ifnameDNS();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=ifnameDNS
//--AgentGen END
};


/**
 *  vlanRowStatus
 *
 * "Column Description"
 */


class vlanRowStatus: public snmpRowStatus {

public:
	vlanRowStatus(const Oidx&);
	virtual ~vlanRowStatus();

	virtual MibEntryPtr	clone();
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);

//--AgentGen BEGIN=vlanRowStatus
//--AgentGen END
};


/**
 *  vlanID
 *
 * "Column Description"
 */


class vlanID: public MibLeaf {

public:
	vlanID(const Oidx&);
	virtual ~vlanID();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=vlanID
//--AgentGen END
};


/**
 *  vlanIfname
 *
 * "Column Description"
 */


class vlanIfname: public SnmpDisplayString {

public:
	vlanIfname(const Oidx&);
	virtual ~vlanIfname();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=vlanIfname
//--AgentGen END
};


/**
 *  radioFirmware
 *
 * "Description"
 */


class radioFirmware: public SnmpDisplayString {

public:
	radioFirmware();
	virtual ~radioFirmware();

	static radioFirmware* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=radioFirmware
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  radioBoardSN
 *
 * "Description"
 */


class radioBoardSN: public SnmpDisplayString {

public:
	radioBoardSN();
	virtual ~radioBoardSN();

	static radioBoardSN* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=radioBoardSN
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  radioTemperature
 *
 * "Description"
 */


class radioTemperature: public MibLeaf {

public:
	radioTemperature();
	virtual ~radioTemperature();

	static radioTemperature* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=radioTemperature
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  radioAgcMode
 *
 * "Description"
 */


class radioAgcMode: public MibLeaf {

public:
	radioAgcMode();
	virtual ~radioAgcMode();

	static radioAgcMode* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=radioAgcMode
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  radioIfout
 *
 * "Description"
 */


class radioIfout: public MibLeaf {

public:
	radioIfout();
	virtual ~radioIfout();

	static radioIfout* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=radioIfout
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  radioStatus
 *
 * "Description"
 */


class radioStatus: public MibLeaf {

public:
	radioStatus();
	virtual ~radioStatus();

	static radioStatus* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=radioStatus
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbFirmware
 *
 * "Description"
 */


class bbFirmware: public SnmpDisplayString {

public:
	bbFirmware();
	virtual ~bbFirmware();

	static bbFirmware* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=bbFirmware
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbFixedMCS
 *
 * "Description"
 */


class bbFixedMCS: public MibLeaf {

public:
	bbFixedMCS();
	virtual ~bbFixedMCS();

	static bbFixedMCS* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=bbFixedMCS
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbMacAddress
 *
 * "Description"
 */


class bbMacAddress: public MibLeaf {

public:
	bbMacAddress();
	virtual ~bbMacAddress();

	static bbMacAddress* instance;

	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=bbMacAddress
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbTxPower
 *
 * "Description"
 */


class bbTxPower: public MibLeaf {

public:
	bbTxPower();
	virtual ~bbTxPower();

	static bbTxPower* instance;

	virtual void       	get_request(Request*, int);
	virtual unsigned long       	get_state();
	virtual void       	set_state(unsigned long);

//--AgentGen BEGIN=bbTxPower
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbSignal
 *
 * "Description"
 */


class bbSignal: public MibLeaf {

public:
	bbSignal();
	virtual ~bbSignal();

	static bbSignal* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=bbSignal
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbNoise
 *
 * "Description"
 */


class bbNoise: public MibLeaf {

public:
	bbNoise();
	virtual ~bbNoise();

	static bbNoise* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=bbNoise
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbBandwidth
 *
 * "Description"
 */


class bbBandwidth: public MibLeaf {

public:
	bbBandwidth();
	virtual ~bbBandwidth();

	static bbBandwidth* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=bbBandwidth
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbHandover
 *
 * "Description"
 */


class bbHandover: public MibLeaf {

public:
	bbHandover();
	virtual ~bbHandover();

	static bbHandover* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=bbHandover
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbStatus
 *
 * "Description"
 */


class bbStatus: public MibLeaf {

public:
	bbStatus();
	virtual ~bbStatus();

	static bbStatus* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=bbStatus
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  assocCount
 *
 * "Description"
 */


class assocCount: public MibLeaf {

public:
	assocCount();
	virtual ~assocCount();

	static assocCount* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=assocCount
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  staRowStatus
 *
 * "Column Description"
 */


class staRowStatus: public snmpRowStatus {

public:
	staRowStatus(const Oidx&);
	virtual ~staRowStatus();

	virtual MibEntryPtr	clone();
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);

//--AgentGen BEGIN=staRowStatus
//--AgentGen END
};


/**
 *  staMacAddress
 *
 * "Column Description"
 */


class staMacAddress: public MibLeaf {

public:
	staMacAddress(const Oidx&);
	virtual ~staMacAddress();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=staMacAddress
//--AgentGen END
};


/**
 *  staSignal
 *
 * "Column Description"
 */


class staSignal: public MibLeaf {

public:
	staSignal(const Oidx&);
	virtual ~staSignal();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=staSignal
//--AgentGen END
};


/**
 *  staNoise
 *
 * "Column Description"
 */


class staNoise: public MibLeaf {

public:
	staNoise(const Oidx&);
	virtual ~staNoise();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=staNoise
//--AgentGen END
};


/**
 *  staSNR
 *
 * "Column Description"
 */


class staSNR: public MibLeaf {

public:
	staSNR(const Oidx&);
	virtual ~staSNR();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=staSNR
//--AgentGen END
};


/**
 *  staRxRate
 *
 * "Column Description"
 */


class staRxRate: public MibLeaf {

public:
	staRxRate(const Oidx&);
	virtual ~staRxRate();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=staRxRate
//--AgentGen END
};


/**
 *  staTxRate
 *
 * "Column Description"
 */


class staTxRate: public MibLeaf {

public:
	staTxRate(const Oidx&);
	virtual ~staTxRate();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=staTxRate
//--AgentGen END
};


/**
 *  staQLoad
 *
 * "Column Description"
 */


class staQLoad: public MibLeaf {

public:
	staQLoad(const Oidx&);
	virtual ~staQLoad();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=staQLoad
//--AgentGen END
};


/**
 *  staRxMcs
 *
 * "Column Description"
 */


class staRxMcs: public MibLeaf {

public:
	staRxMcs(const Oidx&);
	virtual ~staRxMcs();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=staRxMcs
//--AgentGen END
};


/**
 *  staTxMcs
 *
 * "Column Description"
 */


class staTxMcs: public MibLeaf {

public:
	staTxMcs(const Oidx&);
	virtual ~staTxMcs();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=staTxMcs
//--AgentGen END
};


/**
 *  staOnlineTime
 *
 * "Identify the online seconds since the STA associated."
 */


class staOnlineTime: public SnmpDisplayString {

public:
	staOnlineTime(const Oidx&);
	virtual ~staOnlineTime();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=staOnlineTime
//--AgentGen END
};


/**
 *  routeRowStatus
 *
 * "Column Description"
 */


class routeRowStatus: public snmpRowStatus {

public:
	routeRowStatus(const Oidx&);
	virtual ~routeRowStatus();

	virtual MibEntryPtr	clone();
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);

//--AgentGen BEGIN=routeRowStatus
//--AgentGen END
};


/**
 *  routeDestination
 *
 * "Destination MAC address"
 */


class routeDestination: public MibLeaf {

public:
	routeDestination(const Oidx&);
	virtual ~routeDestination();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=routeDestination
//--AgentGen END
};


/**
 *  routeNextHop
 *
 * "Next Hop MAC address"
 */


class routeNextHop: public MibLeaf {

public:
	routeNextHop(const Oidx&);
	virtual ~routeNextHop();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);

//--AgentGen BEGIN=routeNextHop
//--AgentGen END
};


/**
 *  routeMetric
 *
 * "Description"
 */


class routeMetric: public MibLeaf {

public:
	routeMetric(const Oidx&);
	virtual ~routeMetric();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=routeMetric
//--AgentGen END
};


/**
 *  routeFlags
 *
 * "Description"
 */


class routeFlags: public MibLeaf {

public:
	routeFlags(const Oidx&);
	virtual ~routeFlags();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual unsigned long       	get_state();
	virtual void       	set_state(unsigned long);

//--AgentGen BEGIN=routeFlags
//--AgentGen END
};


/**
 *  routeExpiredTime
 *
 * "Description"
 */


class routeExpiredTime: public MibLeaf {

public:
	routeExpiredTime(const Oidx&);
	virtual ~routeExpiredTime();

	virtual MibEntryPtr	clone();
	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=routeExpiredTime
//--AgentGen END
};


/**
 *  bbSSID
 *
 * "Description"
 */


class bbSSID: public SnmpDisplayString {

public:
	bbSSID();
	virtual ~bbSSID();

	static bbSSID* instance;

	virtual void       	get_request(Request*, int);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=bbSSID
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbMESHID
 *
 * "Description"
 */


class bbMESHID: public SnmpDisplayString {

public:
	bbMESHID();
	virtual ~bbMESHID();

	static bbMESHID* instance;

	virtual void       	get_request(Request*, int);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=bbMESHID
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbEncryption
 *
 * "Description"
 */


class bbEncryption: public MibLeaf {

public:
	bbEncryption();
	virtual ~bbEncryption();

	static bbEncryption* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=bbEncryption
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbProtocol
 *
 * "Description"
 */


class bbProtocol: public MibLeaf {

public:
	bbProtocol();
	virtual ~bbProtocol();

	static bbProtocol* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=bbProtocol
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbHT20
 *
 * "Description"
 */


class bbHT20: public MibLeaf {

public:
	bbHT20();
	virtual ~bbHT20();

	static bbHT20* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=bbHT20
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbHT20SGI
 *
 * "Description"
 */


class bbHT20SGI: public MibLeaf {

public:
	bbHT20SGI();
	virtual ~bbHT20SGI();

	static bbHT20SGI* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=bbHT20SGI
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  bbOptMode
 *
 * "Description"
 */


class bbOptMode: public MibLeaf {

public:
	bbOptMode();
	virtual ~bbOptMode();

	static bbOptMode* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=bbOptMode
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  uhfRegion
 *
 * "Description"
 */


class uhfRegion: public MibLeaf {

public:
	uhfRegion();
	virtual ~uhfRegion();

	static uhfRegion* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=uhfRegion
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  uhfChannel
 *
 * "Description"
 */


class uhfChannel: public MibLeaf {

public:
	uhfChannel();
	virtual ~uhfChannel();

	static uhfChannel* instance;

	virtual void       	get_request(Request*, int);
	virtual unsigned long       	get_state();
	virtual void       	set_state(unsigned long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=uhfChannel
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  uhfTxOnOff
 *
 * "Description"
 */


class uhfTxOnOff: public MibLeaf {

public:
	uhfTxOnOff();
	virtual ~uhfTxOnOff();

	static uhfTxOnOff* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=uhfTxOnOff
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  uhfTxPower
 *
 * "Description"
 */


class uhfTxPower: public MibLeaf {

public:
	uhfTxPower();
	virtual ~uhfTxPower();

	static uhfTxPower* instance;

	virtual void       	get_request(Request*, int);
	virtual unsigned long       	get_state();
	virtual void       	set_state(unsigned long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=uhfTxPower
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  uhfTxAutoCal
 *
 * "Description"
 */


class uhfTxAutoCal: public MibLeaf {

public:
	uhfTxAutoCal();
	virtual ~uhfTxAutoCal();

	static uhfTxAutoCal* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=uhfTxAutoCal
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  uhfRxOnOff
 *
 * "Description"
 */


class uhfRxOnOff: public MibLeaf {

public:
	uhfRxOnOff();
	virtual ~uhfRxOnOff();

	static uhfRxOnOff* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=uhfRxOnOff
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  uhfRxGain
 *
 * "Description"
 */


class uhfRxGain: public MibLeaf {

public:
	uhfRxGain();
	virtual ~uhfRxGain();

	static uhfRxGain* instance;

	virtual void       	get_request(Request*, int);
	virtual unsigned long       	get_state();
	virtual void       	set_state(unsigned long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=uhfRxGain
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  uhfRxAutoCal
 *
 * "Description"
 */


class uhfRxAutoCal: public MibLeaf {

public:
	uhfRxAutoCal();
	virtual ~uhfRxAutoCal();

	static uhfRxAutoCal* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=uhfRxAutoCal
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  scanChannel
 *
 * "specify the target channel to be scanned. channel = 0 means all channels"
 */


class scanChannel: public MibLeaf {

public:
	scanChannel();
	virtual ~scanChannel();

	static scanChannel* instance;

	virtual void       	get_request(Request*, int);
	virtual unsigned long       	get_state();
	virtual void       	set_state(unsigned long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=scanChannel
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  scanTimer
 *
 * "Scan timer in second. 0 means infinite."
 */


class scanTimer: public MibLeaf {

public:
	scanTimer();
	virtual ~scanTimer();

	static scanTimer* instance;

	virtual void       	get_request(Request*, int);
	virtual unsigned long       	get_state();
	virtual void       	set_state(unsigned long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=scanTimer
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  scanTrigger
 *
 * "Set true to start channel scan, set false to stop it.
 * Will back to false automatically while scan finished."
 */


class scanTrigger: public MibLeaf {

public:
	scanTrigger();
	virtual ~scanTrigger();

	static scanTrigger* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);
	virtual int        	set(const Vbx&);
	virtual int        	prepare_set_request(Request*, int&);
	virtual boolean    	value_ok(const Vbx&);

//--AgentGen BEGIN=scanTrigger
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  gpsLongitude
 *
 * "Description"
 */


class gpsLongitude: public MibLeaf {

public:
	gpsLongitude();
	virtual ~gpsLongitude();

	static gpsLongitude* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=gpsLongitude
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  gpsLatitude
 *
 * "Description"
 */


class gpsLatitude: public MibLeaf {

public:
	gpsLatitude();
	virtual ~gpsLatitude();

	static gpsLatitude* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=gpsLatitude
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  gpsSpeed
 *
 * "Description"
 */


class gpsSpeed: public MibLeaf {

public:
	gpsSpeed();
	virtual ~gpsSpeed();

	static gpsSpeed* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=gpsSpeed
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  gpsStatus
 *
 * "Description"
 */


class gpsStatus: public MibLeaf {

public:
	gpsStatus();
	virtual ~gpsStatus();

	static gpsStatus* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=gpsStatus
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  dlThroughput
 *
 * "Description"
 */


class dlThroughput: public MibLeaf {

public:
	dlThroughput();
	virtual ~dlThroughput();

	static dlThroughput* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=dlThroughput
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  ulThroughput
 *
 * "Description"
 */


class ulThroughput: public MibLeaf {

public:
	ulThroughput();
	virtual ~ulThroughput();

	static ulThroughput* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=ulThroughput
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  usageCPU
 *
 * "Description"
 */


class usageCPU: public MibLeaf {

public:
	usageCPU();
	virtual ~usageCPU();

	static usageCPU* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=usageCPU
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  usageMem
 *
 * "Description"
 */


class usageMem: public MibLeaf {

public:
	usageMem();
	virtual ~usageMem();

	static usageMem* instance;

	virtual void       	get_request(Request*, int);
	virtual long       	get_state();
	virtual void       	set_state(long);

//--AgentGen BEGIN=usageMem
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  hwBoardEvent
 *
 * "Description"
 */


class hwBoardEvent: public NotificationOriginator {

public:
	hwBoardEvent();
	virtual ~hwBoardEvent();

	virtual void        	generate(Vbx*, int, const OctetStr&);

//--AgentGen BEGIN=hwBoardEvent
//--AgentGen END
};


/**
 *  swKeyParameters
 *
 * "Description"
 */


class swKeyParameters: public NotificationOriginator {

public:
	swKeyParameters();
	virtual ~swKeyParameters();

	virtual void        	generate(Vbx*, int, const OctetStr&);

//--AgentGen BEGIN=swKeyParameters
//--AgentGen END
};


/**
 *  ifnameEntry
 *
 * "Row Description"
 */


class ifnameEntry: public MibTable {

public:
	ifnameEntry();
	virtual ~ifnameEntry();

	static ifnameEntry* instance;

	virtual boolean     	ready_for_service(Vbx*, int);
	virtual void        	row_added(MibTableRow*, const Oidx&, MibTable*);
	virtual void        	row_delete(MibTableRow*, const Oidx&, MibTable*);
	virtual void       	set_row(MibTableRow* r, long p0, char* p1, char* p2, char* p3, char* p4, char* p5, char* p6, char* p7);

//--AgentGen BEGIN=ifnameEntry
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  vlanEntry
 *
 * "Row Description"
 */


class vlanEntry: public MibTable {

public:
	vlanEntry();
	virtual ~vlanEntry();

	static vlanEntry* instance;

	virtual boolean     	ready_for_service(Vbx*, int);
	virtual void        	row_added(MibTableRow*, const Oidx&, MibTable*);
	virtual void        	row_delete(MibTableRow*, const Oidx&, MibTable*);
	virtual void       	set_row(MibTableRow* r, long p0, long p1, char* p2);

//--AgentGen BEGIN=vlanEntry
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  assocEntry
 *
 * "Row Description"
 */


class assocEntry: public MibTable {

public:
	assocEntry();
	virtual ~assocEntry();

	static assocEntry* instance;

	virtual boolean     	ready_for_service(Vbx*, int);
	virtual void        	row_added(MibTableRow*, const Oidx&, MibTable*);
	virtual void        	row_delete(MibTableRow*, const Oidx&, MibTable*);
	virtual void       	set_row(MibTableRow* r, long p0, char* p1, long p2, long p3, long p4, long p5, long p6, long p7, long p8, long p9
		, char* p10);

//--AgentGen BEGIN=assocEntry
//--AgentGen END
 private:
	char* 	path;
};


/**
 *  routeEntry
 *
 * "Row Description"
 */


class routeEntry: public MibTable {

public:
	routeEntry();
	virtual ~routeEntry();

	static routeEntry* instance;

	virtual boolean     	ready_for_service(Vbx*, int);
	virtual void        	row_added(MibTableRow*, const Oidx&, MibTable*);
	virtual void        	row_delete(MibTableRow*, const Oidx&, MibTable*);
	virtual void       	set_row(MibTableRow* r, long p0, char* p1, char* p2, long p3, unsigned long p4, long p5);

//--AgentGen BEGIN=routeEntry
//--AgentGen END
 private:
	char* 	path;
};


class arn_6h_gws_mib: public MibGroup
{
  public:
	arn_6h_gws_mib();
	virtual ~arn_6h_gws_mib() { }

//--AgentGen BEGIN=arn_6h_gws_mib
//--AgentGen END

};

//--AgentGen BEGIN=_END
//--AgentGen END


#endif



