#include <iostream>
#include "String.h"

void testConstructions() {
    String s1; // abc
    String s2 = 'a'; // a
    String s3(5, 'a'); // aaaaa
    String s4("asdf"); // asdf
    String s5{'a', 'b', 'c'}; // abc
    String s6(s2); // a
    s1 = s5;
    std::string s = "hello";
    String s7 = s;
}

void testSizeAndCapacity() {
    String s1;
    String s2 = 'a';
    String s3(16, 'a');
    String s4("asdf");
    String s5{'a', 'b', 'c'};
    String s6(s2);

    std::cout << s1.size() << ' ' << s1.length() << ' ' << s1.capacity() << '\n';
    std::cout << s2.size() << ' ' << s2.length() << ' ' << s2.capacity() << '\n';
    std::cout << s3.size() << ' ' << s3.length() << ' ' << s3.capacity() << '\n';
    std::cout << s4.size() << ' ' << s4.length() << ' ' << s4.capacity() << '\n';
    std::cout << s5.size() << ' ' << s5.length() << ' ' << s5.capacity() << '\n';
    std::cout << s6.size() << ' ' << s6.length() << ' ' << s6.capacity() << '\n';
}

void testClearAndEmpty() {
    String s5{'a', 'b', 'c'};
    std::cout << std::boolalpha << s5.empty() << '\n';
    s5.clear();
    std::cout << std::boolalpha << s5.empty() << '\n';
}

void testAtAndBracketOperator() {
    String s7 = "abcd";
    const String& cs = s7;
    const char& c = cs.front();
    s7[0] = 'b';
    std::cout << s7[0] << ' ' << c << '\n';
}

void testFrontAndBack() {
    const String str = "Lorem ipsum dolor sit amet";
    String modifiedStr = str;
    char firstChar = str.front();
    char lastChar = str.back();
    modifiedStr.front() = '*';
    modifiedStr.back() = '$';
    std::cout << str << '\n';
    std::cout << firstChar << '\n';
    std::cout << lastChar << '\n';
    std::cout << modifiedStr << '\n';
}

void testPushBackAndPopBack() {
    String s8 = "Hello";
    std::cout << s8 << '\n';
    char newChar = '!';
    s8.push_back(newChar);
    std::cout << newChar << ": " << s8 << '\n';
    s8.pop_back();
    std::cout << s8 << '\n';
}

void testAppendEmptyString() {
    String str = "Hello";
    String emptyStr = "";
    str.append(emptyStr);
    std::cout << "Append empty string test: " << str << std::endl;
}

void testAppendToEmptyString() {
    String str;
    str.append("Hello");
    std::cout << "Append to empty string test: " << str << std::endl;
}

void testAppendLargeString() {
    String str = "Hello";
    String largeStr(100, 'X');
    str.append(largeStr);
    std::cout << "Append large string test: " << str.capacity() << std::endl;
}

void testResize() {
    String s1("Hello");
    std::cout << "Before resize: " << s1 << '\n';
    s1.resize(3);
    std::cout << "After resize: " << s1 << '\n';
}

void testResizeWithChar() {
    String s2("Hello");
    std::cout << "Before resize with char: " << s2 << '\n';
    s2.resize(8, '!');
    std::cout << "After resize with char: " << s2 << '\n';
}

void testResizeToZero() {
    String s2("Hello");
    std::cout << "Before resize to zero: " << s2 << '\n';
    s2.resize(0);
    std::cout << "After resize to zero: " << s2 << '\n';
}

void testResizeToLargeSize() {
    String s3("Hello");
    std::cout << "Before resize to large size: " << s3 << '\n';
    s3.resize(1000);
    std::cout << "After resize to large size: " << s3 << '\n';
    std::cout << "Capacity: " << s3.capacity() << " Size: " << s3.size() << '\n';
}

void testEqualityWithCharPointer() {
    String s1("Hello");
    const char* str = "Hello";
    if (s1 == str) {
        std::cout << "Strings are equal\n";
    } else {
        std::cout << "Strings are not equal\n";
    }
}

