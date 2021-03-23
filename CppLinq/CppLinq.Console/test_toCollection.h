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
    inline void RunTestToCollection(TContainer& cont, std::string label, container_type target) {
        std::cout << "toVector " << std::endl;
        auto n_ZA = From(cont).ToVector();
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(From(n_ZA), set_, set_.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(From(n_ZA), mset_, mset_.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(From(n_ZA), { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 })); break;
        }

        std::cout << "tolist :" << std::endl;
        auto n_ZB = From(cont).ToList();
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(From(n_ZB), set_, set_.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(From(n_ZA), mset_, mset_.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(From(n_ZB), { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 })); break;
        }
    }
}
