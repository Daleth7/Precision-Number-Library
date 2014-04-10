#define SEQ_TEMP_ template <                    \
        typename NumberType,                    \
        template<typename...> class Container,  \
        typename GeneratorType                  \
    >
#define SEQ_INST_ Sequence<NumberType, Container, GeneratorType>

#include <utility>
#include <iterator>
#include <stdexcept>
#include <string>

namespace Precision{
//Read-only
    SEQ_TEMP_
    bool SEQ_INST_::empty()const
        {return m_series.empty();}

    SEQ_TEMP_
    typename SEQ_INST_::size_type SEQ_INST_::size()const
        {return m_series.size();}

    SEQ_TEMP_
    typename SEQ_INST_::const_reference SEQ_INST_::operator[](size_type n)const
        {return this->at(n);}

    SEQ_TEMP_
    typename SEQ_INST_::const_reference SEQ_INST_::at(size_type n)const{
        if(!valid_index(n))
            throw std::out_of_range(
                "Precision::Sequence::"
                + std::string(__func__)
            );
        const_iterator it = this->cbegin();
        std::advance(it, n-m_start);
        return *it;
    }

    SEQ_TEMP_
    typename SEQ_INST_::size_type SEQ_INST_::first_index()const
        {return m_start;}

    SEQ_TEMP_
    typename SEQ_INST_::size_type SEQ_INST_::last_index()const
        {return m_series.size()-1+m_start;}

    SEQ_TEMP_
    const typename SEQ_INST_::generator_type& SEQ_INST_::generator()const
        {return m_gen;}

    SEQ_TEMP_
    typename SEQ_INST_::const_reference SEQ_INST_::front()const
        {return *m_series.begin();}

    SEQ_TEMP_
    typename SEQ_INST_::const_reference SEQ_INST_::back()const
        {return *m_series.rbegin();}

    SEQ_TEMP_
    SEQ_INST_ SEQ_INST_::subseries(size_type start, size_type stop)const{
        if(!valid_index(start))                 start = m_start;
        if(!valid_index(stop) || stop <= start) stop = this->last_index();
        const_iterator it = this->cbegin(), it2 = this->cbegin();
        std::advance(it, start - m_start);
        std::advance(it2, stop - start + m_start);
        return SEQ_INST_(it, it2, m_gen, start);
    }

    SEQ_TEMP_
    typename SEQ_INST_::value_type SEQ_INST_::sum(
        size_type start,
        size_type stop
    )const{
        if(!valid_index(start))                 start = m_start;
        if(!valid_index(stop) || stop <= start) stop = this->last_index()+1;
        const_iterator it = this->cbegin(), it2 = this->cbegin();
        std::advance(it, start - m_start);
        std::advance(it2, start - m_start + stop);
        value_type toreturn(0);
        while(it != it2)    toreturn += *(it++);
        return toreturn;
    }

    SEQ_TEMP_
    typename SEQ_INST_::value_type SEQ_INST_::product(
        size_type start,
        size_type stop
    )const{
        if(!valid_index(start))                 start = m_start;
        if(!valid_index(stop) || stop <= start) stop = this->last_index()+1;
        const_iterator it = this->cbegin(), it2 = this->cbegin();
        std::advance(it, start - m_start);
        std::advance(it2, start - m_start + stop);
        value_type toreturn(1);
        while(it != it2)    toreturn *= *(it++);
        return toreturn;
    }

    SEQ_TEMP_
    short SEQ_INST_::compare(const SEQ_INST_& s)const{
        if(m_series == s.m_series)      return 0;
        else if(m_series < s.m_series)  return -1;
        else                            return 1;
    }

    SEQ_TEMP_
    typename SEQ_INST_::size_type SEQ_INST_::max_size()const
        {return m_series.max_size();}

//Modifiers

    SEQ_TEMP_
    void SEQ_INST_::pop_front(size_type num){
        if(num >= m_series.size()){
            this->clear();
            return;
        }
        while(num-- > 0){
            ++m_start;
            m_series.erase(m_series.begin());
        }
    }

    SEQ_TEMP_
    void SEQ_INST_::pop_back(size_type num){
        if(num >= m_series.size()){
            this->clear();
            return;
        }
        while(num-- > 0){
            ++m_start;
            m_series.pop_back();
        }
    }


    SEQ_TEMP_
    void SEQ_INST_::push_front(const value_type& val, size_type num){
        if(num >= m_series.size()){
            this->clear();
            return;
        }
        while(num-- > 0)    m_series.insert(m_series.begin(), val);
    }

    SEQ_TEMP_
    void SEQ_INST_::push_back(const value_type& val, size_type num){
        if(num >= m_series.size()){
            this->clear();
            return;
        }
        while(num-- > 0)    m_series.push_back(val);
    }

    SEQ_TEMP_
    void SEQ_INST_::generate(size_type num){
        while(num-- > 0)
            m_series.push_back(m_gen(m_series.size()+m_start));
    }

    SEQ_TEMP_
    template <typename... ArgPack>
    void SEQ_INST_::generate(size_type num, ArgPack... pack){
        while(num-- > 0){
            m_series.push_back(m_gen(
                m_series.size()+m_start,
                std::forward<ArgPack>(pack)...
            ));
        }
    }

