#pragma once
#include <vector>
#include "layers/Layer.h"
#include "layers/SoftmaxLayer.h"
#include "Tensor.h"

class Network {
private:
    std::vector<Layer*> layers;
    SoftmaxLayer* softmax;

public:
    static constexpr int BATCH = 64;

    Network();
    ~Network();

    void   addLayer(Layer* layer);
    Tensor forward(const Tensor& batch);

    // Returns mean loss; updates weights for a single batch
    float  trainBatch(const std::vector<float>& imgs_flat,
                      const std::vector<int>&   labels,
                      int start, int count, float lr);

    void train(const std::vector<std::vector<float>>& images,
               const std::vector<int>& labels,
               int epochs, float lr);

    float evaluate(const std::vector<std::vector<float>>& images,
                   const std::vector<int>& labels);
};
