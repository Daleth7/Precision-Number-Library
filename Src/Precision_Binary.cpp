#include "Precision_Binary.h"
#include "General_Base/Impl/Precision_Math_Shared_Functions.h"

#include <sstream>
#include <algorithm>

namespace Precision{
    namespace Binary{
        //Overloaded operators
        Int& Int::operator+=(const Int& rhs)
            {return m_bitset+=rhs.m_bitset, *this;}

        Int& Int::operator-=(const Int& rhs)
            {return m_bitset-=rhs.m_bitset, *this;}

        Int& Int::operator*=(const Int& rhs)
            {return m_bitset*=rhs.m_bitset, *this;}

        Int& Int::operator/=(const Int& rhs)
            {return m_bitset/=rhs.m_bitset, *this;}

        Int& Int::operator%=(const Int& rhs)
            {return m_bitset%=rhs.m_bitset, *this;}

        Int& Int::operator--()
            {return --m_bitset, *this;}

        Int Int::operator--(int)
            {return Int(m_bitset--);}

        Int& Int::operator++()
            {return ++m_bitset, *this;}

        Int Int::operator++(int)
            {return Int(m_bitset++);}

        Int& Int::operator&=(const Int& rhs)
            {return bitwise_operation(rhs, 1);}

        Int& Int::operator|=(const Int& rhs)
            {return bitwise_operation(rhs, 2);}

        Int& Int::operator^=(const Int& rhs)
            {return bitwise_operation(rhs, 3);}

        Int& Int::operator<<=(const Int& rhs)
            {return m_bitset<<=rhs.m_bitset, *this;}

        Int& Int::operator>>=(const Int& rhs)
            {return m_bitset>>=rhs.m_bitset, *this;}

        //Logical Operators
        Int Int::logical_and(const Int& s)const
            {return Int(*this).bitwise_operation(s, 1);}

        Int Int::logical_or(const Int& s)const
            {return Int(*this).bitwise_operation(s, 2);}

        Int Int::logical_xor(const Int& s)const
            {return Int(*this).bitwise_operation(s, 3);}

        Int Int::logical_inversion()const
            {return Int(*this).bitwise_operation(*this, 4);}

        Int Int::logical_shift(lli e)const
            {return Int(m_bitset*Math::exponentiate(bitset_type(2), e));}

        Int Int::logical_shift_left(size_type e)const
            {return Int(m_bitset*Math::exponentiate(bitset_type(2), e));}

        Int Int::logical_shift_right(size_type e)const
            {return Int(m_bitset/Math::exponentiate(bitset_type(2), e));}

        //Read-only functions
        typename Int::sign_type Int::sign()const
            {return m_bitset.sign();}

        typename Int::str_type Int::str()const{
            const size_type lim(this->count_digits());
            if(lim == 0)
                return "+0";
            str_type toreturn(lim+1, '0');
            toreturn.front() = (m_bitset.positive() ? '+' : '-');
            for(size_type i(0); i < lim; ++i)
                toreturn[i+1] = (this->digit(lim-i-1));

            return toreturn;
        }

        typename Int::str_type Int::sci_note(size_type prec)const{
            if(*this == Int(0))
                return "+0";
            else if(this->count_digits() == 1)
                return this->str() + "E1";

            str_type toreturn(this->str());
            size_type exp(toreturn.size() - 2);
            toreturn.insert(2, 1, '.');
            if(prec < exp)
                toreturn.erase(3+prec);
            if(toreturn.back() == '.')
                toreturn.pop_back();
            std::stringstream ss;
                ss << exp;
            toreturn += "E" + ss.str();

            return toreturn;
        }

        typename Int::str_type
            Int::sci_note_w_spaces(size_type prec)
        const{
            str_type toreturn(this->sci_note(prec));
            if(toreturn == "0") return toreturn;
            toreturn.insert(1, 1, ' ');//Insert space after the sign
            toreturn.insert(toreturn.find('E'), 1, ' ');
            toreturn.insert(toreturn.find('E')+1, 1, ' ');
            return toreturn;
        }

        Int Int::magnitude()const
            {return m_bitset.magnitude();}

        typename Int::size_type Int::count_digits()const{
            size_type toreturn((m_bitset.count_digits()-1)*k_bits);
            digit_10_type block(m_bitset.digit_10(m_bitset.count_digits()-1));
            while(block){
                ++toreturn;
                block >>= 1;
            }
            return toreturn;
        }

        short Int::compare(const Int& s)const
            {return m_bitset.compare(s.m_bitset);}

        Int Int::operator-()const
            {return -m_bitset;}

        Int Int::operator~()const
            {return Int(*this).bitwise_operation(*this, 4);}

        bool Int::even()const
            {return m_bitset.even();}

