/*_############################################################################
  _## 
  _##  agent.cpp  
  _## 
  _##
  _##  AGENT++ API Version 3.5.29
  _##  -----------------------------------------------
  _##  Copyright (C) 2000-2007 Frank Fock, Jochen Katz
  _##  
  _##  LICENSE AGREEMENT
  _##
  _##  WHEREAS,  Frank  Fock  and  Jochen  Katz  are  the  owners of valuable
  _##  intellectual  property rights relating to  the AGENT++ API and wish to
  _##  license AGENT++ subject to the  terms and conditions set forth  below;
  _##  and
  _##
  _##  WHEREAS, you ("Licensee") acknowledge  that Frank Fock and Jochen Katz
  _##  have the right  to grant licenses  to the intellectual property rights
  _##  relating to  AGENT++, and that you desire  to obtain a license  to use
  _##  AGENT++ subject to the terms and conditions set forth below;
  _##
  _##  Frank  Fock    and Jochen   Katz   grants  Licensee  a  non-exclusive,
  _##  non-transferable, royalty-free  license  to use   AGENT++ and  related
  _##  materials without  charge provided the Licensee  adheres to all of the
  _##  terms and conditions of this Agreement.
  _##
  _##  By downloading, using, or  copying  AGENT++  or any  portion  thereof,
  _##  Licensee  agrees to abide  by  the intellectual property  laws and all
  _##  other   applicable laws  of  Germany,  and  to all of   the  terms and
  _##  conditions  of this Agreement, and agrees  to take all necessary steps
  _##  to  ensure that the  terms and  conditions of  this Agreement are  not
  _##  violated  by any person  or entity under the  Licensee's control or in
  _##  the Licensee's service.
  _##
  _##  Licensee shall maintain  the  copyright and trademark  notices  on the
  _##  materials  within or otherwise  related   to AGENT++, and  not  alter,
  _##  erase, deface or overprint any such notice.
  _##
  _##  Except  as specifically   provided in  this  Agreement,   Licensee  is
  _##  expressly   prohibited  from  copying,   merging,  selling,   leasing,
  _##  assigning,  or  transferring  in  any manner,  AGENT++ or  any portion
  _##  thereof.
  _##
  _##  Licensee may copy materials   within or otherwise related   to AGENT++
  _##  that bear the author's copyright only  as required for backup purposes
  _##  or for use solely by the Licensee.
  _##
  _##  Licensee may  not distribute  in any  form  of electronic  or  printed
  _##  communication the  materials  within or  otherwise  related to AGENT++
  _##  that  bear the author's  copyright, including  but  not limited to the
  _##  source   code, documentation,  help  files, examples,  and benchmarks,
  _##  without prior written consent from the authors.  Send any requests for
  _##  limited distribution rights to fock@agentpp.com.
  _##
  _##  Licensee  hereby  grants  a  royalty-free  license  to  any  and   all 
  _##  derivatives  based  upon this software  code base,  that  may  be used
  _##  as a SNMP  agent development  environment or a  SNMP agent development 
  _##  tool.
  _##
  _##  Licensee may  modify  the sources  of AGENT++ for  the Licensee's  own
  _##  purposes.  Thus, Licensee  may  not  distribute  modified  sources  of
  _##  AGENT++ without prior written consent from the authors. 
  _##
  _##  The Licensee may distribute  binaries derived from or contained within
  _##  AGENT++ provided that:
  _##
  _##  1) The Binaries are  not integrated,  bundled,  combined, or otherwise
  _##     associated with a SNMP agent development environment or  SNMP agent
  _##     development tool; and
  _##
  _##  2) The Binaries are not a documented part of any distribution material. 
  _##
  _##
  _##  THIS  SOFTWARE  IS  PROVIDED ``AS  IS''  AND  ANY  EXPRESS OR  IMPLIED
  _##  WARRANTIES, INCLUDING, BUT NOT LIMITED  TO, THE IMPLIED WARRANTIES  OF
  _##  MERCHANTABILITY AND FITNESS FOR  A PARTICULAR PURPOSE  ARE DISCLAIMED.
  _##  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  _##  INDIRECT,   INCIDENTAL,  SPECIAL, EXEMPLARY,  OR CONSEQUENTIAL DAMAGES
  _##  (INCLUDING,  BUT NOT LIMITED  TO,  PROCUREMENT OF SUBSTITUTE  GOODS OR
  _##  SERVICES; LOSS OF  USE,  DATA, OR PROFITS; OR  BUSINESS  INTERRUPTION)
  _##  HOWEVER CAUSED  AND ON ANY THEORY  OF  LIABILITY, WHETHER IN CONTRACT,
  _##  STRICT LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
  _##  IN  ANY WAY OUT OF  THE USE OF THIS  SOFTWARE,  EVEN IF ADVISED OF THE
  _##  POSSIBILITY OF SUCH DAMAGE. 
  _##
  _##
  _##  Stuttgart, Germany, Sun Nov 11 15:11:32 CET 2007 
  _##  
  _##########################################################################*/