void testEqualityWithString() {
    String s2("Hello");
    String other("Hello");
    if (s2 == other) {
        std::cout << "Strings are equal\n";
    } else {
        std::cout << "Strings are not equal\n";
    }
}

void testEqualityWithChar() {
    String s3("Hello");
    char c = 'H';
    if (s3 == c) {
        std::cout << "String equals character\n";
    } else {
        std::cout << "String does not equal character\n";
    }
}

void testAppendEmptyString2() {
    String s1("Hello");
    String empty;
    s1 += empty;
    std::cout << "After appending empty string: " << s1 << '\n';
}

void testAppendSelf2() {
    String s2("Hello");
    s2 += s2;
    std::cout << "After appending itself: " << s2 << '\n';
}

void testAppendLargeString2() {
    String s4("Hello");
    String largeStr(100, 'X');
    s4 += largeStr;
    std::cout << "After appending large string: " << s4 << '\n';
}

void testConcatenateStringToString() {
    String s1("Hello");
    String s2(" World");
    s1 += s2;
    std::cout << "Concatenate string to string test: " << s1 << '\n';
}

void testConcatenateCStringToString() {
    String s3("Hello");
    const char* str = " World";
    s3 += str;
    std::cout << "Concatenate C string to string test: " << s3 << '\n';
}

void testConcatenateCharToString() {
    String s4("Hello");
    char c = '!';
    s4 += c;
    std::cout << "Concatenate char to string test: " << s4 << '\n';
}

void testConcatenateWithChar() {
    String s1("Hello");
    char c = '!';
    String result = s1 + c;
    std::cout << "Concatenate with char test: " << result << '\n';
}

void testConcatenateWithCString() {
    String s2("Hello");
    const char* str = " World";
    String result = s2 + str;
    std::cout << "Concatenate with C string test: " << result << '\n';
}

void testConcatenateWithAnotherString() {
    String s3("Hello");
    String other(" World");
    String result = s3 + other;
    std::cout << "Concatenate with another string test: " << result << '\n';
}

void testConcatenateFriendCharString() {
    char c = '!';
    String s1("Hello");
    String result = c + s1;
    std::cout << "Concatenate friend char string test: " << result << '\n';
}

void testConcatenateFriendCStringString() {
    const char* str = "Hello";
    String s2(" World");
    String result = str + s2;
    std::cout << "Concatenate friend C string string test: " << result << '\n';
}

void testSubstringWithDefaultParams() {
    String s1("Hello, World!");
    String result = s1.substr();
    std::cout << "Substring with default parameters test: " << result << '\n';
}

void testSubstringWithPos() {
    String s2("Hello, World!");
    String result = s2.substr(7);
    std::cout << "Substring with position test: " << result << '\n';
}

void testSubstringWithPosAndLen() {
    String s3("Hello, World!");
    String result = s3.substr(7, 5);
    std::cout << "Substring with position and length test: " << result << '\n';
}

