#include "Image.h"
#include <iostream>
int main(int argc, char** argv) {
	Image test1("imgs/teste.png");
	Image logo("imgs/Coca-Cola_logo.png");

	test1.overlay(logo, -50, 20);
	test1.write("imgs/output_overlay.png");
	return 0;
}
