# A toolchain file specifying information about the compiler and utility paths for cross-compilation
# This script file is invoked with cmake -DCMAKE_TOOLCHAIN_FILE=path/to/file

#################
# System Config #
#################
set(CMAKE_SYSTEM_NAME Generic) # Name of the operating system for which CMake to build
set(CMAKE_SYSTEM_PROCESSOR arm) # Name of the system processor

####################
# Toolchain Config #
####################
set(CMAKE_C_COMPILER    arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER  arm-none-eabi-g++)
set(AS                  arm-none-eabi-as)
set(CMAKE_AR            arm-none-eabi-gcc-ar)
set(OBJCOPY             arm-none-eabi-objcopy)
set(OBJDUMP             arm-none-eabi-objdump)
set(SIZE                arm-none-eabi-size)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)