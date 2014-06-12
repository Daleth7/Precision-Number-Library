#ifndef NUMBER_CLASSIFICATION_TAG_CLASSES_H__
#define NUMBER_CLASSIFICATION_TAG_CLASSES_H__

//These declare empty classes to be used similarly
//  to iterator tags to help identify the classification
//  a particular number type belongs to.
namespace Precision{
    namespace Tag{
        struct Integral{};
        struct Floating_Point{};
        struct Fraction{};
        struct Complex{};
        struct Polar{};
        struct Unsigned{};
        struct Signed{};
        struct Set{};
        struct Static{};
        struct Dynamic{};
    }
}

#endif