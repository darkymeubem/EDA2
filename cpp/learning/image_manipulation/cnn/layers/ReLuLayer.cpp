#include "ReLULayer.h"

ReLULayer::ReLULayer() : last_input(1, 1, 1) {}

Tensor ReLULayer::forward(const Tensor& input) {
    last_input = input;
    Tensor output(input.channels, input.height, input.width);
    for (int i = 0; i < input.size(); i++)
        output.data[i] = input.data[i] > 0 ? input.data[i] : 0.0f;
    return output;
}

Tensor ReLULayer::backward(const Tensor& grad_output, float lr) {
    Tensor grad_input(last_input.channels, last_input.height, last_input.width);
    for (int i = 0; i < grad_input.size(); i++)
        grad_input.data[i] = last_input.data[i] > 0 ? grad_output.data[i] : 0.0f;
    return grad_input;
}
