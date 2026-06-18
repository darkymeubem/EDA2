#pragma once
#include "../Tensor.h"
#include "../CudaUtils.h"
#include "Layer.h"

class FCLayer : public Layer {
private:
    int in_size, out_size;

    float *d_weights, *d_bias;
    float *d_grad_w,  *d_grad_b;

    float* d_last_input;
    int    last_n;

public:
    FCLayer(int in_size, int out_size);
    ~FCLayer();
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
