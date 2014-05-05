#include "Precision_Math_Shared_Functions.h"

namespace Precision{
    namespace General_Base{
        namespace Complex{
    //Read-only
            COMP_TEMPL_
            typename Int::str_type Int::str()const
                {return m_real.str() + m_imag.str() + str_type(1, _symbols[6]);}

            COMP_TEMPL_
            typename Int::str_type Int::str_w_spaces()const{
                return
                    m_real.str()
                    + str_type(1, _symbols[4])
                    + m_imag.str()
                    + str_type(1, _symbols[4])
                    + str_type(1, _symbols[6])
                ;
            }

        //Set the precision through parameter
            COMP_TEMPL_
            typename Int::str_type Int::sci_note(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.sci_note(inPrec, inShowFull)
                    + m_imag.sci_note(inPrec, inShowFull)
                    + str_type(1, _symbols[6])
                ;
            }

            COMP_TEMPL_
            typename Int::str_type Int::sci_note_w_spaces(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.sci_note_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + m_imag.sci_note_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + str_type(1, _symbols[6])
                ;
            }

    //Constructors and destructor
            COMP_TEMPL_
            Int::Int(
                const scalar_type& new_real,
                const scalar_type& new_imag
            )
                : Number(new_real, new_imag)
            {}

            COMP_TEMPL_
            Int(const str_type& s)
                : Number(s)
            {}
        }
    }
}

namespace Precision{
    namespace General_Base{
        namespace Complex{
    //Read-only
            COMP_TEMPL_
            typename Float::str_type Float::str(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.str(inPrec, inShowFull)
                    + m_imag.str(inPrec, inShowFull)
                    + str_type(1, _symbols[6])
                ;
            }

            COMP_TEMPL_
            typename Float::str_type Float::str_w_spaces(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.str_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + m_imag.str_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + str_type(1, _symbols[6])
                ;
            }

            COMP_TEMPL_
            typename Float::size_type Float::precision()const
                {return m_real.precision();}

        //Set the precision through parameter
            COMP_TEMPL_
            typename Float::str_type Float::sci_note(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.sci_note(inPrec, inShowFull)
                    + m_imag.sci_note(inPrec, inShowFull)
                    + str_type(1, _symbols[6])
                ;
            }

            COMP_TEMPL_
            typename Float::str_type Float::sci_note_w_spaces(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.sci_note_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + m_imag.sci_note_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + str_type(1, _symbols[6])
                ;
            }

    //Constructors and destructor
            COMP_TEMPL_
            Float::Float(
                const scalar_type& new_real,
                const scalar_type& new_imag
            )
                : m_real(new_real)
                , m_imag(new_imag)
            {}

            COMP_TEMPL_
            Float::Float(const str_type& s, size_type inPrec)
                : Number(new_real, new_imag)
            {
                size_type pos(s.find(_symbols[0], 1));
                if(pos == str_type::npos)
                    pos = s.find(_symbols[1], 1);
                if(pos != str_type::npos){
                    m_real = scalar_type(s.substr(0, pos), inPrec);
                    if(pos < s.size()-1 && s.back() == _symbols[6])
                        m_imag = scalar_type(s.substr(pos+1, s.size()-1));
                }
            }
        }
    }
}

namespace Precision{
    namespace General_Base{
        namespace Complex{
    //Read-only
            COMP_TEMPL_
            typename Fract::str_type Fract::str(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.str(inPrec, inShowFull)
                    + m_imag.str(inPrec, inShowFull)
                    + str_type(1, _symbols[6])
                ;
            }

            COMP_TEMPL_
            typename Fract::str_type Fract::str_w_spaces(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.str_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + m_imag.str_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + str_type(1, _symbols[6])
                ;
            }

        //Set the precision through parameter
            COMP_TEMPL_
            typename Fract::str_type Fract::sci_note(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.sci_note(inPrec, inShowFull)
                    + m_imag.sci_note(inPrec, inShowFull)
                    + str_type(1, _symbols[6])
                ;
            }

            COMP_TEMPL_
            typename Fract::str_type Fract::sci_note_w_spaces(
                size_type inPrec,
                bool inShowFull
            )const{
                return
                    m_real.sci_note_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + m_imag.sci_note_w_spaces(inPrec, inShowFull)
                    + str_type(1, _symbols[4])
                    + str_type(1, _symbols[6])
                ;
            }

            COMP_TEMPL_
            typename Fract::size_type Fract::precision()const
                {return m_real.precision();}

            COMP_TEMPL_
            typename Fract::scalar_type Fract::gcd()const
                {return m_real.gcd(m_imag);}

            COMP_TEMPL_
            typename Fract::scalar_type Fract::gcd(const FRACT_INST_& s)const
                {return Math::gcd(this->gcd(), s.gcd());}

    //Constructors and destructor
            COMP_TEMPL_
            Fract::Fract(
                const scalar_type& new_real,
                const scalar_type& new_imag
            )
                : Number(new_real, new_imag)
            {}

            COMP_TEMPL_
            Fract::Fract(const str_type& s, size_type inPrec)
                : m_real(0)
                , m_imag(0)
            {
                size_type pos(s.find(_symbols[0], 1));
                if(pos == str_type::npos)
                    pos = s.find(_symbols[1], 1);
                if(pos != str_type::npos){
                    m_real = scalar_type(s.substr(0, pos), inPrec);
                    if(pos < s.size()-1 && s.back() == _symbols[6])
                        m_imag = scalar_type(s.substr(pos+1, s.size()-1));
                }
            }
        }
    }
}

namespace Precision{
    namespace General_Base{
        namespace Complex{
            template <INST_PARAMS_, typename ScalarType>
            void make_from_scalar(
                const ScalarType& new_real,
                const ScalarType& new_imag,
                COMP_INST* dest
            ){
                dest->real(new_real);
                dest->imaginary(new_imag);
            }

            template <INST_PARAMS_, typename ScalarType>
            void make_from_polar(
                const ScalarType& magnitude,
                const ScalarType& phase,
                COMP_INST* dest
            ){
                const ScalarType m2(magnitude*magnitude);
                dest->real(m2/(++Math::tan(phase)));
                dest->phase(Math::sqrt(m2 + dest->real()*dest->real()));
            }
        }
    }
}