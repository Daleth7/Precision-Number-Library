#ifndef PRECISION_BINARY_BASE_SPECIALIZATION_H___
#define PRECISION_BINARY_BASE_SPECIALIZATION_H___

#include "Precision_Int_General_Base.h"
#include "Precision_UInt_General_Base.h"
#include "Precision_Shared_Pack.h"

#include <limits>
#include <cstdint>

#define SPEC_PARAMS_ Base36::image::type, Base36::image::glyphs, \
    Binary::block_type, 2, Constant::symbols, default_container_type, SignClass

#define INT_INST_ Int<SPEC_PARAMS_>
#define UINT_INST_ UInt<SPEC_PARAMS_>

namespace Precision{
    namespace Binary{
        using block_type = std::int_fast16_t;
    }
    namespace General_Base{
        template <>
        class Int<SPEC_PARAMS_>{
            public:
        //Type aliases
            //byte_type determines how conservative the type shall be.
            //  Despite the best efforts of the implementation, at least
            //  one bit shall be reserved for sign and one bit shall be
            //  reserved for overflow. e.g. for a 16 bit instantiation,
            //  only 14 bits will be used.
                using byte_type     = Binary::block_type;
                using bitset_type   = General_Base::Int<
    //Only use unsigned char because basic_string<void> cannot be instantiated.
                                        unsigned char, nullptr,
                                        byte_type,
            //Calculate the quarter range, or two bits below the unsigned maximum.
                                        ((std::numeric_limits
                                            <byte_type>::max()>>1)+1),
                                        nullptr,
                                        default_container_type,
                                        SignClass
                                    >;
                using str_type      = std::basic_string<Base36::image::type>;
                using lli           = typename bitset_type::lli;
                using ld            = typename bitset_type::ld;
                using image_type    = Base36::image::type;
                using digit_type    = typename bitset_type::digit_type;
                using diglist_type  = typename bitset_type::diglist_type;
                using digit_10_type = typename bitset_type::digit_10_type;
                using sign_type     = typename bitset_type::sign_type;
                using size_type     = typename bitset_type::size_type;

        //Arithmetic operators
                INT_INST_& operator+=(const INT_INST_& s)
                    {return m_bitset += s.m_bitset, *this;}

                INT_INST_& operator-=(const INT_INST_& s)
                    {return m_bitset -= s.m_bitset, *this;}

                INT_INST_& operator*=(const INT_INST_& s)
                    {return m_bitset *= s.m_bitset, *this;}

                INT_INST_& operator/=(const INT_INST_& s)
                    {return m_bitset /= s.m_bitset, *this;}

                INT_INST_& operator%=(const INT_INST_& s)
                    {return m_bitset %= s.m_bitset, *this;}

                INT_INST_& operator--()
                    {return --m_bitset, *this;}

                INT_INST_ operator--(int)
                    {return INT_INST_(m_bitset--);}

                INT_INST_& operator++()
                    {return ++m_bitset, *this;}

                INT_INST_ operator++(int)
                    {return INT_INST_(m_bitset++);}

        //Bitwise operators
                INT_INST_& operator&=(const INT_INST_& s)
                    {return bitwise_operation(s, 1);}

                INT_INST_& operator|=(const INT_INST_& s)
                    {return bitwise_operation(s, 2);}

                INT_INST_& operator^=(const INT_INST_& s)
                    {return bitwise_operation(s, 3);}

                INT_INST_& operator<<=(const INT_INST_& s)
                    {return m_bitset <<= s.m_bitset, *this;}

                INT_INST_& operator>>=(const INT_INST_& s)
                    {return m_bitset >>= s.m_bitset, *this;}

        //Logical Operators
                INT_INST_ logical_and(const INT_INST_& s)const
                    {return INT_INST_(*this).bitwise_operation(s, 1);}

                INT_INST_ logical_or(const INT_INST_& s)const
                    {return INT_INST_(*this).bitwise_operation(s, 2);}

                INT_INST_ logical_xor(const INT_INST_& s)const
                    {return INT_INST_(*this).bitwise_operation(s, 3);}

                INT_INST_ logical_inversion()const
                    {return INT_INST_(*this).bitwise_operation(*this, 4);}

                INT_INST_ logical_shift(lli e)const
                    {return e > 0 ? logical_shift_left(e)
                        : logical_shift_right(-e);}

                INT_INST_ logical_shift_left(size_type e)const
                    {return INT_INST_(m_bitset
                        * Math::exponentiate(bitset_type(2), e));}

                INT_INST_ logical_shift_right(size_type e)const
                    {return INT_INST_(m_bitset
                        / Math::exponentiate(bitset_type(2), e));}


