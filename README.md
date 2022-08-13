# EFM Blink project

This repository is my personal project to build a custom build system for EFM MCU family

## Build Steps

Cross-compiling setting is configured by invoking the following cmake command
```
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
```

## Reference
Example gibut repo is [here](https://github.com/cortexm/baremetal)

CMake Referecnce is [here](https://cmake.org/cmake/help/latest/manual/cmake.1.html#introduction-to-cmake-buildsystems)

Adding arm-none-eabi-gcc package to path [here](https://gist.github.com/joegoggins/7763637)

CMake Project Structure is [here](https://github.com/embeddedartistry/cmake-project-skeleton)