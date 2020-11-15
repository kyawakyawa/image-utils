# Image Utils

## Requirement

- C++ 11 compiler

## Build Example

```
$ git submodule update --init --recursive
$ sh bootstrap.sh
$ cd build
$ make -j
```

## Integration into your CMake Project

```CMake
set(IMAGE_UTILS_BUILD_EXAMPLES OFF CACHE BOOL "Do not build image utils examples")
add_subdirectory(/path/to/image-utils)
```

If your project use ghc filesystem too, please add the following settings

```CMake
set(IMAGE_UTILS_USE_EXTERNAL_GHC_FILESYSTEM ON CACHE BOOL "use external ghc filesystem")
```
