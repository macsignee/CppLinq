
#include <iostream>
#include "testFunc.h"
#include <type_traits>
#include "../CppLinq/MacLinq.h"

int main()
{
    using namespace std;
    using namespace macsignee::cppLinq;
    using namespace simple_test;

    //auto result = From<vector<int>>({ 2, 3, 1, 4, 5, 6, 9, 8, 7, 14, 13, 22 })
    //vector<int> vec = { 2, 3, 1, 4, 5, 6, 9, 8, 7, 14, 13, 2 };
    //auto result = From(vec)
    //    .Where([](const auto& elm) {return elm % 2 == 1; })
    //    //.SortBy([](const auto& lhs, const auto& rhs) {return lhs < rhs; })
    //    .OrderBy([](const auto& elm) {return elm; }, [](const auto& lhs, const auto& rhs) {return lhs < rhs; })
    //    .Select(
    //        [](const auto& elm) {
    //        return make_tuple(elm, (double)elm, to_string(elm) + "-str");
    //    })
    //    .ToVector();

    RunTest(vec_, "vector", container_type::sequence);

    RunTest(deq_, "deque", container_type::sequence);

    RunTest(ary_, "array", container_type::array);

    RunTest(list_, "list", container_type::sequence);

    RunTest(flist_, "forward_list", container_type::forward);

    RunTest(set_, "set", container_type::unique);

    RunTest(uset_, "unordered_set", container_type::hash_unique);

    RunTest(mset_, "mutliset", container_type::multi);

    RunTest(umset_, "unordered_mutliset", container_type::hash_multi);

    //RunTest(map_, "map", container_type::keyValue);
}