        bool Int::odd()const
            {return m_bitset.odd();}

        bool Int::positive()const
            {return m_bitset.positive();}

        bool Int::negative()const
            {return m_bitset.negative();}

        typename Int::image_type Int::digit(size_type i)const
            {return '0' + this->digit_10(i);}

        typename Int::digit_10_type Int::digit_10(size_type i)const{
            return
                (
                    m_bitset.digit_10(i/k_bits)
                    & (digit_10_type(1)<<(i%k_bits))
                ) > 0
            ;
        }

        constexpr typename Int::digit_10_type Int::base()
            {return 2;}

        //Other modifiers
        void Int::shift(lli tens_exp)
            {m_bitset.shift(tens_exp/bitset_type::base());}

        void Int::shift_left(size_type e)
            {m_bitset.shift_left(e/bitset_type::base());}

        void Int::shift_right(size_type e)
            {m_bitset.shift_right(e/bitset_type::base());}

        void Int::sign(sign_type newsign)
            {m_bitset.sign(newsign);}

        void Int::negate()
            {m_bitset.negate();}

        void Int::swap(Int& s)
            {std::swap(m_bitset, s.m_bitset);}

        //Constructors and destructor
        Int::Int(lli newnumber)
            : m_bitset(newnumber)
        {}

        Int::Int(const str_type& newnumber)
            : m_bitset(0)
        {
            bitset_type twos(1);
            const size_type min(
                newnumber.front()=='-'
                || newnumber.front()=='+'
                ? 1u : 0u
            );
            for(
                size_type i(newnumber.size());
                i > min;
                --i, twos *= 2
            )   m_bitset += bitset_type(newnumber[i-1]-'0')*twos;
            m_bitset.sign(newnumber.front()=='-' ? -1 : 1);
        }

        Int::Int(const diglist_type& n, sign_type s)
            : m_bitset(n, s)
        {}

        Int::Int(const bitset_type& newnumber)
            : m_bitset(newnumber)
        {}

        Int& Int::bitwise_operation(
            const Int& s,
            unsigned short condition
        ){
            bitset_type new_set(0), tens(1);
            const size_type lim
                = std::max(m_bitset.count_digits(), s.m_bitset.count_digits());
            for(
                size_type i(0);
                i < lim;
                ++i, tens.shift_left(1)
            ){
                digit_10_type
                    opleft =
                        (i >= m_bitset.count_digits() ? 0 : m_bitset.digit_10(i)),
                    opright = (i >= s.m_bitset.count_digits() || condition == 4
                        ? 0 : s.m_bitset.digit_10(i))
                ;
                switch(condition){
                    case 1:
                        new_set += tens*bitset_type(opleft & opright);
                        break;
                    case 2:
                        new_set += tens*bitset_type(opleft | opright);
                        break;
                    case 3:
                        new_set += tens*bitset_type(opleft ^ opright);
                        break;
                    case 4:
                        new_set += tens
                            * bitset_type((~opleft)&((1<<k_bits)-1));
                        break;
                    default:
                        throw condition; //Should never happen
                }
            }
            bool to_neg(false);
            switch(condition){
                case 1:
                    to_neg = m_bitset.negative() & s.m_bitset.negative();
                    break;
                case 2:
                    to_neg = m_bitset.negative() | s.m_bitset.negative();
                    break;
                case 3:
                    to_neg = m_bitset.negative() ^ s.m_bitset.negative();
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

        Int operator+(Int lhs, const Int& rhs)
            {return lhs += rhs;}

        Int operator-(Int lhs, const Int& rhs)
            {return lhs -= rhs;}

        Int operator*(Int lhs, const Int& rhs)
            {return lhs *= rhs;}

        Int operator/(Int lhs, const Int& rhs)
            {return lhs /= rhs;}

        Int operator%(Int lhs, const Int& rhs)
            {return lhs %= rhs;}

        Int operator&(Int lhs, const Int& rhs)
            {return lhs &= rhs;}

        Int operator|(Int lhs, const Int& rhs)
            {return lhs |= rhs;}

        Int operator^(Int lhs, const Int& rhs)
            {return lhs ^= rhs;}

        Int operator>>(Int lhs, const Int& rhs)
            {return lhs >>= rhs;}

        Int operator<<(Int lhs, const Int& rhs)
            {return lhs <<= rhs;}

        bool operator==(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) == 0;}

        bool operator!=(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) != 0;}

        bool operator>=(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) >= 0;}

        bool operator<=(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) <= 0;}

        bool operator>(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) > 0;}

        bool operator<(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) < 0;}

        bool operator!(const Int& lhs)
            {return lhs == Int(0);}
    }
}

void swap(
    Precision::Binary::Int& a,
    Precision::Binary::Int& b
)   {a.swap(b);}
