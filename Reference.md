 Reference for Arbitrary Precision mathematics
==============================================

Choice of library
-----------------

It is important to note that this library is designed for ease-of-use. Mission-critical
applications should probably use a more established library such as GMP from the GNU
foundation. However, I am also designing this library with readability in mind. Thus, it
could be used in educational settings to teach what is possible using languages such as
C++.

#### Which header?

- For integer math - use `ArbitraryPrecisionInt.h`
- For floating point math - use `ArbitraryPrecisionFloat.h`

Size, precision, and memory usage
---------------------------------

Practically all computers address memory in bytes not bits. The library will round up to
the next closest size as measured in bytes. You can specify the precision of the fraction
and also the range of the exponent. The exponent determines the maximum and minimum value
(distance from 0), the size of fraction/mantissa determines what precision you can store.

You can specify the fraction size (precision), and the constructor will select the size of
exponent for you. You can also specify both values (fraction and exponent size) if you
want a specific size of each. By default, the constructor will target an exponent that is
roughly 25% the size of the fraction.

Here is a table of what the constructor will do if only given a specified precision.

| Specified bits | Fraction (bits) | bytes | Exponent (bits) | bytes | total bytes |
|----------------|-----------------|-------|-----------------|-------|-------------|
| 64             | 64              | 8     | 16              | 2     | 10          |
| 136            | 136             | 17    | 40              | 5     | 22          |
| 133            | 136             | 17    | 40              | 5     | 22          |

Exponents are stored as 2's compliment integers. Though a more performance optimized library
would likely store the exponent as a native integer type. The goal of this library is to do
this entirely using bytes to demonstrate how to create custom data. The trade-off of this is
that I may not get to use the CPU as efficiently as I would if I used a bunch of native
floating point numbers.

Performance and stability considerations
----------------------------------------

This library allows for user-defined precision, and the precision is defined at run-time.
This means that dynamic memory usage is required for a library that can change precision
without being recompiled. When comparing or doing math on variables, try to keep the 
precision the same between them when possible. Get in the habit of calling the
destructor function when you are finished with a given variable.
