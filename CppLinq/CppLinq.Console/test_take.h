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
    inline void RunTestTake(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::cout << "Take " << std::endl;
        {
            auto n_2 = From(cont).Take(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     :
            case container_type::hash_unique: assert(checkUnique(n_2, set_, 2)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUnique(n_2, set_, 2)); break;
            case container_type::sequence   :
            case container_type::array      :
            case container_type::forward    :
            default                         : assert(checkArray(n_2, { 2,3 })); break;
            }
        }
        std::cout << "Take empty" << std::endl;
        {
            TContainer empty{};
            auto n_2_ = From(empty).Take(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::array      : assert(checkArray(n_2_, { 0,0 })); break;
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::forward    :
            default                         : assert(checkArray(n_2_, {})); break;
            }
        }
    }

    template <typename TContainer>
    inline void RunTestTakeKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::cout << "Take " << std::endl;
        {
            auto n_2 = From(cont).Take(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }
        std::cout << "Take empty" << std::endl;
        {
            TContainer empty{};
            auto n_2_ = From(empty).Take(2);
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
