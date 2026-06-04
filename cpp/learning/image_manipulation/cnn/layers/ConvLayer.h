
#pragma once
#include "../Tensor.h"
#include "Layer.h"

class ConvLayer : public Layer {
private:
    int in_channels, out_channels, kernel_size;
    Tensor weights;  // shape: out_channels × in_channels × k × k
    Tensor bias;     // shape: out_channels × 1 × 1
    Tensor last_input; // salvo no forward, usado no backward

public:
    ConvLayer(int in_channels, int out_channels, int kernel_size);

    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
