#pragma once
#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <array>
#include <deque>
#include <tuple>
#include <cassert>

#include "../CppLinq/MacLinq.h"
#include "../CppLinq.Test/CppLinq.Test.h"

namespace simple_test
{
    using namespace macsignee::cppLinq;
    using namespace macsignee::cppLinq::container_test;

    template <typename TContainer>
    inline void RunTestDistinct(TContainer& cont, std::string label, container_type target) {
        std::cout << "distinct : no condition" << std::endl;
        auto n_1 = From(cont).Distinct();
        switch (target) {
        case container_type::unique     : assert(checkArray(n_1, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::hash_unique: assert(checkUnique(n_1, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::multi      : assert(checkArray(n_1, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::hash_multi : assert(checkUnique(n_1, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, { 2, 3, 1, 4, 5, 6, 9, 8, 7 })); break;
        }

        std::cout << "distinct : condition" << std::endl;
        auto n_2 = From(cont).Distinct([](const auto& lhs, const auto& rhs) {return lhs == rhs; });
        switch (target) {
        case container_type::unique     : assert(checkArray(n_2, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::hash_unique: assert(checkUnique(n_2, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::multi      : assert(checkArray(n_2, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::hash_multi : assert(checkUnique(n_2, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_2, { 2, 3, 1, 4, 5, 6, 9, 8, 7 })); break;
        }
    }
}
