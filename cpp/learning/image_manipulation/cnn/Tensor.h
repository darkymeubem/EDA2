#pragma once
#include "Image.h"
#include <cstdint>

class Tensor {
public:
    float* data;
    int channels, height, width;

    Tensor(int c, int h, int w);
    Tensor(const Image& img);  // converte Image (uint8_t) → Tensor (float, normalizado 0-1)

    float& at(int c, int h, int w);
    const float& at(int c, int h, int w) const;
    int size() const { return channels * height * width; }
};