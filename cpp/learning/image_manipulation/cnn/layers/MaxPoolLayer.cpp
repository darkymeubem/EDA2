#include "MaxPoolLayer.h"
#include <algorithm>

MaxPoolLayer::MaxPoolLayer(int pool_size)
    : pool_size(pool_size), last_input(1, 1, 1) {}

Tensor MaxPoolLayer::forward(const Tensor& input) {
    last_input = input;

    int out_h = input.height / pool_size;
    int out_w = input.width  / pool_size;

    Tensor output(input.channels, out_h, out_w);

    for (int c = 0; c < input.channels; c++) {
        for (int oh = 0; oh < out_h; oh++) {
            for (int ow = 0; ow < out_w; ow++) {
                float max_val = -1e9f;
                for (int ph = 0; ph < pool_size; ph++)
                    for (int pw = 0; pw < pool_size; pw++)
                        max_val = std::max(max_val, input.at(c, oh*pool_size+ph, ow*pool_size+pw));
                output.at(c, oh, ow) = max_val;
            }
        }
    }
    return output;
}
Tensor MaxPoolLayer::backward(const Tensor& grad_output, float lr) {
    Tensor grad_input(last_input.channels, last_input.height, last_input.width);

    int out_h = grad_output.height;
    int out_w = grad_output.width;

    for (int c = 0; c < last_input.channels; c++) {
        for (int oh = 0; oh < out_h; oh++) {
            for (int ow = 0; ow < out_w; ow++) {
                // acha qual posição foi o máximo no forward
                float max_val = -1e9f;
                int max_ph = 0, max_pw = 0;
                for (int ph = 0; ph < pool_size; ph++)
                    for (int pw = 0; pw < pool_size; pw++) {
                        float val = last_input.at(c, oh*pool_size+ph, ow*pool_size+pw);
                        if (val > max_val) {
                            max_val = val;
                            max_ph = ph; max_pw = pw;
                        }
                    }
                // gradiente só vai pro elemento que foi o máximo
                grad_input.at(c, oh*pool_size+max_ph, ow*pool_size+max_pw) = grad_output.at(c, oh, ow);
            }
        }
    }
    return grad_input;
}
