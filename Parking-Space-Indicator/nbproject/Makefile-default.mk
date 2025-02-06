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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/CPEG222_Project3_GPLot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/CPEG222_Project3_GPLot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=acl.c adc.c i2c.c lcd.c led.c rgbled.c ssd.c utils.c mic.c Proj3_Template.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/acl.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/i2c.o ${OBJECTDIR}/lcd.o ${OBJECTDIR}/led.o ${OBJECTDIR}/rgbled.o ${OBJECTDIR}/ssd.o ${OBJECTDIR}/utils.o ${OBJECTDIR}/mic.o ${OBJECTDIR}/Proj3_Template.o
POSSIBLE_DEPFILES=${OBJECTDIR}/acl.o.d ${OBJECTDIR}/adc.o.d ${OBJECTDIR}/i2c.o.d ${OBJECTDIR}/lcd.o.d ${OBJECTDIR}/led.o.d ${OBJECTDIR}/rgbled.o.d ${OBJECTDIR}/ssd.o.d ${OBJECTDIR}/utils.o.d ${OBJECTDIR}/mic.o.d ${OBJECTDIR}/Proj3_Template.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/acl.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/i2c.o ${OBJECTDIR}/lcd.o ${OBJECTDIR}/led.o ${OBJECTDIR}/rgbled.o ${OBJECTDIR}/ssd.o ${OBJECTDIR}/utils.o ${OBJECTDIR}/mic.o ${OBJECTDIR}/Proj3_Template.o

# Source Files
SOURCEFILES=acl.c adc.c i2c.c lcd.c led.c rgbled.c ssd.c utils.c mic.c Proj3_Template.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/CPEG222_Project3_GPLot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX370F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/acl.o: acl.c  .generated_files/flags/default/5c876af99e93fd4d8cd6412f62aae041c63476f9 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/acl.o.d 
	@${RM} ${OBJECTDIR}/acl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/acl.o.d" -o ${OBJECTDIR}/acl.o acl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/adc.o: adc.c  .generated_files/flags/default/85cc74859e8bbfb5210036a34f2e126850c44c4c .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${RM} ${OBJECTDIR}/adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/i2c.o: i2c.c  .generated_files/flags/default/1930bf6730749c9c3d3c7f5c259a754a4451e12f .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c.o.d 
	@${RM} ${OBJECTDIR}/i2c.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/i2c.o.d" -o ${OBJECTDIR}/i2c.o i2c.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/lcd.o: lcd.c  .generated_files/flags/default/b366812c93771b32f8e9bbe2f572d7a6816a474d .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd.o.d 
	@${RM} ${OBJECTDIR}/lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/lcd.o.d" -o ${OBJECTDIR}/lcd.o lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/led.o: led.c  .generated_files/flags/default/633d5628590d4fb3df892b3e90aadbb81df292b4 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/led.o.d 
	@${RM} ${OBJECTDIR}/led.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/led.o.d" -o ${OBJECTDIR}/led.o led.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/rgbled.o: rgbled.c  .generated_files/flags/default/66b77b11265473c31046de3f2a64789d81d4c7da .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/rgbled.o.d 
	@${RM} ${OBJECTDIR}/rgbled.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/rgbled.o.d" -o ${OBJECTDIR}/rgbled.o rgbled.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ssd.o: ssd.c  .generated_files/flags/default/e558f61000fccc23fbb980d31331255234cc6892 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd.o.d 
	@${RM} ${OBJECTDIR}/ssd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/ssd.o.d" -o ${OBJECTDIR}/ssd.o ssd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/utils.o: utils.c  .generated_files/flags/default/6f48130085c1b2a140a1fe4ec00b2cf2374dc74a .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/utils.o.d 
	@${RM} ${OBJECTDIR}/utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/utils.o.d" -o ${OBJECTDIR}/utils.o utils.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mic.o: mic.c  .generated_files/flags/default/6ac39b3cf05da97c4801110b3b10a39dfbcc7253 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mic.o.d 
	@${RM} ${OBJECTDIR}/mic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/mic.o.d" -o ${OBJECTDIR}/mic.o mic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Proj3_Template.o: Proj3_Template.c  .generated_files/flags/default/27f19a4d2b1f402c6de87a48b32d2740b9dbc159 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Proj3_Template.o.d 
	@${RM} ${OBJECTDIR}/Proj3_Template.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Proj3_Template.o.d" -o ${OBJECTDIR}/Proj3_Template.o Proj3_Template.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/acl.o: acl.c  .generated_files/flags/default/2d4ea4366d5fed98d4c5714aec5e63a303acb221 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/acl.o.d 
	@${RM} ${OBJECTDIR}/acl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/acl.o.d" -o ${OBJECTDIR}/acl.o acl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/adc.o: adc.c  .generated_files/flags/default/e3755f3ba7a7d182177d9773b0e469a3035b03cd .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${RM} ${OBJECTDIR}/adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/i2c.o: i2c.c  .generated_files/flags/default/d79c5989fd21a76856541ef99442808374bc4868 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c.o.d 
	@${RM} ${OBJECTDIR}/i2c.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/i2c.o.d" -o ${OBJECTDIR}/i2c.o i2c.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/lcd.o: lcd.c  .generated_files/flags/default/93d3014d45723d7053997e55182040e044782b98 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd.o.d 
	@${RM} ${OBJECTDIR}/lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/lcd.o.d" -o ${OBJECTDIR}/lcd.o lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/led.o: led.c  .generated_files/flags/default/b58e2c9f368f35ff8c1e72470628c99181ae5a49 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/led.o.d 
	@${RM} ${OBJECTDIR}/led.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/led.o.d" -o ${OBJECTDIR}/led.o led.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/rgbled.o: rgbled.c  .generated_files/flags/default/969c812ed34550d0016850e396b18ea087e8f449 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/rgbled.o.d 
	@${RM} ${OBJECTDIR}/rgbled.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/rgbled.o.d" -o ${OBJECTDIR}/rgbled.o rgbled.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ssd.o: ssd.c  .generated_files/flags/default/3ff81c20ff9892534b863e2c8db670b631543e71 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ssd.o.d 
	@${RM} ${OBJECTDIR}/ssd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/ssd.o.d" -o ${OBJECTDIR}/ssd.o ssd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/utils.o: utils.c  .generated_files/flags/default/a63c61ef3fa6caa07d06d64b4cd45bd79e260f42 .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/utils.o.d 
	@${RM} ${OBJECTDIR}/utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/utils.o.d" -o ${OBJECTDIR}/utils.o utils.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mic.o: mic.c  .generated_files/flags/default/1b9751950f949365bdf6f0f9ee826fb8b3fbd80e .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mic.o.d 
	@${RM} ${OBJECTDIR}/mic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/mic.o.d" -o ${OBJECTDIR}/mic.o mic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Proj3_Template.o: Proj3_Template.c  .generated_files/flags/default/c6a4015e0887e8acaa32d919a5cf211453cd0a3f .generated_files/flags/default/b049a9946035c0d6f8c1361b9c30a33141c1b72d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Proj3_Template.o.d 
	@${RM} ${OBJECTDIR}/Proj3_Template.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Proj3_Template.o.d" -o ${OBJECTDIR}/Proj3_Template.o Proj3_Template.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/CPEG222_Project3_GPLot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/CPEG222_Project3_GPLot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC0275F  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/CPEG222_Project3_GPLot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/CPEG222_Project3_GPLot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}/xc32-bin2hex ${DISTDIR}/CPEG222_Project3_GPLot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
