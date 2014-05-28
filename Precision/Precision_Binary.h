#ifndef PRECISION_BINARY_SPECIALIZATION
#define PRECISION_BINARY_SPECIALIZATION

#include "General_Base/Precision_Int_General_Base.h"
#include <limits>

/*
    Precision::Binary is a specialization designed for maximum
    memory efficiency at the cost of speed.
*/

namespace Precision{
    namespace Binary{
        class Int{
            public:
        //Type aliases
            //byte_type determines how conservative the type shall be. Despite
            //  the best efforts of the implementation, at least one bit shall
            //  be reserved for sign and one bit shall be reserved for overflow.
            //  e.g. for a 16 bit instantiation, only 14 bits will be used.
                using byte_type     = std::int_fast16_t;
                using bitset_type   = General_Base::Int<
    //Only use unsigned char because basic_string<void> cannot be instantiated.
                                        unsigned char, nullptr,
                                        byte_type,
            //Calculate the quarter range, or two bits below the unsigned maximum.
                                        ((std::numeric_limits
                                            <byte_type>::max()>>1)+1),
                                        nullptr
                                    >;
                using str_type      = std::string;
                using lli           = bitset_type::lli;
                using ld            = bitset_type::ld;
                using image_type    = char;
                using digit_type    = bitset_type::digit_type;
                using diglist_type  = bitset_type::diglist_type;
                using digit_10_type = bitset_type::digit_10_type;
                using sign_type     = bitset_type::sign_type;
                using size_type     = bitset_type::size_type;

        //Arithmetic operators
                Int& operator+=(const Int& s);
                Int& operator-=(const Int& s);
                Int& operator*=(const Int& s);
                Int& operator/=(const Int& s);
                Int& operator%=(const Int& s);
                Int& operator--();
                Int operator--(int);
                Int& operator++();
                Int operator++(int);

        //Bitwise operators
                Int& operator&=(const Int&);
                Int& operator|=(const Int&);
                Int& operator^=(const Int&);
                Int& operator<<=(const Int&);
                Int& operator>>=(const Int&);

        //Logical Operators
                Int logical_and(const Int&)const;
                Int logical_or(const Int&)const;
                Int logical_xor(const Int&)const;
                Int logical_inversion()const;
                Int logical_shift(lli)const;
                Int logical_shift_left(size_type)const;
                Int logical_shift_right(size_type)const;

        //Read-only functions
                sign_type sign()const;
                str_type str()const;
            //Set the precision through parameter
                str_type sci_note(size_type=k_display_prec)const;
                str_type sci_note_w_spaces(size_type=k_display_prec)const;
                Int magnitude()const;
                size_type count_digits()const;
                short compare(const Int&)const;
                Int operator-()const;
                Int operator~()const;
                bool even()const;
                bool odd()const;
                bool positive()const;
                bool negative()const;
                image_type digit(size_type)const;
                digit_10_type digit_10(size_type)const;

                static constexpr digit_10_type base();

        //Other modifiers
                void shift(lli);
                void shift_left(size_type);
                void shift_right(size_type);
                void sign(sign_type);
                void negate();
                void swap(Int&);

        //Constructors and destructor
                Int(lli = 0);
                Int(const str_type&);
                Int(const diglist_type&, sign_type);
                Int(const bitset_type&);

                Int(const Int&)             =default;
                Int(Int&&)                  =default;
                Int& operator=(const Int&)  =default;
                Int& operator=(Int&&)       =default;
                ~Int()                      =default;

            protected:
                Int& bitwise_operation(const Int&, unsigned short);

            private:
                //The dynamic bitset
                bitset_type m_bitset;

                static constexpr digit_10_type k_bits = sizeof(byte_type)*8-2;
        };

        Int operator+(Int, const Int&);
        Int operator-(Int, const Int&);
        Int operator*(Int, const Int&);
        Int operator/(Int, const Int&);
        Int operator%(Int, const Int&);

        Int operator&(Int, const Int&);
        Int operator|(Int, const Int&);
        Int operator^(Int, const Int&);
        Int operator>>(Int, const Int&);
        Int operator<<(Int, const Int&);

        bool operator==(const Int&, const Int&);
        bool operator!=(const Int&, const Int&);
        bool operator>=(const Int&, const Int&);
        bool operator<=(const Int&, const Int&);
        bool operator>(const Int&, const Int&);
        bool operator<(const Int&, const Int&);
        bool operator!(const Int&);
    }
}

void swap(Precision::Binary::Int&, Precision::Binary::Int&);

#endif