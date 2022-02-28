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
    inline void RunTestSkip(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::cout << "skip " << std::endl;
        auto n_1 = From(cont).Skip(2);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkUnique(n_1, set_, 7)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkUnique(n_1, set_, 11)); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_1, { 1,4,5,6,9,8,7, 5, 3, 8, 2 })); break;
        }

        TContainer empty{};
        std::cout << "skip empty" << std::endl;
        auto n_1_ = From(empty).Skip(2);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_1_, { 0,0,0,0,0,0,0,0,0,0, 0 })); break;
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
    inline void RunTestSkipKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::cout << "skip " << std::endl;
        {
            auto n_ = From(cont).Skip(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        std::cout << "skip empty" << std::endl;
        TContainer empty{};
        {
            auto n_ = From(empty).Skip(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }
    }
}
