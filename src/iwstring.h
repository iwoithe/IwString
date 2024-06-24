#ifndef IWSTRING_H
#define IWSTRING_H

namespace iw {
class String
{
public:
    String();
    // String(const char* _str);
    // String(const String& _other);
    // ~String();

    char& characterAt(int index);

    const char* data();
    void setData(const char* d);

    int length();

private:
    char* m_data;
};
}

#endif // IWSTRING_H
