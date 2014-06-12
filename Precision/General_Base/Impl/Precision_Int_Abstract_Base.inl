#include "Precision_Math_Shared_Functions.h"
#include "Precision_Exception.h"

#include <functional>
#include <algorithm>
#include <utility>

namespace Precision{
    namespace General_Base{
        namespace Abstract{
            //Overloaded operators
            INT_TEMPL_
            INT_INST_& INT_INST_::operator+=(const INT_INST_& rhs){
                if(rhs == INT_INST_(0)) return *this;
                if(*this == INT_INST_(0)) return (*this = rhs);

                INT_INST_ big(*this), small(rhs);
                if(big.magnitude() < small.magnitude()) std::swap(big, small);
                while(small.m_number.size() < big.m_number.size())
                    small.m_number.push_back(0);

                this->m_sign = big.m_sign;
                if(big.m_sign.negative())
                    big.m_sign.make_positive(), small.m_sign.negate();

                digit_type carry(0);
                auto biter(big.m_number.begin());
                auto siter(small.m_number.begin());
                for(; siter != small.m_number.end(); ++biter, ++siter){
                    digit_type catalyst(
                        *biter
                        + (*siter)*small.m_sign
                        + carry
                    );
                //Carry a number
                    if(catalyst >= Base)
                        catalyst %= Base, carry=1;
                    else
                        carry = 0;
                //Borrow a number
                    auto bcopy(biter);
                        ++bcopy;
                    if(catalyst < 0 && bcopy != big.m_number.end()){
                        --(*bcopy), catalyst += Base;
                        auto bcopy2(bcopy), bcopy3(bcopy);
                        while(*bcopy3 < 0 && (++bcopy2) != big.m_number.end())
                            *(bcopy3++) += Base, --(*bcopy2);
            //Not the proper way to handle error: -1 for left-most digit_type
            //  Still need to find out how this situation even occurs
                        if(*bcopy3 < 0){
                            *bcopy3 += Base;
                            this->m_sign.negate();
                        }
                    }

                    *biter = catalyst;
                    if(carry > 0 && bcopy == big.m_number.end())
                        big.m_number.push_back(carry);
                }

                while(big.m_number.size() > 1 && big.m_number.back() == 0)
                    big.m_number.pop_back();
                this->m_number = std::move(big.m_number);

                return *this;
            }

            INT_TEMPL_
            INT_INST_& INT_INST_::operator-=(const INT_INST_& rhs){
                if(*this == rhs) return (*this = INT_INST_(0));
                return (*this += (-rhs));
            }

            INT_TEMPL_
            INT_INST_& INT_INST_::operator*=(const INT_INST_& rhs){
                if(rhs == INT_INST_(0))         return *this = INT_INST_(0);
                else if(*this == INT_INST_(0) || rhs == INT_INST_(1))
                                                return *this;
                else if(*this == INT_INST_(1))  return *this = rhs;
                else if(rhs == INT_INST_(-1))   return m_sign.negate(), *this;
                else if(*this == INT_INST_(-1)){
                    *this = rhs;
                    m_sign.negate();
                    return *this;
                }
                sign_type sign_hold(m_sign * rhs.m_sign);

                INT_INST_ big(*this), small(rhs);
                if(big.magnitude() < small.magnitude())
                    std::swap(big, small);
                size_type z_count(0);
                while(big.m_number.size() > 0 && big.m_number.front() == 0)
                    big.m_number.erase(big.m_number.begin()), ++z_count;
                while(small.m_number.size() > 0 && small.m_number.front() == 0)
                    small.m_number.erase(small.m_number.begin()), ++z_count;
                if(big.m_number.size() == 0 || small.m_number.size() == 0)
                    return *this = 0;
                std::vector<INT_INST_> addends;
            //Cut down on runtime by reducing number of iterations
                auto iter(small.m_number.begin());
                for(size_type i(0); i < small.m_number.size(); ++i, ++iter){
                    INT_INST_ addend(0);
                    digit_type operand(*iter);
                    while(operand-- > 0)
                        addend += big;
                    addend.m_number.insert(addend.m_number.begin(), i, 0);
                    addends.push_back(addend);
                }
                m_number = diglist_type(1, 0);
                for(
                    auto addend(addends.begin());
                    addend != addends.end();
                    ++addend
                ) *this += *addend;
                m_number.insert(m_number.begin(), z_count, 0);

                this->m_sign = sign_hold;
                return *this;

            }