#include <stdlib.h>
#include <signal.h>
#include <snmp_pp/oid_def.h>
#include <semaphore.h>
#include <fcntl.h>

#include "OmcMib.h"
#include "error_agent.h"
#include "readconf.h"
#include "../../../package/gwsapi.h"

// table size policies


// globals:

static  bool        bRunning = false;
static  RequestList reqList;

static void sig(int signo) {
    if ((signo == SIGTERM) || (signo == SIGINT) || (signo == SIGSEGV)) {
        printf("\n");
        switch (signo) {
            case SIGSEGV:
            {
                //printf("Segmentation fault, aborting.\n");
                exit(1);
            }
            case SIGTERM:
            case SIGINT:
            {
                if (bRunning) {
                    bRunning = false;
                    printf("User abort\n");
                }
            }
        }
    }
}


static void init_signals()
{
    signal (SIGTERM, sig);
    signal (SIGINT, sig);
    signal (SIGSEGV, sig);
}	

#define OMC_AGENT_VERSION       "version 1.20-4"
#define DEFAULT_SNMP_PORT       161
#define PATH_CONF_AGENT         "/etc/config/omcagent.conf"
#define CMD_SERVER_PORT         "-port"
#define CMD_SERVER_START        "-start"
#define CMD_SERVER_STOP         "-stop"
#define CMD_SERVER_LOG          "-tracelog"
#define CMD_SERVER_ECHO         "-echo"
#define CMD_SET_COMMUNITY_READ  "-set_pass_read"
#define CMD_SET_COMMUNITY_WRITE "-set_pass_write"
#define CMD_SET_COMMUNITY_TRAP  "-set_pass_trap"
#define CMD_GET_COMMUNITY_READ  "-read_community"
#define CMD_GET_COMMUNITY_WRITE "-write_community"
#define CMD_GET_COMMUNITY_TRAP  "-trap_community"
#define CMD_GET_VERSION         "-version"

#define OPTION_COMMUNITY_READ   "CommRead"
#define OPTION_COMMUNITY_WRITE  "CommWrite"
#define OPTION_COMMUNITY_TRAP   "CommNotify"
#define MAX_CODE    64
#define START_DIGI  0x41        //'A'
#define START_CHAR  0x61        //'a'
#define C_ENCRYPT   true
#define C_DECRYPT   false

static char* community_coding(bool encrypt, char* community) {
    static const char salt_codes[MAX_CODE] = {
        0xf3, 0x27, 0xac, 0xf3, 0xdd, 0x28, 0xfb, 0x18,
        0x4f, 0x10, 0x78, 0x8b, 0x36, 0x66, 0xab, 0xce,
        0xbe, 0x53, 0x36, 0xf7, 0xba, 0x0b, 0xbf, 0x6f,
        0xbf, 0xba, 0x0b, 0xe3, 0x30, 0xf2, 0x42, 0x41,
        0x5f, 0x1c, 0x4a, 0x37, 0x90, 0xb8, 0x25, 0x37,
        0xde, 0xce, 0xf9, 0xb9, 0x4a, 0x6f, 0x30, 0x78,
        0xa4, 0x15, 0x84, 0xfd, 0xc6, 0xef, 0xbb, 0xca,
        0xa2, 0xb3, 0x40, 0x6f, 0x4c, 0xbf, 0x3e, 0x64,
    };
    static char output[MAX_CODE+1];
    char input[MAX_CODE+1];
    int i, k;
    
    memset (input, 0x00, MAX_CODE + 1);
    memset (output, 0x00, MAX_CODE + 1);
    if (community) {
        strncpy(input, community, encrypt ? MAX_CODE / 2 : MAX_CODE);
        int len = strlen(input);
        if (encrypt) {  //coding
            for (k = 0, i = 0; i < len; i ++) {
                unsigned char key = input[i] ^ salt_codes[i];
                output[k] = START_DIGI + (0x0f & (key >> 4));
                output[k+1] = START_CHAR + (0x0f & key);
                k += 2;
            }
        } else { //decoding
            for (k = 0, i = 0; k < len; k += 2) {
                unsigned char hi = (input[k] - START_DIGI) << 4;
                unsigned char lo = (input[k+1] - START_CHAR) & 0x0f;
                output[i] = (hi | lo) ^ salt_codes[i];
                i ++;
            }
        }
    }
    return output;
}

