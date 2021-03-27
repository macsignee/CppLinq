#pragma once
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
    inline void RunTestUnion(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        std::vector<val_type> res{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 99, 954, 1298 };
        std::set<val_type> res2{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 99, 954, 1298 };
        std::cout << "union : and vector " << std::endl;
        auto n_0 = From(cont).Union(argVec, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkUnique(n_0, res2, res2.size())); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkUnique(n_0, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_0, res)); break;
        }

        std::cout << "union : and list " << std::endl;
        auto n_1 = From(cont).Union(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_1, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_1, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "union : and forward_list " << std::endl;
        auto n_2 = From(cont).Union(argFlst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_2, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_2, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "union : and deque " << std::endl;
        auto n_3 = From(cont).Union(argDqu, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_3, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_3, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "union : and array " << std::endl;
        auto n_4 = From(cont).Union(argAry, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_4, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_4, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "union : and set" << std::endl;
        auto n_5 = From(cont).Union(argSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkUnique(n_5, res2, res2.size())); break;
        }

        std::cout << "union : and unordered_set" << std::endl;
        auto n_6 = From(cont).Union(argUSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_6, res2, res2.size())); break;
        }

        std::cout << "union : and multiset" << std::endl;
        auto n_7 = From(cont).Union(argMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_7, res2, res2.size())); break;
        }

        std::cout << "union : and unordered_multiset" << std::endl;
        auto n_8 = From(cont).Union(argUMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_8, res2, res2.size())); break;
        }

        TContainer empty{};
        std::cout << "union : empty" << std::endl;
        auto n_9_ = From(empty).Union(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_9_, { 0, 99, 5, 954, 2, 1298 })); break;
        case container_type::unique     : assert(checkUnique(n_9_, { 99, 5, 954, 2, 1298 })); break;
        case container_type::multi      : assert(checkUnique(n_9_, { 99, 5, 954, 2, 1298 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::hash_unique:
        case container_type::hash_multi :
        default                         : assert(checkArray(n_9_, { 99, 5, 954, 2, 1298 })); break;
        }
    }

    template <typename TContainer>
    inline void RunTestUnionKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        std::vector<val_type> res{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 99, 954, 1298 };
        std::set<val_type> res2{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 99, 954, 1298 };
        std::cout << "union : and vector " << std::endl;
        auto n_0 = From(cont).Union(argVec, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "union : and list " << std::endl;
        auto n_1 = From(cont).Union(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

        std::cout << "union : and forward_list " << std::endl;
        auto n_2 = From(cont).Union(argFlst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

        std::cout << "union : and deque " << std::endl;
        auto n_3 = From(cont).Union(argDqu, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

        std::cout << "union : and array " << std::endl;
        auto n_4 = From(cont).Union(argAry, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

        std::cout << "union : and set" << std::endl;
        auto n_5 = From(cont).Union(argSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

        std::cout << "union : and unordered_set" << std::endl;
        auto n_6 = From(cont).Union(argUSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

        std::cout << "union : and multiset" << std::endl;
        auto n_7 = From(cont).Union(argMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

        std::cout << "union : and unordered_multiset" << std::endl;
        auto n_8 = From(cont).Union(argUMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

        TContainer empty{};
        std::cout << "union : empty" << std::endl;
        auto n_9_ = From(empty).Union(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue:
        case container_type::multi_kv:
        case container_type::hash_kv:
        case container_type::hash_mul_kv: assert(false);  break;
        default: assert(false);  break;
        }

    }
}
