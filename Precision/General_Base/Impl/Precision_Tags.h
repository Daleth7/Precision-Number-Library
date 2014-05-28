#ifndef NUMBER_CLASSIFICATION_TAG_CLASSES_H__
#define NUMBER_CLASSIFICATION_TAG_CLASSES_H__

//These declare empty classes to be used similarly
//  to iterator tags to help identify the classification
//  a particular number type belongs to.
namespace Precision{
    namespace Tag{
        class Integral{};
        class Floating_Point{};
        class Fraction{};
        class Complex{};
        class Polar{};
        class Unsigned{};
        class Signed{};
        class Set{};
    }
}

#endif