################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-640842129: ../image.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/Development/Code Composer Studio/ccs/utils/sysconfig_1.16.1/sysconfig_cli.sh" --script "/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone/image.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/error.h: build-640842129 ../image.syscfg
syscfg/: build-640842129

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/Development/Code Composer Studio/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -O3 --include_path="/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone" --include_path="/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone/MCU+Image" --include_path="/source" --include_path="/kernel/nortos" --include_path="/kernel/nortos/posix" --include_path="/Applications/Development/Code Composer Studio/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=DeviceFamily_CC3220 --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone/MCU+Image/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-350433679: ../pwmled2.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/Development/Code Composer Studio/ccs/utils/sysconfig_1.16.1/sysconfig_cli.sh" --script "/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone/pwmled2.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/error.h: build-350433679 ../pwmled2.syscfg
syscfg/: build-350433679


