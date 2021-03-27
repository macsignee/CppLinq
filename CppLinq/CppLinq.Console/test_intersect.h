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
    inline void RunTestIntersect(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<val_type> res{ 5, 2 };
        std::set<val_type>    res2{ 5, 2 };

        std::cout << "intersect : and vector" << std::endl;
        auto n_1 = From(cont).Intersect(argVec, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_1, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "intersect : and list" << std::endl;
        auto n_2 = From(cont).Intersect(argLst, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_2, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "intersect : and forward_list" << std::endl;
        auto n_3 = From(cont).Intersect(argFlst, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_3, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "intersect : and deque" << std::endl;
        auto n_4 = From(cont).Intersect(argDqu, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_4, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "intersect : and array " << std::endl;
        auto n_5 = From(cont).Intersect(argAry, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_5, res)); break;
        }

        std::cout << "intersect : and set" << std::endl;
        auto n_6 = From(cont).Intersect(argSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_6, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_6, res2, res2.size())); break;
        }

        std::cout << "intersect : and unordered_set" << std::endl;
        auto n_7 = From(cont).Intersect(argUSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_7, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_7, res2, res2.size())); break;
        }

        std::cout << "intersect : and multiset" << std::endl;
        auto n_8 = From(cont).Intersect(argMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_8, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_8, res2, res2.size())); break;
        }

        std::cout << "intersect : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Intersect(argUMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_9, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_9, res2, res2.size())); break;
        }

        TContainer empty{};
        std::cout << "intersect : empty" << std::endl;
        auto n_A_ = From(empty).Intersect(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_A_, {})); break;
        }
    }

    template <typename TContainer>
    inline void RunTestIntersectKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<val_type> res{ 5, 2 };
        std::set<val_type>    res2{ 5, 2 };

        std::cout << "intersect : and vector" << std::endl;
        auto n_1 = From(cont).Intersect(argVec, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "intersect : and list" << std::endl;
        auto n_2 = From(cont).Intersect(argLst, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "intersect : and forward_list" << std::endl;
        auto n_3 = From(cont).Intersect(argFlst, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "intersect : and deque" << std::endl;
        auto n_4 = From(cont).Intersect(argDqu, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "intersect : and array " << std::endl;
        auto n_5 = From(cont).Intersect(argAry, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "intersect : and set" << std::endl;
        auto n_6 = From(cont).Intersect(argSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "intersect : and unordered_set" << std::endl;
        auto n_7 = From(cont).Intersect(argUSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "intersect : and multiset" << std::endl;
        auto n_8 = From(cont).Intersect(argMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "intersect : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Intersect(argUMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        TContainer empty{};
        std::cout << "intersect : empty" << std::endl;
        auto n_A_ = From(empty).Intersect(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }
    }
}
