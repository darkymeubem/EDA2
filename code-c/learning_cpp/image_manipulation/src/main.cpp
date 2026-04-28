#include "Image.h"
#include <iostream>
int main(int argc, char** argv) {
	Image test1("imgs/colered.jpg");
	Image test2("imgs/teste.png");

    Image diff = test2;
	diff.diffMap_scale(test1);
	diff.write("imgs/colered_diff.jpg");

	return 0;
}
