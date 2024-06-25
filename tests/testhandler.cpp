#include "testhandler.h"

#include <cassert>
#include <ctime>
#include <chrono>
#include <iostream>
#include <memory>

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

void TestHandler::printResults()
{
    std::cout << std::ctime(&m_testResults.time) << std::endl;
    std::cout << "Successful " << successPercentage() << "% out of " << m_funcNames.size() << " tests\n" << std::endl;
    for (auto& [funcNamePtr, errCode] : m_testResults.results) {
        switch (errCode) {
            case ErrCode::SUCCESS:
                std::cout << funcNamePtr.get()->cstr() << " SUCCESS" << std::endl;
                break;
            case ErrCode::FAIL:
                std::cout << funcNamePtr.get()->cstr() << " FAIL" << std::endl;
                break;
            default:
                std::cout << funcNamePtr.get()->cstr() << " UNKNOWN" << std::endl;
                break;
        }
    }
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

    return ErrCode::OK;
}

float TestHandler::successPercentage()
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

    return (float)successes / (float)(successes + fails + unknowns) * 100.0f;
}
