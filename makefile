
__file_out := firmware.elf

__as_src   :=
__cc_src   := startup.cpp kmain.cpp

##################################################################################################

__build_dir := build
__objs_dir  := build/objs

__cc_incs   := -I.
__cc_defs   :=

__cm_flags  := --target=thumbv7m-none-eabi
__as_flags  :=
__cc_flags  := -Wall -Werror -Wreturn-type
__cc_flags  += -std=c++17 -Og -fno-exceptions -fno-rtti -fno-unwind-tables -fshort-enums -ffreestanding
__cc_flags  += -ffunction-sections -fdata-sections
__ld_flags  := -nostdlib -nodefaultlibs -Wl,--gc-sections -Tstm32f103c8.ld

__as_util   :=
__cc_util   := clang++
__ld_util   := clang++
__oc_util   := llvm-objcopy
__od_util   := llvm-objdump

__objects   := $(__as_src:%.s=$(__objs_dir)/%.o) $(__cc_src:%.cpp=$(__objs_dir)/%.o)

__file_elf  := $(if $(strip $(__file_out)),$(__build_dir)/$(__file_out))
__file_bin  := $(__file_elf:%$(suffix $(__file_out))=%.bin)
__file_lst  := $(__objects:%=%.lst) $(__file_elf:%=%.lst)

##################################################################################################

.PHONY: help build rebuild clean

print:
	@echo $(__objects)
	@echo $(__file_elf)
	@echo $(__file_bin)
	@echo $(__file_lst)

help:
	@echo ""
	@echo "Использование: make [цель]"
	@echo ""
	@echo "Цели:"
	@echo "    build   - сборка проекта."
	@echo "    rebuild - пересборка проекта."
	@echo "    clean   - очистка директории '$(__build_dir)'."
	@echo "    dumps   - делает дампы объектных файлов."
	@echo "    help    - для вывода этой помощи."
	@echo ""

build:
	@make --no-print-directory __stage_obj
	@make --no-print-directory __stage_ld
	@make --no-print-directory __stage_oc
	@echo "Завершено!"

dumps:
	@make --no-print-directory __stage_od
	@echo "Дампы сделаны!"

clean:
	@echo "Очистка проекта."
	@rm -rf build/*

rebuild: clean build

##################################################################################################

__stage_obj: $(__objects)
	@echo -n ""

__stage_ld: $(__file_elf)
	@echo -n ""

__stage_oc: $(__file_bin)
	@echo -n ""

__stage_od: $(__file_lst)
	@echo -n ""

##################################################################################################

$(__objs_dir)/%.o: %.s
	@echo "[AS] $@ (from: $<)"
	@mkdir -p $(dir $@)
	@$(__as_util) $(__cm_flags) $(__as_flags) -c $< -o $@

$(__objs_dir)/%.o: %.cpp
	@echo "[CC] $@ (from: $<)"
	@mkdir -p $(dir $@)
	@$(__cc_util) $(__cm_flags) $(__cc_flags) $(__cc_defs) $(__cc_incs) -c $< -o $@

$(__file_elf): $(__objects)
	@echo "[LD] $@"
	@$(__ld_util) $(__cm_flags) $(__ld_flags) $? -o $@

$(__file_bin): $(__file_elf)
	@echo "[OC] $@"
	@$(__oc_util) -O binary $< $@

%.lst: %
	@echo "#################################### HEADER ####################################" >  $@
	@$(__od_util) -h $< >> $@
	@echo -e ' ' >> $@
	@echo "################################## DISASSEMBLY #################################" >> $@
	@$(__od_util) -d $< >> $@
	@echo -e ' ' >> $@
	@echo "################################### CONTENTS ###################################" >> $@
	@$(__od_util) -s $< >> $@
	@echo -e ' ' >> $@
	@echo "################################### SYMTABLE ###################################" >> $@
	@$(__od_util) -t $< >> $@
	@echo -e ' ' >> $@
