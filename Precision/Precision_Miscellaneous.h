#ifndef PRECISION_MISCELLANEOUS_FUNCTIONS_H___
#define PRECISION_MISCELLANEOUS_FUNCTIONS_H___

#include "Precision_Default.h"

namespace Precision{
    template <typename Integer_Type>
    bool palindrome(const Integer_Type&);

    std::string Num_to_Words(Int);
}

#include "Impl/Precision_Miscellaneous.inl"

#endif