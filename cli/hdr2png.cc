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

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#include "spdlog/spdlog.h"

#ifdef __clang__
#pragma clang diagnostic pop
#endif

int main(int argc, char const* argv[]) {
  if (argc <= 1) {
    spdlog::error("Please specify the hdr image filename");
    return 1;
  }

  const auto image = image_utils::LoadAndConvertImage<float>(argv[1]);

  const std::vector<float>& pixels = std::get<0>(image);
  const size_t width               = std::get<1>(image);
  const size_t height              = std::get<2>(image);
  const size_t channel             = std::get<3>(image);

  bool ret = image_utils::WritePNG<float>(pixels, width, height, channel,
                                          "output.png");

  if (!ret) {
    spdlog::error("failed writing png");
    return 1;
  }

  spdlog::info("success to write png");

  return 0;
}
