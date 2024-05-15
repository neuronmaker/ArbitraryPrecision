# Reference for Arbitrary Precision mathematics

A library that implements large number arithmetic, arbitrary precision mathematics.

## Choice of library

This library was designed as a personal challenge. I wanted it to be relatively easy to use and be relatively easy to understand, and since other (well maintained) libraries exist, I chose to make my library focus on demonstrating how it is done rather than making the most optimal implementation possible. Mission-critical applications should probably use a more established library such as [GMP](https://gmplib.org/) from the GNU foundation.

#### Which header?

- For integer math - use `ArbitraryPrecisionInt.h`
- For floating point math - use `ArbitraryPrecisionFloat.h`

## Size, precision, and memory usage

Practically all computers address memory in bytes not bits. The library will round up to the next closest size as measured in bytes. You can specify the precision of the fraction and also the range of the exponent. The exponent determines the maximum and minimum value (distance from 0), the size of fraction/mantissa determines what precision you can store.

You can specify the fraction size (precision), and the constructor will select the size of exponent for you. You can also specify both values (fraction and exponent size) if you want a specific size of each. By default, the constructor will target an exponent that is roughly 25% the size of the fraction.

Here is a table of what the constructor will do if only given a specified precision.

| Specified bits | Fraction (bits) | bytes | Exponent (bits) | bytes | total bytes |
|----------------|-----------------|-------|-----------------|-------|-------------|
| 64             | 64              | 8     | 16              | 2     | 10          |
| 136            | 136             | 17    | 40              | 5     | 22          |
| 133            | 136             | 17    | 40              | 5     | 22          |

Exponents are stored as 2's compliment integers. Though a more performance optimized library would likely store the exponent as a native integer type. The goal of this library is to do this entirely using bytes to demonstrate how to create custom data. The trade-off of this is that I may not get to use the CPU as efficiently as I would if I used a bunch of native
floating point numbers.

## Basic data structure

The entire library stores numbers as a dynamically allocated array of some native data type. At this time, I am using unsigned chars for my arrays since they are exactly one byte in size. Regardless of the datatype used internally, the basic structure of the data is more or less the same.

Internally, the string of bits is stored as follows:  
MSB (Most Significant Bit) <- bits <- LSB (Least Significant Bit)

The bits are stored like this (MSB on the left):  
MSB side | ` char[n] <- char[n-1] <- ... <- char[1] <- char[0] ` | LSB side

Any data type could be used in place of `unsigned char`, other data types (such as `unsigned
int`) have their own advantages and disadvantages. I've chosen to use single byte types so
that I can make the library construct the number to within a single byte of any given size.
The native `unsigned int` type is probably better for performance as the majority of
compilers and CPU designs are made to operate on integers larger than one single byte.

## Performance and stability considerations

This library allows for user-defined precision, and the precision is defined at run-time. Get in the habit of calling the destructor function when you are finished with a given variable. Using dynamic memory allows the library to change precision without being recompiled. When comparing or doing math on two or more variables, when possible, try to keep both variables using the same precision.
