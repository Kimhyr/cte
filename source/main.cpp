#include "buffer.hpp"
#include "debug/log.hpp"

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
	buffer_T();
	return 0;
}
