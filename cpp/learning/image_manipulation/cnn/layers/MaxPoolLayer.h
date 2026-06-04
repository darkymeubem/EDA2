#pragma once
#include "../Tensor.h"
#include "Layer.h"

class MaxPoolLayer : public Layer {
private:
    int pool_size;
    Tensor last_input;
public:
    MaxPoolLayer(int pool_size);
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
