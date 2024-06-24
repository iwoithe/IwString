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

char& String::characterAt(int index)
{
    return m_data[index];
}

const char* String::cstr()
{
    // A wrapper for String::data()
    return data();
}

const char* String::data()
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
