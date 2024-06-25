#include "../src/iwstring.h"
#include "testhandler.h"

using namespace iw;

ErrCode testPlusOperator()
{
    String hello = "Hello";
    String world = "World";
    String res = hello + ", " + world + "!";
    String expectedResult = "Hello, World!";

    ASSERT_TRUE(res, expectedResult)
}

ErrCode testLength()
{
    String str = "Hello, World!";

    ASSERT_TRUE(str.length(), 13);
}

int main()
{
    TestHandler* testHandler = new TestHandler();

    testHandler->addTest("testPlusOperator", &testPlusOperator);
    testHandler->addTest("testLength", &testLength);
    
    ErrCode err = testHandler->runTests();
    if (err != ErrCode::OK) {
        return -1;
    }

    testHandler->printResults();

    return 0;
}
