Arbitrary Precision library
===========================
This is a C++ library which allows for relatively easy implementation of high
precision mathematics. This is far from the only way or even the right way to do
this, but I have created this with the goal that it be easy for a relatively
new programmer to be able to understand how it works and also to modify to fit
their project's requirements if needed.

What files do
--------------

1. main.cpp - The main file for a simple application showing the basics of how
to use the library.
2. ArbitraryPrecisionInt.h - For integer mathematics
3. ArbitraryPrecisionInt.cpp - This has all the functions and other interesting bits
4. ArbitraryPrecisionFloat.h - This is for floating point math (with decimals)
5. ArbitraryPrecisionFloat.cpp - Interesting bits again
6. build.sh - a shell script with the build commands for the sample application,
this will be helpful to a beginner programmer

How to use
----------

You only need to include the header and source file in your project, a sample
is provided in the build.sh file which will compile the sample application.
Download the header and class source file or clone the repo.

Included Functions and Classes
------------------------------

Refer to `Reference.md` file
1. Basic arithmetic - Most arithmetic can be done like you would on a normal float, double, or int
2. Logic and equality - Allows for comparisons between values like normal
3. Creation and initialization
4. Setting precision - tradeoff between precision and size/complexity
5. Assignment operator that will copy the value and precision to the new variable

Why?
----

I tried to build a library like this a long time ago when I had only been
programming for a very short time. I did not understand very much about C++
and the resources I had at my disposal were not beginner-friendly. Most 
experienced programmers will not need this library, and most math can be done
using built-in data types. Though the person I am aiming to help is another 
beginner programmer starting where I started. Hence, I will keep the code as
simple as possible since the goal is to show how to do it, and not to make the
most optimal number crunching library.