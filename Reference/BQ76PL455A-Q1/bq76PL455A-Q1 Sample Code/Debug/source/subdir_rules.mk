################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/dabort.obj: ../source/dabort.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/dabort.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/esm.obj: ../source/esm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/esm.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/gio.obj: ../source/gio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/gio.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/notification.obj: ../source/notification.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/notification.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/pinmux.obj: ../source/pinmux.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/pinmux.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/pl455.obj: ../source/pl455.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/pl455.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/rti.obj: ../source/rti.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/rti.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sci.obj: ../source/sci.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sci.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_core.obj: ../source/sys_core.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_core.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_intvecs.obj: ../source/sys_intvecs.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_intvecs.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_main.obj: ../source/sys_main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_main.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_mpu.obj: ../source/sys_mpu.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_mpu.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_pcr.obj: ../source/sys_pcr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_pcr.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_phantom.obj: ../source/sys_phantom.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_phantom.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_pmu.obj: ../source/sys_pmu.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_pmu.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_selftest.obj: ../source/sys_selftest.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_selftest.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_startup.obj: ../source/sys_startup.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_startup.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sys_vim.obj: ../source/sys_vim.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/sys_vim.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/system.obj: ../source/system.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --include_path="C:/xcelw/Phantom-BMS/Reference/BQ76PL455A-Q1/bq76PL455A-Q1 Example Code/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="source/system.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


