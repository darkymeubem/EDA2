#include "Tensor.h"

Tensor::Tensor(int c, int h, int w) : channels(c), height(h), width(w) {
    data = new float[c * h * w]();
}
Tensor::Tensor(const Image& img) : channels(img.channels), height(img.h), width(img.w) {
    data = new float[channels * height * width];
    for (int i = 0; i < img.size; ++i) {
        data[i] = img.data[i] / 255.0f;  // normaliza para [0, 1]
    }
}

float& Tensor::at(int c, int h, int w) {
    return data[c * height * width + h * width + w];
}