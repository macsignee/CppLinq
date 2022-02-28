
#include <iostream>
#include "testFunc.h"
#include <type_traits>
#include "../CppLinq/MacLinq.h"

using namespace macsignee::cppLinq;

int main()
{
    using namespace std;
    using namespace macsignee::cppLinq;
    using namespace simple_test;

    //std::pair<const int, int> d1 = std::make_pair<const int, int>(10, 20);
    //nullable_<std::pair<const int,int> > a1;
    //nullable_<std::pair<const int, int> > a2{ d1 };
    //nullable_<std::pair<const int, int> > a3 = d1;
    //nullable_<std::pair<const int, int> > a4 = a1;
    //nullable_<std::pair<const int, int> > a5{ a1 };
    //a1 = std::make_pair<const int, int>(3, 4);
    ////d1 = *a1;
    //a1 = a2;

    //std::pair<int, int> d2 = std::make_pair<int, int>(10, 20);
    //nullable_<std::pair<int, int> > a21;
    //nullable_<std::pair<int, int> > a22{ d2 };
    //nullable_<std::pair<int, int> > a23 = d2;
    //nullable_<std::pair<int, int> > a24 = a21;
    //a21 = std::make_pair<int, int>(3, 4);
    //d2 = *a21;

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

    //RunTestKV(map_, "map", container_type::keyValue);
}
