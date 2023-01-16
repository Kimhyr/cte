#ifndef CTE_Memory_H
#define CTE_Memory_H

#include "Definitions.H"

namespace CTE {

template<class Data_T>
class Memory {
public:
	static
	Data_T *reallocate(Nat64 size, Data_T **data, Nat64 space);
};

}

#endif // CTE_Memory_H
