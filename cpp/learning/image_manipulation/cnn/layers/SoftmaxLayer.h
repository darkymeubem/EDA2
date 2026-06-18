#pragma once
#include "../Tensor.h"
#include "../CudaUtils.h"
#include "Layer.h"
#include <cudnn.h>
#include <vector>

class SoftmaxLayer : public Layer {
private:
    cudnnTensorDescriptor_t desc;

public:
    // Network lê estes diretamente para calcular loss/gradiente
    std::vector<float> h_last_output;
    int last_n, num_classes;

    SoftmaxLayer();
    ~SoftmaxLayer();
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