    SEQ_TEMP_
    void SEQ_INST_::resize(size_type new_size){
        if(new_size < m_series.size())
            this->pop_back(m_series.size() - new_size);
        else if(new_size > m_series.size())
            this->generate(new_size - m_series.size());
    }

    SEQ_TEMP_
    void SEQ_INST_::clear()
        {m_series.clear();}

    SEQ_TEMP_
    void SEQ_INST_::swap(SEQ_INST_& s){
        std::swap(m_start, s.m_start);
        std::swap(m_gen, s.m_gen);
        std::swap(m_series, s.m_series);
    }


    SEQ_TEMP_
    typename SEQ_INST_::reference SEQ_INST_::operator[](size_type n){
        if(!valid_index(n))
            throw std::out_of_range("Precision::Sequence::operator[](size_type)");
        iterator it = this->begin();
        std::advance(it, n-m_start);
        return *it;
    }

    SEQ_TEMP_
    void SEQ_INST_::first_index(size_type new_start)
        {m_start = new_start;}

    SEQ_TEMP_
    void SEQ_INST_::last_index(size_type new_end){
        if(new_end > this->last_index())
            this->generate(new_end - this->last_index());
        else
            this->pop_back(this->last_index() - new_end);
    }

    SEQ_TEMP_
    void SEQ_INST_::generator(const generator_type& new_gen)
        {m_gen = new_gen;}


    SEQ_TEMP_
    typename SEQ_INST_::const_iterator SEQ_INST_::begin()const
        {return m_series.cbegin();}

    SEQ_TEMP_
    typename SEQ_INST_::const_iterator SEQ_INST_::end()const
        {return m_series.cend();}

    SEQ_TEMP_
    typename SEQ_INST_::const_reverse_iterator SEQ_INST_::rbegin()const
        {return m_series.crbegin();}

    SEQ_TEMP_
    typename SEQ_INST_::const_reverse_iterator SEQ_INST_::rend()const
        {return m_series.crend();}

    SEQ_TEMP_
    typename SEQ_INST_::const_iterator SEQ_INST_::cbegin()const
        {return m_series.cbegin();}

    SEQ_TEMP_
    typename SEQ_INST_::const_iterator SEQ_INST_::cend()const
        {return m_series.cend();}

    SEQ_TEMP_
    typename SEQ_INST_::const_reverse_iterator SEQ_INST_::crbegin()const
        {return m_series.crbegin();}

    SEQ_TEMP_
    typename SEQ_INST_::const_reverse_iterator SEQ_INST_::crend()const
        {return m_series.crend();}


    SEQ_TEMP_
    typename SEQ_INST_::const_iterator SEQ_INST_::find(const_reference val)const
        {return this->cfind();}

    SEQ_TEMP_
    typename SEQ_INST_::const_iterator
        SEQ_INST_::cfind(const_reference val)
    const{
        if(m_series.size() == 0)
            return m_series.cend();
        const_iterator it1(m_series.cbegin()), it2(m_series.cend());
        --it2;
        do{
            if(*it1 == val)         return it1;
            else if(*it2 == val)    return it2;
            ++it1, --it2;
        }while(it1 != it2 && std::distance(it1, it2) > 1);
        if(std::distance(it1, it2) == 1){
            if(*it1 == val)         return it1;
            else if(*it2 == val)    return it2;
        }
        return m_series.cend();
    }


    SEQ_TEMP_
    typename SEQ_INST_::iterator SEQ_INST_::begin()
        {return m_series.begin();}

    SEQ_TEMP_
    typename SEQ_INST_::iterator SEQ_INST_::end()
        {return m_series.end();}

    SEQ_TEMP_
    typename SEQ_INST_::reverse_iterator SEQ_INST_::rbegin()
        {return m_series.rbegin();}

    SEQ_TEMP_
    typename SEQ_INST_::reverse_iterator SEQ_INST_::rend()
        {return m_series.rend();}


    SEQ_TEMP_
    typename SEQ_INST_::iterator SEQ_INST_::find(const_reference val){
        if(m_series.size() == 0)
            return m_series.end();
        iterator it(m_series.begin()), it2(m_series.end());
        --it2;
        do{
            if(*it == val)          return it;
            else if(*it2 == val)    return it2;
            ++it, --it2;
        }while(it != it2 && std::distance(it, it2) > 1);
        if(std::distance(it, it2) == 1){
            if(*it == val)          return it;
            else if(*it2 == val)    return it2;
        }
        return m_series.end();
    }

//Constructors and destructor

    SEQ_TEMP_
    SEQ_INST_::Sequence(
        const generator_type& new_gen,
        size_type start,
        size_type init_size
    )
        : m_start(start)
        , m_gen(new_gen)
        , m_series()
    {this->generate(init_size);}

    SEQ_TEMP_
    template <typename Iter>
    SEQ_INST_::Sequence(
        const Iter& start, const Iter& stop,
        const generator_type& new_gen,
        size_type start_index
    )
        : m_start(start_index)
        , m_gen(new_gen)
        , m_series(start, stop)
    {}

    SEQ_TEMP_
    bool SEQ_INST_::valid_index(size_type index)const
        {return index >= m_start && index-m_start < m_series.size();}
}

#undef SEQ_INST_