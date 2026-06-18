#pragma once
#include "../Tensor.h"
#include "../CudaUtils.h"
#include "Layer.h"
#include <cudnn.h>

class ReLULayer : public Layer {
private:
    cudnnActivationDescriptor_t act_desc;
    cudnnTensorDescriptor_t     tensor_desc;

    float* d_last_output;
    int    last_n, last_c, last_h, last_w;

public:
    ReLULayer();
    ~ReLULayer();
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
