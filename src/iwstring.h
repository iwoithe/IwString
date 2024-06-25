#ifndef IWSTRING_H
#define IWSTRING_H

#include <cstring>
#include <vector>

namespace iw {
class String
{
public:
    String();
    String(char c);
    String(char* str);
    String(const char* str);
    String(String& str);
    String(const String& str);
    ~String();

    String operator=(const char* str);
    String operator=(const String& other);
    String operator+(const String& other);
    String& operator+=(const String& other);
    String operator<<(const String& other);
    char& operator[](const int& index);
    bool operator==(const String& other);
    bool operator!=(const String& other);

    String append(const String& other) const;

    char& characterAt(int index) const;

    const char* cstr() const;

    const char* data() const;
    void setData(char c);
    void setData(const char* d);

    const int length() const;

    std::vector<char> toCharVector() const;
    String toLower();
    String toUpper();

private:
    char* m_data;
};
}

#endif // IWSTRING_H
