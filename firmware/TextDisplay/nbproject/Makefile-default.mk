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
FINAL_IMAGE=${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=attiny1614_sr595.c main.c neopixel.c neopixel_anim.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/attiny1614_sr595.o ${OBJECTDIR}/main.o ${OBJECTDIR}/neopixel.o ${OBJECTDIR}/neopixel_anim.o
POSSIBLE_DEPFILES=${OBJECTDIR}/attiny1614_sr595.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/neopixel.o.d ${OBJECTDIR}/neopixel_anim.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/attiny1614_sr595.o ${OBJECTDIR}/main.o ${OBJECTDIR}/neopixel.o ${OBJECTDIR}/neopixel_anim.o

# Source Files
SOURCEFILES=attiny1614_sr595.c main.c neopixel.c neopixel_anim.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATtiny1614
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/attiny1614_sr595.o: attiny1614_sr595.c  .generated_files/flags/default/803cc168f4eec505509e8858be6d6a3651ef7c95 .generated_files/flags/default/bd475ebd6f82757b7e18724870dc1f7d95ee367d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/attiny1614_sr595.o.d 
	@${RM} ${OBJECTDIR}/attiny1614_sr595.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/attiny1614_sr595.o.d" -MT "${OBJECTDIR}/attiny1614_sr595.o.d" -MT ${OBJECTDIR}/attiny1614_sr595.o -o ${OBJECTDIR}/attiny1614_sr595.o attiny1614_sr595.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/a2d0dad73307c8bfcd327ed832b6df63a27cad66 .generated_files/flags/default/bd475ebd6f82757b7e18724870dc1f7d95ee367d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/neopixel.o: neopixel.c  .generated_files/flags/default/895446624735432daac11a614cb2d856696c5803 .generated_files/flags/default/bd475ebd6f82757b7e18724870dc1f7d95ee367d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/neopixel.o.d 
	@${RM} ${OBJECTDIR}/neopixel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/neopixel.o.d" -MT "${OBJECTDIR}/neopixel.o.d" -MT ${OBJECTDIR}/neopixel.o -o ${OBJECTDIR}/neopixel.o neopixel.c 
	
${OBJECTDIR}/neopixel_anim.o: neopixel_anim.c  .generated_files/flags/default/609551fc3e0e7dffd16169b82453d833b0fd4f3c .generated_files/flags/default/bd475ebd6f82757b7e18724870dc1f7d95ee367d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/neopixel_anim.o.d 
	@${RM} ${OBJECTDIR}/neopixel_anim.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/neopixel_anim.o.d" -MT "${OBJECTDIR}/neopixel_anim.o.d" -MT ${OBJECTDIR}/neopixel_anim.o -o ${OBJECTDIR}/neopixel_anim.o neopixel_anim.c 
	
else
${OBJECTDIR}/attiny1614_sr595.o: attiny1614_sr595.c  .generated_files/flags/default/a49e0de78e92794b549ae37981c3d4bb64a39ec6 .generated_files/flags/default/bd475ebd6f82757b7e18724870dc1f7d95ee367d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/attiny1614_sr595.o.d 
	@${RM} ${OBJECTDIR}/attiny1614_sr595.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/attiny1614_sr595.o.d" -MT "${OBJECTDIR}/attiny1614_sr595.o.d" -MT ${OBJECTDIR}/attiny1614_sr595.o -o ${OBJECTDIR}/attiny1614_sr595.o attiny1614_sr595.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/94252e5479b3707a0eebcabf25364d7569a835b9 .generated_files/flags/default/bd475ebd6f82757b7e18724870dc1f7d95ee367d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/neopixel.o: neopixel.c  .generated_files/flags/default/84d7091c183c19c895c426091941e28680e89aaf .generated_files/flags/default/bd475ebd6f82757b7e18724870dc1f7d95ee367d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/neopixel.o.d 
	@${RM} ${OBJECTDIR}/neopixel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/neopixel.o.d" -MT "${OBJECTDIR}/neopixel.o.d" -MT ${OBJECTDIR}/neopixel.o -o ${OBJECTDIR}/neopixel.o neopixel.c 
	
${OBJECTDIR}/neopixel_anim.o: neopixel_anim.c  .generated_files/flags/default/a5a10f8e17b77e4be44ab0b80efeeee0d6ae127b .generated_files/flags/default/bd475ebd6f82757b7e18724870dc1f7d95ee367d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/neopixel_anim.o.d 
	@${RM} ${OBJECTDIR}/neopixel_anim.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/neopixel_anim.o.d" -MT "${OBJECTDIR}/neopixel_anim.o.d" -MT ${OBJECTDIR}/neopixel_anim.o -o ${OBJECTDIR}/neopixel_anim.o neopixel_anim.c 
	
endif

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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/TextDisplay.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1     -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/TextDisplay.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/TextDisplay.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "${DISTDIR}/TextDisplay.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/TextDisplay.${IMAGE_TYPE}.hex"
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
