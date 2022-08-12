cmake_minimum_required(VERSION 3.00)

project(EFM-Blink)

# Select linker script
set(LINKER_SCRIPT "device/efm32g.ld")
# Select CPU options
set(CPU_OPTIONS -mcpu=cortex-m3 -mthumb)
# optimizations (-O0 -O1 -O2 -O3 -Os -Ofast -Og -flto)
set(CMAKE_C_FLAGS_DEBUG "-Og -g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-Os -flto")

add_compile_options(
    ${CPU_OPTIONS}
    $<$<COMPILE_LANG>>
)