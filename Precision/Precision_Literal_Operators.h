#ifndef PRECISION_LITERALS_DEFINITIONS_H__
#define PRECISION_LITERALS_DEFINITIONS_H__

#include "Precision_Default.h"

inline namespace Precision{

    Int operator"" _P_Int(char const *const, std::size_t);
    Int operator"" _P_Int_E(char const *const, std::size_t);
    Int operator"" _P_Int(unsigned long long);


    Float operator"" _P_Float(char const *const, std::size_t);
    Float operator"" _P_Float_E(char const *const, std::size_t);
    Float operator"" _P_Float(long double);
    Float operator"" _P_Float(unsigned long long);


    inline UInt operator"" _P_UInt(char const *const, std::size_t);
    inline UInt operator"" _P_UInt_E(char const *const, std::size_t);
    inline UInt operator"" _P_UInt(unsigned long long);


    inline UFloat operator"" _P_UFloat(char const *const, std::size_t);
    inline UFloat operator"" _P_UFloat_E(char const *const, std::size_t);
    inline UFloat operator"" _P_UFloat(unsigned long long);
    inline UFloat operator"" _P_UFloat(long double);

}

#endif