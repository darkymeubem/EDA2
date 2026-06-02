#include "Image.h"
#include <iostream>

#include <cstdlib>
#include <cmath>
#include <chrono>

int main(int argc, char** argv) {
	
	Image img("imgs/test5.jpg");

	//para fazer edge detection a imagem precisa estar em gray scale
	img.grayscale_lum();
	int img_size = img.w*img.h;

	Image gray_img(img.w, img.h, 1);


	for(uint64_t k=0; k<img_size; ++k){
		gray_img.data[k] = img.data[img.channels*k];
	}

	gray_img.write("imgs/teste5_gray.png");

	//blur

	return 0;
}
