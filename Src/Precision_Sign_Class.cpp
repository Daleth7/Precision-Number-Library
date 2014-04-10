#include "General_Base/Precision_Sign_Class.h"

namespace Precision{
//Read-only
    SignClass::signed_type SignClass::value()const
        {return m_positive ? 1 : -1;}
    bool SignClass::positive()const
        {return m_positive;}
    bool SignClass::negative()const
        {return !m_positive;}
    SignClass::operator signed_type()const
        {return this->value();}

//Modifiers
    void SignClass::flip()
        {m_positive = !m_positive;}
        //Just another name for flip
    void SignClass::negate()
        {this->flip();}
    void SignClass::assign(signed_type n)
        {m_positive = n < 0 ? false : true;}
    void SignClass::make_positive()
        {m_positive = true;}
    void SignClass::make_negative()
        {m_positive = false;}

//Constructors and Destructor
    SignClass::SignClass(signed_type n)
        : m_positive(n < 0 ? false : true)
    {}
}
