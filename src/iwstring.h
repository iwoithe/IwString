#ifndef IWSTRING_H
#define IWSTRING_H

#include <cstring>
#include <vector>

namespace iw {
class String
{
public:
    String();
    String(String &&) = default;
    String &operator=(String &&) = default;
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
    String append(const String& other, const bool& insertNullTerm) const;

    char& characterAt(int index) const;

    const char* cstr() const;

    const char* data() const;
    void setData(char c);
    void setData(const char* d);

    const int find(const String& findStr) const;
    const int find(const int& startIndex, const String& findStr) const;

    const int length() const;

    String prepend(const String& other) const;

    void replace(const String& findStr, const String& replaceStr);

    std::vector<char> toCharVector() const;
    String toLower();
    String toUpper();

private:
    char* m_data;
};
}

#endif // IWSTRING_H
