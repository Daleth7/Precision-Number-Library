#include <cstddef>

namespace Precision{
    template<typename IntegerType>
    IntegerType convert(
        const IntegerType& orig,
        const typename IntegerType::wrapper_type& new_wrap
    ){
        if(new_wrap.base() == orig.base()){
            IntegerType toreturn(orig);
            toreturn.wrapper(new_wrap);
            return toreturn;
        }else if(orig.base() == 0)
            return IntegerType(new_wrap);

        IntegerType toreturn(new_wrap), base_factor(1, new_wrap);

        const std::size_t lim(orig.count_digits());
        for(
            std::size_t i(0);
            i < lim ;
            ++i, base_factor *= IntegerType(orig.base(), new_wrap)
        )
            toreturn += base_factor * IntegerType(orig.digit_10(i), new_wrap);
        toreturn.sign(orig.sign());
        return toreturn;
    }
}