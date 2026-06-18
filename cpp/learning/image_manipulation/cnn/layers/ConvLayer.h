#pragma once
#include "../Tensor.h"
#include "../CudaUtils.h"
#include "Layer.h"
#include <cudnn.h>

class ConvLayer : public Layer {
private:
    int in_c, out_c, ksize;

    float *d_weights, *d_bias;
    float *d_grad_w,  *d_grad_b;

    cudnnTensorDescriptor_t  in_desc, out_desc, bias_desc;
    cudnnFilterDescriptor_t  filter_desc;
    cudnnConvolutionDescriptor_t conv_desc;

    cudnnConvolutionFwdAlgo_t    fwd_algo;
    cudnnConvolutionBwdDataAlgo_t   bwd_data_algo;
    cudnnConvolutionBwdFilterAlgo_t bwd_filter_algo;

    float* d_workspace;
    size_t workspace_size;

    float* d_last_input;
    int    last_n, last_h, last_w;

    void setDescriptors(int n, int h, int w);

public:
    ConvLayer(int in_c, int out_c, int ksize);
    ~ConvLayer();
    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& grad_output, float lr) override;
};
