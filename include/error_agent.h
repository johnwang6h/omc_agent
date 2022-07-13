/* 
 * File:   error_agent.h
 * Author: wyy


 */
#ifndef _ERROR_AGENT_H
#define	_ERROR_AGENT_H

#include <errno.h>

extern const char* szErrorMessage[125];

#define SNMP_AGENT_TIMEOUT_SECOND   25

#define SUCCESS_OK                      0
#define ERROR_INVALIDATE_MIB            -10000
#define ERROR_AGENT_ADD_MIB_ENTRY       -10001
#define ERROR_AGENT_MIB_INIT            -10002
#define ERROR_AGENT_MIB_OPEN_DB         -10003
#define ERROR_AGENT_CONNECT_SHMEM       -10004
#define ERROR_AGENT_CONNECT_MEG_Q       -10005

#define ERROR_MAIN_BOARD_INIT_FAIL  -10007

#define DATABASE_NAME_SCADA         "/mnt/sd/realtime"
#define DATABASE_NAME_HISTORY       "/mnt/sd/history"
#define DATABASE_NAME_TEMPLATE      "/mnt/sd/intelligent"
#define DRIVER_NAME_WATCHDOG        "/dev/watchdog"

#define MAX_OF(x,y)                 ((x>y) ? x:y)
#define MIN_OF(x,y)                 ((x<y) ? x:y)
#define END_OF_MAX                  -65535
#define END_OF_MIN                  65535

#define CFG_TAB_COL_CONFIG_INDEX    0
#define CFG_TAB_COL_TRAP_MANAGER    1
#define CFG_TAB_COL_TRAP_COMMUNITY  2
#define CFG_TAB_COL_READ_COMMUNITY  3
#define CFG_TAB_COL_WRITE_COMMUNITY 4
#define CFG_TAB_COL_TRAP_VERSION    5
#define CFG_TAB_COL_SNMP_TIME_OUT   6
#define CFG_TAB_COL_COM_PORT        7
#define CFG_TAB_COL_COM_BAUD        8
#define CFG_TAB_COL_COM_TIME_OUT    9
#define CFG_TAB_COL_COM_PERIORD     10

#define CFG_TAB_COL_MBS_GROUP_INDEX                     0
#define CFG_TAB_COL_MBS_DEVICE_TYPE                     1
#define CFG_TAB_COL_MBS_DIO_SECTION_1_REG_BASE		2
#define CFG_TAB_COL_MBS_DIO_SECTION_1_REG_COUNT		3
#define CFG_TAB_COL_MBS_DIO_SECTION_1_WRITABLE		4
#define CFG_TAB_COL_MBS_DIO_SECTION_2_REG_BASE		5
#define CFG_TAB_COL_MBS_DIO_SECTION_2_REG_COUNT		6
#define CFG_TAB_COL_MBS_DIO_SECTION_2_WRITABLE		7
#define CFG_TAB_COL_MBS_DIO_SECTION_3_REG_BASE		8
#define CFG_TAB_COL_MBS_DIO_SECTION_3_REG_COUNT		9
#define CFG_TAB_COL_MBS_DIO_SECTION_3_WRITABLE		10
#define CFG_TAB_COL_MBS_DIO_SECTION_4_REG_BASE		11
#define CFG_TAB_COL_MBS_DIO_SECTION_4_REG_COUNT		12
#define CFG_TAB_COL_MBS_DIO_SECTION_4_WRITABLE		13
#define CFG_TAB_COL_MBS_AIO_SECTION_1_REG_BASE		14
#define CFG_TAB_COL_MBS_AIO_SECTION_1_REG_COUNT		15
#define CFG_TAB_COL_MBS_AIO_SECTION_1_WRITABLE		16
#define CFG_TAB_COL_MBS_AIO_SECTION_2_REG_BASE		17
#define CFG_TAB_COL_MBS_AIO_SECTION_2_REG_COUNT		18
#define CFG_TAB_COL_MBS_AIO_SECTION_2_WRITABLE		19
#define CFG_TAB_COL_MBS_AIO_SECTION_3_REG_BASE		20
#define CFG_TAB_COL_MBS_AIO_SECTION_3_REG_COUNT		21
#define CFG_TAB_COL_MBS_AIO_SECTION_3_WRITABLE		22
#define CFG_TAB_COL_MBS_AIO_SECTION_4_REG_BASE		23
#define CFG_TAB_COL_MBS_AIO_SECTION_4_REG_COUNT		24
#define CFG_TAB_COL_MBS_AIO_SECTION_4_WRITABLE		25

#define MIB_TAB_COL_INSTANCE        -1
#define MIB_TAB_COL_ALARM_TITLE     0
#define MIB_TAB_COL_ALARM_STATE     1
#define MIB_TAB_COL_ALARM_DESCR     2
#define MIB_TAB_COL_ALARM_LEVEL     3
#define MIB_TAB_COL_ALARM_TRIGER    4
#define MIB_TAB_COL_ALARM_ENABLE    5

#define MIB_TAB_COL_STATUS_TITLE    0
#define MIB_TAB_COL_STATUS_STATE    1
#define MIB_TAB_COL_STATUS_CUR_STA  2
#define MIB_TAB_COL_STATUS_TRUE     3
#define MIB_TAB_COL_STATUS_FALSE    4
#define MIB_TAB_COL_STATUS_TRIGER   5
#define MIB_TAB_COL_STATUS_ENABLE   6

#define MIB_TAB_COL_ANALOG_TITLE    0
#define MIB_TAB_COL_ANALOG_VALUE    1
#define MIB_TAB_COL_ANALOG_FORMU    2
#define MIB_TAB_COL_ANALOG_FORMD    3
#define MIB_TAB_COL_ANALOG_UNIT     4
#define MIB_TAB_COL_ANALOG_THRHH    5
#define MIB_TAB_COL_ANALOG_THRH     6
#define MIB_TAB_COL_ANALOG_THRL     7
#define MIB_TAB_COL_ANALOG_THRLL    8
#define MIB_TAB_COL_ANALOG_ENABLE   9

#define MIB_TAB_COL_CONTROL_TITLE   0
#define MIB_TAB_COL_CONTROL_STATE   1
#define MIB_TAB_COL_CONTROL_CUR_STA 2
#define MIB_TAB_COL_CONTROL_TRUE    3
#define MIB_TAB_COL_CONTROL_FALSE   4
#define MIB_TAB_COL_CONTROL_ENABLE  5

#define MIB_TAB_COL_DEVICE_TITLE    0
#define MIB_TAB_COL_DEVICE_PARAM    1
#define MIB_TAB_COL_DEVICE_DESCR    2
#define MIB_TAB_COL_DEVICE_ENABLE   3

#endif	/* _ERROR_AGENT_H */
