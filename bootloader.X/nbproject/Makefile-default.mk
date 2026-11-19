#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=${DISTDIR}/bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=${DISTDIR}/bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=UserApplication/boot_main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/UserApplication/boot_main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/UserApplication/boot_main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/UserApplication/boot_main.o

# Source Files
SOURCEFILES=UserApplication/boot_main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_CC="C:\Program Files (x86)\PICC\CCSCON.exe"
MP_LD="C:\Program Files (x86)\PICC\CCSCON.exe"
sourceline.device=sourceline="\#device PIC24FJ128GL302"
sourceline.xccompat=sourceline="\#device ANSI" sourceline="\#device PASS_STRINGS=IN_RAM" sourceline="\#device CONST=READ_ONLY" sourceline="\#case" sourceline="\#TYPE SIGNED" sourceline="\#type INT=16, LONG=32"
sourceline.gcccompat=sourceline="\#device ANSI" sourceline="\#device PASS_STRINGS=IN_RAM" sourceline="\#device CONST=READ_ONLY" sourceline="\#case" sourceline="\#TYPE SIGNED"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/UserApplication/boot_main.o: UserApplication/boot_main.c  nbproject/Makefile-${CND_CONF}.mk 
	${MKDIR} ${OBJECTDIR}/UserApplication 
ifeq (2,1) 
	${MKDIR} ${DISTDIR} 
	${MP_CC}  out="${OBJECTDIR}\UserApplication"  UserApplication/boot_main.c +FD +EX +DF +CC #__DEBUG=1 +ICD +Y=9 +EA ${sourceline.device} +DF +LN +T +A +M +J +Z -P #__PIC24FJ128GL302__=1 
	@mv ${OBJECTDIR}/UserApplication/boot_main.cof "${DISTDIR}/bootloader.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/UserApplication/boot_main.hex "${DISTDIR}/bootloader.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\UserApplication"" UserApplication/boot_main.c +EXPORT +FD +EX +DF +CC #__DEBUG=1 +ICD +Y=9 +EA ${sourceline.device} +DF +LN +T +A +M +J +Z -P #__PIC24FJ128GL302__=1 +EXPORTD="${OBJECTDIR}/UserApplication"  
	
endif 
	
else
${OBJECTDIR}/UserApplication/boot_main.o: UserApplication/boot_main.c  nbproject/Makefile-${CND_CONF}.mk 
	${MKDIR} ${OBJECTDIR}/UserApplication 
ifeq (2,1) 
	${MKDIR} ${DISTDIR} 
	${MP_CC}  out="${OBJECTDIR}\UserApplication"  UserApplication/boot_main.c +FD +EX +DF +CC +Y=9 +EA ${sourceline.device} +DF +LN +T +A +M +J +Z -P #__PIC24FJ128GL302__=1 
	@mv ${OBJECTDIR}/UserApplication/boot_main.cof "${DISTDIR}/bootloader.X.${IMAGE_TYPE}.cof" 
	@mv ${OBJECTDIR}/UserApplication/boot_main.hex "${DISTDIR}/bootloader.X.${IMAGE_TYPE}.hex"
else 
	${MP_CC}  out=""${OBJECTDIR}\UserApplication"" UserApplication/boot_main.c +EXPORT +FD +EX +DF +CC +Y=9 +EA ${sourceline.device} +DF +LN +T +A +M +J +Z -P #__PIC24FJ128GL302__=1 +EXPORTD="${OBJECTDIR}/UserApplication"  
	
endif 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	${MKDIR} ${DISTDIR} 
ifeq (2,1) 
	
else 
	${MP_LD}   out="${DISTDIR}"  +FD +EX +DF +CC LINK=bootloader.X.${IMAGE_TYPE}.hex=${OBJECTDIR}/UserApplication/boot_main.o +Y=9 +EA ${sourceline.device} +DF +LN +T +A +M +J +Z -P
	
endif 
	
else
${DISTDIR}/bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	${MKDIR} ${DISTDIR} 
ifeq (2,1) 
	
else 
	${MP_LD}   out="${DISTDIR}"  +FD +EX +DF +CC LINK=bootloader.X.${IMAGE_TYPE}.hex=${OBJECTDIR}/UserApplication/boot_main.o +Y=9 +EA ${sourceline.device} +DF +LN +T +A +M +J +Z -P
	
endif 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