        //Read-only functions
                sign_type sign()const
                    {return m_bitset.sign();}

                str_type str()const{
                    const size_type lim(this->count_digits());
                    if(lim == 0)
                        return str_type(1, Constant::symbols[0])
                            + str_type(1, Base36::image::glyphs[0]);
                    str_type toreturn(lim+1, Base36::image::glyphs[0]);
                    toreturn.front() = (m_bitset.positive()
                        ? Constant::symbols[0] : Constant::symbols[1]);
                    for(size_type i(0); i < lim; ++i)
                        toreturn[i+1] = (this->digit(lim-i-1));

                    return toreturn;
                }

            //Set the precision through parameter
                str_type sci_note(size_type prec= k_display_prec)const{
                    if(*this == INT_INST_(0))
                        return str_type(1, Constant::symbols[0])
                            + str_type(1, Base36::image::glyphs[0]);
                    else if(this->count_digits() == 1){
                        str_type toreturn(this->str());
                        toreturn.push_back(Constant::symbols[3]);
                        toreturn.push_back(Base36::image::glyphs[1]);
                        return toreturn;
                    }

                    str_type toreturn(this->str());
                    size_type exp(toreturn.size() - 2);
                    toreturn.insert(2, 1, Constant::symbols[2]);
                    if(prec < exp)
                        toreturn.erase(3+prec);
                    if(toreturn.back() == Constant::symbols[2])
                        toreturn.pop_back();
                    toreturn.push_back(Constant::symbols[3]);
                    toreturn += INT_INST_(exp).str().substr(1);

                    return toreturn;
                }

                str_type sci_note_w_spaces(size_type prec=k_display_prec)const{
                    str_type toreturn(this->sci_note(prec));
                    if(*this == INT_INST_(0)) return toreturn;
                        //Insert space after the sign
                    toreturn.insert(1, 1, Constant::symbols[4]);
                    toreturn.insert(toreturn.find(Constant::symbols[3]),
                        1, Constant::symbols[4]);
                    toreturn.insert(toreturn.find(Constant::symbols[3])+1,
                        1, Constant::symbols[4]);
                    return toreturn;
                }

                INT_INST_ magnitude()const
                    {return m_bitset.magnitude();}

                size_type count_digits()const{
                    size_type toreturn((m_bitset.count_digits()-1)*k_bits);
                    digit_10_type block(m_bitset.digit_10
                        (m_bitset.count_digits()-1));
                    while(block){
                        ++toreturn;
                        block >>= 1;
                    }
                    return toreturn;
                }

                short compare(const INT_INST_& s)const
                    {return m_bitset.compare(s.m_bitset);}

                INT_INST_ operator-()const
                    {return -m_bitset;}

                INT_INST_ operator~()const
                    {return INT_INST_(*this).bitwise_operation(*this, 4);}

                bool even()const
                    {return m_bitset.even();}

                bool odd()const
                    {return m_bitset.odd();}

                bool positive()const
                    {return m_bitset.positive();}

                bool negative()const
                    {return m_bitset.negative();}

                image_type digit(size_type i)const
                    {return Base36::image::glyphs[0] + this->digit_10(i);}

                digit_10_type digit_10(size_type i)const{
                    return
                        (
                            m_bitset.digit_10(i/k_bits)
                            & (digit_10_type(1)<<(i%k_bits))
                        ) > 0
                    ;
                }

                static constexpr digit_10_type base()
                    {return 2;}

        //Other modifiers
                void shift(lli e)
                    {e > 0 ? shift_left(e) : shift_right(-e);}

                void shift_left(size_type e)
                    {m_bitset*=Math::exponentiate(bitset_type(2), e);}

                void shift_right(size_type e)
                    {m_bitset/=Math::exponentiate(bitset_type(2), e);}

                void sign(sign_type s)
                    {m_bitset.sign(s);}

                void negate()
                    {m_bitset.negate();}

                void swap(INT_INST_& s)
                    {m_bitset.swap(s.m_bitset);}

            //Shift by whole byte_type instead
                void shift_byte(lli e)
                    {m_bitset.shift(e);}

                void shift_left_byte(size_type e)
                    {m_bitset.shift_left(e);}

                void shift_right_byte(size_type e)
                    {m_bitset.shift_right(e);}

        //Constructors and destructor
                Int(lli newnumber = 0)
                    : m_bitset(newnumber)
                {}

