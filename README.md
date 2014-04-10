Precision-Number-Library
========================

A library with number types with an unlimited digit count and whose floating point system operates on precision and accuracy. All systems in this library shall support any number base.


Written in C++ using the C++11 standard.


Basic library compiling instructions:

- Set compiler's search directory to include the Precision directory

- Compile

If you don't wish to compile, you may request a compiled static library to be sent to you by e-mail.

- i.publish.docs@gmail.com


Current features:

- Multi-precision number types (Precision::Int, Precision::Float, Precision::Fract and their unsigned counterparts)

-- Basic arithmetic operations

-- Type aliases to ease use of number type components

-- Ability to convert to a string of images (std::basic_string<CharT>)

-- Various tests such as even() and positive()

-- Shift functions to aid in changing the number of digits

-- Methods to retrieve individual digits

-- Int:

--- Bitwise logical operations

--- Base dependent logical operations

-- Float:

--- All comparators are based upon precision (e.g. FloatObj1 == FloatObj2 is safe to use)

--- Count digits on the left and/or right side of the decimal point

--- Keeps track of precision (immutable after construction unless the object is replaced via assignment)

-- Fract:

--- Retrieve the numerator, denominator, and the decimal form

--- Memory of precision for the decimal form

--- Ability to cast to Float

-- Float and Fract:

--- Tests if the number is an integer

--- Methods for exponentiating and inverting

--- Ability to cast to Int

- General number base templates (Precision::General_Base::Int, Precision::General_Base::Float, Precision::General_Base::Fract and their unsigned counterparts)

-- For more details on how to instantiate a new number base, see Precision/General_Base/Precision_Int_General_Base.h

- Exotic number bases (Precision::Hexadecimal, Precision::Octal, Precision::ABC)

- String literal operators (e.g. "1E7"_Precision_Int_E)

-- Support for regular and scientific notations

- Psuedo random number generator (Precision::Random)

- Exception system

- A limited mathematics system

- A tag system to determine what category the number type falls under


Features currently under construction:

- Binary Number Specialization (Precision::Binary)

- Complex Number System (Precision::Complex)

- Number Sequence System (Precision::Sequence, Precision::StrictSequence, Precision::RecursiveSequence, Precision::StrictRecursiveSequence)

- Mathematics System (Precision::Math)

-- Functions under Precision/General_Base/Math_Shared_Functions.h (included by Precision/Precision_Math.h) are fully functional


Future features:

- A revised system to get rid of the ugly constants in Precision/General_Base/Shared_Constants.h with compile-time constants

-- Possibly have constants system support general base as well (either by conversion from base 10 or by compile calculations)

- New algorithms to aid in converting number bases for floating point, fraction, and complex number systems

- Extending the psuedo random number generator to also generate Float and Fract numbers

-- Perhaps also the Complex


Features still being researched or experimented with:

- Multi-dimensional matrices system

- A faster algorithm for converting among number bases

- Replacing core of implementation with a dynamic bitset to aid in memory efficiency

- Making the main number types: Int, Float, and Fract; STL-like with iterators

- A new system to aid in passing container types with optional template parameters for the passed container types
-- That is: template <template <typename...> class Container> will have a way to pass in additional arguments to modify the container type, such as passing custom allocators
