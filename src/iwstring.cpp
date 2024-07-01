#include "iwstring.h"

#include <cstring>
#include <stdexcept>

using namespace iw;

String::String()
{
    initData(0);
}

String::String(char c)
{
    setData(c, false);
}

String::String(const char* str)
{
    setData(str, false);
}

String::String(const String& str)
{
    setData(str, false);
}

String::~String()
{
    if (m_data == nullptr) {
        delete[] m_data;
    }
}

String& String::operator=(const char* str)
{
    if (m_data == nullptr) {
        setData(str, false);
    } else {
        setData(str);
    }
    return *this;
}

String& String::operator=(const String& other)
{
    if (m_data == nullptr) {
        setData(other, false);
    } else {
        setData(other);
    }
    return *this;
}

String String::operator+(const String& other)
{
    return append(other);
}

String& String::operator+=(const String& other)
{
    append(other);
    return *this;
}

bool String::operator<(const String& other)
{
    int res = strcmp(m_data, other.m_data);

    if (res < 0) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const String& other)
{
    os << other.cStr() << std::endl;
    return os;
}

char& String::operator[](const size_t& index)
{
    if (index >= length() || index < 0) {
        throw std::out_of_range("Index out of range");
    }

    return m_data[index];
}

bool String::operator==(const String& other)
{
    return equalTo(other);
}

bool String::operator!=(const String& other)
{
    return !(m_data == other.data());
}

String& String::append(const String& other)
{
    strcat_s(m_data, length() + String::length(other, true), other.data());
    return *this;
}

char& String::characterAt(size_t index) const
{
    return m_data[index];
}

String& String::clear()
{
    clearData();
    return *this;
}

const char* String::cStr() const
{
    // A wrapper for String::data()
    return data();
}

const char* String::data() const
{
    return m_data;
}

bool String::equalTo(const String& other)
{
    // This data length
    int tDataLen = strlen(m_data);
    // Other data length
    int oDataLen = strlen(other.data());

    if (tDataLen != oDataLen) {
        return false;
    }

    for (int i = 0; i < tDataLen; i++) {
        if (m_data[i] == other.data()[i]) {
            continue;
        } else {
            return false;
        }
    }

    return true; 
}

void String::setData(char c)
{
    setData(c, true);
}

void String::setData(const char* d)
{
    setData(d, true);
}

void String::setData(const String& str)
{
    setData(str, true);
}

void String::setData(char c, bool clearFirst)
{
    if (clearFirst) {
        clearData(1, true);
    } else {
        initData(1, true);
    }

    m_data[0] = c;
    appendNullTerminator();
}

void String::setData(const char* d, bool clearFirst)
{
    int len = String::length(d, true);

    if (clearFirst) {
        clearData(String::length(d), true);
    } else {
        initData(String::length(d), true);
    }

    strcpy_s(m_data, len, d);
    appendNullTerminator();
}

void String::setData(const String& str, bool clearFirst)
{
    if (clearFirst) {
        clearData(str.length(), true);
    } else {
        initData(str.length(), true);
    }

    for (int i = 0; i < str.length(true); i++) {
        m_data[i] = str.characterAt(i);
    }

    appendNullTerminator();
}

const size_t String::find(const String& findStr) const
{
    return find(0, findStr);
}

const size_t String::find(const size_t& startIndex, const String& findStr) const
{
    for (int i = startIndex; i < length(); i++) {
        for (int j = 0; j < findStr.length(); j++) {
            if (m_data[i + j] == findStr.characterAt(j)) {
                if (j < findStr.length() - 1) {
                    continue;
                } else {
                    return i;
                }
            } else {
                break;
            }
        }
    }

    return -1;
}

const size_t String::length() const
{
    return length(false);
}

const size_t String::length(const bool includeNullTerminator) const
{
    if (m_data) {
        if (includeNullTerminator) {
            return strlen(m_data) + 1;
        } else {
            return strlen(m_data);
        }
    } else {
        return -1;
    }
}

const size_t String::length(const char* str)
{
    return length(str, false);
}

const size_t String::length(const char* str, const bool includeNullTerminator)
{
    if (str) {
        if (includeNullTerminator) {
            return strlen(str) + 1;
        } else {
            return strlen(str);
        }
    } else {
        return -1;
    }
}

const size_t String::length(const String& str)
{
    return length(str.data(), false);
}

const size_t String::length(const String& str, const bool includeNullTerminator)
{
    return length(str.data(), includeNullTerminator);
}

String& String::prepend(const String& other)
{
    String res;
    res.append(other);
    res.append(m_data);

    m_data = res.m_data;

    return *this;
}

String& String::replace(const String& findStr, const String& replaceStr)
{
    size_t findIndex = find(findStr);
    
    while (findIndex != -1) {
        int remainingStrLength = length(true) - (findIndex + findStr.length());
        char* remainingStr = new char[remainingStrLength + 1];
        for (int i = 0; i < remainingStrLength; i++) {
            remainingStr[i] = m_data[findIndex + findStr.length() + i];
        }

        remainingStr[remainingStrLength - 1] = '\0';

        int newStrLength = findIndex + replaceStr.length() + remainingStrLength;

        char* newStr = new char[newStrLength];
        newStr[0] = '\0';

        char* data = new char[findIndex + 1];
        for (int i = 0; i < findIndex; i++) {
            data[i] = m_data[i];
        }

        data[findIndex] = '\0';

        strcat_s(newStr, newStrLength, data);
        strcat_s(newStr, newStrLength, replaceStr.data());
        strcat_s(newStr, newStrLength, remainingStr);

        setData(newStr);

        findIndex = find(findStr);

        delete[] remainingStr;
        delete[] newStr;
    }

    return *this;
}

std::vector<char> String::toCharVector() const
{
    std::vector<char> charVector;

    for (int i = 0; i < strlen(m_data); i++) {
        charVector.push_back(m_data[i]);
    }

    return charVector;
}

String& String::toLower()
{
    strlwr(m_data);
    return *this;
}

String& String::toUpper()
{
    strupr(m_data);
    return *this;
}


void String::appendNullTerminator()
{
    int len = length();

    if (m_data[len - 1] != '\0') {
        m_data[len] = '\0';
    }
}

String String::appendString(const String& other)
{
    char* str = new char[length() + other.length() + 1];
    strcat_s(str, length(), m_data);
    strcat_s(str, String::length(other, true), other.data());

    String res(str);
    delete[] str;
    return res;
}

void String::clearData()
{
    delete[] m_data;
    initData(0, true);
}

void String::clearData(const int newLength)
{
    clearData(newLength, true);
}

void String::clearData(const int newLength, const bool appendNullTerminator_)
{
    delete[] m_data;

    if (appendNullTerminator_) {
        initData(newLength + 1);
    } else {
        initData(newLength);
    }
}

void String::initData(const int newLength)
{
    initData(newLength, true);
}

void String::initData(const int newLength, const bool appendNullTerminator_)
{
    // WARNING: This method is dangerous
    // Deleting `m_data` MUST be handled separately from this method
    if (appendNullTerminator_) {
        m_data = new char[newLength + 1];
    } else {
        m_data = new char[newLength];
    }

    if (newLength == 0 && appendNullTerminator_) {
        m_data[0] = '\0';
    }
}
