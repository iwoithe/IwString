#include <iostream>

#include "../src/iwstring.h"

int main()
{
    iw::String str = iw::String();
    str.setData("Hello, World!");
    std::cout << str.data() << std::endl;

    std::cout << str.length() << std::endl;

    return 0;
}
