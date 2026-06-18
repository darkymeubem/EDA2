#include "MNISTLoader.h"
#include <cstdio>
#include <cstdlib>

// MNIST é big-endian, x86 é little-endian — precisa inverter os bytes
static int reverseInt(int i) {
    unsigned char c1 = i & 255;
    unsigned char c2 = (i >> 8) & 255;
    unsigned char c3 = (i >> 16) & 255;
    unsigned char c4 = (i >> 24) & 255;
    return ((int)c1 << 24) | ((int)c2 << 16) | ((int)c3 << 8) | c4;
}

std::vector<std::vector<float>> MNISTLoader::loadImages(const char* path, int max) {
    FILE* f = fopen(path, "rb");
    if (!f) { printf("Erro ao abrir %s\n", path); exit(1); }

    int magic, n, rows, cols;
    fread(&magic, 4, 1, f);  magic = reverseInt(magic);
    fread(&n,     4, 1, f);  n     = reverseInt(n);
    fread(&rows,  4, 1, f);  rows  = reverseInt(rows);
    fread(&cols,  4, 1, f);  cols  = reverseInt(cols);

    if (max > 0 && max < n) n = max;

    printf("Carregando %d imagens de %s...\n", n, path);

    std::vector<std::vector<float>> images;
    images.reserve(n);

    for (int i = 0; i < n; i++) {
        std::vector<float> img(rows * cols);
        for (int j = 0; j < rows * cols; j++) {
            unsigned char pixel;
            fread(&pixel, 1, 1, f);
            img[j] = pixel / 255.0f;
        }
        images.push_back(std::move(img));
        if ((i + 1) % 10000 == 0)
            printf("  %d/%d\n", i + 1, n);
    }
    printf("Imagens carregadas!\n");
    fclose(f);
    return images;
}

std::vector<int> MNISTLoader::loadLabels(const char* path, int max) {
    FILE* f = fopen(path, "rb");
    if (!f) { printf("Erro ao abrir %s\n", path); exit(1); }

    int magic, n;
    fread(&magic, 4, 1, f);  magic = reverseInt(magic);
    fread(&n,     4, 1, f);  n     = reverseInt(n);

    if (max > 0 && max < n) n = max;

    std::vector<int> labels(n);
    for (int i = 0; i < n; i++) {
        unsigned char label;
        fread(&label, 1, 1, f);
        labels[i] = label;
    }
    fclose(f);
    return labels;
}
