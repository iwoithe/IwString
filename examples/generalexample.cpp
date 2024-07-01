#include <iostream>

#include "../src/iwstring.h"

using namespace iw;

int main()
{
    String str = String();
    str.setData("Hello, World!");
    std::cout << str.data() << std::endl;
    std::cout << str.cStr() << std::endl;

    std::cout << str.length() << std::endl;

    std::cout << str.characterAt(0) << std::endl;

    String helloStr = String("Hello");
    String worldStr = String("World");
    String resStr = helloStr + ", " + worldStr + "!";
    std::cout << resStr.cStr() << std::endl;

    String res2Str = helloStr + ", " + worldStr + "!";
    std::cout << res2Str.cStr() << std::endl;

    return 0;
}