            INT_TEMPL_
            INT_INST_& INT_INST_::operator/=(const INT_INST_& rhs){
                if(*this == rhs) return (*this = 1);
                else if(rhs == INT_INST_(0)){
                    throw exception(
                        exception::divide_by_zero,
                        "Precision::General_Base::Abstract::Int::operator/=(Int)"
                    );
                }else if(this->magnitude() < rhs.magnitude())
                    return (*this = INT_INST_(0));
                else if(rhs == INT_INST_(1)) return *this;
                divide(rhs, this, nullptr);
                return *this;
            }

            INT_TEMPL_
            INT_INST_& INT_INST_::operator%=(const INT_INST_& rhs){
                if(rhs == *this|| rhs == INT_INST_(1))
                    return (*this = INT_INST_(0));
                else if(rhs == INT_INST_(0)){
                    throw exception(
                        exception::divide_by_zero,
                        "Precision::General_Base::Abstract::Int::operator%=(Int)"
                    );
                }else if(rhs.magnitude() > this->magnitude()) return *this;
                else if(rhs == INT_INST_(2))   return *this = this->odd();
                divide(rhs, nullptr, this);
                return *this;
            }

            INT_TEMPL_
            INT_INST_& INT_INST_::operator--()
                {return (*this += -1);}

            INT_TEMPL_
            INT_INST_ INT_INST_::operator--(int)
                {return (*this += INT_INST_(-1))+INT_INST_(1);}

            INT_TEMPL_
            INT_INST_& INT_INST_::operator++()
                {return (*this += 1);}

            INT_TEMPL_
            INT_INST_ INT_INST_::operator++(int)
                {return (*this += INT_INST_(1))+INT_INST_(-1);}

            INT_TEMPL_
            INT_INST_& INT_INST_::operator&=(const INT_INST_& rhs){
                return bitwise_operation(
                    rhs, [](bool l, bool r){return (l == r && l == true);}
                );
            }

            INT_TEMPL_
            INT_INST_& INT_INST_::operator|=(const INT_INST_& rhs){
                return bitwise_operation(
                    rhs, [](bool l, bool r){return (l == true || r == true);}
                );
            }

            INT_TEMPL_
            INT_INST_& INT_INST_::operator^=(const INT_INST_& rhs){return
                bitwise_operation(rhs, [](bool l, bool r){return (l != r);});}

            INT_TEMPL_
            INT_INST_& INT_INST_::operator<<=(const INT_INST_& rhs)
                {return *this *= Math::exponentiate(INT_INST_(2), rhs);}

            INT_TEMPL_
            INT_INST_& INT_INST_::operator>>=(const INT_INST_& rhs)
                {return *this /= Math::exponentiate(INT_INST_(2), rhs);}


    //Logical Operators
            INT_TEMPL_
            INT_INST_ INT_INST_::logical_and(const INT_INST_& s)const
                {return this->logical_operation(s, 1);} //res = (a*b)%base

            INT_TEMPL_
            INT_INST_ INT_INST_::logical_or(const INT_INST_& s)const
                {return this->logical_operation(s, 2);} //res = ~(~a & ~b)

            INT_TEMPL_
            INT_INST_ INT_INST_::logical_xor(const INT_INST_& s)const
             //res = (~((a+b)%base))%base
                {return this->logical_operation(s, 3);}

            INT_TEMPL_
            INT_INST_ INT_INST_::logical_inversion()const
                {return this->logical_operation(*this, 4);} //res = Base - 1 - a

            INT_TEMPL_
            INT_INST_ INT_INST_::logical_shift(lli e)const{
                if(e < 0)
                    return this->logical_shift_right(-e);
                else if(0 < e)
                    return this->logical_shift_left(e);
                else
                    return *this;
            }

