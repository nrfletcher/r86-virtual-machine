#include <stdio.h>

typedef void (*functiontype)();

void func(void (*f)()) {
	(*f)();
}

void printer() {
	printf("Hello \n");
}

// Argument: a function which returns void, and has 2 args of:
// arg1: function pointer
void multifunc(void (*f)(int (*a)(int), int (*b)(int))) {
	void *p = f;
	int x = (*p)(returner, returner);
	printf("%d \n", x);
}

int adder(int (*a)(int), int (*b)(int)) {
	return x + y;
}

int returner(int x) {
	return x;
}

int main() {
	functiontype fun = &func;
	fun(printer);
	functiontype multi = &multifunc;
	multi(&adder);
	return 0;
}
