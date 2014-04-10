#ifndef SIGN_CLASS_DEFINITION_H__
#define SIGN_CLASS_DEFINITION_H__

namespace Precision{
    class SignClass{
        public:
    //Type Aliases
            using signed_type   = signed short;

    //Read-only
            signed_type value()const;
            bool positive()const;
            bool negative()const;
            operator signed_type()const;

    //Modifiers
            void flip();
                //Just another name for flip
            void negate();
            void assign(signed_type);
            void make_positive();
            void make_negative();

    //Constructors and Destructor
            SignClass(signed_type);
            SignClass()                             = default;
            SignClass(const SignClass&)             = default;
            SignClass(SignClass&&)                  = default;
            SignClass& operator=(const SignClass&)  = default;
            SignClass& operator=(SignClass&&)       = default;
            ~SignClass()                            = default;
        private:
            bool m_positive;
    };
}

#endif