# EFM Blink project

This repository is my personal project to build a custom build system for EFM MCU family

## Build Steps
Edit Bin util and arm toolchain directory path for the host platform inside cmake/arm-none-eabi.cmake
```
set(ARM_TOOLCHAIN_DIR "path/to/binutil/") # set arm toolchain directory path
set(BINUTILS_PATH ${ARM_TOOLCHAIN_DIR}) # set binary utility directory path
```

Cross-compiling setting is configured by invoking the following cmake command
```
cmake -B build -D CMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
```

## Reference
Example gibut repo is [here](https://github.com/cortexm/baremetal)

CMake Referecnce is [here](https://cmake.org/cmake/help/latest/manual/cmake.1.html#introduction-to-cmake-buildsystems)

Adding arm-none-eabi-gcc package to path [here](https://gist.github.com/joegoggins/7763637)

CMake Project Structure is [here](https://github.com/embeddedartistry/cmake-project-skeleton)