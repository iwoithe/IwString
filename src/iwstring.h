#ifndef IWSTRING_H
#define IWSTRING_H

#include <cstddef>
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
    bool operator<(const String& other);
    friend std::ostream& operator<<(std::ostream& os, const String& other);
    char& operator[](const size_t& index);
    bool operator==(const String& other);
    bool operator!=(const String& other);

    String& append(const String& other);

    char& characterAt(size_t index) const;

    String& clear();

    const char* cStr() const;

    const char* data() const;
    void setData(char c);
    void setData(const char* d);
    void setData(const String& str);
    void setData(char c, bool clearFirst);
    void setData(const char* d, bool clearFirst);
    void setData(const String& str, bool clearFirst);

    const size_t find(const String& findStr) const;
    const size_t find(const size_t& startIndex, const String& findStr) const;

    const size_t length() const;
    const size_t length(const bool includeNullTerminator) const;
    static const size_t length(const char* str);
    static const size_t length(const char* str, const bool includeNullTerminator);
    static const size_t length(const String& str);
    static const size_t length(const String& str, const bool includeNullTerminator);

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
