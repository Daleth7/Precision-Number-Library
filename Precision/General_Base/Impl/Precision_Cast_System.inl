template <
    typename Number_Type1,
    typename Number_Type2,
    typename Base_Type,
    typename Unknown_Type,
    typename Prec_Cate
>
Number_Type1 cast(
    const Number_Type1&,
    const Number_Type2& n,
    Base_Type,
    Unknown_Type,
    Prec_Cate
){return static_cast<Number_Type1>(n);}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1&,
    const Number_Type2& n,
    Tag::Static,
    Tag::Integral,
    Prec_Cate
){return Number_Type1(n);}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1& sample,
    const Number_Type2& n,
    Tag::Dynamic,
    Tag::Integral,
    Prec_Cate
){return Number_Type1(n, sample.wrapper());}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(
    const Number_Type1& sample,
    const Number_Type2& n,
    Tag::Static,
    Tag::Floating_Point,
    Tag::Integral
){return Number_Type1(n, sample.precision());}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1&,
    const Number_Type2& n,
    Tag::Static,
    Tag::Floating_Point,
    Prec_Cate
){return Number_Type1(n);}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(
    const Number_Type1& sample,
    const Number_Type2& n,
    Tag::Dynamic,
    Tag::Floating_Point,
    Tag::Integral
){return Number_Type1(n, sample.precision(), sample.wrapper());}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1& sample,
    const Number_Type2& n,
    Tag::Dynamic,
    Tag::Floating_Point,
    Prec_Cate
){return Number_Type1(n, sample.wrapper());}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(
    const Number_Type1& sample,
    const Number_Type2& n,
    Tag::Static,
    Tag::Fraction,
    Tag::Integral
){return Number_Type1(n, sample.precision());}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1&,
    const Number_Type2& n,
    Tag::Static,
    Tag::Fraction,
    Prec_Cate
){return Number_Type1(n);}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(
    const Number_Type1& sample,
    const Number_Type2& n,
    Tag::Dynamic,
    Tag::Fraction,
    Tag::Integral
){return Number_Type1(n, sample.precision(), sample.wrapper());}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1& sample,
    const Number_Type2& n,
    Tag::Dynamic,
    Tag::Fraction,
    Prec_Cate
){return Number_Type1(n, sample.wrapper());}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(const Number_Type1& sample, const Number_Type2& n){
    return cast(
        sample, n,
        typename Type_Trait::find_base<Number_Type1, PRE_BASE_>::base(),
        typename Type_Trait::find_base<Number_Type1, PRE_CATE_>::base(),
        typename Type_Trait::find_base<
            typename std::remove_reference<Number_Type2>::type, PRE_CATE_>::base()
    );
}

template <
    typename Number_Type1,
    typename Number_Type2,
    typename Base_Type,
    typename Unknown_Type,
    typename Prec_Cate
>
Number_Type1 cast(
    const Number_Type1&,
    Number_Type2&& n,
    Base_Type,
    Unknown_Type,
    Prec_Cate
){return static_cast<Number_Type1>(n);}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1&,
    Number_Type2&& n,
    Tag::Static,
    Tag::Integral,
    Prec_Cate
){return Number_Type1(std::forward<Number_Type2>(n));}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1& sample,
    Number_Type2&& n,
    Tag::Dynamic,
    Tag::Integral,
    Prec_Cate
){return Number_Type1(std::forward<Number_Type2>(n), sample.wrapper());}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(
    const Number_Type1& sample,
    Number_Type2&& n,
    Tag::Static,
    Tag::Floating_Point,
    Tag::Integral
){return Number_Type1(std::forward<Number_Type2>(n), sample.precision());}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1&,
    Number_Type2&& n,
    Tag::Static,
    Tag::Floating_Point,
    Prec_Cate
){return Number_Type1(std::forward<Number_Type2>(n));}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(
    const Number_Type1& sample,
    Number_Type2&& n,
    Tag::Dynamic,
    Tag::Floating_Point,
    Tag::Integral
){
    return Number_Type1(
        std::forward<Number_Type2>(n),
        sample.precision(),
        sample.wrapper()
    );
}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1& sample,
    Number_Type2&& n,
    Tag::Dynamic,
    Tag::Floating_Point,
    Prec_Cate
){return Number_Type1(std::forward<Number_Type2>(n), sample.wrapper());}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(
    const Number_Type1& sample,
    Number_Type2&& n,
    Tag::Static,
    Tag::Fraction,
    Tag::Integral
){return Number_Type1(std::forward<Number_Type2>(n), sample.precision());}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1&,
    Number_Type2&& n,
    Tag::Static,
    Tag::Fraction,
    Prec_Cate
){return Number_Type1(std::forward<Number_Type2>(n));}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(
    const Number_Type1& sample,
    Number_Type2&& n,
    Tag::Dynamic,
    Tag::Fraction,
    Tag::Integral
){
    return Number_Type1(
        std::forward<Number_Type2>(n),
        sample.precision(),
        sample.wrapper()
    );
}

template <typename Number_Type1, typename Number_Type2, typename Prec_Cate>
Number_Type1 cast(
    const Number_Type1& sample,
    Number_Type2&& n,
    Tag::Dynamic,
    Tag::Fraction,
    Prec_Cate
){return Number_Type1(std::forward<Number_Type2>(n), sample.wrapper());}

template <typename Number_Type1, typename Number_Type2>
Number_Type1 cast(const Number_Type1& sample, Number_Type2&& n){
    return cast(
        sample, std::forward<Number_Type2>(n),
        typename Type_Trait::find_base<Number_Type1, PRE_BASE_>::base(),
        typename Type_Trait::find_base<Number_Type1, PRE_CATE_>::base(),
        typename Type_Trait::find_base<
            typename std::remove_reference<Number_Type2>::type, PRE_CATE_>::base()
    );
}