                Int(const str_type& newnumber)
                    : m_bitset(0)
                {
                    bitset_type twos(1);
                    const size_type min(
                        newnumber.front()==Constant::symbols[1]
                        || newnumber.front()==Constant::symbols[0]
                        ? 1u : 0u
                    );
                    for(
                        size_type i(newnumber.size());
                        i > min;
                        --i, twos *= 2
                    ){
                        m_bitset += bitset_type(newnumber[i-1]
                            - Base36::image::glyphs[0])*twos;
                    }
                    m_bitset.sign(newnumber.front()
                        == Constant::symbols[1] ? -1 : 1);
                }

                Int(const diglist_type& n, sign_type s)
                    : m_bitset(n, s)
                {}

                Int(const bitset_type& newnumber)
                    : m_bitset(newnumber)
                {}

                Int(const INT_INST_&)                   = default;
                Int(INT_INST_&&)                        = default;
                INT_INST_& operator=(const INT_INST_&)  = default;
                INT_INST_& operator=(INT_INST_&&)       = default;
                ~Int()                                  = default;

            protected:
                INT_INST_& bitwise_operation
                    (const INT_INST_& s, unsigned short condition){
                    bitset_type new_set(0), tens(1);
                    const size_type lim
                        = std::max(m_bitset.count_digits()
                        , s.m_bitset.count_digits())
                    ;
                    auto count_bits = [](digit_10_type b)
                        {size_type toreturn(0);if(!b)return 0u;
                        do{++toreturn;}while(b>>=1);return toreturn;};
                    for(
                        size_type i(0);
                        i < lim;
                        ++i, tens.shift_left(1)
                    ){
                        digit_10_type
                            lop =
                                (i >= m_bitset.count_digits()
                                ? 0 : m_bitset.digit_10(i))
                            ,
                            rop = (i >= s.m_bitset.count_digits()
                                || condition == 4
                                ? 0 : s.m_bitset.digit_10(i))
                        ;
                        switch(condition){
                            case 1:
                                new_set += tens*bitset_type(lop & rop);
                                break;
                            case 2:
                                new_set += tens*bitset_type(lop | rop);
                                break;
                            case 3:
                                new_set += tens*bitset_type(lop ^ rop);
                                break;
                            case 4:
                                new_set += tens
                                    * bitset_type(
                                        (~lop)
                                        & ((1<<(i!=lim-1 ? k_bits
                                        : count_bits(lop)))-1)
                                    );
                                break;
                            default:
                                throw condition; //Should never happen
                        }
                    }
                    bool to_neg(false);
                    switch(condition){
                        case 1:
                            to_neg = m_bitset.negative()
                                & s.m_bitset.negative();
                            break;
                        case 2:
                            to_neg = m_bitset.negative()
                                | s.m_bitset.negative();
                            break;
                        case 3:
                            to_neg = m_bitset.negative()
                                ^ s.m_bitset.negative();
                            break;
                        case 4:
                            to_neg = !m_bitset.negative();
                            break;
                        default:
                                throw condition; //Should never happen
                    }
                    m_bitset = std::move(new_set);
                    m_bitset.sign(!to_neg-1);
                    return *this;
                }

            private:
                //The raw dynamic bitset
                bitset_type m_bitset;

                static constexpr digit_10_type k_bits = sizeof(byte_type)*8-2;
        };

        template <>
        class UInt<SPEC_PARAMS_>{
            public:
        //Type aliases
                using Signed_Int    = Int<SPEC_PARAMS_>;
                using byte_type     = typename Signed_Int::byte_type;
                using bitset_type   = typename Signed_Int::bitset_type;
                using str_type      = typename Signed_Int::str_type;
                using ulli          = unsigned long long int;
                using ld            = typename Signed_Int::ld;
                using lli           = typename Signed_Int::lli;
                using image_type    = typename Signed_Int::image_type;
                using diglist_type  = typename Signed_Int::diglist_type;
                using digit_type    = typename Signed_Int::digit_type;
                using digit_10_type = typename Signed_Int::digit_10_type;
                using sign_type     = typename Signed_Int::sign_type;
                using size_type     = typename Signed_Int::size_type;
        //Arithmetic operators
                UINT_INST_& operator+=(const UINT_INST_& rhs)
                    {return m_base += rhs.m_base, *this;}

                UINT_INST_& operator-=(const UINT_INST_& rhs){
                    m_base -= rhs.m_base;
                    if(m_base.negative())
                        m_base = 0;
                    return *this;
                }

                UINT_INST_& operator*=(const UINT_INST_& rhs)
                    {return m_base *= rhs.m_base, *this;}

                UINT_INST_& operator/=(const UINT_INST_& rhs)
                    {return m_base /= rhs.m_base, *this;}

                UINT_INST_& operator%=(const UINT_INST_& rhs)
                    {return m_base %= rhs.m_base, *this;}

                UINT_INST_& operator--()
                    {return (*this -= 1);}

