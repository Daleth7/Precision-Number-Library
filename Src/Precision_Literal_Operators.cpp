#include "Precision_Literal_Operators.h"

#include <sstream>

inline namespace Precision{

    Int operator"" _Precision_Int(char const *const raw, std::size_t)
        {return Int(Int::str_type(raw));}
    Int operator"" _Precision_Int_E(char const *const raw, std::size_t)
    {
        using str_type = Int::str_type;
        const str_type convert(raw);
        Int::size_type e_pos(convert.find('E'));
        if(e_pos == str_type::npos) e_pos = convert.find('e');
        if(e_pos == str_type::npos)
            return Int(str_type(raw));
            //Negative exponent
        if(convert[e_pos+1] == '-') return 0;

        str_type base(convert.substr(0, e_pos));
        Int::size_type exp(0);
        std::stringstream catalyst(convert.substr(e_pos+1));
        catalyst >> exp;
        Int::size_type point(base.find('.'));
        if(point == str_type::npos || point == base.size()-1){
            if(point == convert.size()-1)
                base.erase(point, 1);
            base.insert(base.size(), exp, '0');
            return base;
        }

        base.erase(point, 1);
        while(exp > 0 && point < base.size())
            --exp, ++point;
        if(point < base.size())
            base.erase(point);
        if(exp > 0)
            base.insert(base.size(), exp, '0');
        
        return base;
    }
    Int operator"" _Precision_Int(unsigned long long cooked)
        {return Int(cooked);}

    Float operator"" _Precision_Float(
        char const *const raw,
        std::size_t
    ){return Float(raw);}
    Float operator"" _Precision_Float_E(
        char const *const raw,
        std::size_t
    ){
        using str_type = Float::str_type;
        const str_type convert(raw);
        Float::size_type e_pos(convert.find('E'));
        if(e_pos == str_type::npos) e_pos = convert.find('e');
        if(e_pos == str_type::npos)
            return Float(str_type(raw));

        Float toreturn(convert.substr(0, e_pos));
        long long int exp(0);
        std::istringstream catalyst(convert.substr(e_pos+1));
        catalyst >> exp;
        toreturn.shift(exp);

        return toreturn;

    }
    Float operator"" _Precision_Float(long double cooked)
        {return Float(cooked);}
    Float operator"" _Precision_Float(unsigned long long cooked)
        {return Float(cooked);}


    UInt operator"" _Precision_UInt(
        char const *const raw,
        std::size_t
    ){return UInt::str_type(raw);}

    UInt operator"" _Precision_UInt_E(
        char const *const raw,
        std::size_t
    ){return operator"" _Precision_Int_E(raw, 0);}

    UInt operator"" _Precision_UInt
        (unsigned long long cooked)
    {return cooked;}


    UFloat operator"" _Precision_UFloat(
        char const *const raw,
        std::size_t
    ){return UFloat::str_type(raw);}

    UFloat operator"" _Precision_UFloat_E(
        char const *const raw,
        std::size_t
    ){return UFloat(operator"" _Precision_Float_E(raw, 0));}

    UFloat operator"" _Precision_UFloat
        (unsigned long long cooked)
    {return UFloat(cooked);}

    UFloat operator"" _Precision_UFloat
        (long double cooked)
    {return UFloat(cooked);}

}