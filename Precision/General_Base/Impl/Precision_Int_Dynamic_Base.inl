#include "Precision_Math_Shared_Functions.h"
#include "Precision_Exception.h"
#include "Precision_InterBase_Functions.h"

#include <functional>
#include <algorithm>
#include <utility>
#include <sstream>

namespace Precision{
    namespace Dynamic_Base{
        //Overloaded operators
        INT_TEMPL_
        INT_INST_& INT_INST_::operator+=(const INT_INST_& rhs){
            if(rhs == INT_INST_(0, rhs.m_wrap)) return *this;
            if(*this == INT_INST_(0, rhs.m_wrap))
                return (*this = Precision::convert(rhs, m_wrap));

            INT_INST_ big(*this), small(rhs);
            if(small.base() != big.base())
                small = Precision::convert(small, m_wrap);
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
                if(catalyst >= m_wrap.base())
                    catalyst %= m_wrap.base(), carry=1;
                else
                    carry = 0;
            //Borrow a number
                auto bcopy(biter);
                    ++bcopy;
                if(catalyst < 0 && bcopy != big.m_number.end()){
                    --(*bcopy), catalyst += m_wrap.base();
                    auto bcopy2(bcopy), bcopy3(bcopy);
                    while(*bcopy3 < 0 && (++bcopy2) != big.m_number.end())
                        *(bcopy3++) += m_wrap.base(), --(*bcopy2);
        //Not the proper way to handle error: -1 for left-most digit_type
        //  Still need to find out how this situation even occurs
                    if(*bcopy3 < 0){
                        *bcopy3 += m_wrap.base();
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
            if(*this == rhs) return (*this = INT_INST_(0, m_wrap));
            return (*this += (-rhs));
        }

        INT_TEMPL_
        INT_INST_& INT_INST_::operator*=(const INT_INST_& rhs){
            if(rhs == INT_INST_(0, rhs.m_wrap))
                return *this = INT_INST_(0, m_wrap);
            else if(*this == INT_INST_(0, m_wrap) || rhs == INT_INST_(1, m_wrap))
                return *this;
            else if(*this == INT_INST_(1, m_wrap))
                return *this = Precision::convert(rhs, m_wrap);
            else if(rhs == INT_INST_(-1, rhs.m_wrap))
                return m_sign.negate(), *this;
            else if(*this == INT_INST_(-1, m_wrap)){
                *this = Precision::convert(rhs, m_wrap);
                m_sign.negate();
                return *this;
            }
            sign_type sign_hold(m_sign * rhs.m_sign);

            INT_INST_ big(*this), small(rhs);
            if(small.base() != big.base())
                small = Precision::convert(small, m_wrap);
            if(big.magnitude() < small.magnitude())
                std::swap(big, small);
            size_type z_count(0);
            while(big.m_number.size() > 0 && big.m_number.front() == 0)
                big.m_number.erase(big.m_number.begin()), ++z_count;
            while(small.m_number.size() > 0 && small.m_number.front() == 0)
                small.m_number.erase(small.m_number.begin()), ++z_count;
            if(big.m_number.size() == 0 || small.m_number.size() == 0)
                return *this = INT_INST_(0, m_wrap);
            std::vector<INT_INST_> addends;
        //Cut down on runtime by reducing number of iterations
            auto iter(small.m_number.begin());
            for(size_type i(0); i < small.m_number.size(); ++i, ++iter){
                INT_INST_ addend(0, m_wrap);
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
            if(*this == rhs) return (*this = INT_INST_(1, m_wrap));
            else if(rhs == INT_INST_(0, rhs.m_wrap)){
                throw exception(
                    exception::divide_by_zero,
                    "Precision::Dynamic_Base::Int::operator/=(Int)"
                );
            }else if(this->magnitude() < rhs.magnitude())
                return (*this = INT_INST_(0, m_wrap));
            else if(rhs == INT_INST_(1, rhs.m_wrap)) return *this;
            divide(rhs, this, nullptr);
            return *this;
        }

        INT_TEMPL_
        INT_INST_& INT_INST_::operator%=(const INT_INST_& rhs){
            if(rhs == *this|| rhs == INT_INST_(1, rhs.m_wrap))
                return (*this = INT_INST_(0, m_wrap));
            else if(rhs == INT_INST_(0, rhs.m_wrap)){
                throw exception(
                    exception::divide_by_zero,
                    "Precision::Dynamic_Base::Int::operator%=(Int)"
                );
            }else if(rhs.magnitude() > this->magnitude()) return *this;
            else if(rhs == INT_INST_(2, rhs.m_wrap))
                return *this = INT_INST_(this->odd(), m_wrap);
            divide(rhs, nullptr, this);
            return *this;
        }

        INT_TEMPL_
        INT_INST_& INT_INST_::operator--()
            {return (*this += INT_INST_(-1, m_wrap));}

        INT_TEMPL_
        INT_INST_ INT_INST_::operator--(int)
            {return (*this += INT_INST_(-1, m_wrap))+INT_INST_(1, m_wrap);}

        INT_TEMPL_
        INT_INST_& INT_INST_::operator++()
            {return (*this += INT_INST_(1, m_wrap));}

        INT_TEMPL_
        INT_INST_ INT_INST_::operator++(int)
            {return (*this += INT_INST_(1, m_wrap))+INT_INST_(-1, m_wrap);}

        INT_TEMPL_
        INT_INST_& INT_INST_::operator&=(const INT_INST_& rhs)
            {return bitwise_operation(rhs, 1);}

        INT_TEMPL_
        INT_INST_& INT_INST_::operator|=(const INT_INST_& rhs)
            {return bitwise_operation(rhs, 2);}

        INT_TEMPL_
        INT_INST_& INT_INST_::operator^=(const INT_INST_& rhs)
            {return bitwise_operation(rhs, 3);}

        INT_TEMPL_
        INT_INST_& INT_INST_::operator<<=(const INT_INST_& rhs)
            {return *this *= Math::exponentiate(INT_INST_(2, m_wrap), rhs);}

        INT_TEMPL_
        INT_INST_& INT_INST_::operator>>=(const INT_INST_& rhs)
            {return *this /= Math::exponentiate(INT_INST_(2, m_wrap), rhs);}


//Logical Operators
        INT_TEMPL_
        INT_INST_ INT_INST_::logical_and(const INT_INST_& s)const
            {return this->logical_operation(s, 1);} //res = (a*b)%base

        INT_TEMPL_
        INT_INST_ INT_INST_::logical_or(const INT_INST_& s)const
            {return this->logical_operation(s, 2);} //res = ~(~a & ~b)

        INT_TEMPL_
        INT_INST_ INT_INST_::logical_xor(const INT_INST_& s)const
            {return this->logical_operation(s, 3);} //res = (~((a+b)%base))%base

        INT_TEMPL_
        INT_INST_ INT_INST_::logical_inversion()const
            {return this->logical_operation(*this, 4);} //res = m_wrap.base() - 1 - a

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
        typename INT_INST_::str_type INT_INST_::str()const{
            if(*this == INT_INST_(0, m_wrap))
                return str_type(1, m_wrap.plus()) + str_type(1, m_wrap[0]);
            str_type toreturn(m_number.size() + 1, m_wrap[0]);
            toreturn[0] = (m_sign.positive() ? m_wrap.plus() : m_wrap.minus());
            size_type i(1);
            for(
                auto iter(m_number.crbegin());
                iter != m_number.crend();
                ++iter, ++i
            )   toreturn[i] = m_wrap[*iter];
            return toreturn;
        }

        INT_TEMPL_
        typename INT_INST_::str_type INT_INST_::sci_note(size_type prec)const{
            if(*this == INT_INST_(0, m_wrap))
                return str_type(1, m_wrap.plus()) + str_type(1, m_wrap[0]);
            else if(m_number.size() < 2)
                //Display +#E0
                return this->str()
                    + str_type(1, m_wrap.exponent()) + str_type(1, m_wrap[0]);

            str_type toreturn(this->str());
            size_type exp(toreturn.size() - 2);
            toreturn.insert(2, 1, m_wrap.point());
            if(prec < exp)
                toreturn.erase(3+prec);
            if(toreturn.back() == m_wrap.point())
                toreturn.pop_back();
            toreturn += str_type(1, m_wrap.exponent())
                + INT_INST_(exp, m_wrap).str().substr(1);

            return toreturn;
        }

        INT_TEMPL_
        typename INT_INST_::str_type
            INT_INST_::sci_note_w_spaces(size_type prec)
        const{
            str_type toreturn(this->sci_note(prec));
            if(toreturn == str_type(1, m_wrap[0])) return toreturn;
            toreturn.insert(1, 1, m_wrap.space());//Insert space after the sign
            toreturn.insert(toreturn.find(m_wrap.exponent()), 1, m_wrap.space());
            toreturn.insert(toreturn.find(m_wrap.exponent())+1, 1, m_wrap.space());
            return toreturn;
        }

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
        short INT_INST_::compare(const INT_INST_& rhs)const{
            INT_INST_ s(rhs);
            if(s.base() != this->base()) s = Precision::convert(s, m_wrap);
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
            if(*this == INT_INST_(0, m_wrap)){
                throw exception(
                    exception::insufficient_memory,
                    "Precision::Dynamic_Base::Int::operator~()"
                );
            }
            return INT_INST_(*this).bitwise_operation(*this, 4);
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
        typename INT_INST_::image_type INT_INST_::digit(size_type i)const
            {return *(m_wrap+this->digit_10(i));}

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
        typename INT_INST_::digit_type INT_INST_::base()const
            {return m_wrap.base();}

        INT_TEMPL_
        const typename INT_INST_::img_iter_type& INT_INST_::digit0()const
            {return m_wrap.digit0();}

        INT_TEMPL_
        const typename INT_INST_::img_iter_type& INT_INST_::symbols()const
            {return m_wrap.sybols();}

        INT_TEMPL_
        const typename INT_INST_::wrapper_type& INT_INST_::wrapper()const
            {return m_wrap;}

        //Other modifiers

        INT_TEMPL_
        typename INT_INST_::wrapper_type INT_INST_::wrapper(
            const img_iter_type& new_0,
            const img_iter_type& new_sym,
            digit_type new_base
        ){return this->wrapper(wrapper_type(new_0, new_sym, new_base));}

        INT_TEMPL_
        typename INT_INST_::wrapper_type INT_INST_::wrapper
            (const wrapper_type& new_wrap)
        {
            wrapper_type toreturn(m_wrap);

            if(m_wrap.base() == new_wrap.base()){
                m_wrap = new_wrap;
                return toreturn;
            }

            *this = Precision::convert(*this, new_wrap);
            return toreturn;
        }

        INT_TEMPL_
        typename INT_INST_::digit_type INT_INST_::base(digit_type new_base)
            {return wrapper(m_wrap.digit0(), m_wrap.symbols(), new_base).base();}

        INT_TEMPL_
        typename INT_INST_::img_iter_type INT_INST_::digit0
            (const typename INT_INST_::img_iter_type& new_imgs)
        {return m_wrap.digit0(new_imgs);}

        INT_TEMPL_
        typename INT_INST_::img_iter_type INT_INST_::symbols
            (const typename INT_INST_::img_iter_type& new_imgs)
        {return m_wrap.symbols(new_imgs);}

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
        constexpr INT_INST_::Int(
            const img_iter_type& new_0,
            const img_iter_type& new_sym,
            digit_type new_base
        )
            : Int(wrapper_type(new_0, new_sym, new_base))
        {}

        INT_TEMPL_
        INT_INST_::Int(
            lli newnumber,
            const img_iter_type& new_0,
            const img_iter_type& new_sym,
            digit_type new_base
        )
            : Int(newnumber, wrapper_type(new_0, new_sym, new_base))
        {}

        INT_TEMPL_
        INT_INST_::Int(
            const str_type& newnumber,
            const img_iter_type& new_0,
            const img_iter_type& new_sym,
            digit_type new_base
        )
            : Int(newnumber, wrapper_type(new_0, new_sym, new_base))
        {}

        INT_TEMPL_
        constexpr INT_INST_::Int(
            const diglist_type& n,
            sign_type s,
            const img_iter_type& new_0,
            const img_iter_type& new_sym,
            digit_type new_base
        )
            : Int(n, s, wrapper_type(new_0, new_sym, new_base))
        {}

        INT_TEMPL_
        constexpr INT_INST_::Int(const wrapper_type& new_wrap)
            : m_wrap(new_wrap)
            , m_number(1, 0)
            , m_sign(1)
        {}

        INT_TEMPL_
        INT_INST_::Int(lli newnumber, const wrapper_type& new_wrap)
            : m_wrap(new_wrap)
            , m_number(0, 0)
            , m_sign(newnumber < 0 ? -1 : 1)
        {
            newnumber *= m_sign;
            while(newnumber > 0){
                m_number.push_back(newnumber%m_wrap.base());
                newnumber /= m_wrap.base();
            }
            if(m_number.size() == 0)
                m_number = diglist_type(1, 0);
        }

        INT_TEMPL_
        INT_INST_::Int(const str_type& newnumber, const wrapper_type& new_wrap)
            : m_wrap(new_wrap)
            , m_number(newnumber.size(), 0)
            , m_sign(newnumber[0] == m_wrap.minus() ? -1 : 1)
        {
            size_type e_pos(newnumber.find(m_wrap.exponent()));
            if(e_pos == str_type::npos)
                parse(newnumber);
            else{
                //Negative exponent
                if(newnumber[e_pos+1] != m_wrap.minus()){
                    str_type whole(newnumber.substr(0, e_pos));
                    size_type exp(0);
                    std::stringstream catalyst(newnumber.substr(e_pos+1));
                    catalyst >> exp;
                    size_type point(whole.find(m_wrap.point()));
                    if(point == str_type::npos || point == whole.size()-1){
                        if(point == newnumber.size()-1)
                            whole.erase(point, 1);
                        whole.insert(whole.size(), exp, m_wrap[0]);
                        parse(whole);
                    }else{
                        whole.erase(point, 1);
                        while(exp > 0 && point < whole.size())
                            --exp, ++point;
                        if(point < whole.size())
                            whole.erase(point);
                        if(exp > 0)
                            whole.insert(whole.size(), exp, m_wrap[0]);
                        
                        parse(whole);
                    }
                }
            }
        }

        INT_TEMPL_
        INT_INST_::Int(
            const diglist_type& n,
            sign_type s,
            const wrapper_type& new_wrap
        )
            : m_wrap(new_wrap)
            , m_number(n)
            , m_sign(s)
        {
            for(auto iter(m_number.begin()); iter != m_number.end(); ++iter)
                *iter = (*iter < 0 || *iter >= m_wrap.base()) ? 0 : *iter;
            std::reverse(m_number.begin(), m_number.end());
            while(m_number.size() > 1 && m_number.back() == 0)
                m_number.pop_back();
        }

        INT_TEMPL_
        void INT_INST_::parse(const str_type& newnumber){
            if(newnumber.size() > 0){
                auto iter(m_number.begin());
                size_type i(newnumber.size());
                while(i-- > 0){
                    *iter = m_wrap.template get_index<policy>(newnumber[i]);
                    if(*iter >= m_wrap.base())
                        *iter = 0;
                    ++iter;
                }

                while(m_number.size() > 1 && m_number.back() == 0)
                    m_number.pop_back();

                if(m_number.size() == 1 && m_number.front() == 0)
                    m_sign.make_positive();
            }
        }

        INT_TEMPL_
        void INT_INST_::divide(
            const INT_INST_& s,
            INT_INST_* div_req,
            INT_INST_* mod_req
        ){
            INT_INST_ rhs(s);
            if(s.base() != this->base())
                rhs = Precision::convert(rhs, m_wrap);
            if(rhs == INT_INST_(0, rhs.m_wrap)){
                throw exception(
                    exception::divide_by_zero,
                    "Precision::Dynamic_Base::Int::divide(Int, bool)"
                );
            }else if(rhs == INT_INST_(1, m_wrap)){
                if(div_req != nullptr)  *div_req = *this;
                if(mod_req != nullptr)  *mod_req = INT_INST_(0, m_wrap);
            }else if(*this == rhs){
                if(div_req != nullptr)  *div_req = INT_INST_(1, m_wrap);
                if(mod_req != nullptr)  *mod_req = INT_INST_(0, m_wrap);
            }else if(this->magnitude() < rhs.magnitude()){
                if(mod_req != nullptr)  *mod_req = *this;
                if(div_req != nullptr)  *div_req = INT_INST_(0, m_wrap);
            }

            INT_INST_
                quotient(0, m_wrap),
                remainder(this->magnitude()),
                tens(rhs.magnitude())
            ;
            size_type t_counter(remainder.m_number.size()-tens.m_number.size());

            tens.m_number.insert(tens.m_number.begin(), t_counter, 0);

            while(tens >= rhs.magnitude()){
                INT_INST_ addend(1, m_wrap);
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
            const INT_INST_& s,
            unsigned short oper
        ){
            wrapper_type bin_wrap(m_wrap.digit0(), m_wrap.digit0(), 2);
            INT_INST_
                tbin(Precision::convert(*this, bin_wrap)),
                sbin(oper != 4 ? Precision::convert(s, bin_wrap) : tbin)
            ;
            switch(oper){
                case 1:
                    *this = Precision::convert(tbin.logical_and(sbin), m_wrap);
                    break;
                case 2:
                    *this = Precision::convert(tbin.logical_or(sbin), m_wrap);
                    break;
                case 3:
                    *this = Precision::convert(tbin.logical_xor(sbin), m_wrap);
                    break;
                case 4:
                    *this = Precision::convert(tbin.logical_inversion(), m_wrap);
                    break;
                default:
                    throw oper; //Should never happen
            }
            return *this;
        }
        INT_TEMPL_
        INT_INST_ INT_INST_::logical_operation(
            const INT_INST_& rhs,
            unsigned short oper
        )const{
            INT_INST_ s(rhs.base() != this->base()
                ? Precision::convert(rhs, m_wrap) : rhs);
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
                        *biter = (*biter * *siter)%m_wrap.base();
                        break;
                    case 2:
                        *biter = 
                            (
                                m_wrap.base() - 1
                                - ( ( (m_wrap.base()-1-*biter)%m_wrap.base() )
                                * ( (m_wrap.base()-1-*siter)%m_wrap.base() ) )
                                % m_wrap.base()
                            )%m_wrap.base();
                        break;
                    case 3:
                        *biter = (m_wrap.base()-(*biter + *siter)
                            %m_wrap.base())%m_wrap.base();
                        break;
                    case 4:
                        *biter = m_wrap.base() - 1 - *biter;
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
                        m_sign.negative() & s.m_sign.negative() ? -1 : 1,
                        m_wrap
                        );
                case 2:
                    return INT_INST_(big,
                        m_sign.negative() | s.m_sign.negative() ? -1 : 1,
                        m_wrap
                        );
                case 3:
                    return INT_INST_(big,
                        m_sign.negative() ^ s.m_sign.negative() ? -1 : 1,
                        m_wrap
                        );
                case 4:
                    return INT_INST_(big, -m_sign, m_wrap);
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
            {return lhs == INT_INST_(0, lhs.wrapper());}
    }
}

INT_TEMPL_
void swap(
    Precision::Dynamic_Base::INT_INST_& a,
    Precision::Dynamic_Base::INT_INST_& b
)   {a.swap(b);}
