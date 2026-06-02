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
	double gauss_ker[] = {1.0/16, 1.0/8, 1.0/16,
					 1.0/8,  1.0/4, 1.0/8,
					 1.0/16, 1.0/8, 1.0/16};
	gray_img.convolve_linear(0, 3, 3, gauss_ker, 1, 1);
	
	Image blurred_img(img.w, img.h, 1);
	blurred_img = gray_img;
	blurred_img.write("imgs/teste5_blurred.png");

	//edge detection
	double *tx = new double[img_size];
	double *ty = new double[img_size];
	double *gx = new double[img_size];
	double *gy = new double[img_size];

	//separable convolution
	for(uint32_t c=1; c<blurred_img.w-1; ++c){
		for(uint32_t r=0; r<blurred_img.h; ++r){
			tx[blurred_img.w*r+c] = blurred_img.data[blurred_img.w*r+c+1] - blurred_img.data[blurred_img.w*r+c-1];
			ty[blurred_img.w*r+c] = 47*blurred_img.data[blurred_img.w*r+c+1] + 162 * blurred_img.data[blurred_img.w*r+c] + 47 * blurred_img.data[blurred_img.w*r+c-1];
		}
	}


	for(uint32_t c=1; c<blurred_img.w-1; ++c){
		for(uint32_t r=1; r<blurred_img.h-1; ++r){
			gx[blurred_img.w*r+c] = 47*tx[blurred_img.w*(r+1)+c] + 162 * tx[blurred_img.w*r+c] + 47 * tx[blurred_img.w*(r-1)+c];
			gy[blurred_img.w*r+c] = ty[blurred_img.w*(r+1)+c] - ty[blurred_img.w*(r-1)+c];
		}
	}

	delete[] tx;
	delete[] ty;

	//make test images
	double max_x = -INFINITY,max_y = -INFINITY, min_x = INFINITY, min_y = INFINITY;

	for(uint64_t k=0; k<img_size; ++k){
		max_x = fmax(max_x, gx[k]);
		max_y = fmax(max_y, gy[k]);
		min_x = fmin(min_x, gx[k]);
		min_y = fmin(min_y, gy[k]);
	}

	Image Gx_img(img.w, img.h, 1);
	Image Gy_img(img.w, img.h, 1);

	for(uint64_t k=0; k<img_size; ++k){
		Gx_img.data[k] = (uint8_t)(255*(gx[k]-min_x)/(max_x-min_x));
		Gy_img.data[k] = (uint8_t)(255*(gy[k]-min_y)/(max_y-min_y));
	}
	Gx_img.write("imgs/teste5_Gx.png");
	Gy_img.write("imgs/teste5_Gy.png");
	
	Image diff_img(img.w, img.h, 1);
	diff_img = Gx_img;
	diff_img.diffMap(Gy_img);

	Image diff_img1(img.w, img.h, 1);
	diff_img1 = Gy_img;
	diff_img1.diffMap(Gx_img);

	diff_img.write("imgs/teste5_diff.png");
	diff_img1.write("imgs/teste5_diff1.png");

	// magnitude do gradiente: sqrt(gx² + gy²)
	double *mag = new double[img_size];
	double max_mag = -INFINITY, min_mag = INFINITY;

	for(uint64_t k=0; k<img_size; ++k){
		mag[k] = sqrt(gx[k]*gx[k] + gy[k]*gy[k]);
		max_mag = fmax(max_mag, mag[k]);
		min_mag = fmin(min_mag, mag[k]);
	}

	Image edge_img(img.w, img.h, 1);
	for(uint64_t k=0; k<img_size; ++k)
		edge_img.data[k] = (uint8_t)(255*(mag[k]-min_mag)/(max_mag-min_mag));

	edge_img.write("imgs/teste5_edges.png");
	delete[] mag;

	return 0;
}
