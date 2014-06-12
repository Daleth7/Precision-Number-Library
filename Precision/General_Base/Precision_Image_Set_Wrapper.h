#ifndef IMAGE_SET_WRAPPER_____H___
#define IMAGE_SET_WRAPPER_____H___

#include "Precision_Search_Policy.h"
#include "Impl/Shared_Constants.h"

#include <cstddef>

#define ISW_TEMPL_ template <   \
        typename CharT,         \
        typename CharTIterator, \
        typename ByteType,      \
        class SearchPolicy      \
    >

#define ISW_INST_ type<CharT, CharTIterator, ByteType, SearchPolicy>

namespace Precision{
    namespace Image_Set_Wrapper{
        template <
            typename CharT,
            typename CharTIterator, // Must dereference to a constant value
            typename ByteType = byte_type,
            class SearchPolicy = Search_Policy::Normal
        >
        class type{
            public:
        //Type aliases
                using image_type        = CharT;
                using const_reference   = const image_type&;
                using iterator_type     = CharTIterator;
                using policy            = SearchPolicy;
                using size_type         = std::size_t;
                using digit_type        = ByteType;

        //Read only
                bool is_valid(const_reference)const;
                template <typename DiffSearchPol>
                    bool is_valid(const_reference)const;
                size_type get_index(const_reference)const;
                template <typename DiffSearchPol>
                    size_type get_index(const_reference)const;
                const_reference image(size_type)const;
                const_reference operator[](size_type)const;
                const_reference symbol(size_type)const;
                const_reference plus()const;
                const_reference minus()const;
                const_reference point()const;
                const_reference exponent()const;
                const_reference space()const;
                const_reference slash()const;
                const_reference imaginary()const;
                digit_type base()const;
                const iterator_type& digit0()const;
                const iterator_type& symbols()const;

        //Modifiers
                void base(digit_type);
                void digit0(const iterator_type&);
                void symbols(const iterator_type&);

        //Constructors and destructor
                constexpr type(
                    const iterator_type&,
                    const iterator_type&,
                    digit_type
                );

                type()                                  = default;
                type(const ISW_INST_&)                  = default;
                type(ISW_INST_&&)                       = default;
                ISW_INST_& operator=(const ISW_INST_&)  = default;
                ISW_INST_& operator=(ISW_INST_&&)       = default;
                ~type()                                 = default;

            protected:
        //Helpers
                bool is_valid_helper(const_reference, Search_Policy::Normal)const;
                bool is_valid_helper(const_reference, Search_Policy::Binary)const;

                size_type get_index_sifter(
                    const_reference,
                    const iterator_type&,
                    const iterator_type&,
                    Search_Policy::Normal
                )const;

                size_type get_index_sifter(
                    const_reference,
                    const iterator_type&,
                    const iterator_type&,
                    Search_Policy::Binary
                )const;

                size_type get_index_bin_helper(
                    const_reference,
                    const iterator_type&,
                    const iterator_type&
                )const;

            private:
                iterator_type   m_0;
                iterator_type   m_symbols;
                digit_type      m_base;
        };
    }
}

#include "Impl/Precision_Image_Set_Wrapper.inl"

#endif