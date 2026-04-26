#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include "Image.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

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