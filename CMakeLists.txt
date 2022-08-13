cmake_minimum_required(VERSION 3.00)

project(EFM-Blink)

# Select linker script
set(LINKER_SCRIPT "src/device/efm32g.ld")
# Select CPU options
set(CPU_OPTIONS -mcpu=cortex-m3 -mthumb)
# optimizations (-O0 -O1 -O2 -O3 -Os -Ofast -Og -flto)
set(CMAKE_C_FLAGS_DEBUG "-Og -g3 -gdwarf-2")
set(CMAKE_C_FLAGS_RELEASE "-Os -flto")

add_compile_options(
    ${CPU_OPTIONS}
    $<$<COMPILE_LANGUAGE:C>:-std=c99>

    -O0
    -Wall
    -Wextra
    -c
    -fmessage-length=0
    -mno-sched-prolog
    -fno-builtin
    -ffunction-sections
    -fdata-sections
)