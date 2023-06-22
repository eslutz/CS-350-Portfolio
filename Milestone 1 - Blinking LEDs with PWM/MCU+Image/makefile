################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/Development/Code Composer Studio/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main_nortos.obj" \
"./pwmled2.obj" \
"../cc32xxs_nortos.cmd" \
$(GEN_CMDS__FLAG) \
-lti_utils_build_linker.cmd.genlibs \
-l"ti/devices/cc32xx/driverlib/ccs/Release/driverlib.a" \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
Module\ 2\ Milestone.out \

EXE_OUTPUTS__QUOTED += \
"Module 2 Milestone.out" \

CUSTOM_TOOL_OUTPUTS_1521475375 += \
Module\ 2\ Milestone.bin \

CUSTOM_TOOL_OUTPUTS_1521475375__QUOTED += \
"Module 2 Milestone.bin" \

CUSTOM_TOOL_OUTPUTS_345508475 += \
syscfg/Module\ 2\ Milestone.sli \

CUSTOM_TOOL_OUTPUTS_345508475__QUOTED += \
"syscfg/Module 2 Milestone.sli" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Module 2 Milestone.out" secondary-outputs

# Tool invocations
Module\ 2\ Milestone.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"/Applications/Development/Code Composer Studio/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -O3 --define=DeviceFamily_CC3220 --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"Module 2 Milestone.map" -i"/source" -i"/kernel/nortos" -i"/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone/MCU+Image/syscfg" -i"/Applications/Development/Code Composer Studio/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" --diag_suppress=10063 --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Module 2 Milestone_linkInfo.xml" --entry_point=resetISR --rom_model -o "Module 2 Milestone.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Module\ 2\ Milestone.bin: $(EXE_OUTPUTS) Module\ 2\ Milestone.out
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm ObjCopy'
	"/Applications/Development/Code Composer Studio/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armobjcopy" -O binary --only-section .text --only-section .const --only-section .cinit --only-section .resetVecs "Module 2 Milestone.out" "Module 2 Milestone.bin"
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

syscfg/Module\ 2\ Milestone.sli: $(EXE_OUTPUTS) Module\ 2\ Milestone.bin syscfg/ti_drivers_net_wifi_config.json
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Image Creator'
	"/source/ti/drivers/net/imagecreator/bin/SLImageCreator" syscfg create_image --sdk_path "" --json "/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone/MCU+Image/syscfg/ti_drivers_net_wifi_config.json" --file "/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone/MCU+Image/syscfg/Module 2 Milestone.sli" --mcu "/Users/ericslutz/Code/SNHU-Code/CS-350/Module 2 Milestone/MCU+Image/Module 2 Milestone.bin"
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CUSTOM_TOOL_OUTPUTS_345508475__QUOTED)$(CUSTOM_TOOL_OUTPUTS_1521475375__QUOTED)$(GEN_MISC_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main_nortos.obj" "pwmled2.obj" 
	-$(RM) "main_nortos.d" "pwmled2.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(CUSTOM_TOOL_OUTPUTS_1521475375) $(CUSTOM_TOOL_OUTPUTS_345508475)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

