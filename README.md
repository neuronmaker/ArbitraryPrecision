# Arbitrary Precision library

This is a C++ library which allows for relatively easy implementation of high
precision mathematics. This is not designed to be a replacement for other
libraries. It was built as a personal challenge, and to see how one of these
libraries can be built.

## What files do

1. `main.cpp` - The main file for a simple application showing the basics of how
   to use the library.
2. `APInt.h` - For integer mathematics
3. `APInt.cpp` - This has all the functions and other interesting bits
4. `APfloat.h` - This is for floating point math (with decimals)
5. `APfloat.cpp` - Interesting bits again

## Included Functions and Classes

Refer to `Reference.md` file

1. Basic arithmetic - Most arithmetic can be done like you would on a normal float, double, or int
2. Logic and equality - Allows for comparisons between values like normal
3. Creation and initialization
4. Setting precision - tradeoff between precision and size/complexity
5. Assignment operator that will copy the value and precision to the new variable