                UINT_INST_ operator--(int)
                    {return (*this -= 1) + 1;}

                UINT_INST_& operator++()
                    {return ++m_base, *this;}

                UINT_INST_ operator++(int)
                    {return m_base++;}

        //Bitwise operators
                UINT_INST_& operator&=(const UINT_INST_& rhs)
                    {return m_base &= rhs.m_base, *this;}

                UINT_INST_& operator|=(const UINT_INST_& rhs)
                    {return m_base |= rhs.m_base, *this;}

                UINT_INST_& operator^=(const UINT_INST_& rhs)
                    {return m_base ^= rhs.m_base, *this;}

                UINT_INST_& operator<<=(const UINT_INST_& rhs)
                    {return m_base <<= rhs.m_base, *this;}

                UINT_INST_& operator>>=(const UINT_INST_& rhs)
                    {return m_base >>= rhs.m_base, *this;}

        //Logical Operators
                UINT_INST_ logical_and(const UINT_INST_& s)const
                    {return UINT_INST_(m_base.logical_and(s.m_base));}

                UINT_INST_ logical_or(const UINT_INST_& s)const
                    {return UINT_INST_(m_base.logical_or(s.m_base));}

                UINT_INST_ logical_xor(const UINT_INST_& s)const
                    {return UINT_INST_(m_base.logical_xor(s.m_base));}

                Signed_Int logical_inversion()const
                    {return m_base.logical_inversion();}

                UINT_INST_ logical_shift(lli e)const
                    {return UINT_INST_(m_base.logical_shift(e));}

                UINT_INST_ logical_shift_left(size_type e)const
                    {return UINT_INST_(m_base.logical_shift_left(e));}

                UINT_INST_ logical_shift_right(size_type e)const
                    {return UINT_INST_(m_base.logical_shift_right(e));}

        //Read-only functions
                sign_type sign()const
                    {return 1;}

                str_type str()const
                    {return m_base.str();}

                bool even()const
                    {return m_base.even();}

                bool odd()const
                    {return m_base.odd();}

                bool positive()const
                    {return true;}

                bool negative()const
                    {return false;}

            //Set the precision through parameter
                str_type sci_note(size_type inPrec = k_display_prec)const
                    {return m_base.sci_note(inPrec);}

                str_type
                    sci_note_w_spaces(size_type inPrec = k_display_prec)const
                {return m_base.sci_note_w_spaces(inPrec);}

                size_type count_digits()const
                    {return m_base.count_digits();}

                short compare(const UINT_INST_& s)const
                    {return m_base.compare(s.m_base);}

                const UINT_INST_& magnitude()const
                    {return *this;}

                const Signed_Int& get_signed()const
                    {return m_base;}

                Signed_Int operator-()const
                    {return -m_base;}

                    //Does not work for ~0
                Signed_Int operator~()const
                    {return Signed_Int(~m_base);}

                static constexpr digit_10_type base()
                    {return Signed_Int::base();}

                static constexpr digit_type digit0()
                    {return Signed_Int::digit0();}

        //Other modifiers
                void sign(sign_type){}
                    //Multiplies integer by a power of 2
                void shift(lli tens_exp)
                    {m_base.shift(tens_exp);}

                void shift_left(size_type e)
                    {m_base.shift_left(e);}

                void shift_right(size_type e)
                    {m_base.shift_right(e);}

                    //Shift by byte_type instead
                void shift_byte(lli tens_exp)
                    {m_base.shift_byte(tens_exp);}

                void shift_left_byte(size_type e)
                    {m_base.shift_left_byte(e);}

                void shift_right_byte(size_type e)
                    {m_base.shift_right_byte(e);}

                void swap(UINT_INST_& s)
                    {m_base.swap(s.m_base);}

        //Conversion operators
                explicit operator Signed_Int()
                    {return m_base;}

        //Constructors and destructor
                UInt(ulli inInt = 0)
                    : m_base(inInt)
                {}

                UInt(const str_type& inImage)
                    : m_base(inImage)
                {m_base.sign(1);}

                UInt(const Signed_Int& inInt)
                    : m_base(inInt)
                {m_base.sign(1);}

                UInt(Signed_Int&& inInt)
                    : m_base(std::move(inInt))
                {m_base.sign(1);}

                UInt(const UINT_INST_&)            =default;
                UInt(UINT_INST_&&)                 =default;
                UInt& operator=(const UINT_INST_&) =default;
                UInt& operator=(UINT_INST_&&)      =default;
                ~UInt()                            =default;
            private:
                Signed_Int   m_base;
        };
    }
}

#undef INT_INST_
#undef UINT_INST_

#endif