/* 
 * File:   agentHeader.h
 * Author: wyy
 *
 * Created on 2009�???0?? �??5:36
 */

//#ifndef _AGENTHEADER_H
#define	_AGENTHEADER_H

#ifdef SNMP_PP_NAMESPACE
using namespace Snmp_pp;
#endif

#ifdef AGENTPP_NAMESPACE
using namespace Agentpp;
#endif

#define VERSION 1000
#define INVALID -1
#define EMPTY   0x00000000
#define DWORD   unsigned long
#define WORD    unsigned short
#define BYTE    unsigned char

#define OID_6H          46002
#define OID_6H_S        "46002"
//#define VBLIST  List<Vbx>
//#define MAX_ALARM   16

#include "error_agent.h"
#include <linux/reboot.h>
#include <sys/reboot.h>
#include <pthread.h>


extern          bool                bIsDebugOn;
#define         COLOR_BLACK_WHITE       "\038"
#define         COLOR_RED_BLACK         "\031"
#define         COLOR_GREEN_WHITE       "\032"
#define         COLOR_YELLOW_WHITE      "\033"
#define         COLOR_BLUE_WHITE        "\034"
#define         COLOR_PINK_WHITE        "\035"
#define         COLOR_LGREEN_WHITE      "\036"
#define         COLOR_WHITE_WHITE       "\037"
#define         COLOR_GREY_WHITE        "\038"
#define         TRACE_0                 if(bIsDebugOn) printf
//#endif	/* _AGENTHEADER_H */

