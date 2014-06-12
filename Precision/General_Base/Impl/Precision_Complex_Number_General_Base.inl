#include "Precision_Math_Shared_Functions.h"

namespace Precision{
    namespace General_Base{
        namespace Complex{
    //Arithmetic operators
            COMP_TEMPL_
            COMP_INST_& Complex::operator+=(const COMP_INST_& s)
                {return mreal += s.m_real, m_imag += s.m_imag, *this;}

            COMP_TEMPL_
            COMP_INST_& Complex::operator-=(const COMP_INST_& s)
                {return mreal -= s.m_real, m_imag -= s.m_imag, *this;}

            COMP_TEMPL_
            COMP_INST_& Complex::operator*=(const COMP_INST_& s){
                m_real = s.m_real*m_real - s.m_imag*m_imag;
                m_imag = s.m_real*m_imag + s.m_imag*m_real;
                return *this;
            }

            COMP_TEMPL_
            COMP_INST_& Complex::operator/=(const COMP_INST_& s){
                const scalar_type denom
                    = s.m_real*s.m_real - s.m_image*s.m_imag;
                *this *= COMP_INST_(s.m_real, -s.m_imag);
                m_real /= denom;
                m_imag /= denom;
                return *this;
            }

            COMP_TEMPL_
            COMP_INST_ Complex::operator-()const
                {return m_real.negate(), m_imag.negate(), *this;}

        //Read-only functions
            COMP_TEMPL_
            typename Complex::sign_type Complex::sign(bool wants_1)const
                {return wants_1 ? m_real.sign() : m_imag.sign();}

            COMP_TEMPL_
            const typename Complex::scalar_type& Complex::real()const
                {return m_real;}

            COMP_TEMPL_
            const typename Complex::scalar_type& Complex::imaginary()const
                {return m_imag;}

            COMP_TEMPL_
            typename Complex::scalar_type Complex::magnitude()const
                {return Math::sqrt(m_real*m_real + m_imag*m_imag);}

            COMP_TEMPL_
            typename Complex::scalar_type Complex::phase()const
                {return Math::arctan(m_imag/m_real);}

            COMP_TEMPL_
            short Complex::compare(const COMP_INST_& s)const{
                short p(this->phase().compare(s.phase()));
                if(p != 0)  return p;
                else        return this->magnitude().compare(s.magnitude());
            }

            COMP_TEMPL_
            constexpr digit_type Complex::base()
                {return scalar_type::base();}

            COMP_TEMPL_
            constexpr digit_type Complex::digit0()
                {return scalar_type::digit0();}

        //Modifers
            COMP_TEMPL_
            void Complex::sign(sign_type s, bool wants_1)
                {wants_1 ? m_real.sign(s) : m_imag.sign(s);}

            COMP_TEMPL_
            void real(const scalar_type& r)
                {m_real = r;}
                   
            COMP_TEMPL_ 
            void imaginary(const scalar_type& i)
                {m_imag = i;}

            COMP_TEMPL_
            void Complex::negate()
                {m_real.negate(), m_imag.negate();}

            COMP_TEMPL_
            void Complex::swap(COMP_INST_& s){
                m_real.swap(s.m_real);
                m_imag.swap(s.m_imag);
            }

    //Constructors and destructor
            COMP_TEMPL_
            Complex::Complex(
                const scalar_type& new_real,
                const scalar_type& new_imag
            )
                : m_real(new_real)
                , m_imag(new_imag)
            {}

            COMP_TEMPL_
            Complex::Complex(
                scalar_type&& new_real,
                scalar_type&& new_imag
            )
                : m_real(std::move(new_real))
                , m_imag(std::move(new_imag))
            {}

            COMP_TEMPL_
            Complex::Complex(const str_type& s)
                : m_real(0)
                , m_imag(0)
            {
                size_type pos(s.find(_symbols[0], 1));
                if(pos == str_type::npos)
                    pos = s.find(_symbols[1], 1);
                if(pos != str_type::npos){
                    m_real = scalar_type(s.substr(0, pos));
                    if(pos < s.size()-1 && s.back() == _symbols[6])
                        m_imag = scalar_type(s.substr(pos+1, s.size()-1));
                }
            }
        }
    }
}