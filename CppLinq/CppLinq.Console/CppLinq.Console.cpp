
#include <iostream>
#include "testFunc.h"
#include "..\CppLinq\MacLinq.h"

int main()
{
    std::cout << "Hello World!\n";

    std::string str = "aaaaaaa";
    auto a = From(str);
}
