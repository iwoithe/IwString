#ifndef TESTHANDLER_H
#define TESTHANDLER_H

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../src/iwstring.h"

namespace iw {
#define ASSERT_TRUE(a, b) if (a == b) { return ErrCode::Success; } else { return ErrCode::Fail; }
#define ASSERT_FALSE(a, b) if (a != b) { return ErrCode::Success; } else { return ErrCode::Fail; }
// Less Than
#define ASSERT_LT(a, b) if (a < b) { return ErrCode::Success; } else { return ErrCode::Fail; }
// Less Than Equal To
#define ASSERT_LTE(a, b) if (a <= b) { return ErrCode::Success; } else { return ErrCode::Fail; }
// Greater Than
#define ASSERT_GT(a, b) if (a > b) { return ErrCode::Success; } else { return ErrCode::Fail; }
// Greater Than Equal To
#define ASSERT_GTE(a, b) if (a >= b) { return ErrCode::Success; } else { return ErrCode::Fail; }


enum ErrCode {
    Ok,
    UnknownError,
    Fail,
    Success
};

struct TestResults {
    time_t time;
    int successful;
    int failed;
    int unknown;
    std::unordered_map<std::unique_ptr<String>, ErrCode> results;
};

using TestFunc = std::function<ErrCode()>;

class TestHandler {
public:
    TestHandler();
    ~TestHandler() = default;

    void addTest(TestFunc testFunc);
    void addTest(String funcName, TestFunc testFunc);

    const String resultsString() const;
    void printResults() const;
    void saveResultsToFile() const;
    void saveResultsToFile(const bool& append) const;
    void saveResultsToFile(const String& fileName, const bool& appendMode) const;

    ErrCode runTests();

    void addResults();
    float calcSuccessPercentage() const;
private:
    std::vector<String> m_funcNames;
    std::vector<TestFunc> m_tests;
    TestResults m_testResults;
};
}

#endif // TESTHANDLER_H
