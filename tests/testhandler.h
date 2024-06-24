#ifndef TESTHANDLER_H
#define TESTHANDLER_H

#include <chrono>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../src/iwstring.h"

namespace iw {
#define ASSERT_TRUE(a, b) if (a == b) { return ErrCode::SUCCESS; } else { return ErrCode::FAIL; }
#define ASSERT_FALSE(a, b) if (a != b) { return ErrCode::SUCCESS; } else { return ErrCode::FAIL; }
// Less Than
#define ASSERT_LT(a, b) if (a < b) { return ErrCode::SUCCESS; } else { return ErrCode::FAIL; }
// Less Than Equal To
#define ASSERT_LTE(a, b) if (a <= b) { return ErrCode::SUCCESS; } else { return ErrCode::FAIL; }
// Greater Than
#define ASSERT_GT(a, b) if (a > b) { return ErrCode::SUCCESS; } else { return ErrCode::FAIL; }
// Greater Than Equal To
#define ASSERT_GTE(a, b) if (a >= b) { return ErrCode::SUCCESS; } else { return ErrCode::FAIL; }


enum ErrCode {
    OK,
    UNKNOWN_ERROR,
    FAIL,
    SUCCESS
};

struct TestResults {
    time_t time;
    // TODO: Use iw::String instead
    std::unordered_map<std::string, ErrCode> results;
};

using TestFunc = std::function<ErrCode()>;

class TestHandler {
public:
    TestHandler();
    ~TestHandler();

    void addTest(TestFunc testFunc);
    void addTest(std::string funcName, TestFunc testFunc);

    void printResults();

    ErrCode runTests();

    float successPercentage();
private:
    std::vector<std::string> m_funcNames = {};
    std::vector<TestFunc> m_tests = {};
    TestResults m_testResults = TestResults();
};
}

#endif // TESTHANDLER_H
