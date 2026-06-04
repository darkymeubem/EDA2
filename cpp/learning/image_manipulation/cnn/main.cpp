#include <iostream>
#include "Tensor.h"
#include "Network.h"
#include "MNISTLoader.h"
#include "layers/ConvLayer.h"
#include "layers/ReLuLayer.h"
#include "layers/MaxPoolLayer.h"
#include "layers/FCLayer.h"

int main() {
    // carrega MNIST (use max para testar com menos dados)
    auto images = MNISTLoader::loadImages("MNIST_dataset/train-images.idx3-ubyte");
    auto labels = MNISTLoader::loadLabels("MNIST_dataset/train-labels.idx1-ubyte");

    auto test_images = MNISTLoader::loadImages("MNIST_dataset/t10k-images.idx3-ubyte");
    auto test_labels = MNISTLoader::loadLabels("MNIST_dataset/t10k-labels.idx1-ubyte");

    // monta a rede — LeNet-5 com MaxPool
    Network net;
    net.addLayer(new FCLayer(84, 10));
    net.addLayer(new FCLayer(120, 84));
    net.addLayer(new FCLayer(256, 120));
    net.addLayer(new MaxPoolLayer(2));
    net.addLayer(new ReLULayer());
    net.addLayer(new ConvLayer(6, 16, 5));
    net.addLayer(new MaxPoolLayer(2));
    net.addLayer(new ReLULayer());
    net.addLayer(new ConvLayer(1, 6, 5));

    // treina
    float lr = 0.01f;
    int epochs = 5;
    net.train(images, labels, epochs, lr);

    // avalia no conjunto de teste
    int correct = 0;
    for (int i = 0; i < (int)test_images.size(); i++) {
        Tensor out = net.forward(test_images[i]);
        int pred = 0;
        for (int j = 1; j < out.size(); j++)
            if (out.data[j] > out.data[pred]) pred = j;
        if (pred == test_labels[i]) correct++;
    }
    printf("Acurácia: %.2f%%\n", 100.0f * correct / test_images.size());

    return 0;
}