            INT_TEMPL_
            INT_INST_ INT_INST_::logical_shift_left(size_type e)const{
                INT_INST_ toreturn(*this);
                toreturn.shift_left(e);
                return toreturn;
            }

            INT_TEMPL_
            INT_INST_ INT_INST_::logical_shift_right(size_type e)const{
                INT_INST_ toreturn(*this);
                toreturn.shift_right(e);
                return toreturn;
            }


            //Read-only functions
            INT_TEMPL_
            typename INT_INST_::sign_type INT_INST_::sign()const
                {return m_sign;}

            INT_TEMPL_
            INT_INST_ INT_INST_::magnitude()const{
                //Seclude from multiplication operators
                INT_INST_ toreturn(*this);
                    toreturn.m_sign = 1;
                return toreturn;
            }

            INT_TEMPL_
            typename INT_INST_::size_type INT_INST_::count_digits()const
                {return m_number.size();}

            INT_TEMPL_
            short INT_INST_::compare(const INT_INST_& s)const{
                if(this == &s)                                  return 0;
                else if(m_sign < s.m_sign)                      return -1;
                else if(m_sign > s.m_sign)                      return 1;
                else if(m_number == s.m_number)                 return 0;
                else if(m_sign == -1 && m_number.size() > s.m_number.size())
                                                                return -1;
                else if(m_sign == -1 && m_number.size() < s.m_number.size())
                                                                return 1;
                else if(m_number.size() < s.m_number.size())    return -1;
                else if(m_number.size() > s.m_number.size())    return 1;
                for(
                    auto titer(m_number.crbegin()), siter(s.m_number.crbegin());
                    titer != m_number.crend();
                    ++titer, ++siter
                ){
                    if(*titer < *siter)         return -m_sign.value();
                    else if(*titer > *siter)    return m_sign.value();
                }
                                                                return 0;
            }

            INT_TEMPL_
            INT_INST_ INT_INST_::operator-()const{
                INT_INST_ toreturn(*this);
                toreturn.m_sign.negate();
                return toreturn;
            }

            INT_TEMPL_
            INT_INST_ INT_INST_::operator~()const{
                if(*this == INT_INST_(0)){
                    throw exception(
                        exception::insufficient_memory,
                        "Precision::General_Base::Abstract::Int::operator~()"
                    );
                }
                INT_INST_ toreturn(0), reducer(this->magnitude());
                size_type i(0);
                sign_type new_s(this->sign());
                new_s.negate();
                const INT_INST_ z_(0), two_(2);
                while(reducer != z_){
                    toreturn += reducer.odd() ? 0 : Math::exponentiate(two_, i);
                    ++i, reducer /= two_;
                }
                toreturn.sign(new_s);
                return toreturn;
            }

            INT_TEMPL_
            bool INT_INST_::even()const
                {return !(this->odd());}

            INT_TEMPL_
            bool INT_INST_::odd()const
                {return m_number.front() % 2;}

            INT_TEMPL_
            bool INT_INST_::positive()const
                {return m_sign.positive();}

            INT_TEMPL_
            bool INT_INST_::negative()const
                {return m_sign.negative();}

            INT_TEMPL_
            typename INT_INST_::digit_type INT_INST_::digit_10(size_type i)const{
                auto toreturn(m_number.cbegin());
                std::advance(toreturn, i);
                return *toreturn;
            }

            INT_TEMPL_
            typename INT_INST_::diglist_type INT_INST_::digit_list()const{
                diglist_type toreturn(m_number);
                std::reverse(toreturn.begin(), toreturn.end());
                return toreturn;
            }

            INT_TEMPL_
            constexpr typename INT_INST_::digit_type INT_INST_::base()
                {return Base;}

            //Other modifiers
            INT_TEMPL_
            void INT_INST_::shift(lli tens_exp){
                if(tens_exp < 0)
                    this->shift_right(-tens_exp);
                else
                    this->shift_left(tens_exp);
            }

