#include "../src/iwstring.h"
#include "testhandler.h"

using namespace iw;

ErrCode testAppend()
{
    String str = "Hello";
    str.append(", World!");
    ASSERT_TRUE(str, String("Hello, World!"));
}

ErrCode testArrayIndexOperator()
{
    String str = "Hello";
    ASSERT_TRUE(str[2], 'l');
}

ErrCode testEqOperatorMismatchStrSameLength()
{
    String str1 = "String 1";
    String str2 = "String 23";

    ASSERT_FALSE(str1, str2);
}

ErrCode testFind()
{
    String str = "Hello, World!";
    ASSERT_TRUE(str.find("el"), 1);
}

ErrCode testLength()
{
    String str = "Hello, World!";

    ASSERT_TRUE(str.length(), 13);
}

ErrCode testLessThanOperator()
{
    String a = "abcd";
    String b = "abed";
    ASSERT_LT(a, b);
}

ErrCode testPlusOperator()
{
    String hello = "Hello";
    String world = "World";
    String res = hello + ", " + world + "!";
    String expectedResult = "Hello, World!";

    ASSERT_TRUE(res, expectedResult)
}

ErrCode testPlusEqOperator()
{
    String str = "Hello";
    str += ", World!";
    String expectedResult = "Hello, World!";

    ASSERT_TRUE(str, expectedResult)
}

ErrCode testPrepend()
{
    String str = "Hello";
    ASSERT_TRUE(str.prepend(", World!"), String(", World!Hello"));
}

ErrCode testReplace()
{
    String str = "Hello World Foo Bar";
    str.replace("Wor", "Co");
    ASSERT_TRUE(str, String("Hello Cold Foo Bar"));
}

ErrCode testReplaceMultiWords()
{
    String str = "Hello World Hello World";
    str.replace("World", "Replaced");
    ASSERT_TRUE(str, String("Hello Replaced Hello Replaced"));
}

ErrCode testSetValue()
{
    String hello = "Hello";
    String res;
    res.setData("Hello");
    ASSERT_TRUE(hello, res)
}

ErrCode testToLower()
{
    String str = "Hello, World!";
    String expectedResult = "hello, world!";
    ASSERT_TRUE(str.toLower(), expectedResult);
}

ErrCode testToUpper()
{
    String str = "Hello, World!";
    str.toUpper();
    String expectedResult = "HELLO, WORLD!";
    ASSERT_TRUE(str, expectedResult);
}

int main()
{
    TestHandler* testHandler = new TestHandler();

    testHandler->addTest("testAppend", &testAppend);
    testHandler->addTest("testArrayIndexOperator", &testArrayIndexOperator);
    testHandler->addTest("testEqOperatorMismatchStrSameLength", &testEqOperatorMismatchStrSameLength);
    testHandler->addTest("testLength", &testLength);
    testHandler->addTest("testLessThanOperator", &testLessThanOperator);
    testHandler->addTest("testEqOperator", &testSetValue);
    testHandler->addTest("testFind", &testFind);
    testHandler->addTest("testPlusOperator", &testPlusOperator);
    testHandler->addTest("testPlusEqOperator", &testPlusEqOperator);
    testHandler->addTest("testPrepend", &testPrepend);
    testHandler->addTest("testReplace", &testReplace);
    testHandler->addTest("testReplaceMultiWords", &testReplaceMultiWords);
    testHandler->addTest("testToLower", &testToLower);
    testHandler->addTest("testToUpper", &testToUpper);

    ErrCode err = testHandler->runTests();
    if (err != ErrCode::OK) {
        return -1;
    }

    testHandler->printResults();

    delete testHandler;

    return 0;
}
