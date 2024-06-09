#include <iostream>
#include "compilerv.h"

int main() {
	int bin{};
	bin = 0b11010011;
	std::cout << std::hex << bin << '\n';
	return 0;
}
