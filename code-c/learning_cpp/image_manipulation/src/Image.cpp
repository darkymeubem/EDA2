#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#define BYTE_BOUND(value) ((value) < 0 ? 0 : ((value) > 255 ? 255 : (value)))

#include "stb_image.h"
#include "stb_image_write.h"

#include "Image.h"


Image::Image(const char* filename){
    data = nullptr;
    size = 0;
    w = 0;
    h = 0;
    channels = 0;
    if(read(filename)){
        printf("Read %s\n", filename);
        size = w * h * channels;
    }
    else{
        printf("Failed to read %s\n", filename);
    }
}
Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
	size = w*h*channels;
	data = new uint8_t[size];
}
Image::Image(const Image& img): Image(img.w, img.h, img.channels){
    if (img.data != nullptr && data != nullptr && size == img.size && size > 0){ 
        memcpy(data, img.data, size);
    }
    else{
        printf("Failed to copy image\n");
    }
}
Image::~Image(){
    if(data != nullptr){
        stbi_image_free(data);
        data = nullptr;
    }
}

bool Image::read(const char* filename){
    if (data != nullptr) {
        stbi_image_free(data);
        data = nullptr;
    }
    data = stbi_load(filename, &w, &h, &channels, 0);
    if (data == nullptr) {
        w = 0;
        h = 0;
        channels = 0;
        size = 0;
        return false;
    }
    size = static_cast<size_t>(w) * static_cast<size_t>(h) * static_cast<size_t>(channels);
    return true;
}
bool Image::write(const char* filename){
    if (data == nullptr || w <= 0 || h <= 0 || channels <= 0 || size == 0) {
        printf("\e[31;1m Failed to write \e[36m%s\e[0m, image data is empty/invalid\n", filename);
        return false;
    }
    ImageType type = getFileType(filename);
    int sucess = 0;
    switch(type){
        case PNG:
            sucess = stbi_write_png(filename, w, h, channels, data, w * channels);
            break;
        case JPG:
            sucess = stbi_write_jpg(filename, w, h, channels, data, 100);
            break;
        case BMP:
            sucess = stbi_write_bmp(filename, w, h, channels, data);
            break;
        case TGA:
            sucess = stbi_write_tga(filename, w, h, channels, data);
            break;
        
    }
    if(sucess != 0) {
        printf("\e[32mWrote \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
        return true;
    }
    else {
        printf("\e[31;1m Failed to write \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
        return false;
    }

}
ImageType Image::getFileType(const char* filename){

    const char* ext = strrchr(filename, '.');
    if(ext != nullptr){
        if(strcmp(ext, ".png") == 0){
            return PNG;
        }
        else if(strcmp(ext, ".jpg") == 0){
            return JPG;
        }
        else if(strcmp(ext, ".bmp") == 0){
            return BMP;
        }
    }
    return PNG;
}

Image& Image::grayscale_avg(){
    for(int i = 0; i < w*h*channels; i+= channels){
        data[i] = (data[i] + data[i+1] + data[i+2])/3;
        memset(data+i, data[i], 3);
    }
    return *this;   
}

Image& Image::grayscale_lum(){
    if(channels < 3){
        printf("Image must have at least 3 channels\n");
        return *this;
    }
    for(int i = 0; i < w*h*channels; i+= channels){
        data[i] = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
        memset(data+i, data[i], 3);
    }
    return *this;
}

Image& Image::colorMask(float r, float g, float b){
    if(channels < 3){
        printf("\e[31m[ERROR] Color mask requires at least 3 channels, but this image has %d channels\e[0m\n", channels);
    }
    else{
        for(int i =0; i < size; i+= channels){
            data[i] *= r;
            data[i+1] *= g;
            data[i+2] *= b;
        }
    }
    return *this;
}

Image& Image::encodeMessage(const char* message){
    uint32_t len = strlen(message) *8;
    if(len + STEG_HEADER_SIZE > size) {
		printf("\e[31m[ERROR] This message is too large (%lu bits / %zu bits)\e[0m\n", len+STEG_HEADER_SIZE, size);
		return *this;
	}

    printf("LENGTH: %d\n", len);
     for(uint8_t i=0; i < STEG_HEADER_SIZE; i++){
        uint8_t bit = (len >> (STEG_HEADER_SIZE - i - 1)) & 1UL;
        data[i] = (data[i] & 0xFE) | bit;
     }

     for(uint32_t i=0; i < len; i++){
        data[STEG_HEADER_SIZE +i] &= 0xFE; //isola ultimo bit
        data[STEG_HEADER_SIZE + i] = (message[i/8] >> ((len-1-i)%8)) & 1UL; //adiciona bit ao pixel
     }
    return *this;
}
Image& Image::decodeMessage(char *buffer, size_t* messageLength){
    uint32_t len = 0;
    for(uint8_t i=0; i < STEG_HEADER_SIZE; i++){
        len = (len << 1) | (data[i] & 1UL);
     }
    *messageLength = len;
    for(uint32_t i=0; i < len; i++){
       buffer[i/8] = (buffer[i/8] << 1) | (data[STEG_HEADER_SIZE + i] & 1U);
     }
    buffer[len/8] = '\0';
    return *this;
}

Image& Image::diffMap(Image& img){
    int compare_width = fmin(w, img.w);
    int compare_height = fmin(h, img.h); 
    int compare_channels = fmin(channels, img.channels);

    for(uint32_t i=0; i<compare_height; ++i) {
		for(uint32_t j=0; j<compare_width; ++j) {
			for(uint8_t k=0; k<compare_channels; ++k) {
				data[(i*w+j)*channels+k] = BYTE_BOUND(abs(data[(i*w+j)*channels+k] - img.data[(i*img.w+j)*img.channels+k]));
			}
		}
	}
	return *this;
}

Image& Image::diffMap_scale(Image& img, uint8_t scl){
    int compare_width = fmin(w, img.w);
    int compare_height = fmin(h, img.h); 
    int compare_channels = fmin(channels, img.channels);


    uint8_t largest = 0;
    for(uint32_t i=0; i<compare_height; ++i) {
		for(uint32_t j=0; j<compare_width; ++j) {
			for(uint8_t k=0; k<compare_channels; ++k) {
				data[(i*w+j)*channels+k] = BYTE_BOUND(abs(data[(i*w+j)*channels+k] - img.data[(i*img.w+j)*img.channels+k]));
			    largest = fmax(largest, data[(i*w+j)*channels+k]);
            }
		}
	}
    scl = 255/fmax(1,fmax(scl,largest));

    for(int i = 0; i < size; ++i){
        data[i] *=scl;
    }

	return *this;
}
