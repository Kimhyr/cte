#ifndef CTE_SPACE_HPP
#define CTE_SPACE_HPP

#include "definitions.hpp"

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

#endif // CTEE_SPACE_HPP
