#include "Image.h"
#include <iostream>
int main(int argc, char** argv) {
	Image test1("imgs/colered.jpg");
	
	double ker[9] = {
		1/16., 2/16., 1/16.,
		2/16., 4/16., 2/16.,
		1/16., 2/16., 1/16.
	};

	Image a = test1;
	Image b = test1;
	Image c = test1;
	a.std_convolve_clamp_to_0(0, 3, 3, ker, 1, 1);
	a.std_convolve_clamp_to_0(1, 3, 3, ker, 1, 1);
	a.std_convolve_clamp_to_0(2, 3, 3, ker, 1, 1);


	a.write("imgs/blurred.jpg");

	b.std_convolve_clamp_to_border(0, 3, 3, ker, 1, 1);
	b.std_convolve_clamp_to_border(1, 3, 3, ker, 1, 1);
	b.std_convolve_clamp_to_border(2, 3, 3, ker, 1, 1);


	b.write("imgs/blurred1.jpg");

	c.std_convolve_clamp_to_cycle(0, 3, 3, ker, 1, 1);
	c.std_convolve_clamp_to_cycle(1, 3, 3, ker, 1, 1);
	c.std_convolve_clamp_to_cycle(2, 3, 3, ker, 1, 1);

	c.write("imgs/blurred2.jpg");

	Image diff = a;
	diff.diffMap_scale(c);
	diff.write("imgs/diff.jpg");
	return 0;
}
