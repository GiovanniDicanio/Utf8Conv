////////////////////////////////////////////////////////////////////////////////
//
// Utf8ConvTest.cpp     -- by Giovanni Dicanio
//
// Unit test the UTF-8 <-> UTF-16 conversion functions declared in Utf8Conv.hpp
//
////////////////////////////////////////////////////////////////////////////////


//
// You can also test the code undefining the following overflow check macro
// *before* including "Utf8Conv.hpp":
//
//#define GIOVANNI_DICANIO_UTF8CONV_CHECK_INTEGER_OVERFLOWS_ONLY_IN_DEBUG
//

#include "Utf8Conv.hpp"     // Library to test

#include <iostream>         // Console output

using std::cout;
using std::string;
using std::wstring;

using Utf8Conv::Utf16ToUtf8;
using Utf8Conv::Utf8ToUtf16;


void Check(bool condition, const char* message)
{
    cout << "[Check]: " << message;
    if (condition)
    {
        cout << " [OK]\n";
    }
    else
    {
        cout << " [Failed]\n";
    }
}


void TestEmptyStrings()
{
    Check(Utf16ToUtf8(L"").empty(), "Input empty UTF-16 C-string converted to empty UTF-8");
    Check(Utf8ToUtf16("").empty(), "Input empty UTF-8 C-string converted to empty UTF-16");

    Check(Utf16ToUtf8(nullptr).empty(), "Input NULL UTF-16 pointer converted to empty UTF-8");
    Check(Utf8ToUtf16(nullptr).empty(), "Input NULL UTF-8 pointer converted to empty UTF-16");

    Check(Utf16ToUtf8(wstring{}).empty(), "Input empty UTF-16 wstring converted to empty UTF-8");
    Check(Utf8ToUtf16(string{}).empty(), "Input empty UTF-8 string converted to empty UTF-16");
}


void TestSimpleStrings()
{
    {
        string s1 = "Connie";
        wstring ws = Utf8ToUtf16(s1);
        string s2 = Utf16ToUtf8(ws);
        Check(s1 == s2, "Conversion loop UTF-8 -> UTF-16 -> UTF-8");
    }

    {
        wstring ws1 = L"Connie Plus Plus";
        string s = Utf16ToUtf8(ws1);
        wstring ws2 = Utf8ToUtf16(s);
        Check(ws1 == ws2, "Conversion loop UTF-16 -> UTF-8 -> UTF-16");
    }


    //
    // Unicode UTF-16 string with a Japanese kanji
    //
    // https://www.compart.com/en/unicode/U+5B66
    //
    {
        wstring ws1 = L"Connie \u5B66 C++";
        string s = Utf16ToUtf8(ws1);
        wstring ws2 = Utf8ToUtf16(s);
        Check(ws1 == ws2, "Conversion loop UTF-16 -> UTF-8 -> UTF-16");
    }
}


void TestConversionErrors()
{
    //
    // Try an invalid UTF-8 sequence
    //
    string utf8Invalid = "Invalid UTF-8 *** @ *** Invalid UTF-8";
    size_t pos = utf8Invalid.find('@');
    utf8Invalid[pos] = static_cast<char>(0xC1); // Invalid UTF-8 byte

    // I expect the following conversion to throw an exception:
    bool exceptionRaised = false;
    try
    {
        wstring impossible = Utf8ToUtf16(utf8Invalid);
    }
    catch (Utf8Conv::Utf8ConversionException const& ex)
    {
        if (ex.Direction() == Utf8Conv::Utf8ConversionException::ConversionType::FromUtf8ToUtf16)
        {
            exceptionRaised = true;
        }
    }
    Check(exceptionRaised, "Utf8ConversionException caught from invalid UTF-8");


    //
    // Try an invalid UTF-16 sequence
    //
    wstring utf16Invalid = L"Invalid UTF-16 *** @ *** Invalid UTF-16";
    pos = utf16Invalid.find(L'@');
    utf16Invalid[pos] = static_cast<wchar_t>(0xD800); // Invalid UTF-16

    // I expect the following conversion to throw an exception:
    exceptionRaised = false;
    try
    {
        string impossible = Utf16ToUtf8(utf16Invalid);
    }
    catch (Utf8Conv::Utf8ConversionException const& ex)
    {
        if (ex.Direction() == Utf8Conv::Utf8ConversionException::ConversionType::FromUtf16ToUtf8)
        {
            exceptionRaised = true;
        }
    }
    Check(exceptionRaised, "Utf8ConversionException caught from invalid UTF-16");

}


//
// Run the various tests
//
int main()
{
    constexpr int kExitOk = 0;
    constexpr int kExitError = 1;

    try
    {
        cout << "===============================================\n";
        cout << "*** Giovanni Dicanio's Utf8Conv C++ Library ***\n";
        cout << "===============================================\n";

        cout << "\nRunning tests...\n\n";

        TestEmptyStrings();
        TestSimpleStrings();
        TestConversionErrors();
    }
    catch (const std::exception& ex)
    {
        cout << "\n*** Error ***\n";
        cout << ex.what() << '\n';

        return kExitError;
    }

    return kExitOk;
}
