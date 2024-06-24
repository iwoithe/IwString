#ifndef IWSTRING_H
#define IWSTRING_H

#include <cstring>

namespace iw {
class String
{
public:
    String();
    String(const char* str);
    // String(const String& _other);
    // ~String();

    String operator+(String& other)
    {
        String res;

        // This data length
        int tDataLen = strlen(this->data());
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

    char& characterAt(int index);

    const char* cstr();

    const char* data();
    void setData(const char* d);

    int length();

private:
    char* m_data;
};
}

#endif // IWSTRING_H
