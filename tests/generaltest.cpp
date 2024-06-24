#include <iostream>

#include "../src/iwstring.h"

using namespace iw;

int main()
{
    String str = String();
    str.setData("Hello, World!");
    std::cout << str.data() << std::endl;
    std::cout << str.cstr() << std::endl;

    std::cout << str.length() << std::endl;

    std::cout << str.characterAt(0) << std::endl;

    return 0;
}
