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
    inline void RunTestReverse(TContainer& cont, std::string label, container_type target) {
        std::cout << "reverse :" << std::endl;
        auto n_1 = From(cont).Reverse();
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkUnique(n_1, { 9,8,7,6,5,4,3,2,1 })); break;
        case container_type::multi      : assert(checkArray(n_1, { 9,8,8,7,6,5,5,4,3,3,2,2,1 })); break;
        case container_type::hash_multi : assert(checkUnique(n_1, { 9,8,8,7,6,5,5,4,3,3,2,2,1 })); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, { 2,8,3,5,7,8,9,6,5,4,1,3,2 })); break;
        }

        TContainer empty{};
        std::cout << "reverse : empty" << std::endl;
        auto n_1_ = From(empty).Reverse();
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_1_, { 0,0,0,0,0,0,0,0,0,0,0,0,0 })); break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_1_, {})); break;
        }
    }

    template <typename TContainer>
    inline void RunTestReverseKV(TContainer& cont, std::string label, container_type target) {
        std::cout << "reverse :" << std::endl;
        auto n_1 = From(cont).Reverse();
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        TContainer empty{};
        std::cout << "reverse : empty" << std::endl;
        auto n_1_ = From(empty).Reverse();
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }
    }
}
