 Reference for Arbitrary Precision mathematics
==============================================

Choice of library
-----------------

It is important to note that this library is designed for ease-of-use. Mission-critical
applications should probably use a more established library such as the GMP from the GNU
foundation. However, I am also designing this library with readability in mind. Thus, it
could be used in educational settings to teach what is possible using languages such as
C++.

#### Which header?

- For integer math - use `ArbitraryPrecisionInt.h`
- For floating point math - use `ArbitraryPrecisionFloat.h`

Performance and stability considerations
----------------------------------------

This library allows for user-defined precision, and the precision is defined at run-time.
This means that dynamic memory usage is required for a library that can change precision
without being recompiled. When comparing or doing math on variables, try to keep the 
precision the same between them when possible. Get in the habit of calling the
destructor function when you are finished with a given variable.