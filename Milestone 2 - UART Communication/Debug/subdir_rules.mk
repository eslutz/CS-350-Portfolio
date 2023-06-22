################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-1997527009: ../image.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/Development/Code Composer Studio/ccs/utils/sysconfig_1.16.1/sysconfig_cli.sh" --script "/Users/ericslutz/Code/SNHU-Code/CS-350/Module 3 Milestone/image.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/error.h: build-1997527009 ../image.syscfg
syscfg/: build-1997527009

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/Development/Code Composer Studio/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="/Users/ericslutz/Code/SNHU-Code/CS-350/Module 3 Milestone" --include_path="/Users/ericslutz/Code/SNHU-Code/CS-350/Module 3 Milestone/Debug" --include_path="/source" --include_path="/kernel/nortos" --include_path="/kernel/nortos/posix" --include_path="/Applications/Development/Code Composer Studio/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/ericslutz/Code/SNHU-Code/CS-350/Module 3 Milestone/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-744034719: ../uartecho.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/Development/Code Composer Studio/ccs/utils/sysconfig_1.16.1/sysconfig_cli.sh" --script "/Users/ericslutz/Code/SNHU-Code/CS-350/Module 3 Milestone/uartecho.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/error.h: build-744034719 ../uartecho.syscfg
syscfg/: build-744034719


