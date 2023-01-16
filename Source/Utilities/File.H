#ifndef CTE_File_H
#define CTE_File_H

#include <stdio.h>

#include "Definitions.H"

namespace CTE {

class File {
public:
	enum class Permission {
		READ,
		WRITE,
	};

public:
	File(Permission permissions, const Sym *path);

	~File();

public:
	

private:
	const Sym *path_;
	FILE *file_;
	Nat64 size_;
};

}

#endif // CTE_File_H
