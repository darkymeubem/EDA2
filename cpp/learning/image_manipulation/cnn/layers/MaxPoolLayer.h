#pragma once
#include "../Tensor.h"
#include "../CudaUtils.h"
#include "Layer.h"
#include <cudnn.h>

class MaxPoolLayer : public Layer {
private:
    int pool_size;

    cudnnPoolingDescriptor_t pool_desc;
    cudnnTensorDescriptor_t  in_desc, out_desc;

    float *d_last_input, *d_last_output;
    int    last_n, last_c, last_h, last_w, last_oh, last_ow;

public:
    MaxPoolLayer(int pool_size);
    ~MaxPoolLayer();
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