static bool svrTestInstance(sem_t* sem) {
    if (sem && 0 == sem_trywait(sem)) {
        sem_post(sem);
        return false;   //unlocked, means we can exit
    } else {
        return true;    //locked, we must continue our work
    }
}

static int print_help() {
    printf("\nUssage:   omc_agent [-parameter value] ...\n");
    printf(" parameters :\n"
//            " " CMD_GET_COMMUNITY_READ     "            #show current 'SNMP_GET' password\n"
//            " " CMD_GET_COMMUNITY_WRITE    "           #show current 'SNMP_SET' password\n"
            " " CMD_SET_COMMUNITY_READ     " password   #modify password for 'SNMP_GET'\n"
            " " CMD_SET_COMMUNITY_WRITE    " password  #modify password for 'SNMP_SET'\n"
            " " CMD_SERVER_PORT "                     #specify the SNMP server port, default is 161\n"
            " " CMD_SERVER_START "                    #start GWS SNMP agent process\n"
            "  e.g.\n"
            "\t# omc_agent " CMD_SET_COMMUNITY_WRITE " abc123\n"
            "\t# omc_agent -port 1060 -start\n"
            "\t# omc_agent -start &\n\n"
            );
    return 0;
}

#define SEM_NAME_OMC_SNMP_AGENT  "SEM_NAME_OMC_SNMP_AGENT"
static sem_t* svrInitInstance() {
    static sem_t* semInstance = sem_open(SEM_NAME_OMC_SNMP_AGENT,O_CREAT|O_RDWR,00777,1);
    if (SEM_FAILED == semInstance) {   //errno == EEXIST
        printf("\nFailed on initializing instance.\n\n");
        return SEM_FAILED;
    } else {
        if (0 == sem_trywait(semInstance)) return semInstance;
        else {
            printf("\nAn other omc_agent is running.\n\n");
            return SEM_FAILED;
        }
    }
}

static void ShutdownInstance() {
    sem_t*  sem = sem_open(SEM_NAME_OMC_SNMP_AGENT,O_RDWR,00777,1);
    if (SEM_FAILED != sem) {
        sem_post(sem);
        sem_unlink(SEM_NAME_OMC_SNMP_AGENT);
        sem_close(sem);
    }
}

int main (int argc, char* argv[])
{
    u_short port = DEFAULT_SNMP_PORT;
    bool    bLog = false;
    char    community[64];



    memset(community, 0x00, 64);
    for (int c = 1; c < argc; c ++) {
        if (0 == strcmp(argv[c],CMD_SERVER_LOG)) { bLog = bIsDebugOn = true; }
        else if (0 == strcmp(argv[c],CMD_SERVER_ECHO)) COmcMib::m_bEchoOff = false;
        else if (0 == strcmp(argv[c],CMD_SET_COMMUNITY_READ)) {
            if (c+1 < argc) {
                return write_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_READ,community_coding(C_ENCRYPT,argv[c+1]));
            } else return print_help();
        } else if (0 == strcmp(argv[c],CMD_SET_COMMUNITY_TRAP)) {
            if (c+1 < argc) {
                return write_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_TRAP,community_coding(C_ENCRYPT,argv[c+1]));
            } else return print_help();
        } else if (0 == strcmp(argv[c],CMD_SET_COMMUNITY_WRITE)) {
            if (c+1 < argc) {
                return write_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_WRITE,community_coding(C_ENCRYPT,argv[c+1]));
            } else return print_help();
        } else if (0 == strcmp(argv[c],CMD_SERVER_PORT)) {
            if (c+1 < argc) {
                port = atoi(argv[c+1]);
            } else port = DEFAULT_SNMP_PORT;
        } else if (0 == strcmp(argv[c],CMD_GET_COMMUNITY_READ)) {
            if (0 == read_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_READ,community))
                printf("\n%s\n",community_coding(C_DECRYPT,community));
            return 0;
        } else if (0 == strcmp(argv[c],CMD_GET_COMMUNITY_TRAP)) {
            if (0 == read_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_TRAP,community))
                printf("\n%s\n",community_coding(C_DECRYPT,community));
            return 0;
        } else if (0 == strcmp(argv[c],CMD_GET_COMMUNITY_WRITE)) {
            if (0 == read_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_WRITE,community))
                printf("\n%s\n",community_coding(C_DECRYPT,community));
            return 0;
        } else if (0 == strcmp(argv[c],CMD_GET_VERSION)) {
            printf("\n%s [%s %s-build]\n",OMC_AGENT_VERSION,__DATE__,__TIME__);
            return 0;
        } else if (0 == strcmp(argv[c],CMD_SERVER_START)) {
            bRunning = true;
        } else if (0 == strcmp(argv[c],CMD_SERVER_STOP)) {
            ShutdownInstance();
            return 0;
        } else {
            printf("\nUnknown parameter : %s\n",argv[c]);
            return print_help();
        }
    }
    if (!bRunning) return print_help();

