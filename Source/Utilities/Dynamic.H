#ifndef CTE_Dynmaic_H
#define CTE_Dynmaic_H

#include "Definitions.H"

#include "Memory.H"

namespace CTE {

template<class Data_T>
class Dynamic {
public:
	static constexpr
	const Nat64 INITIAL_SPACE = 8;

public:
	Dynamic(Nat64 space = INITIAL_SPACE);

	~Dynamic();

public:
	inline constexpr
	Nat64 space()
	const noexcept { return this->space_; }

	inline constexpr
	const Data_T *data()
	noexcept { return this->data_; }

	inline constexpr
	const Data_T *front()
	noexcept { return this->data_; };
	
	inline constexpr
	const Data_T *back()
	noexcept { return this->back_; };

	inline constexpr
	Nat64 size()
	const noexcept { return this->back_ - this->front_; }

	inline constexpr
	Bool isEmpty()
	const noexcept { return this->back_ == this->front_; }

public:
	Void put(Data_T datum);
	
	Void pop();
	
	Void contract() {
		this->space = this->size();
		this->data_ = Memory<Data_T>::reallocate(this->space_, &this->data_,
							 this->space_);
	}

private:
	Nat64 space_;
	Data_T *data_;
	Data_T *back_;

private:
	Void expand() {
		this->space *= 2;
		this->data_ = Memory<Data_T>::reallocate(this->size(), &this->data_,
							 this->space_);
	}
};

}

#endif // CTE_Dynmaic_H
