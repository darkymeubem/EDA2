
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>


#define STEG_HEADER_SIZE sizeof(uint32_t) * 8

enum ImageType{
	PNG, JPG, BMP, TGA
};

struct Image {
	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;

	Image(const char* filename);
	Image(int w, int h, int channels);
	Image(const Image& img);
	~Image();

	bool read(const char* filename);
	bool write(const char* filename);

	ImageType getFileType(const char* filename);

	//grayscale methods
	Image& grayscale_avg();
	Image& grayscale_lum();


	Image& colorMask(float r, float g, float b);

	//esteganografia methods
	Image& encodeMessage(const char* message);
	Image& decodeMessage(char *buffer, size_t* messageLength);

	Image& diffMap(Image& img);
	Image& diffMap_scale(Image& img, uint8_t scl = 0);

	//convolução
	Image& std_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	Image& std_convolve_clamp_to_border(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	Image& std_convolve_clamp_to_cycle(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);



};
