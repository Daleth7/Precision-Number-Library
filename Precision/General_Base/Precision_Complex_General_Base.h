#ifndef PRECISION_COMPLEX_NUMBER_DEFINITION___H___
#define PRECISION_COMPLEX_NUMBER_DEFINITION___H___

#include "Precision_Complex_Number_General_Base.h"

#include "Precision_Int_General_Base.h"
#include "Precision_Float_General_Base.h"
#include "Precision_Fract_General_Base.h"

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define COMP_TEMPL_                     \
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

#define INST_PARAMS_                            \
        CharT, _0, ByteType, Base, _symbols,    \
        Container, SignType, ScalarType

namespace Precision{
    namespace General_Base{
        namespace Complex{
        //For the rest of the interfaces, refer to
        //  Precision_Complex_Number_General_Base.h"
            template <
                typename CharT, CharT const *const _0,
                typename ByteType = byte_type, ByteType Base = 10,
                CharT const *const _symbols = Constant::symbols,
                template <typename...> class Container = default_container_type,
                typename SignType = SignClass,
                typename ScalarType = General_Base::Int<INST_PARAMS_>
            >
            struct Int : Tag::Integral, Tag::Signed, Number<INT_INST_>{
        //Read-only
                str_type str()const;
                str_type str_w_spaces()const;
            //Set the precision through parameter
                str_type sci_note(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
                str_type sci_note_w_spaces(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
        //Constructors and destructor
                Int(
                    const scalar_type& new_real = scalar_type(0),
                    const scalar_type& new_imag = scalar_type(0)
                );
                Int(const str_type&);
                Int(const INT_INST_&)                   = default;
                Int(INT_INST_&&)                        = default;
                INT_INST_& operator=(const INT_INST_&)  = default;
                INT_INST_& operator=(INT_INST_&&)       = default;
                ~Int()                                  = default;
            };

            template <
                typename CharT, CharT const *const _0,
                typename ByteType = byte_type, ByteType Base = 10,
                CharT const *const _symbols = Constant::symbols,
                template <typename...> class Container = default_container_type,
                typename SignType = SignClass,
                typename ScalarType = General_Base::Float<INST_PARAMS_>
            >
            struct Float : Tag::Floating, Tag::Signed, Number<FLOAT_INST_>{
        //Read-only
                str_type str(size_type = 0, bool inShowFull = false)const;
                str_type str_w_spaces(size_type = 0, bool inShowFull = false)const;
                size_type precision()const;
            //Set the precision through parameter
                str_type sci_note(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
                str_type sci_note_w_spaces(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
        //Constructors and destructor
                Float(
                    const scalar_type& new_real = scalar_type(0),
                    const scalar_type& new_imag = scalar_type(0)
                );
                Float(const str_type&, size_type = k_default_prec);
                Float(const FLOAT_INST_&)                   = default;
                Float(FLOAT_INST_&&)                        = default;
                FLOAT_INST_& operator=(const FLOAT_INST_&)  = default;
                FLOAT_INST_& operator=(FLOAT_INST_&&)       = default;
                ~Float()                                    = default;
            };

            template <
                typename CharT, CharT const *const _0,
                typename ByteType = byte_type, ByteType Base = 10,
                CharT const *const _symbols = Constant::symbols,
                template <typename...> class Container = default_container_type,
                typename SignType = SignClass,
                typename ScalarType = General_Base::Fract<INST_PARAMS_>
            >
            struct Fract : Tag::Fraction, Tag::Signed, Number<FRACT_INST_>{
        //Read-only
                str_type str(size_type = 0, bool inShowFull = false)const;
                str_type str_w_spaces(size_type = 0, bool inShowFull = false)const;
            //Set the precision through parameter
                str_type sci_note(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
                str_type sci_note_w_spaces(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
                size_type precision()const;
                scalar_type gcd()const;
                scalar_type gcd(const FRACT_INST_&)const;
        //Constructors and destructor
                Fract(
                    const scalar_type& new_real = scalar_type(0),
                    const scalar_type& new_imag = scalar_type(0)
                );
                Fract(const str_type&, size_type = k_default_prec);
                Fract(const FRACT_INST_&)                   = default;
                Fract(FRACT_INST_&&)                        = default;
                FRACT_INST_& operator=(const FRACT_INST_&)  = default;
                FRACT_INST_& operator=(FRACT_INST_&&)       = default;
                ~Fract()                                    = default;
            };

            template <INST_PARAMS_, typename ScalarType>
            void make_from_scalar(
                const ScalarType& real,
                const ScalarType& imaginary,
                COMP_INST*
            );
            template <INST_PARAMS_, typename ScalarType>
            void make_from_polar(
                const ScalarType& magnitude,
                const ScalarType& phase,
                COMP_INST*
            );
        }
    }
}

#include "Impl/Precision_Complex_General_Base.inl"

#undef COMP_TEMPL_
#undef INST_PARAMS_

#endif