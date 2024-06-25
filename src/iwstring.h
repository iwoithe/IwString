#ifndef IWSTRING_H
#define IWSTRING_H

#include <cstring>

namespace iw {
class String
{
public:
    String();
    String(const char* str);
    String(String& str);
    String(const String& str);
    ~String();

    String operator=(const char* str);
    String operator=(const String& other);
    String operator+(const String& other);
    String operator<<(const String& other);
    bool operator==(const String& other);

    String append(const String& other) const;

    char& characterAt(int index) const;

    const char* cstr() const;

    const char* data() const;
    void setData(const char* d);

    const int length() const;

private:
    char* m_data;
};
}

#endif // IWSTRING_H
