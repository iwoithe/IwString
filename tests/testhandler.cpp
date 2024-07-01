#include "testhandler.h"

#include <cassert>
#include <ctime>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>

using namespace iw;

TestHandler::TestHandler() {}
TestHandler::~TestHandler() {}

void TestHandler::addTest(TestFunc testFunc)
{
    addTest("{Function name hidden}", testFunc);
}

void TestHandler::addTest(String funcName, TestFunc testFunc)
{
    m_funcNames.push_back(funcName);
    m_tests.push_back(testFunc);
}

const String TestHandler::resultsString() const
{
    String res;

    res.append(std::ctime(&m_testResults.time));
    res.append("\n");
    res.append("Successful ");
    res.append(calcSuccessPercentage());
    res.append("% out of ");
    res.append(m_funcNames.size());
    res.append(" tests\n");
    res.append(m_testResults.successful);
    res.append(" successful, ");
    res.append(m_testResults.failed);
    res.append(" fails, ");
    res.append(m_testResults.unknown);
    res.append(" unknowns\n\n");

    for (auto& [funcNamePtr, errCode] : m_testResults.results) {
        res.append(funcNamePtr.get()->cStr());
        switch (errCode) {
            case ErrCode::SUCCESS:
                res.append(" SUCCESS\n");
                break;
            case ErrCode::FAIL:
                res.append(" FAIL\n");
                break;
            default:
                res.append(" UNKNOWN\n");
                break;
        }
    }

    return res;
}

void TestHandler::printResults() const
{
    resultsString().writeToConsole();
}

ErrCode TestHandler::runTests()
{
    m_testResults = TestResults();
    m_testResults.time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    int i = 0;

    for (auto test : m_tests) {
        ErrCode c = test();
        m_testResults.results[std::make_unique<String>(m_funcNames[i])] = c;
        i++;
    }

    addResults();

    return ErrCode::OK;
}

void TestHandler::addResults()
{
    int successes = 0;
    int fails = 0;
    int unknowns = 0;

    for (auto& [funcName, errCode] : m_testResults.results) {
        switch (errCode) {
            case ErrCode::SUCCESS:
                successes++;
                break;
            case ErrCode::FAIL:
                fails++;
                break;
            case ErrCode::UNKNOWN_ERROR:
                unknowns++;
                break;
            default:
                break;
        }
    }

    m_testResults.successful = successes;
    m_testResults.failed = fails;
    m_testResults.unknown = unknowns;
}

float TestHandler::calcSuccessPercentage() const
{
    return (float)m_testResults.successful / (float)(m_funcNames.size()) * 100.0f;
}