            INT_TEMPL_
            void INT_INST_::shift_left(size_type e){
                if(m_number.size() == 1 && m_number.front() == 0)
                    return;
                else
                    m_number.insert(m_number.begin(), e, 0);
            }

            INT_TEMPL_
            void INT_INST_::shift_right(size_type e){
                if(m_number.size() <= e)
                    m_number = diglist_type(1, 0);
                else{
                    auto end(m_number.begin());
                    std::advance(end, e);
                    m_number.erase(m_number.begin(), end);
                }
            }

            INT_TEMPL_
            void INT_INST_::sign(sign_type newsign)
                {m_sign = newsign;}

            INT_TEMPL_
            void INT_INST_::negate()
                {m_sign.negate();}

            INT_TEMPL_
            void INT_INST_::swap(INT_INST_& s){
                std::swap(m_number, s.m_number);
                std::swap(m_sign, s.m_sign);
            }

            //Constructors and destructor
            INT_TEMPL_
            INT_INST_::Int(lli newnumber)
                : m_number(0, 0)
                , m_sign(newnumber < 0 ? -1 : 1)
            {
                newnumber *= m_sign;
                while(newnumber > 0){
                    m_number.push_back(newnumber%Base);
                    newnumber /= Base;
                }
                if(m_number.size() == 0)
                    m_number = diglist_type(1, 0);
            }

            INT_TEMPL_
            INT_INST_::Int(const diglist_type& n, sign_type s)
                : m_number(n)
                , m_sign(s)
            {
                for(auto iter(m_number.begin()); iter != m_number.end(); ++iter)
                    *iter = (*iter < 0 || *iter >= Base) ? 0 : *iter;
                std::reverse(m_number.begin(), m_number.end());
                while(m_number.size() > 1 && m_number.back() == 0)
                    m_number.pop_back();
            }

            INT_TEMPL_
            void INT_INST_::divide(
                const INT_INST_& rhs,
                INT_INST_* div_req,
                INT_INST_* mod_req
            ){
                if(rhs == INT_INST_(0)){
                    throw exception(
                        exception::divide_by_zero,
                        "Precision::General_Base::Abstract::Int::divide(Int, bool)"
                    );
                }else if(rhs == INT_INST_(1)){
                    if(div_req != nullptr)  *div_req = *this;
                    if(mod_req != nullptr)  *mod_req = 0;
                }else if(*this == rhs){
                    if(div_req != nullptr)  *div_req = 1;
                    if(mod_req != nullptr)  *mod_req = 0;
                }else if(this->magnitude() < rhs.magnitude()){
                    if(mod_req != nullptr)  *mod_req = *this;
                    if(div_req != nullptr)  *div_req = 0;
                }

                INT_INST_
                    quotient(0),
                    remainder(this->magnitude()),
                    tens(rhs.magnitude())
                ;
                size_type t_counter(remainder.m_number.size()-tens.m_number.size());

                tens.m_number.insert(tens.m_number.begin(), t_counter, 0);

                while(tens >= rhs.magnitude()){
                    INT_INST_ addend(1);
                    addend.shift_left(t_counter);
                    while(remainder >= tens){
                        quotient += addend;
                        remainder -= tens;
                    }
                    tens.m_number.erase(tens.m_number.begin()), --t_counter;
                }
                if(div_req != nullptr){
                    quotient.m_sign = this->m_sign * rhs.m_sign;
                    *div_req = std::move(quotient);
                }
                if(mod_req != nullptr)
                    *mod_req = std::move(remainder);
            }

            INT_TEMPL_
            INT_INST_& INT_INST_::bitwise_operation(
                INT_INST_ s,
                const std::function<bool(bool, bool)>& condition
            ){
                INT_INST_ toreturn(0);
                size_type i(0);
                sign_type new_s(condition(this->negative(), s.negative()) ? -1 : 1);
                const INT_INST_ z_(0), two_(2);
                while(*this != z_ || s != z_){
                    toreturn += condition(this->odd(), s.odd())
                        ? Math::exponentiate(two_, i) : 0;
                    ++i, *this /= two_, s /= two_;
                }
                toreturn.sign(new_s);
                return *this = toreturn;
            }

