#include "Precision_Miscellaneous.h"

#include "Precision_Default.h"

#include <string>
#include <utility>
#include <map>

namespace Precision{
    namespace{
        const std::map<Precision::Int, std::string> NumberWordBank{
            std::make_pair("0"_p_int, "zero"),
            std::make_pair("1"_p_int, "one"),
            std::make_pair("2"_p_int, "two"),
            std::make_pair("3"_p_int, "three"),
            std::make_pair("4"_p_int, "four"),
            std::make_pair("5"_p_int, "five"),
            std::make_pair("6"_p_int, "six"),
            std::make_pair("7"_p_int, "seven"),
            std::make_pair("8"_p_int, "eight"),
            std::make_pair("9"_p_int, "nine"),
            std::make_pair("10"_p_int, "ten"),
            std::make_pair("11"_p_int, "eleven"),
            std::make_pair("12"_p_int, "twelve"),
            std::make_pair("13"_p_int, "thirteen"),
            std::make_pair("14"_p_int, "fourteen"),
            std::make_pair("15"_p_int, "fifteen"),
            std::make_pair("16"_p_int, "sixteen"),
            std::make_pair("17"_p_int, "seventeen"),
            std::make_pair("18"_p_int, "eighteen"),
            std::make_pair("19"_p_int, "nineteen"),
            std::make_pair("20"_p_int, "twenty"),
            std::make_pair("30"_p_int, "thirty"),
            std::make_pair("40"_p_int, "forty"),
            std::make_pair("50"_p_int, "fifty"),
            std::make_pair("60"_p_int, "sixty"),
            std::make_pair("70"_p_int, "seventy"),
            std::make_pair("80"_p_int, "eighty"),
            std::make_pair("90"_p_int, "ninety"),
            std::make_pair("1e2"_p_int, "hundred"),
            std::make_pair("1e3"_p_int, "thousand"),
            std::make_pair("1e6"_p_int, "million"),
            std::make_pair("1e9"_p_int, "billion"),
            std::make_pair("1e12"_p_int, "trillion"),
            std::make_pair("1e15"_p_int, "quadrillion"),
            std::make_pair("1e18"_p_int, "quintillion"),
            std::make_pair("1e21"_p_int, "sextillion"),
            std::make_pair("1e24"_p_int, "septillion"),
            std::make_pair("1e27"_p_int, "octillion"),
            std::make_pair("1e30"_p_int, "nonillion"),
            std::make_pair("1e33"_p_int, "decillion"),
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
