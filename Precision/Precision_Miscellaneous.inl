namespace Precision{
    template <typename Integer_Type>
    bool palindrome(const Integer_Type& testee){
        typename Integer_Type::str_type test_string(testee.str().substr(1));
        const size_t max_s(test_string.size());
        for(size_t i(0); i < max_s/2; ++i)
            if(test_string[i] != test_string[max_s - i - 1])
                return false;
        return true;
    }
}