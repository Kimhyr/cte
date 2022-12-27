#ifndef CE_SPACE_HPP
#define CE_SPACE_HPP

#include "definitions.hpp"

namespace CE {

struct Dimension {
	Nat16 width;
	Nat16 height;
};

struct Location {
	Nat16 row;
	Nat16 column;
};

}

#endif // CE_SPACE_HPP