#ifdef _NO_LOGGING
    DefaultLog::log()->set_filter(ERROR_LOG, 0);
    DefaultLog::log()->set_filter(WARNING_LOG, 0);
    DefaultLog::log()->set_filter(EVENT_LOG, 0);
    DefaultLog::log()->set_filter(INFO_LOG, 0);
    DefaultLog::log()->set_filter(DEBUG_LOG, 0);
#else
    if (bLog) {
        DefaultLog::log()->set_filter(ERROR_LOG, 5);
        DefaultLog::log()->set_filter(WARNING_LOG, 5);
        DefaultLog::log()->set_filter(EVENT_LOG, 5);
        DefaultLog::log()->set_filter(INFO_LOG, 5);
        DefaultLog::log()->set_filter(DEBUG_LOG, 8);
    } else {
        DefaultLog::log()->set_filter(ERROR_LOG, 0);
        DefaultLog::log()->set_filter(WARNING_LOG, 0);
        DefaultLog::log()->set_filter(EVENT_LOG, 0);
        DefaultLog::log()->set_filter(INFO_LOG, 0);
        DefaultLog::log()->set_filter(DEBUG_LOG, 0);
    }
#endif
	int status;
	Snmp::socket_startup();  // Initialize socket subsystem
#ifdef SNMP_PP_WITH_UDPADDR
	// bind localhost only -> agent will not be reachable from
	// outside
	// UdpAddress inaddr("127.0.0.1");
	UdpAddress inaddr("0.0.0.0");
	inaddr.set_port(port);
	Snmpx snmp(status, inaddr);
#else
	// bind on any address on local host
	Snmpx snmp(status, port);
#endif


	if (status == SNMP_CLASS_SUCCESS) {

		LOG_BEGIN(EVENT_LOG | 1);
		LOG("main: SNMP listen port");
		LOG(port);
		LOG_END;
	}
	else {
		LOG_BEGIN(ERROR_LOG | 0);
		LOG("main: SNMP port init failed");
		LOG(status);
		LOG(Snmp::error_msg(status));
		LOG_END;
		exit(1);
	}
        
//    sem_t*  semInstance = svrInitInstance();
//    if (SEM_FAILED != semInstance) {
        char*           trapCommunity = NULL;
        int             error_code = SUCCESS_OK;
        COmcMib*        pMib = new COmcMib();
        COmcMib&        omcMib = *pMib;
	// register requestList for outgoing requests
	omcMib.set_request_list(&reqList);
	init_signals();

        if (0 == read_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_READ,community)) {
            reqList.set_read_community(community_coding(false, community));
        }
        if (0 == read_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_WRITE,community)) {
            reqList.set_write_community(community_coding(false, community));
        }
        if (0 == read_cfg(PATH_CONF_AGENT,OPTION_COMMUNITY_TRAP,community)) {
            trapCommunity = community_coding(false, community);
        }
	// add supported objects
	if( (error_code = omcMib.m_Init(trapCommunity)) < SUCCESS_OK ) {
            printf("\nError and Exit,Code = %d",error_code);
            omcMib.m_Exit();
            delete &omcMib;
            return error_code;
        }

	reqList.set_snmp(&snmp);

	while (bRunning) {
            Request* req = reqList.receive(2);
            if (req) {
                omcMib.m_ProcessRequest(req);
            } else {
                omcMib.cleanup();
            }
            omcMib.m_ProcessMibSync();
	}
	Snmp::socket_cleanup();  // Shut down socket subsystem
        omcMib.m_Exit();
        sleep(2);
	delete pMib;
        
        return 0;
}
