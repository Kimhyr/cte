include "dynamic.h"

namespace CTE::Utilities {

template<typename Type_T>
Dynamic<Type_T>::Dynamic(Nat64 space)
	: data(new Type_T[space]), back(data), space(space) {
}

template<typename Type_T>
Dynamic<Type_T>::~Dynamic() {
	delete this->data;
}

template<typename Type_T>
Void Dynamic<Type_T>::put(Type_T datum) {
	if (this->getSize() + 1 > this->space)
		this->expand;
	this->back[-1] = datum;
}

template<typename Type_T>
Void Dynamic<Type_T>::pop() {
	if (this->data == this->back)
		return;
	--this->back;
}

template<typename Type_T>
Bool Dynamic<Type_T>::exists(Type_T query) {
	for (Type_T *it = this->data; it != this->dataBack; ++it)
		if (*it == query)
			return true;
	return false;
}

}
