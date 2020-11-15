/*
MIT License

Copyright (c) 2020 kyawakyawa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef IMAGE_IO_H_
#define IMAGE_IO_H_

#include <string>
#include <tuple>
#include <vector>

namespace image_utils {

enum class ConvertOption {
  USE_FILE_EXTENSION,
  FORCE_CONVERT,
  FORCE_NO_CONVERT
};

template <typename T>
std::tuple<std::vector<T>, size_t, size_t, size_t> LoadAndConvertImage(
    const std::string& filename,
    ConvertOption convert_option = ConvertOption::USE_FILE_EXTENSION);

template <typename T>
bool WritePNG(std::vector<T> pixels, const size_t width, const size_t height,
              const size_t channel, const std::string& filename,
              ConvertOption convert_option = ConvertOption::USE_FILE_EXTENSION);

extern template std::tuple<std::vector<float>, size_t, size_t, size_t>
LoadAndConvertImage(const std::string& filename, ConvertOption convert_option);

extern template std::tuple<std::vector<double>, size_t, size_t, size_t>
LoadAndConvertImage(const std::string& filename, ConvertOption convert_option);

extern template bool WritePNG(std::vector<float> pixels, const size_t width,
                              const size_t height, const size_t channel,
                              const std::string& filename,
                              ConvertOption convert_option);

extern template bool WritePNG(std::vector<double> pixels, const size_t width,
                              const size_t height, const size_t channel,
                              const std::string& filename,
                              ConvertOption convert_option);
}  // namespace image_utils

#endif  // IMAGE_IO_H