            INT_TEMPL_
            INT_INST_ INT_INST_::logical_operation(
                const INT_INST_& s,
                unsigned short oper
            )const{
                diglist_type big(m_number), small(s.m_number);
                if(big.size() < small.size())
                    std::swap(big, small);
                small.insert(small.end(), big.size() - small.size(), 0);
                for(
                    auto biter(big.begin()), siter(small.begin());
                    siter != small.end();
                    ++biter, ++siter
                ){
                    switch(oper){
                        case 1:
                            *biter = (*biter * *siter)%Base;
                            break;
                        case 2:
                            *biter = (Base - 1 - ( ( (Base-1-*biter)%Base )
                                * ( (Base-1-*siter)%Base ) )%Base)%Base;
                            break;
                        case 3:
                            *biter = (Base-(*biter + *siter)%Base)%Base;
                            break;
                        case 4:
                            *biter = Base - 1 - *biter;
                            break;
                        default:
                            throw oper; //Should never happen
                    }
                }
                while(big.size() > 1 && big.back() == 0)
                    big.pop_back();
                std::reverse(big.begin(), big.end());
                switch(oper){
                    case 1:
                        return INT_INST_(big,
                            m_sign.negative() & s.m_sign.negative() ? -1 : 1);
                    case 2:
                        return INT_INST_(big,
                            m_sign.negative() | s.m_sign.negative() ? -1 : 1);
                    case 3:
                        return INT_INST_(big,
                            m_sign.negative() ^ s.m_sign.negative() ? -1 : 1);
                    case 4:
                        return INT_INST_(big, -m_sign);
                    default:
                        throw oper; //Should never happen
                }
            }

            INT_TEMPL_
            INT_INST_ operator+(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs += rhs;}

            INT_TEMPL_
            INT_INST_ operator-(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs -= rhs;}

            INT_TEMPL_
            INT_INST_ operator*(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs *= rhs;}

            INT_TEMPL_
            INT_INST_ operator/(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs /= rhs;}

            INT_TEMPL_
            INT_INST_ operator%(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs %= rhs;}

            INT_TEMPL_
            INT_INST_ operator&(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs &= rhs;}

            INT_TEMPL_
            INT_INST_ operator|(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs |= rhs;}

            INT_TEMPL_
            INT_INST_ operator^(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs ^= rhs;}

            INT_TEMPL_
            INT_INST_ operator>>(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs >>= rhs;}

            INT_TEMPL_
            INT_INST_ operator<<(INT_INST_ lhs, const INT_INST_& rhs)
                {return lhs <<= rhs;}

            INT_TEMPL_
            bool operator==(const INT_INST_& lhs, const INT_INST_& rhs)
                {return lhs.compare(rhs) == 0;}

            INT_TEMPL_
            bool operator!=(const INT_INST_& lhs, const INT_INST_& rhs)
                {return lhs.compare(rhs) != 0;}

            INT_TEMPL_
            bool operator>=(const INT_INST_& lhs, const INT_INST_& rhs)
                {return lhs.compare(rhs) >= 0;}

            INT_TEMPL_
            bool operator<=(const INT_INST_& lhs, const INT_INST_& rhs)
                {return lhs.compare(rhs) <= 0;}

            INT_TEMPL_
            bool operator>(const INT_INST_& lhs, const INT_INST_& rhs)
                {return lhs.compare(rhs) > 0;}

            INT_TEMPL_
            bool operator<(const INT_INST_& lhs, const INT_INST_& rhs)
                {return lhs.compare(rhs) < 0;}

            INT_TEMPL_
            bool operator!(const INT_INST_& lhs)
                {return lhs == INT_INST_(0);}
        }
    }
}

INT_TEMPL_
void swap(
    Precision::General_Base::Abstract::INT_INST_& a,
    Precision::General_Base::Abstract::INT_INST_& b
)   {a.swap(b);}
