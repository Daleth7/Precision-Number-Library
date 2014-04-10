namespace Precision{
    namespace Math{
        template <typename Integer_Type>
        Integer_Type fibonacci(size_t* term_holder, size_t term){
            static Integer_Type toreturn(1), hold1(1), hold2(0);
            static size_t curr_term(2);
            if(term > 1)
                toreturn = 1, hold1 = 1, hold2 = 0, --term;
            curr_term += term;
            for(; term > 0; --term)
                hold2 = toreturn, toreturn += hold1, hold1 = hold2;
            if(term_holder != nullptr) *term_holder = curr_term;
            return toreturn;
        }

        template <typename OutIter>
        void erato_sieve(OutIter dest, size_t max){
            const size_t init_prime(2);
            static std::vector<bool> flags((max-init_prime), true);
            static bool already_filled(false);

            if(!already_filled && max != flags.size()){
                flags.resize(max);
                size_t init(0);
                while(init < flags.size()){
                    size_t iter(init), gap(init + init_prime);

                    while((iter += gap) < flags.size())
                        flags[iter] = false;
                    
                    while(!flags[++init] && init < flags.size());
                }
                already_filled = true;
            }
            for(size_t i(0); i < flags.size(); ++i){
                if(flags[i])
                    *(dest++) = (i + init_prime);
            }
        }

        template <typename Floating_Type>
        Floating_Type remainder(const Floating_Type& f, const Floating_Type& s)
            {return f.remainder(s);}
    }
}