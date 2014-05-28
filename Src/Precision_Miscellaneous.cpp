#include "Precision_Miscellaneous.h"

#include "Precision_Default.h"
#include "Precision_Literal_Operators.h"

#include <string>
#include <utility>
#include <map>

namespace Precision{
    namespace{
        const std::map<Precision::Int, std::string> NumberWordBank{
            std::make_pair("0"_P_Int, "zero"),
            std::make_pair("1"_P_Int, "one"),
            std::make_pair("2"_P_Int, "two"),
            std::make_pair("3"_P_Int, "three"),
            std::make_pair("4"_P_Int, "four"),
            std::make_pair("5"_P_Int, "five"),
            std::make_pair("6"_P_Int, "six"),
            std::make_pair("7"_P_Int, "seven"),
            std::make_pair("8"_P_Int, "eight"),
            std::make_pair("9"_P_Int, "nine"),
            std::make_pair("10"_P_Int, "ten"),
            std::make_pair("11"_P_Int, "eleven"),
            std::make_pair("12"_P_Int, "twelve"),
            std::make_pair("13"_P_Int, "thirteen"),
            std::make_pair("14"_P_Int, "fourteen"),
            std::make_pair("15"_P_Int, "fifteen"),
            std::make_pair("16"_P_Int, "sixteen"),
            std::make_pair("17"_P_Int, "seventeen"),
            std::make_pair("18"_P_Int, "eighteen"),
            std::make_pair("19"_P_Int, "nineteen"),
            std::make_pair("20"_P_Int, "twenty"),
            std::make_pair("30"_P_Int, "thirty"),
            std::make_pair("40"_P_Int, "forty"),
            std::make_pair("50"_P_Int, "fifty"),
            std::make_pair("60"_P_Int, "sixty"),
            std::make_pair("70"_P_Int, "seventy"),
            std::make_pair("80"_P_Int, "eighty"),
            std::make_pair("90"_P_Int, "ninety"),
            std::make_pair("1e2"_P_Int_E, "hundred"),
            std::make_pair("1e3"_P_Int_E, "thousand"),
            std::make_pair("1e6"_P_Int_E, "million"),
            std::make_pair("1e9"_P_Int_E, "billion"),
            std::make_pair("1e12"_P_Int_E, "trillion"),
            std::make_pair("1e15"_P_Int_E, "quadrillion"),
            std::make_pair("1e18"_P_Int_E, "quintillion"),
            std::make_pair("1e21"_P_Int_E, "sextillion"),
            std::make_pair("1e24"_P_Int_E, "septillion"),
            std::make_pair("1e27"_P_Int_E, "octillion"),
            std::make_pair("1e30"_P_Int_E, "nonillion"),
            std::make_pair("1e33"_P_Int_E, "decillion"),
        };
        const std::string k_and("and ");
        const unsigned k_ten(10), k_thousand(1e3);
    }
    std::string Num_to_Words(Int toconvert){
        std::string toreturn(toconvert.sign() == -1 ? "negative " : "");

        toconvert = toconvert.magnitude();
        while(toconvert > 0){
            size_t i( toconvert.count_digits() );
        //key1 accesses words of order 10, like "thousand"
        //key2 accesses the single digits words, like "one"
            Int
                key1(Math::exponentiate(Int(k_ten), Int(i-1))),
                key2(toconvert / key1)
            ;

        switch(i){
            case 1: //One digit
                toreturn += NumberWordBank.at(key2);
                break;
            case 2: //Two digits
                if(toconvert >= 2*k_ten)
                    toreturn
                        += NumberWordBank.at(key2 * k_ten)
                        + (toconvert%k_ten > 0 ? "-" : "")
                    ;
                else if(toconvert >= k_ten){
                    toreturn += NumberWordBank.at(toconvert);
                    return toreturn;
                }
                break;
            case 3: //Three digits
                toreturn += NumberWordBank.at(key2) + ' ';
                toreturn += NumberWordBank.at(key1) + ' ';
                break;
            default:    //Four or more digits
                key2 = toconvert;
                key1 = 1;
                while(key2.count_digits() > 3){
                    key1 *= k_thousand;
                    key2 /= k_thousand;
                }

                toreturn += Num_to_Words(key2) + ' ';
                toreturn += NumberWordBank.at(key1) + ' ';
                break;
        }
        //Stop adding things once toconvert is 0
            if(key1*key2 == toconvert) break;
        //Inserting "and"
            if(
                (i == 3 && toconvert%100 > 0) ||
                (i >= 4 && toconvert%k_thousand < 100)
            ) toreturn += k_and;

            toconvert -= key1*key2;
        }
        while(toreturn.back() == ' ') toreturn.pop_back();

        return toreturn;
    }
}
