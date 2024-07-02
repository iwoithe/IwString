#include "testhandler.h"

#include <cassert>
#include <ctime>
#include <chrono>
#include <fstream>
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

const String TestHandler::resultsString() const
{
    String res;

    res.appendColor(Color::Blue, ColorLayer::Foreground);
    res.append(std::ctime(&m_testResults.time));
    res.appendColor(Color::None, ColorLayer::Foreground);
    res.append("\n");
    res.append("Successful ");

    float perc = calcSuccessPercentage();
    if  (perc == 100){
        res.appendColor(Color::Green, ColorLayer::Foreground);
    } else if (perc >= 50.0f) {
        res.appendColor(Color::Yellow, ColorLayer::Foreground);
    } else if (perc >= 0.0f) {
        res.appendColor(Color::Red, ColorLayer::Foreground);
    }

    res.append(perc);

    res.appendColor(Color::None, ColorLayer::Foreground);
    res.append("% out of ");
    res.append(m_funcNames.size());
    res.append(" tests\n");
    res.appendColor(Color::Green, ColorLayer::Foreground);
    res.append(m_testResults.successful);
    res.appendColor(Color::None, ColorLayer::Foreground);
    res.append(" successful, ");
    res.appendColor(Color::Red, ColorLayer::Foreground);
    res.append(m_testResults.failed);
    res.appendColor(Color::None, ColorLayer::Foreground);
    res.append(" fails, ");
    res.appendColor(Color::Yellow, ColorLayer::Foreground);
    res.append(m_testResults.unknown);
    res.appendColor(Color::None, ColorLayer::Foreground);
    res.append(" unknowns\n\n");

    res.appendColor(Color::None, ColorLayer::Foreground);

    for (auto& [funcNamePtr, errCode] : m_testResults.results) {
        res.append(funcNamePtr.get()->cStr());
        switch (errCode) {
            case ErrCode::Success:
                res.append(" ");
                res.appendColor(Color::Green, ColorLayer::Foreground);
                res.append("Success");
                res.appendColor(Color::None, ColorLayer::Foreground);
                res.append("\n");
                break;
            case ErrCode::Fail:
                res.append(" ");
                res.appendColor(Color::Red, ColorLayer::Foreground);
                res.append("Fail");
                res.appendColor(Color::None, ColorLayer::Foreground);
                res.append("\n");
                break;
            default:
                res.append(" ");
                res.appendColor(Color::Yellow, ColorLayer::Foreground);
                res.append("Unknown");
                res.appendColor(Color::None, ColorLayer::Foreground);
                res.append("\n");
                break;
        }
    }

    return res;
}

void TestHandler::printResults() const
{
    resultsString().writeToConsole();
}

void TestHandler::saveResultsToFile() const
{
    // TODO: Append, not override
    String fileName = "testresults.txt";
    std::fstream file;
    file.open(fileName.cStr(), std::ios::out);
    if (file.is_open()) {
        file << resultsString() << std::endl;
    } else {
        String errMessage = "[ERROR] (TestHandler::saveResultsToFile) \"";
        errMessage.append(fileName).append("\" could not be opened");
        errMessage.writeToConsole();
    }

    file.close();
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

    return ErrCode::Ok;
}

void TestHandler::addResults()
{
    int successes = 0;
    int fails = 0;
    int unknowns = 0;

    for (auto& [funcName, errCode] : m_testResults.results) {
        switch (errCode) {
            case ErrCode::Success:
                successes++;
                break;
            case ErrCode::Fail:
                fails++;
                break;
            case ErrCode::UnknownError:
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
