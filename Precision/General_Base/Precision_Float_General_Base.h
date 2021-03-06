#ifndef HH____PRECISION_FLOAT_IMPL_GENERAL_BASE_H
#define HH____PRECISION_FLOAT_IMPL_GENERAL_BASE_H

#include "Precision_Int_General_Base.h"
#include "Precision_UInt_General_Base.h"

#include "Impl/Precision_Tags.h"
#include "Impl/Shared_Constants.h"

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define FLOAT_TEMPL_                    \
    template <                          \
        typename CharT,                 \
        CharT const *const _0,          \
        typename ByteType,              \
        ByteType Base,                  \
        CharT const *const _symbols,    \
        template <typename...>          \
            class Container,            \
        typename SignType               \
    >

#define INST_PARAMS_                        \
        CharT, _0, ByteType, Base, _symbols, Container, SignType

#define FLOAT_INST_ Float <INST_PARAMS_>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0,
            typename ByteType = byte_type, ByteType Base = 10,
            CharT const *const _symbols = Constant::symbols,
            template <typename...> class Container = default_container_type,
            typename SignType = SignClass
        >
        class Float : Tag::Floating_Point, Tag::Signed, Tag::Static {
            public:
        //Type aliases
                using Integer       = Int<INST_PARAMS_>;
                using UInteger      = UInt<INST_PARAMS_>;
                using str_type      = typename Integer::str_type;
                using sign_type     = typename Integer::sign_type;
                using image_type    = typename Integer::image_type;
                using diglist_type  = typename Integer::diglist_type;
                using digit_type    = typename Integer::digit_type;
                using lli           = typename Integer::lli;
                using ld            = typename Integer::ld;
                using size_type     = typename Integer::size_type;
        //Arithmetic operators
                Float& operator+=(const Float&);
                Float& operator-=(const Float&);
                Float& operator*=(const Float&);
                Float& operator/=(const Float&);
                Float& operator%=(const Float&);
                Float& operator--();
                Float operator--(int);
                Float& operator++();
                Float operator++(int);

                Float operator-()const;
        //Other operators with different meaning
                    //Return the inverse
                Float operator~()const;
                    //Raise to the power of
                Float& operator^=(const Float&);
        //Read-only functions
                sign_type sign()const;
                bool even()const;
                bool odd()const;
                bool positive()const;
                bool negative()const;
                str_type str(size_type = 0, bool inShowFull = false)const;
            //Set the precision through parameter
                str_type sci_note(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
                str_type sci_note_w_spaces(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
                Float magnitude()const;
                size_type count_digits()const;
                size_type count_left_digits()const;
                size_type count_right_digits()const;
                size_type precision()const;
                short compare(const Float&)const;
                Integer integer()const;
                bool show_full()const;

                Float remainder(const Float&)const;
                Float inverse()const;
                bool is_integer()const;
                image_type digit(size_type)const;
                digit_type digit_10(size_type)const;

                static constexpr digit_type base();
                static constexpr image_type const * digit0();
        //Modifers
                bool show_full(bool);
                    //Multiplies integer by a power of Base
                void shift(lli);
                void shift_left(size_type);
                void shift_right(size_type);
                void sign(sign_type);
                void negate();
                Float& exponentiate(const Integer&);
                Float& exponentiate(const Float&);
                Float& invert();
                void swap(Float&);

        //Overload cast operators
                explicit operator Integer() const;

        //Constructors and destructor
                Float(ld = 0.0, size_type = k_default_prec);
                Float(const str_type&, size_type = k_default_prec);
                Float(const Integer&);
                Float(const Integer&, size_type p);
                Float(const UInteger&, size_type = k_default_prec);

                Float(const Float&)             = default;
                Float(Float&&)                  = default;
                Float& operator=(const Float&)  = default;
                Float& operator=(Float&&)       = default;
                ~Float()                        = default;
            protected:
        //Helpers
                void parse(const str_type&, size_type);
                void Update_Precision(size_type);
                Integer Generate_Operand(size_type)const;
            private:
            //Use a mantissa-like format
                Integer                 m_whole;
            //Precision represents the number of digits to
            //  the right of the decimal point.
                size_type               m_precision;
                bool                    m_show_full;
        };

        FLOAT_TEMPL_
        FLOAT_INST_ operator+(FLOAT_INST_, const FLOAT_INST_&);
        FLOAT_TEMPL_
        FLOAT_INST_ operator-(FLOAT_INST_, const FLOAT_INST_&);
        FLOAT_TEMPL_
        FLOAT_INST_ operator*(FLOAT_INST_, const FLOAT_INST_&);
        FLOAT_TEMPL_
        FLOAT_INST_ operator/(FLOAT_INST_, const FLOAT_INST_&);
        FLOAT_TEMPL_
        FLOAT_INST_ operator%(FLOAT_INST_, const FLOAT_INST_&);

        FLOAT_TEMPL_
        FLOAT_INST_ operator^(FLOAT_INST_, const FLOAT_INST_&);

        FLOAT_TEMPL_
        bool operator==(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator!=(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator>=(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator<=(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator>(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator<(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator!(const FLOAT_INST_&);
    }
}

FLOAT_TEMPL_
void swap(
    Precision::General_Base::FLOAT_INST_&,
    Precision::General_Base::FLOAT_INST_&
);

#include "Impl/Precision_Float_General_Base.inl"

#undef FLOAT_TEMPL_
#undef FLOAT_INST_
#undef INST_PARAMS_

#endif  //Include guard