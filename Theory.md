Moderately in-depth overview
============================

This is a simple explanation of how this library works. I am aiming this part of the
documentation at beginner programmers, hence this will be redundant information to
experienced programmers.

Integers
--------

Integers are the data type a programmer uses to store numbers that do not have a decimal
point. Numbers like 10, 1, 57, etc. do not have a fractional component and thus no decimal
point. Implementing them in circuitry is relatively easy, thus they were considerably 
faster to process for older hardware. They have set, fixed values and so can be reliably
compared for equality to each other, this makes them really handy for counting loop
iterations.

We usually handle negative integer numbers using something called 2's compliment. 2's 
compliment numbers are quite clever and allow for the use of a sign bit without having a
positive and negative 0 number. Basically, take the place value of the most significant bit,
that is, the bit that represents the largest value. 2's compliment treats this most
significant bit as if its value was negative.

There are two versions of integers in this library, signed and unsigned. Unsigned numbers
are positive only, signed numbers sacrifice one bit to grant access to negative numbers.

Floating point
--------------

Computers generally use floating point to represent numbers with decimals in them. They are
basically a binary version of scientific notation. They do not provide fixed intervals like
integer numbers do, thus it is unwise to rely on two floating point numbers being exactly
equal. Therefore, it is often best to check if two or more floating point numbers are within
a given range of each other (close enough vs exactly equal).

They are made of 3 main parts:
1. Sign bit - stores if this number is positive or negative
2. Fraction or Mantissa - Stores the actual value
3. Exponent - Tells the system how large or small that value is

Just as the number 123.456 can be represented as 1.23456 * 10^2, a computer does something
similar in floating point numbers.