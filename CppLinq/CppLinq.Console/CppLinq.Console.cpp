
#include <iostream>
#include "testFunc.h"
#include "..\CppLinq\MacLinq.h"

int main()
{
    std::cout << "Hello World!\n";

    auto n10 = From<std::vector<int>>({ 2, 3, 1, 4, 5, 6, 9, 8, 7, 14, 13, 22 })
        //auto n10 = From<std::list<int>>({ 2, 3, 1, 4, 5, 6, 9, 8, 7, 14, 13, 22 }) // also Ok
        .Where([](const auto& elm) {return elm % 2 == 1; })
        //.SortBy([](const auto& lhs, const auto& rhs) {return lhs < rhs; })
        .OrderBy([](const auto& elm) {return elm; }, [](const auto& lhs, const auto& rhs) {return lhs < rhs; })
        .Select(
            [](const auto& elm) {
                return std::make_tuple(elm, (double)elm, std::to_string(elm) + "-str");
            })
        .ToVector();
}
