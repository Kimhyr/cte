#ifndef CE_DEFINITIONS_HPP
#define CE_DEFINITIONS_HPP

#define nil nullptr

namespace CE {

using Void = void;

using Bool = bool;

using Sym = char;

using Int = int;

using Nat = unsigned int;
using Nat8 = unsigned char;
using Nat16 = unsigned short int;
using Nat32 = unsigned int;
using Nat64 = unsigned long int;

template <typename Type_T>
inline constexpr Type_T operator|(Type_T a, Type_T b) {
        return Type_T(static_cast<Nat>(a) | static_cast<Nat>(b));
}

template <typename Type_T>
inline constexpr Type_T operator~(Type_T a) {
        return Type_T(~static_cast<Nat>(a));
}

}

#endif // CE_DEFINITIONS_HPP
