#include "buffer.hpp"

#include <stdio.h>

using namespace CE;

Void buffer_T() {
	Buffer::Flag flags = Buffer::Flag::SAVEABLE | Buffer::Flag::WRITEABLE;
	try {
		Buffer buffer(flags, "/home/k/projects/ce/tests/test.txt");
		buffer.printData();
	} catch (Int e) {
		printf("%i\n", e);
	}
}

Int main() {
	// LOG("Hello, World!");
	// buffer_T();
	for (Int i = 0; i < 10;)
                printf("%i\n", i++);
        return 0;
}
