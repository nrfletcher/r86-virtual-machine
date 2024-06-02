#include <iostream>

int generator(int a, int b);

int main() {
	std::cout << generator(4, 4);
	std::cout << "\n";
	return 0;
}

int generator(int a, int b) {
	return b + a;
}
