#ifndef PRECISION_EXCEPTION_DEFINITION_CLASS_H__
#define PRECISION_EXCEPTION_DEFINITION_CLASS_H__

#include <exception>
#include <string>

namespace Precision{
    class exception : public std::exception{
        public:
            enum code : unsigned short{
                insufficient_memory = 0,
                divide_by_zero,
                indeterminate,  //Will probably be rarely used 
                complex_number, //Only thrown by types not supporting complex
                invalid_digit,
                none
            };
            using str_type = std::string;

            const char* what()const noexcept;
            code type()const noexcept;
            const char* source()const noexcept;

            exception(code, const char* = "Unknown source")noexcept;
            explicit exception(code, const str_type&)noexcept;
            exception(const exception&)             = default;
            exception& operator=(const exception&)  = default;
            ~exception()noexcept{}
        private:
            code err_type;
            str_type src;
            str_type full_message;
            static constexpr char const* message_map[none] = {
                "Insufficient memory.",
                "Division by zero attempt.",
                "Indeterminate result.",
                "Complex result.",
                "Invalid digit."
            };
    };
}

#endif
