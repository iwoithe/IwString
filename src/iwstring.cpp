#include "iwstring.h"

using namespace iw;

String::String()
{
    m_data = new char[1];
    m_data[0] = '\0';
}

String::String(char c)
{
    setData(c);
}

String::String(char* str)
{
    setData(str);
}

String::String(const char* str)
{
    setData(str);
}

String::String(String& str)
{
    setData(str.data());
}

String::String(const String& str)
{
    setData(const_cast<char*>(str.data()));
}

String::~String() {}

String String::operator=(const char* str)
{
    String res;
    res.setData(str);
    return res;
}

String String::operator=(const String& other)
{
    String res;
    res.setData(const_cast<char*>(other.data()));
    return res;
}

String String::operator+(const String& other)
{
    return append(other);
}

String& String::operator+=(const String& other)
{
    setData(append(other).data());
    return *this;
}

String String::operator<<(const String& other)
{
    return append(other);
}

char& String::operator[](const int& index)
{
    return m_data[index];
}

bool String::operator==(const String& other)
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

bool String::operator!=(const String& other)
{
    return !(m_data == other.data());
}

String& String::append(const String& other)
{
    strcat_s(m_data, sizeof(m_data) + sizeof(other.data()), other.data());
    return *this;
}

char& String::characterAt(int index) const
{
    return m_data[index];
}

const char* String::cstr() const
{
    // A wrapper for String::data()
    return data();
}

const char* String::data() const
{
    return m_data;
}

void String::setData(char c)
{
    m_data = new char[2];
    m_data[0] = c;
    m_data[1] = '\0';
}

void String::setData(const char* d)
{
    int n = strlen(d);

    m_data = new char[n];

    for (int i = 0; i < n; i++) {
        m_data[i] = d[i];
    }

    if (m_data[n - 1] != '\0') {
        m_data[n] = '\0';
    }
}

const int String::find(const String& findStr) const
{
    return find(0, findStr);
}

const int String::find(const int& startIndex, const String& findStr) const
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

const int String::length() const
{
    return strlen(m_data);
}

String& String::prepend(const String& other)
{
    String res;
    res.append(other);
    res.append(m_data);

    m_data = res.m_data;

    return *this;
}

void String::replace(const String& findStr, const String& replaceStr)
{
    int findIndex = find(findStr);
    
    while (findIndex != -1) {
        String remainingStr;
        
        int remainingStrLength = length() - (findIndex + findStr.length());
        for (int i = 0; i < remainingStrLength; i++) {
            remainingStr += m_data[findIndex + findStr.length() + i];
        }

        String newStr;
        for (int i = 0; i < findIndex; i++) {
            newStr += m_data[i];
        }

        newStr += replaceStr;
        newStr += remainingStr;

        setData(newStr.data());

        findIndex = find(findStr);
    }
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
