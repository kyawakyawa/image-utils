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

set(EXECUTABLE_TARGETS "")

add_executable(hdr2png ./hdr2png.cc)
list(APPEND EXECUTABLE_TARGETS hdr2png)

foreach(EXECUTABLE_TARGET IN LISTS EXECUTABLE_TARGETS)
    target_compile_features(${EXECUTABLE_TARGET} PRIVATE cxx_std_11)

    set_target_properties(${EXECUTABLE_TARGET} PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

    target_compile_options(${EXECUTABLE_TARGET}
            PRIVATE
            $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic>
            $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
            $<$<CXX_COMPILER_ID:MSVC>:/W4>)

    target_link_libraries(${EXECUTABLE_TARGET} PRIVATE
                          ${PROJECT_NAME} spdlog::spdlog)
endforeach()
