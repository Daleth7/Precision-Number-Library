#include "General_Base/Precision_Exception.h"

namespace Precision{
    const char* exception::what()const noexcept
        {return full_message.c_str();}
    exception::code exception::type()const noexcept
        {return err_type;}
    const char* exception::source()const noexcept
        {return src.c_str();}

    exception::exception(code c, const char* new_src)noexcept
        : err_type(c)
        , src(new_src)
        , full_message( (src + " ~ ") + message_map[err_type] )
    {}

    exception::exception(code c, const str_type& new_src)noexcept
        : err_type(c)
        , src(new_src)
        , full_message( (src + " ~ ") + message_map[err_type] )
    {}

    constexpr char const* exception::message_map[exception::none];
}
