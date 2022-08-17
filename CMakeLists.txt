cmake_minimum_required(VERSION 3.00)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(EFM-Blink)

set(EXECUTABLE ${PROJECT_NAME}.elf)
# Select linker script
set(LINKER_SCRIPT "src/device/efm32g.ld")
# Select CPU options

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CPU_OPTIONS -mcpu=cortex-m3 -mthumb)
# optimizations (-O0 -O1 -O2 -O3 -Os -Ofast -Og -flto)
set(CMAKE_C_FLAGS_DEBUG "-Og -g3 -gdwarf-2")
set(CMAKE_C_FLAGS_RELEASE "-Os -flto")

#List of source files
set(SRC_FILES 
        src/main.c

        emlib/src/em_cmu.c
        emlib/src/em_gpio.c
        emlib/src/em_system.c

        device/startup_efm32g.c
        device/system_efm32g.c
)

# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

# List of compiler defines, prefix with -D compiler option
target_compile_definitions(${EXECUTABLE} PRIVATE
        -DEFM32G230F64=1
        -DFTX_900=1
        )

# List of includ directories
target_include_directories(${EXECUTABLE} PRIVATE
        src 
        emlib
        device
        )

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