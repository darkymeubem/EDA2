#pragma once
#include <vector>

class MNISTLoader {
public:
    // Returns vector of images; each image is 784 floats (28x28, normalized 0-1)
    static std::vector<std::vector<float>> loadImages(const char* path, int max = -1);
    static std::vector<int>                loadLabels(const char* path, int max = -1);
};
