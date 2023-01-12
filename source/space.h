#ifndef CTE_SPACE_H
#define CTE_SPACE_H

#include "definitions.h"

namespace CTE {

struct Dimension {
	Nat16 width;
	Nat16 height;
};

struct Coordinate {
	Nat16 row;
	Nat16 column;
};

}

#endif // CTEE_SPACE_H
