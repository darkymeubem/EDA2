#pragma once
#include "../Tensor.h"
#include "Layer.h"

class FCLayer : public Layer {
private:
    int in_size, out_size;
    Tensor weights;  // shape: out_size × 1 × in_size
    Tensor bias;     // shape: out_size × 1 × 1
    Tensor last_input;
public:
    FCLayer(int in_size, int out_size);
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
