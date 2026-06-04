
#include "ConvLayer.h"
#include <cstdlib>
#include <cmath>

ConvLayer::ConvLayer(int in_ch, int out_ch, int k)
    : in_channels(in_ch), out_channels(out_ch), kernel_size(k),
      weights(out_ch * in_ch, k, k),
      bias(out_ch, 1, 1),
      last_input(1, 1, 1)  // placeholder, redimensionado no forward
{
    // inicialização He: bom para ReLU
    float std = sqrtf(2.0f / (in_ch * k * k));
    for (int i = 0; i < weights.size(); i++)
        weights.data[i] = ((float)rand() / RAND_MAX) * 2 * std - std;

    for (int i = 0; i < bias.size(); i++)
        bias.data[i] = 0.0f;
        
}

Tensor ConvLayer::forward(const Tensor& input) {
    last_input = input;

    int out_h = input.height - kernel_size + 1;
    int out_w = input.width  - kernel_size + 1;

    Tensor output(out_channels, out_h, out_w);

    for (int f = 0; f < out_channels; f++) {
        for (int oh = 0; oh < out_h; oh++) {
            for (int ow = 0; ow < out_w; ow++) {
                float sum = bias.data[f];

                for (int ic = 0; ic < in_channels; ic++) {
                    for (int kh = 0; kh < kernel_size; kh++) {
                        for (int kw = 0; kw < kernel_size; kw++) {
                            float inp = input.at(ic, oh + kh, ow + kw);
                            float w   = weights.at(f * in_channels + ic, kh, kw);
                            sum += inp * w;
                        }
                    }
                }
                output.at(f, oh, ow) = sum;
            }
        }
    }
    return output;
}

Tensor ConvLayer::backward(const Tensor& grad_output, float lr) {
    int out_h = grad_output.height;
    int out_w = grad_output.width;

    Tensor grad_input(in_channels, last_input.height, last_input.width);
    // começa zerado (Tensor inicializa com 0)

    for (int f = 0; f < out_channels; f++) {
        // 3. gradiente do bias: soma todo o grad_output desse filtro
        for (int oh = 0; oh < out_h; oh++)
            for (int ow = 0; ow < out_w; ow++)
                bias.data[f] -= lr * grad_output.at(f, oh, ow);

        for (int ic = 0; ic < in_channels; ic++) {
            for (int kh = 0; kh < kernel_size; kh++) {
                for (int kw = 0; kw < kernel_size; kw++) {
                    float dw = 0.0f;

                    for (int oh = 0; oh < out_h; oh++) {
                        for (int ow = 0; ow < out_w; ow++) {
                            // 2. gradiente do peso
                            dw += grad_output.at(f, oh, ow) * last_input.at(ic, oh+kh, ow+kw);

                            // 1. gradiente do input
                            grad_input.at(ic, oh+kh, ow+kw) += grad_output.at(f, oh, ow) * weights.at(f*in_channels+ic, kh, kw);
                        }
                    }
                    // 2. atualiza peso com SGD
                    weights.at(f*in_channels+ic, kh, kw) -= lr * dw;
                }
            }
        }
    }
    return grad_input;
}
