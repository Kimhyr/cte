#ifndef CTE_Space_H
#define CTE_Space_H

#include "Definitions.H"

namespace CTE {

struct Dimension {
	Nat16 width;
	Nat16 height;
};

struct Position {
	Nat64 row;
	Nat64 column;
};

struct Span {
	Nat64 start;
	Nat64 end;
};

}

#endif // CTE_Space_H
