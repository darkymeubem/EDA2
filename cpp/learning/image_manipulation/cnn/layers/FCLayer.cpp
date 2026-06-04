#include "FCLayer.h"
#include <cstdlib>
#include <cmath>

FCLayer::FCLayer(int in_size, int out_size)
    : in_size(in_size), out_size(out_size),
      weights(out_size, 1, in_size),
      bias(out_size, 1, 1),
      last_input(1, 1, 1)
{
    float std = sqrtf(2.0f / in_size);
    for (int i = 0; i < weights.size(); i++)
        weights.data[i] = ((float)rand() / RAND_MAX) * 2 * std - std;
    for (int i = 0; i < bias.size(); i++)
        bias.data[i] = 0.0f;
}

Tensor FCLayer::forward(const Tensor& input) {
    last_input = input;
    Tensor output(out_size, 1, 1);

    for (int o = 0; o < out_size; o++) {
        float sum = bias.data[o];
        for (int i = 0; i < in_size; i++)
            sum += input.data[i] * weights.at(o, 0, i);
        output.data[o] = sum;
    }
    return output;
}

Tensor FCLayer::backward(const Tensor& grad_output, float lr) {
    Tensor grad_input(1, 1, in_size);

    for (int o = 0; o < out_size; o++) {
        float grad = grad_output.data[o];

        bias.data[o] -= lr * grad;

        for (int i = 0; i < in_size; i++) {
            grad_input.data[i] += grad * weights.at(o, 0, i);
            weights.at(o, 0, i) -= lr * grad * last_input.data[i];
        }
    }
    return grad_input;
}
