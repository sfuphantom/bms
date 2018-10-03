################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./source/dabort.obj" \
"./source/esm.obj" \
"./source/gio.obj" \
"./source/notification.obj" \
"./source/pinmux.obj" \
"./source/pl455.obj" \
"./source/rti.obj" \
"./source/sci.obj" \
"./source/sys_core.obj" \
"./source/sys_intvecs.obj" \
"./source/sys_main.obj" \
"./source/sys_mpu.obj" \
"./source/sys_pcr.obj" \
"./source/sys_phantom.obj" \
"./source/sys_pmu.obj" \
"./source/sys_selftest.obj" \
"./source/sys_startup.obj" \
"./source/sys_vim.obj" \
"./source/system.obj" \
"../source/sys_link.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir_vars.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
bq76PL455A-Q1\ Example\ Code.out \

EXE_OUTPUTS__QUOTED += \
"bq76PL455A-Q1 Example Code.out" \


# All Target
all: bq76PL455A-Q1\ Example\ Code.out

# Tool invocations
bq76PL455A-Q1\ Example\ Code.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed -z -m"bq76PL455A-Q1 Example Code.map" --heap_size=0x800 --stack_size=0x800 -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --reread_libs --display_error_number --diag_wrap=off --warn_sections --xml_link_info="bq76PL455A-Q1 Example Code_linkInfo.xml" --rom_model --be32 -o "bq76PL455A-Q1 Example Code.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "source\dabort.obj" "source\esm.obj" "source\gio.obj" "source\notification.obj" "source\pinmux.obj" "source\pl455.obj" "source\rti.obj" "source\sci.obj" "source\sys_core.obj" "source\sys_intvecs.obj" "source\sys_main.obj" "source\sys_mpu.obj" "source\sys_pcr.obj" "source\sys_phantom.obj" "source\sys_pmu.obj" "source\sys_selftest.obj" "source\sys_startup.obj" "source\sys_vim.obj" "source\system.obj" 
	-$(RM) "source\esm.d" "source\gio.d" "source\notification.d" "source\pinmux.d" "source\pl455.d" "source\rti.d" "source\sci.d" "source\sys_main.d" "source\sys_pcr.d" "source\sys_phantom.d" "source\sys_selftest.d" "source\sys_startup.d" "source\sys_vim.d" "source\system.d" 
	-$(RM) "source\dabort.d" "source\sys_core.d" "source\sys_intvecs.d" "source\sys_mpu.d" "source\sys_pmu.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

