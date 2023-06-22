################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/ericslutz/code composer studio workspace/Module 5 Milestone" --include_path="C:/Users/ericslutz/code composer studio workspace/Module 5 Milestone/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/kernel/nortos/posix" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/ericslutz/code composer studio workspace/Module 5 Milestone/MCU+Image/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1330704143: ../gpiointerrupt.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1_8_0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_5_20_00_06/.metadata/product.json" --script "C:/Users/ericslutz/code composer studio workspace/Module 5 Milestone/gpiointerrupt.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1330704143 ../gpiointerrupt.syscfg
syscfg/ti_drivers_config.h: build-1330704143
syscfg/ti_utils_build_linker.cmd.genlibs: build-1330704143
syscfg/syscfg_c.rov.xs: build-1330704143
syscfg/ti_utils_runtime_model.gv: build-1330704143
syscfg/ti_utils_runtime_Makefile: build-1330704143
syscfg/: build-1330704143

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/ericslutz/code composer studio workspace/Module 5 Milestone" --include_path="C:/Users/ericslutz/code composer studio workspace/Module 5 Milestone/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/kernel/nortos/posix" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/ericslutz/code composer studio workspace/Module 5 Milestone/MCU+Image/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-415929473: ../image.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1_8_0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_5_20_00_06/.metadata/product.json" --script "C:/Users/ericslutz/code composer studio workspace/Module 5 Milestone/image.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_net_wifi_config.json: build-415929473 ../image.syscfg
syscfg/: build-415929473


