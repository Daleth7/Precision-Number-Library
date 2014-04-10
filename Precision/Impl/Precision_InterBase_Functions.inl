#include "General_Base/Precision_Math_Shared_Functions.h"
#include <type_traits>

namespace Precision{
    namespace Helpers{
        template <typename Base_Return>
        Base_Return convert(const Base_Return& orig, std::true_type)
            {return orig;}
        template <typename Base_Return, typename Base_Param>
        Base_Return convert(const Base_Param& orig, std::false_type){
            if(Base_Param::base() == Base_Return::base()){
                typename Base_Return::diglist_type toreturn;
                for(size_t i(0); i < orig.count_digits(); ++i)
                    toreturn.push_back(orig.digit_10(i));
                std::reverse(toreturn.begin(), toreturn.end());
                return Base_Return(toreturn, orig.sign());
            }else{
                Base_Return
                    toreturn(0),
                    base_factor(Math::exponentiate(
                        Base_Return(Base_Param::base()),
                        orig.count_digits()-1
                    ))
                ;
                for(
                    size_t i(0);
                    i < orig.count_digits();
                    ++i, base_factor /= Base_Param::base()
                )   toreturn += base_factor * Base_Return(orig.digit_10(i));
                return toreturn;
            }
        }
    }

    template <typename Base_Return, typename Base_Param>
    Base_Return convert(const Base_Param& orig){
        return Helpers::convert<Base_Return>
            (orig, typename std::is_same<Base_Return, Base_Param>::type());
    }
}
