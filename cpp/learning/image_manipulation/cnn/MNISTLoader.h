#pragma once
#include <vector>
#include "Tensor.h"

class MNISTLoader {
public:
    static std::vector<Tensor> loadImages(const char* path, int max = -1);
    static std::vector<int>    loadLabels(const char* path, int max = -1);
};
