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

#include "image-utils.h"

#include <math.h>

#include <algorithm>
#include <iostream>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#if defined(__cplusplus) && __cplusplus >= 201703L && defined(__has_include)
#if __has_include(<filesystem>)
#define GHC_USE_STD_FS
#include <filesystem>
namespace fs = std::filesystem;
#endif
#endif
#ifndef GHC_USE_STD_FS
#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;
#endif

#include "stb_image.h"
#include "stb_image_write.h"

#ifdef __clang__
#pragma clang diagnostic pop
#endif

namespace image_utils {

template <typename T>
static T sRGBToLiner(const T c_srgb) {
  T c_liner;
  if (c_srgb <= static_cast<T>(0.04045)) {
    c_liner = c_srgb / static_cast<T>(12.92);
  } else {
    const T a = static_cast<T>(0.055);
    c_liner =
        std::pow((c_srgb + a) / (static_cast<T>(1.0) + a), static_cast<T>(2.4));
  }

  return c_liner;
}

template <typename T>
static T LinerTosRGB(const T c_liner) {
  T c_srgb;
  if (c_liner <= static_cast<T>(0.0031308)) {
    c_srgb = static_cast<T>(12.92) * c_liner;
  } else {
    const T a = static_cast<T>(0.055);
    c_srgb    = std::pow((static_cast<T>(1.0) + a) * c_liner,
                      static_cast<T>(1.0 / 2.4)) -
             a;
  }

  return c_srgb;
}

template <typename T>
static std::tuple<std::vector<T>, size_t, size_t, size_t> LoadImage(
    const std::string& filename) {
  // TODO : EXR file
  int tmp_w = 0;
  int tmp_h = 0;
  int tmp_c = 0;

  float* pixelf = stbi_loadf(filename.c_str(), &tmp_w, &tmp_h, &tmp_c, 0);

  const size_t width   = (pixelf != nullptr) ? static_cast<size_t>(tmp_w) : 0;
  const size_t height  = (pixelf != nullptr) ? static_cast<size_t>(tmp_h) : 0;
  const size_t channel = (pixelf != nullptr) ? static_cast<size_t>(tmp_c) : 0;

  std::vector<T> ret(width * height * channel);

  for (size_t i = 0; i < width * height * channel; i++) {
    ret[i] = static_cast<T>(pixelf[i]);
  }

  stbi_image_free(pixelf);

  return std::make_tuple(ret, width, height, channel);
}

template <typename T>
std::tuple<std::vector<T>, size_t, size_t, size_t> LoadAndConvertImage(
    const std::string& filename, ConvertOption convert_option) {
  auto ret = LoadImage<T>(filename);

  std::vector<T>& pixels = std::get<0>(ret);
  const size_t width     = std::get<1>(ret);
  const size_t height    = std::get<2>(ret);
  const size_t channel   = std::get<3>(ret);

  const fs::path filepath = filename;

  const std::string file_extension = filepath.extension();

  const bool is_hdr = (file_extension == ".hdr" || file_extension == ".HDR" ||
                       file_extension == ".exr" || file_extension == ".EXR");

  if (convert_option != ConvertOption::FORCE_NO_CONVERT &&
      (!is_hdr || convert_option == ConvertOption::FORCE_CONVERT)) {
    std::cerr << "Start sRGBToLiner" << std::endl;
    for (size_t i = 0; i < width * height; i++) {
      for (size_t c = 0; c < std::min<size_t>(channel, 3); c++) {
        pixels[i * channel + c] = sRGBToLiner(pixels[i * channel + c]);
      }
    }
    std::cerr << "End sRGBToLiner" << std::endl;
  }

  return ret;
}

template std::tuple<std::vector<float>, size_t, size_t, size_t>
LoadAndConvertImage(const std::string& filename, ConvertOption convert_option);

template std::tuple<std::vector<double>, size_t, size_t, size_t>
LoadAndConvertImage(const std::string& filename, ConvertOption convert_option);

template <typename T>
bool WritePNG(std::vector<T> pixels, const size_t width, const size_t height,
              const size_t channel, const std::string& filename,
              ConvertOption convert_option) {
  const fs::path filepath          = filename;
  const std::string file_extension = filepath.extension();
  if (file_extension != ".png" && file_extension != ".PNG") {
    std::cerr << "warning! the file extension is not \"png\"" << std::endl;
  }

  if (pixels.size() == 0 || pixels.size() != width * height * channel) {
    std::cerr << "the image data is broken" << std::endl;
    return false;
  }

  if (convert_option != ConvertOption::FORCE_NO_CONVERT) {
    std::cerr << "Start LinerTosRGB" << std::endl;
    for (size_t i = 0; i < width * height; i++) {
      for (size_t c = 0; c < std::min<size_t>(channel, 3); c++) {
        pixels[i * channel + c] = LinerTosRGB(pixels[i * channel + c]);
      }
    }
    std::cerr << "Finish LinerTosRGB" << std::endl;
  }

  std::vector<unsigned char> pixel8(width * height * channel);

  for (size_t i = 0; i < width * height * channel; i++) {
    pixel8[i] = static_cast<unsigned char>(std::max(
        static_cast<T>(0.0),
        std::min(static_cast<T>(255.0), pixels[i] * static_cast<T>(256.0))));
  }

  int ret = stbi_write_png(filename.c_str(), int(width), int(height),
                           int(channel), pixel8.data(), int(width * channel));

  if (!ret) {
    std::cerr << "faild save image" << std::endl;
    return false;
  }

  std::cerr << "write png file [ " << filename << " ]" << std::endl;

  return true;
}

template bool WritePNG(std::vector<float> pixels, const size_t width,
                       const size_t height, const size_t channel,
                       const std::string& filename,
                       ConvertOption convert_option);

template bool WritePNG(std::vector<double> pixels, const size_t width,
                       const size_t height, const size_t channel,
                       const std::string& filename,
                       ConvertOption convert_option);
}  // namespace image_utils
