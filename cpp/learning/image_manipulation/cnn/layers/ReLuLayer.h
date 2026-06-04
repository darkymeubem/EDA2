#pragma once
#include "../Tensor.h"
#include "Layer.h"

class ReLULayer : public Layer {
private:
    Tensor last_input;
public:
    ReLULayer();
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
