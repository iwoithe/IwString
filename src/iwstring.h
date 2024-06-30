#ifndef IWSTRING_H
#define IWSTRING_H

#include <cstring>
#include <vector>
#include <ostream>

namespace iw {
class String
{
public:
    String();
    String(String &&) = default;
    String &operator=(String &&) = default;
    String(char c);
    String(const char* str);
    String(const String& str);
    ~String();

    String& operator=(const char* str);
    String& operator=(const String& other);
    String operator+(const String& other);
    String& operator+=(const String& other);
    friend std::ostream& operator<<(std::ostream& os, const String& other);
    char& operator[](const int& index);
    bool operator==(const String& other);
    bool operator!=(const String& other);

    String& append(const String& other);

    char& characterAt(int index) const;

    String& clear();

    const char* cstr() const;

    const char* data() const;
    void setData(char c);
    void setData(const char* d);
    void setData(const String& str);
    void setData(char c, bool clearFirst);
    void setData(const char* d, bool clearFirst);
    void setData(const String& str, bool clearFirst);

    const int find(const String& findStr) const;
    const int find(const int& startIndex, const String& findStr) const;

    const int length() const;
    const int length(const bool includeNullTerminator) const;
    static const int length(const char* str);
    static const int length(const char* str, const bool includeNullTerminator);
    static const int length(const String& str);
    static const int length(const String& str, const bool includeNullTerminator);

    String& prepend(const String& other);

    String& replace(const String& findStr, const String& replaceStr);

    std::vector<char> toCharVector() const;
    String& toLower();
    String& toUpper();

private:
    char* m_data;

    void appendNullTerminator();

    String appendString(const String& other);

    void clearData();
    void clearData(const int newLength);
    void clearData(const int newLength, const bool appendNullTerminator_);

    void initData(const int newLength);
    void initData(const int newLength, const bool appendNullTerminator_);
};
}

#endif // IWSTRING_H
