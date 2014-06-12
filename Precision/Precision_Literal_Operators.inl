inline namespace Precision{

    inline Int operator"" _p_int(char const *const raw, std::size_t)
        {return Int(Int::str_type(raw));}

    inline Int operator"" _p_int(unsigned long long cooked)
        {return Int(cooked);}

    inline Float operator"" _p_float(char const *const raw, std::size_t num)
        {return Float(raw, num);}

    inline Float operator"" _p_float(long double cooked)
        {return Float(cooked);}

    inline Float operator"" _p_float(unsigned long long cooked)
        {return Float(cooked);}


    inline UInt operator"" _p_uint(char const *const raw, std::size_t)
        {return UInt::str_type(raw);}

    inline UInt operator"" _p_uint(unsigned long long cooked)
        {return cooked;}


    inline UFloat operator"" _p_ufloat(char const *const raw, std::size_t)
        {return UFloat::str_type(raw);}

    inline UFloat operator"" _p_ufloat(unsigned long long cooked)
        {return UFloat(cooked);}

    inline UFloat operator"" _p_ufloat(long double cooked)
        {return UFloat(cooked);}
}