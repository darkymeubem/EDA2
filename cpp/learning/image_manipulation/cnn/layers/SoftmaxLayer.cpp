#include "SoftmaxLayer.h"
#include <cmath>

SoftmaxLayer::SoftmaxLayer() : last_output(1, 1, 1) {}

Tensor SoftmaxLayer::forward(const Tensor& input) {
    last_output = Tensor(input.channels, input.height, input.width);

    // subtrai o máximo para estabilidade numérica
    float max_val = input.data[0];
    for (int i = 1; i < input.size(); i++)
        max_val = std::max(max_val, input.data[i]);

    float sum = 0.0f;
    for (int i = 0; i < input.size(); i++) {
        last_output.data[i] = expf(input.data[i] - max_val);
        sum += last_output.data[i];
    }
    for (int i = 0; i < input.size(); i++)
        last_output.data[i] /= sum;

    return last_output;
}

float SoftmaxLayer::loss(int label) const {
    return -logf(last_output.data[label] + 1e-9f);
}

Tensor SoftmaxLayer::backward(const Tensor& grad_output, float lr) {
    // gradiente combinado softmax + cross-entropy: output - one_hot(label)
    // grad_output já vem com esse valor calculado pelo Network
    return grad_output;
}
