#ifndef _DEFINITIONS_HPP
#define _DEFINITIONS_HPP

#define nil nullptr

using Void = void;

using Bool = bool;

using Sym = char;

using Nat = unsigned int;
using Nat8 = unsigned char;
using Nat16 = unsigned short int;
using Nat32 = unsigned int;

template <typename Type_T>
inline constexpr Type_T operator|(Type_T a, Type_T b) {
        return Type_T(static_cast<Nat>(a) | static_cast<Nat>(b));
}

template <typename Type_T>
inline constexpr Type_T operator~(Type_T a) {
        return Type_T(~static_cast<Nat>(a));
}


#endif // _DEFINITIONS_HPP
