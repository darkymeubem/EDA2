#include "Image.h"
#include <iostream>
int main(int argc, char** argv) {
    Image test("teste.png");
    test.write("test.jpg");

    Image copy = test;

    for(int i = 0; i < copy.w*copy.channels; i++){
        copy.data[i] = 255;
    }

    copy.write("test_copy.png");
    Image blank(100,100,3);
    for(int i = 0; i < blank.w*blank.channels*blank.h; i++){
        blank.data[i] = 255 - i*255/(blank.w*blank.channels*blank.h);
    }
    blank.write("blank.jpg");
	return 0;
}