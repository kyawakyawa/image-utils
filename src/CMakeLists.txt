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

add_library(${PROJECT_NAME} SHARED ./image-utils.cc
                                   ./stb_image.cc
                                   ./stb_image_write.cc)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} SYSTEM  PRIVATE
                           ${PROJECT_SOURCE_DIR}/third_party/stb/)

target_link_libraries(${PROJECT_NAME} PRIVATE ghc_filesystem)

set_source_files_properties(./image-utils.cc PROPERTIES
  COMPILE_FLAGS 
  "$<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4>"
)

target_compile_features(${PROJECT_NAME}
        PRIVATE cxx_std_11)
