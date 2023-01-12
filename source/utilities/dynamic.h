#ifndef CTE_UTILITIES_DYNAMIC_H
#define CTE_UTILITIES_DYNAMIC_H

#include <stdlib.h>

#include "../definitions.h"

namespace CTE::Utilities {

template<typename Type_T>
class Dynamic {
public:
	static constexpr
	const Nat64 INITIAL_SPACE = 8;
	
public:
	Dynamic(Nat64 space = Dynamic::INITIAL_SPACE);

	~Dynamic();

public:
	Void put(Type_T datum);

	Void pop();

	Bool exists(Type_T query) const;

	constexpr
	Nat64 getSize() const noexcept {
		return this->back - this->data;
	}

private:
	Type_T *data;
	Type_T *back;
	Nat64 space;

private:
	inline
	Void expand() {
		if ((this->data = realloc(this->data, this->space *= 2)) == nil)
			throw false;
	
	}
};

}

#endif // CTE_UTILITIES_DYNAMIC_H
