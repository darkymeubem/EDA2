#pragma once
#include "../Tensor.h"

class Layer {
public:
    virtual Tensor forward(const Tensor& input) = 0;
    virtual Tensor backward(const Tensor& grad_output, float lr) = 0;
    virtual ~Layer() = default;
};
