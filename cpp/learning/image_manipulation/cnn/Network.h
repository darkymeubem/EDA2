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
    Network();
    ~Network();

    void addLayer(Layer* layer);
    Tensor forward(const Tensor& input);
    float backward(int label, float lr);  // retorna o loss
    float evaluate(std::vector<Tensor>& images, std::vector<int>& labels);
    void train(std::vector<Tensor>& images, std::vector<int>& labels, int epochs, float lr);
};
