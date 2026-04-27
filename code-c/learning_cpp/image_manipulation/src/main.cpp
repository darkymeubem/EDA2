#include "Image.h"
#include <iostream>
int main(int argc, char** argv) {
    Image test("teste.png");
    test.encodeMessage("Hello, World!");
    test.write("teste_encoded.png");
    char buffer[256] ={0};
    size_t len = 0;
    test.decodeMessage(buffer, &len);

    printf("Message: %s (%zu bits)\n", buffer, len);
   
	return 0;
}