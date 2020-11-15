# MIT License
# 
# Copyright (c) 2020 kyawakyawa
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.13)
project(image-utils LANGUAGES CXX C)

option(IMAGE_UTILS_USE_EXTERNAL_GHC_FILESYSTEM "use external ghc filesystem" OFF)
option(IMAGE_UTILS_BUILD_EXAMPLES "build image utils example" OFF)

#Enable Policy CMP0077
cmake_policy(SET CMP0077 NEW)

# - stb
# - ghc filesystem

# check stb
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/third_party/stb/stb.h")
    message(FATAL_ERROR "stb was not found!"
        "Please execute the command \"git submodule update --init --recursive\"")
endif()

# check ghc filesystem
if (NOT ${IMAGE_UTILS_USE_EXTERNAL_GHC_FILESYSTEM})
  if (NOT EXISTS "${PROJECT_SOURCE_DIR}/third_party/filesystem/CMakeLists.txt")
      message(FATAL_ERROR "ghc filesystem was not found!"
          "Please execute the command \"git submodule update --init --recursive\"")
  endif()


  add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/filesystem)
endif()

# build selection
add_subdirectory(src)

if (${IMAGE_UTILS_BUILD_EXAMPLES})
  # spdlog
  set(SPDLOG_BUILD_SHARED ON CACHE BOOL "Build libspdlog shared library")
  add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/spdlog)

  add_subdirectory(cli)
endif()
