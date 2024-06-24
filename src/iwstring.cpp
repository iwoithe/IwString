#include "iwstring.h"

using namespace iw;

String::String()
{
    m_data = new char[1];
    m_data[0] = '\0';
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
    m_data = const_cast<char*>(str.data());
}

String String::operator+(const String& other)
{
    return appendString(other);
}

String String::operator<<(const String& other)
{
    return appendString(other);
}

String String::appendString(const String& other)
{
    String res;

    // This data length
    int tDataLen = strlen(m_data);
    // Other data length
    int oDataLen = strlen(other.data());

    char* strData = new char[tDataLen + oDataLen];

    for (int i = 0; i < tDataLen; i++) {
        strData[i] = m_data[i];
    }

    for (int i = 0; i < oDataLen; i++) {
        strData[i + tDataLen] = other.characterAt(i);
    }

    strData[tDataLen + oDataLen] = '\0';

    res.setData(strData);

    return res;
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

void String::setData(const char* d)
{
    int n = strlen(d);

    m_data = new char[n];

    for (int i = 0; i < n; i++) {
        m_data[i] = d[i];
    }

    m_data[n] = '\0';
}

int String::length()
{
    return strlen(m_data);
}
