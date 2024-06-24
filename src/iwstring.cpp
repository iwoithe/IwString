#include "iwstring.h"

#include <cstring>

using namespace iw;

String::String()
{
    m_data = new char[1];
    m_data[0] = '\0';
}

const char* String::data()
{
    return m_data;
}

void String::setData(const char* d)
{
    int i = 0;
    int n = strlen(d);

    m_data = new char[n];

    for (i; i < n; i++) {
        m_data[i] = d[i];
    }

    m_data[n] = '\0';
}

int String::length()
{
    return strlen(m_data);
}
