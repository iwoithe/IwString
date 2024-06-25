#include "../src/iwstring.h"
#include "testhandler.h"

using namespace iw;

ErrCode testEqOperatorMismatchStrSameLength()
{
    String str1 = "String 1";
    String str2 = "String 23";

    ASSERT_FALSE(str1, str2);
}

ErrCode testLength()
{
    String str = "Hello, World!";

    ASSERT_TRUE(str.length(), 13);
}

ErrCode testPlusOperator()
{
    String hello = "Hello";
    String world = "World";
    String res = hello + ", " + world + "!";
    String expectedResult = "Hello, World!";

    ASSERT_TRUE(res, expectedResult)
}

ErrCode testSetValue()
{
    String hello = "Hello";
    String res;
    res.setData("Hello");
    ASSERT_TRUE(hello, res)
}

ErrCode testLength()
{
    String str = "Hello, World!";

    ASSERT_TRUE(str.length(), 13);
}


int main()
{
    TestHandler* testHandler = new TestHandler();

    testHandler->addTest("testEqOperatorMismatchStrSameLength", &testEqOperatorMismatchStrSameLength);
    testHandler->addTest("testLength", &testLength);
    testHandler->addTest("testEqOperator", &testSetValue);
    testHandler->addTest("testPlusOperator", &testPlusOperator);
    
    ErrCode err = testHandler->runTests();
    if (err != ErrCode::OK) {
        return -1;
    }

    testHandler->printResults();

    return 0;
}
