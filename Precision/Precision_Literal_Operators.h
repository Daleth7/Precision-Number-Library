#ifndef PRECISION_LITERALS_DEFINITIONS_H__
#define PRECISION_LITERALS_DEFINITIONS_H__

#include "Precision_Default.h"

inline namespace Precision{

    Int operator"" _Precision_Int(char const *const, std::size_t);
    Int operator"" _Precision_Int_E(char const *const, std::size_t);
    Int operator"" _Precision_Int(unsigned long long);


    Float operator"" _Precision_Float(char const *const, std::size_t);
    Float operator"" _Precision_Float_E(char const *const, std::size_t);
    Float operator"" _Precision_Float(long double);
    Float operator"" _Precision_Float(unsigned long long);


    inline UInt operator"" _Precision_UInt(char const *const, std::size_t);
    inline UInt operator"" _Precision_UInt_E(char const *const, std::size_t);
    inline UInt operator"" _Precision_UInt(unsigned long long);


    inline UFloat operator"" _Precision_UFloat(char const *const, std::size_t);
    inline UFloat operator"" _Precision_UFloat_E(char const *const, std::size_t);
    inline UFloat operator"" _Precision_UFloat(unsigned long long);
    inline UFloat operator"" _Precision_UFloat(long double);

}

#endif