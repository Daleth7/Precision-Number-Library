#include <algorithm>
#include <iterator>

namespace Precision{
    namespace General_Base{
    //Read-only
        template <typename Integer_Type>
        auto Random<Integer_Type>::seed()const->type const &
            {return m_seed;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::max()const->type const &
            {return m_max;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::min()const->type const &
            {return m_min;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::and1()const->type const &
            {return m_and1;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::and2()const->type const &
            {return m_and2;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::and3()const->type const &
            {return m_and3;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::and4()const->type const &
            {return m_and4;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::order_of_entropy()const->lli
            {return m_order_of_entropy;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::push1()const->size_type
            {return m_push1;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::push2()const->size_type
            {return m_push2;}

        template <typename Integer_Type>
        auto Random<Integer_Type>::push3()const->size_type
            {return m_push3;}

        template <typename Integer_Type>
        constexpr auto Random<Integer_Type>::base()->digit_type
            {return wrap::base;}

    //Retrive and/or change state

        template <typename Integer_Type>
        auto Random<Integer_Type>::operator()()->type
            {return this->generate(typename std::is_fundamental<type>::type());}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::discard()
            {return this->generate
                (typename std::is_fundamental<type>::type()), *this;}
    //Change settings

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::seed(const type& new_seed)
            {return m_seed = new_seed, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::max(const type& new_max)
            {return m_max = new_max, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::min(const type& new_min)
            {return m_min = new_min, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::and1(const type& a1)
            {return m_and1 = a1, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::and2(const type& a2)
            {return m_and1 = a2, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::and3(const type& a3)
            {return m_and1 = a3, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::and4(const type& a4)
            {return m_and1 = a4, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>&
            Random<Integer_Type>::order_of_entropy(lli ooe)
        {return m_order_of_entropy = ooe, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::push1(size_type p1)
            {return m_push1 = p1, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::push2(size_type p2)
            {return m_push1 = p2, *this;}

        template <typename Integer_Type>
        Random<Integer_Type>& Random<Integer_Type>::push3(size_type p3)
            {return m_push1 = p3, *this;}

    //Constructor

        template <typename Integer_Type>
        Random<Integer_Type>::Random(
            const type& INseed,
            const type& INmax, const type& INmin,
            bool call_discard,
            lli INorder_of_entropy,
            const type& INand1, const type& INand2,
            const type& INand3, const type& INand4,
            size_type INpush1, size_type INpush2, size_type INpush3
        )
            : m_seed(wrap::positive(INseed) ? INseed : 1)
            , m_max(INmax), m_min(INmin)
            , m_and1(INand1), m_and2(INand2), m_and3(INand3), m_and4(INand4)
            , m_order_of_entropy(INorder_of_entropy)
            , m_push1(INpush1), m_push2(INpush2), m_push3(INpush3)
        {
            if(call_discard){
                size_type i(7);
                while(i-- > 0)
                    this->discard();
            }
        }

        template <typename IntegerType>
        auto Random<IntegerType>::generate(std::true_type) -> type
        {
        //Algorithm is a modified form of the SFMT as described in this paper:
        // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/sfmt.pdf
            const size_type quad(sizeof(type)>>1);
            type
                word_1(m_seed & ((1<<quad)-1)),
                word_2((m_seed & ((1<<(quad*2))-1)) ^ word_1),
                word_3((m_seed & ((1<<(quad*3))-1)) ^ word_1 ^ word_2),
                word_4(m_seed ^ word_1 ^ word_2 ^ word_3)
            ;
            m_seed *= m_order_of_entropy;
            m_seed ^=
                (m_seed << m_push1)                     //wA
                ^ (
                    ((word_1 >> m_push2) & m_and1)
                    ^ ((word_2  >> m_push2) & m_and2)
                    ^ ((word_3 >> m_push2) & m_and3)
                    ^ ((word_4 >> m_push2) & m_and4)
                    )                                   //wB
                ^ (m_seed >> m_push1)                   //wC
                ^ (m_seed << m_push3)                   //wD
            ;

            return m_seed = m_seed%(m_max-m_min) + m_min;
        }

        template <typename IntegerType>
        auto Random<IntegerType>::generate(std::false_type) -> type
        {
        //Algorithm is a modified form of the SFMT as described in this paper:
        // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/sfmt.pdf
            typedef typename type::diglist_type digit_list;
            digit_list image(m_seed.digit_list());
            auto it1 = image.begin(), it2 = it1, it3 = it1;
                const size_type quad(image.size()/4);
                std::advance(it2, quad);
                std::advance(it3, quad<<1);
            m_seed.shift(m_order_of_entropy);
            image =
                m_seed
                . logical_shift_left(m_push1)
                . logical_xor(m_seed)                                   //wA
                . logical_xor(
                    type(digit_list(image.begin(), it1), 1)
                        . logical_shift_right(m_push2)
                        . logical_and(m_and1)
                        . logical_shift_left(quad*3)
                    + type(digit_list(it1, it2), 1)
                        . logical_shift_right(m_push2)
                        . logical_and(m_and2)
                        . logical_shift_left(quad*2)
                    + type(digit_list(it2, it3), 1)
                        . logical_shift_right(m_push2)
                        . logical_and(m_and3)
                        . logical_shift_left(quad)
                    + type(digit_list(it3, image.end()), 1)
                        . logical_shift_right(m_push2)
                        . logical_and(m_and4)
                    )                                                   //wB
                . logical_xor(m_seed.logical_shift_right(m_push1))      //wC
                . logical_xor(m_seed.logical_shift_left(m_push3))       //wD
                . digit_list()
            ;

            std::reverse(image.begin(), image.end());
            return m_seed = (type(image, 1)%(m_max-m_min) + m_min);
        }
    }
}
