#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=mips-openwrt-linux-gcc
CCC=mips-openwrt-linux-g++
CXX=mips-openwrt-linux-g++
FC=gfortran
AS=mips-openwrt-linux-nm

# Macros
CND_PLATFORM=GNU_MIPS32-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/GwsIf.o \
	${OBJECTDIR}/src/GwsInterface.o \
	${OBJECTDIR}/src/OmcMib.o \
	${OBJECTDIR}/src/arn_6h_gws_mib.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/readconf.o \
	${OBJECTDIR}/src/shmem.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=libs/libdes.a libs/libsnmp__.a libs/libagent__.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/omc_agent

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/omc_agent: libs/libdes.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/omc_agent: libs/libsnmp__.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/omc_agent: libs/libagent__.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/omc_agent: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/omc_agent ${OBJECTFILES} ${LDLIBSOPTIONS} -lpthread -lgwsapi

${OBJECTDIR}/src/GwsIf.o: src/GwsIf.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -Iinclude/des -Iinclude/snmp_pp -Iinclude/agent_pp -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GwsIf.o src/GwsIf.cc

${OBJECTDIR}/src/GwsInterface.o: src/GwsInterface.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -Iinclude/des -Iinclude/snmp_pp -Iinclude/agent_pp -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GwsInterface.o src/GwsInterface.cc

${OBJECTDIR}/src/OmcMib.o: src/OmcMib.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -Iinclude/des -Iinclude/snmp_pp -Iinclude/agent_pp -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OmcMib.o src/OmcMib.cc

${OBJECTDIR}/src/arn_6h_gws_mib.o: src/arn_6h_gws_mib.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -Iinclude/des -Iinclude/snmp_pp -Iinclude/agent_pp -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/arn_6h_gws_mib.o src/arn_6h_gws_mib.cc

${OBJECTDIR}/src/main.o: src/main.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -Iinclude/des -Iinclude/snmp_pp -Iinclude/agent_pp -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cc

${OBJECTDIR}/src/readconf.o: src/readconf.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -Iinclude/des -Iinclude/snmp_pp -Iinclude/agent_pp -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/readconf.o src/readconf.cc

${OBJECTDIR}/src/shmem.o: src/shmem.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -Iinclude/des -Iinclude/snmp_pp -Iinclude/agent_pp -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/shmem.o src/shmem.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/omc_agent

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
