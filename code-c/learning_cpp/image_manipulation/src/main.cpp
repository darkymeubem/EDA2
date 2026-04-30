#include "Image.h"
#include <iostream>
int main(int argc, char** argv) {
	Image test1("imgs/teste.png");
	Image test2 = test1;
	test1.flipX();
	test1.write("imgs/teste_flipX.png");

	test2.flipY();
	test2.write("imgs/teste_flipY.png");
	return 0;
}
