#include "Image.h"
#include <iostream>

#include <cstdlib>
#include <cmath>
#include <chrono>

int main(int argc, char** argv) {
	
	Image img("imgs/teste.png");

	//para fazer edge detection a imagem precisa estar em gray scale
	img.grayscale_lum();
	int img_size = img.w*img.h;

	Image gray_img(img.w, img.h, 1);


	for(uint64_t k=0; k<img_size; ++k){
		gray_img.data[k] = img.data[img.channels*k];
	}

	gray_img.write("imgs/teste_gray.png");

	//blur
	double gauss_ker[] = {1.0/16, 1.0/8, 1.0/16,
					 1.0/8,  1.0/4, 1.0/8,
					 1.0/16, 1.0/8, 1.0/16};
	gray_img.convolve_linear(0, 3, 3, gauss_ker, 1, 1);
	
	Image blurred_img(img.w, img.h, 1);
	blurred_img = gray_img;
	blurred_img.write("imgs/teste_blurred.png");

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
	Gx_img.write("imgs/teste_Gx.png");
	Gy_img.write("imgs/teste_Gy.png");
	
	// Image diff_img(img.w, img.h, 1);
	// diff_img = Gx_img;
	// diff_img.diffMap(Gy_img);

	// Image diff_img1(img.w, img.h, 1);
	// diff_img1 = Gy_img;
	// diff_img1.diffMap(Gx_img);

	// diff_img.write("imgs/teste5_diff.png");
	// diff_img1.write("imgs/teste5_diff1.png");

	//parte divertida?
	double threshold = 0.09;
	double *theta = new double[img_size];
	double x,y;
	// magnitude do gradiente: sqrt(gx² + gy²)
	double *mag = new double[img_size];
	double max_mag = -INFINITY, min_mag = INFINITY;

	for(uint64_t k=0; k<img_size; ++k){
		mag[k] = sqrt(gx[k]*gx[k] + gy[k]*gy[k]);
		theta[k] = atan2(gy[k], gx[k]);
		max_mag = fmax(max_mag, mag[k]);
		min_mag = fmin(min_mag, mag[k]);
	}

	Image edge_img(img.w, img.h, 1);
	Image angle_img(img.w, img.h, 3);

	double h,s,l;
	double v;
	for(uint64_t k=0; k<img_size; ++k){
		//theta to determine hue 
		h = theta[k]*180/M_PI + 180;

		//v eh o relativo a intensidade da borda
		if(max_mag == min_mag){
			v = 0;
		}else{
			v = (mag[k]-min_mag)/(max_mag-min_mag) > threshold ? (mag[k]-min_mag)/(max_mag-min_mag) : 0;
		}	
		s = l = v;
		//hsl para rgb
		double c = (1 - fabs(2*l - 1))*s;
		double x = c*(1 - fabs(fmod(h/60.0, 2) - 1));
		double m = l - c/2;
		double r,g,b;

		if(h < 60){
			r = c; g = x; b = 0;
		}else if(h < 120){
			r = x; g = c; b = 0;
		}else if(h < 180){
			r = 0; g = c; b = x;
		}else if(h < 240){
			r = 0; g = x; b = c;	
		}else if(h < 300){
			r = x; g = 0; b = c;
		}else{
			r = c; g = 0; b = x;
		}
		uint8_t red= (uint8_t)((r+m)*255);
		uint8_t green = (uint8_t)((g+m)*255);
		uint8_t blue = (uint8_t)((b+m)*255);

		angle_img.data[3*k] = red;
		angle_img.data[3*k+1] = green;
		angle_img.data[3*k+2] = blue;

		edge_img.data[k] = (uint8_t)(255*v);

	}

	edge_img.write("imgs/teste_edges.png");
	angle_img.write("imgs/teste_angles.png");


	delete[] mag;
	delete[] theta;
	delete[] gx;
	delete[] gy;

	return 0;
}
