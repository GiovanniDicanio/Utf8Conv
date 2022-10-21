# Utf8Conv v1.0.0-cpp14 (C++14 Compatible Branch)
## Unicode UTF-8 &lt;-> Unicode UTF-16 Conversion Utility Functions for Windows C++ Code

by Giovanni Dicanio

Code that implements utility functions to convert between Unicode UTF-8 and Unicode UTF-16.

**UTF-8** strings are stored as `std::string` instances; **UTF-16** strings are represented 
using `std::wstring`.

There are also conversion overloads that take "string views" (represented as a pointer and a count)
and C-style NUL-terminated string pointers.

This is a branch developed using **Visual Studio 2019** (v16.9.1) in default C++14 mode.
The code compiles cleanly at warning level 4 (`/W4`) in both 32-bit and 64-bit builds.

This is a **header-only** library, implemented in the **[`Utf8Conv.hpp`](Utf8Conv/Utf8Conv.hpp)** 
header file.

`Utf8ConvTest.cpp` contains some test code for the library: check it out for some sample usage.

The library exposes two main conversion functions: **`Utf8ToUtf16()`** and **`Utf16ToUtf8()`**.
Conversion errors are signaled throwing exceptions.

For example, you can simply convert a string from UTF-8 to UTF-16 using code like this:

```c++
// From UTF-8 to UTF-16
wstring utf16String = Utf8ToUtf16(utf8String);
```

and viceversa:

```c++
// From UTF-16 to UTF-8
string utf8String = Utf16ToUtf8(utf16String);
```

The library stuff lives under the `Utf8Conv` namespace.

See the **[`Utf8Conv.hpp`](Utf8Conv/Utf8Conv.hpp)** header file for more details
and **documentation** about the implemented conversion functions.
