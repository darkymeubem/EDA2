#pragma once
#include "../Tensor.h"
#include "Layer.h"

class SoftmaxLayer : public Layer {
public:
    Tensor last_output;
    SoftmaxLayer();
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
    float loss(int label) const;  // cross-entropy loss
};
