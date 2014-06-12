#include <iterator>
#include <algorithm>

namespace Precision{
    namespace Image_Set_Wrapper{
//Read only
        ISW_TEMPL_
        bool ISW_INST_::is_valid(const_reference testee)const
            {return is_valid_helper(testee, policy());}

        ISW_TEMPL_
        template <typename DiffSearchPol>
        bool ISW_INST_::is_valid(const_reference testee)const
            {return is_valid_helper(testee, DiffSearchPol());}

        ISW_TEMPL_
        auto ISW_INST_::get_index(const_reference testee)const -> size_type{
            iterator_type end(m_0);
            std::advance(end, m_base);
            return this->get_index_sifter(testee, m_0, end, policy());
        }

        ISW_TEMPL_
        template <typename DiffSearchPol>
        auto ISW_INST_::get_index(const_reference testee)const -> size_type{
            iterator_type end(m_0);
            std::advance(end, m_base);
            return this->get_index_sifter(testee, m_0, end, DiffSearchPol());
        }

        ISW_TEMPL_
        auto ISW_INST_::image(size_type index)const -> const_reference{
            iterator_type temp_copy(m_0);
            std::advance(temp_copy, index);
            return *temp_copy;
        }

        ISW_TEMPL_
        auto ISW_INST_::operator[](size_type index)const -> const_reference
            {return image(index);}

        ISW_TEMPL_
        auto ISW_INST_::symbol(size_type index)const -> const_reference{
            iterator_type temp_copy(m_symbols);
            std::advance(temp_copy, index);
            return *temp_copy;
        }

        ISW_TEMPL_
        auto ISW_INST_::plus()const -> const_reference
            {return *m_symbols;}

        ISW_TEMPL_
        auto ISW_INST_::minus()const -> const_reference
            {return symbol(1);}

        ISW_TEMPL_
        auto ISW_INST_::point()const -> const_reference
            {return symbol(2);}

        ISW_TEMPL_
        auto ISW_INST_::exponent()const -> const_reference
            {return symbol(3);}

        ISW_TEMPL_
        auto ISW_INST_::space()const -> const_reference
            {return symbol(4);}

        ISW_TEMPL_
        auto ISW_INST_::slash()const -> const_reference
            {return symbol(5);}

        ISW_TEMPL_
        auto ISW_INST_::imaginary()const -> const_reference
            {return symbol(6);}

        ISW_TEMPL_
        auto ISW_INST_::base()const -> digit_type
            {return m_base;}

        ISW_TEMPL_
        auto ISW_INST_::digit0()const -> const iterator_type&
            {return m_0;}

        ISW_TEMPL_
        auto ISW_INST_::symbols()const -> const iterator_type&
            {return m_symbols;}

//Modifiers
        ISW_TEMPL_
        void ISW_INST_::base(digit_type new_base)
            {m_base = new_base;}

        ISW_TEMPL_
        void ISW_INST_::digit0(const iterator_type& new_0)
            {m_0 = new_0;}

        ISW_TEMPL_
        void ISW_INST_::symbols(const iterator_type& new_sym)
            {m_symbols = new_sym;}

//Constructors and destructor
        ISW_TEMPL_
        constexpr ISW_INST_::type(
            const iterator_type& new_0,
            const iterator_type& new_symbols,
            digit_type new_base
        )
            : m_0(new_0)
            , m_symbols(new_symbols)
            , m_base(new_base)
        {}

//Helpers
        ISW_TEMPL_
        bool ISW_INST_::is_valid_helper(
            const_reference testee,
            Search_Policy::Normal
        )const{return this->get_index(testee) < m_base;}

        ISW_TEMPL_
        bool ISW_INST_::is_valid_helper(
            const_reference testee,
            Search_Policy::Binary
        )const{
            iterator_type end(m_0);
            std::advance(end, m_base);
            return std::binary_search(m_0, end, testee);
        }

        ISW_TEMPL_
        auto ISW_INST_::get_index_sifter(
            const_reference testee,
            const iterator_type& begin,
            const iterator_type& end,
            Search_Policy::Normal
        )const -> size_type {
            --end;
            while(std::distance(begin, end) >= 0){
                if(testee == *begin)
                    return std::distance(m_0, begin);
                else if(testee == *end)
                    return std::distance(m_0, end);
                ++begin, --end;
            }
            return m_base;
        }

        ISW_TEMPL_
        auto ISW_INST_::get_index_sifter(
            const_reference testee,
            const iterator_type& begin,
            const iterator_type& end,
            Search_Policy::Binary
        )const -> size_type
        {return this->get_index_bin_helper(testee, begin, end);}

        ISW_TEMPL_
        auto ISW_INST_::get_index_bin_helper(
            const_reference testee,
            const iterator_type& begin,
            const iterator_type& end
        )const -> size_type {
            if(std::distance(begin, end) <= 0)
                return m_base;
            iterator_type mid(begin);
            std::advance(mid, std::distance(begin, end)/2);
            if(testee < *mid)
                return get_index_bin_helper(testee, begin, mid);
            else if(*mid < testee)
                return get_index_bin_helper(testee, mid, end);
            return std::distance(m_0, mid);
        }
    }
}