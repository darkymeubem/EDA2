#include "Image.h"
#include <iostream>
int main(int argc, char** argv) {
	Image test1("imgs/teste.png");
	
	Font roboto("Roboto-Regular.ttf", 100);
	test1.overlayText("Hello, World!", roboto, 100, 100);
	test1.write("imgs/output_overlay_text.png");
	return 0;
}
