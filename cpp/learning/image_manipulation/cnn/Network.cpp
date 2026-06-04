#include "Network.h"
#include <iostream>
#include <cstdio>

Network::Network() : softmax(new SoftmaxLayer()) {
    layers.push_back(softmax);
}

Network::~Network() {
    for (Layer* l : layers) delete l;
}

void Network::addLayer(Layer* layer) {
    layers.insert(layers.begin(), layer);  // insere antes do softmax
}

Tensor Network::forward(const Tensor& input) {
    Tensor current = input;
    for (Layer* l : layers)
        current = l->forward(current);
    return current;
}

float Network::backward(int label, float lr) {
    float loss = softmax->loss(label);

    // gradiente inicial: softmax_output - one_hot(label)
    Tensor grad(softmax->last_output.channels, 1, 1);
    for (int i = 0; i < grad.size(); i++)
        grad.data[i] = softmax->last_output.data[i] - (i == label ? 1.0f : 0.0f);

    // propaga de trás pra frente
    for (int i = layers.size() - 1; i >= 0; i--)
        grad = layers[i]->backward(grad, lr);

    return loss;
}

void Network::train(std::vector<Tensor>& images, std::vector<int>& labels, int epochs, float lr) {
    for (int e = 0; e < epochs; e++) {
        float total_loss = 0.0f;
        for (int i = 0; i < (int)images.size(); i++) {
            forward(images[i]);
            total_loss += backward(labels[i], lr);
        }
        printf("Epoch %d | Loss: %.4f\n", e+1, total_loss / images.size());
    }
}