void testSubstringWithOutOfRangePos() {
    String s4("Hello, World!");
    try {
        String result = s4.substr(20);
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}

void testInsertString() {
    String s1("Hello");
    String toInsert(" World");
    s1.insert(5, toInsert);
    std::cout << "Insert string test: " << s1 << '\n';
}

void testInsertCString() {
    String s2("Hello");
    const char* toInsert = " World";
    s2.insert(5, toInsert);
    std::cout << "Insert C string test: " << s2 << '\n';
}

void testInsertCharCount() {
    String s3("Hello");
    s3.insert(5, 3, '!');
    std::cout << "Insert char count test: " << s3 << '\n';
}

void testInsertOutOfRange() {
    try {
        String s4("Hello");
        String toInsert(" World");
        s4.insert(20, toInsert);
        std::cout << "Insert out of range test: " << s4 << '\n';
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
}

void testErase() {
    String s1("Hello, World!");
    s1.erase(5, 7);
    std::cout << "Erase test: " << s1 << '\n';
}

void testEraseAtEnd() {
    String s2("Hello");
    s2.erase(3, 10);
    std::cout << "Erase at end test: " << s2 << '\n';
}

void testEraseOutOfBounds() {
    String s3("Hello");
    s3.erase(10, 3);
    std::cout << "Erase out of bounds test: " << s3 << '\n';
}

void testReplaceString() {
    String s1("Hello, World!");
    String replacement("Universe");
    s1.replace(7, 5, replacement);
    std::cout << "Replace string test: " << s1 << '\n';
}

void testReplaceCString() {
    String s2("Hello, World!");
    const char* replacement = "Universe";
    s2.replace(7, 5, replacement);
    std::cout << "Replace C string test: " << s2 << '\n';
}

void testReplaceCharCount() {
    String s3("Hello, World!");
    s3.replace(0, 5, 10, '*');
    std::cout << "Replace char count test: " << s3 << '\n';
}

void testReplaceOutOfBounds() {
    try {
        String s4("Hello");
        s4.replace(10, 3, "World");
        std::cout << "Replace out of bounds test: " << s4 << '\n';
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
}

void testFindString() {
    String s1("Hello, World!");
    String searchStr("World");
    size_t pos = s1.find(searchStr);
    std::cout << "Find string test: Position of 'World' in '" << s1 << "' is " << pos << '\n';
}

void testFindCString() {
    String s2("Hello, World!");
    const char* searchStr = "World";
    size_t pos = s2.find(searchStr);
    std::cout << "Find C string test: Position of 'World' in '" << s2 << "' is " << pos << '\n';
}

void testFindCStringWithPos() {
    String s3("World, Hello, World!");
    const char* searchStr = "World";
    size_t pos = s3.find(searchStr, 7);
    std::cout << "Find C string with pos test: Position of 'World' in '" << s3 << "' after position 7 is " << pos << '\n';
}

void testFindChar() {
    String s4("Hello, World!");
    char searchChar = 'o';
    size_t pos = s4.find(searchChar);
    std::cout << "Find char test: Position of 'o' in '" << s4 << "' is " << pos << '\n';
}

void testFindNotFound() {
    String s5("Hello, World!");
    const char* searchStr = "Universe";
    size_t pos = s5.find(searchStr);
    if (pos != std::string::npos) {
        std::cout << "Find string test: Position of 'Universe' in '" << s5 << "' is " << pos << '\n';
    } else {
        std::cout << "Not Found" << '\n';
    }
}

void testAssignmentToSum() {
    String s1 ("Hello");
    String s2 ("World");
    String s3 ("String");
    // s1 + s2 = s3; -> error
}

void testComparisonWithString() {
    std::cout << "Comparison With String" << '\n';
    String s1 ("hello");
    String s2 ("world");
    std::cout << "s1 == s2 -> " << std::boolalpha << (s1 == s2) << '\n';
    std::cout << "s1 != s2 -> " << std::boolalpha << (s1 != s2) << '\n';
    std::cout << "s1 > s2 -> " << std::boolalpha << (s1 > s2) << '\n';
    std::cout << "s1 >= s2 -> " << std::boolalpha << (s1 >= s2) << '\n';
    std::cout << "s1 < s2 -> " << std::boolalpha << (s1 < s2) << '\n';
    std::cout << "s1 <= s2 -> " << std::boolalpha << (s1 <= s2) << '\n';
}

void testComparisonWithCString() {
    std::cout << "Comparison With C String" << '\n';
    String s1 ("hello");
    const char* s2 ("world");
    std::cout << "s1 == s2 -> " << std::boolalpha << (s1 == s2) << '\n';
    std::cout << "s1 != s2 -> " << std::boolalpha << (s1 != s2) << '\n';
    std::cout << "s1 > s2 -> " << std::boolalpha << (s1 > s2) << '\n';
    std::cout << "s1 >= s2 -> " << std::boolalpha << (s1 >= s2) << '\n';
    std::cout << "s1 < s2 -> " << std::boolalpha << (s1 < s2) << '\n';
    std::cout << "s1 <= s2 -> " << std::boolalpha << (s1 <= s2) << '\n';
}

void testComparisonWithSTDString() {
    std::cout << "Comparison With String Object" << '\n';
    String s1 ("hello");
    std::string s2 ("world");
    std::cout << "s1 == s2 -> " << std::boolalpha << (s1 == s2) << '\n';
    std::cout << "s1 != s2 -> " << std::boolalpha << (s1 != s2) << '\n';
    std::cout << "s1 > s2 -> " << std::boolalpha << (s1 > s2) << '\n';
    std::cout << "s1 >= s2 -> " << std::boolalpha << (s1 >= s2) << '\n';
    std::cout << "s1 < s2 -> " << std::boolalpha << (s1 < s2) << '\n';
    std::cout << "s1 <= s2 -> " << std::boolalpha << (s1 <= s2) << '\n';
}

int main() {
    testConstructions();
    std::cout << '\n';
    testSizeAndCapacity();
    std::cout << '\n';
    testClearAndEmpty();
    std::cout << '\n';
    testAtAndBracketOperator();
    std::cout << '\n';
    testFrontAndBack();
    std::cout << '\n';
    testPushBackAndPopBack();
    std::cout << '\n';
    testAppendEmptyString();
    std::cout << '\n';
    testAppendToEmptyString();
    std::cout << '\n';
    testAppendLargeString();
    std::cout << '\n';
    testResize();
    std::cout << '\n';
    testResizeWithChar();
    std::cout << '\n';
    testResizeToZero();
    std::cout << '\n';
    testResizeToLargeSize();
    std::cout << '\n';
    testEqualityWithCharPointer();
    std::cout << '\n';
    testEqualityWithString();
    std::cout << '\n';
    testEqualityWithChar();
    std::cout << '\n';
    testAppendEmptyString2();
    std::cout << '\n';
    testAppendSelf2();
    std::cout << '\n';
    testAppendLargeString2();
    std::cout << '\n';
    testConcatenateStringToString();
    std::cout << '\n';
    testConcatenateCStringToString();
    std::cout << '\n';
    testConcatenateCharToString();
    std::cout << '\n';
    testConcatenateWithChar();
    std::cout << '\n';
    testConcatenateWithCString();
    std::cout << '\n';
    testConcatenateWithAnotherString();
    std::cout << '\n';
    testConcatenateFriendCharString();
    std::cout << '\n';
    testConcatenateFriendCStringString();
    std::cout << '\n';
    testSubstringWithDefaultParams();
    std::cout << '\n';
    testSubstringWithPos();
    std::cout << '\n';
    testSubstringWithPosAndLen();
    std::cout << '\n';
    testSubstringWithOutOfRangePos();
    std::cout << '\n';
    testInsertString();
    std::cout << '\n';
    testInsertCString();
    std::cout << '\n';
    testInsertCharCount();
    std::cout << '\n';
    testInsertOutOfRange();
    std::cout << '\n';
    testErase();
    std::cout << '\n';
    testEraseAtEnd();
    std::cout << '\n';
    testEraseOutOfBounds();
    std::cout << '\n';
    testReplaceString();
    std::cout << '\n';
    testReplaceCString();
    std::cout << '\n';
    testReplaceCharCount();
    std::cout << '\n';
    testReplaceOutOfBounds();
    std::cout << '\n';
    testFindString();
    std::cout << '\n';
    testFindCString();
    std::cout << '\n';
    testFindCStringWithPos();
    std::cout << '\n';
    testFindChar();
    std::cout << '\n';
    testFindNotFound();
    std::cout << '\n';
    testComparisonWithString();
    std::cout << '\n';
    testComparisonWithCString();
    std::cout << '\n';
    testComparisonWithSTDString();
    return 0;
}
