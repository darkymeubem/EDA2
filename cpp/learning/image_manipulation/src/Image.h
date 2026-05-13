
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "schrift.h"

#define STEG_HEADER_SIZE sizeof(uint32_t) * 8

enum ImageType{
	PNG, JPG, BMP, TGA
};

struct Font;

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

	//flip na imagem
	Image& flipX();
	Image& flipY();

	Image& overlay(const Image& source, int x, int y);
	Image& overlayText(const char* txt, const Font& font, int x, int y, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);

};

struct Font{
	SFT sft = {NULL, 12, 12, 0, 0, SFT_DOWNWARD_Y|SFT_RENDER_IMAGE};

	Font(const char* fontfile, uint16_t size) {
		if((sft.font = sft_loadfile(fontfile)) == NULL) {
			printf("\e[31m[ERROR] Failed to load %s\e[0m\n", fontfile);
			return;
		}
		setSize(size);
	} 

	~Font() {
		sft_freefont(sft.font);
	}
	void setSize(uint16_t size) {
		sft.xScale = size;
		sft.yScale = size;
	}
};