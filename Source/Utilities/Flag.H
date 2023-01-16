#ifndef CTE_Flag_H
#define CTE_Flag_H

#include "Definitions.H"

namespace CTE {

template<class Type_T>
constexpr Type_T operator |(Type_T a, Type_T b) {
	return (Type_T)((Nat)a | (Nat)b);
}

template<class Type_T>
constexpr Type_T operator ~(Type_T a) {
	return (Type_T)(~(Nat)a);
}

}

#endif // CTE_Flag_H
