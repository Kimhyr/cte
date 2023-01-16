#include "Dynamic.H"

namespace CTE {

template<class Data_T>
Dynamic<Data_T>::Dynamic(Nat64 space)
	: space_(space), data_(new Data_T[space]), back_(this->data_) {}

template<class Data_T>
Dynamic<Data_T>::~Dynamic() {
	delete this->data_;
}

template<class Data_T>
Void Dynamic<Data_T>::put(Data_T datum) {
	if (this->size() + 1 >= this->space_)
		this->expand();
	*this->back_ = datum;
	++this->back_;
}

template<class Data_T>
Void Dynamic<Data_T>::pop() {
	if (this->isEmpty())
		return;
	--this->back_;
	this->back_->~Data_T();
}

}
