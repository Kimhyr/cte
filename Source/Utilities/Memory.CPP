#include "Memory.H"

namespace CTE {

template<class Data_T>
Data_T *Memory<Data_T>::reallocate(Nat64 size, Data_T **data, Nat64 space) {
	auto mlock = new Data_T[space];
	for (Nat64 i = 0; i < size; ++i)
		mlock[i] = (*data)[i];
	delete *data;
	*data = mlock;
}

}
