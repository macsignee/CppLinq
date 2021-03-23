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
    inline void RunTestExcept(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        auto lmb_gt = [](const auto& lhs, const auto& rhs) {return lhs < rhs; };

        std::vector<val_type> res{ 3, 1, 4, 6, 9, 8, 7 };
        std::set<val_type>    res2{ 3, 1, 4, 6, 9, 8, 7 };

        std::cout << "except : and vector" << std::endl;
        auto n_1 = From(cont).Except(argVec, lmb_gt);
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
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "except : and list" << std::endl;
        auto n_2 = From(cont).Except(argLst, lmb_gt);
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
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "except : and forward_list" << std::endl;
        auto n_3 = From(cont).Except(argFlst, lmb_gt);
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
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "except : and deque" << std::endl;
        auto n_4 = From(cont).Except(argDqu, lmb_gt);
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
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "except : and array " << std::endl;
        auto n_5 = From(cont).Except(argAry, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_5, res)); break;
        }

        std::cout << "except : and set" << std::endl;
        auto n_6 = From(cont).Except(argSet, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_6, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_6, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkUnique(n_6, res2, res2.size())); break;
        }

        std::cout << "except : and unordered_set" << std::endl;
        auto n_7 = From(cont).Except(argUSet, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_7, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_7, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkUnique(n_7, res2, res2.size())); break;
        }

        std::cout << "except : and multiset" << std::endl;
        auto n_8 = From(cont).Except(argMset, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_8, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_8, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkUnique(n_8, res2, res2.size())); break;
        }

        std::cout << "except : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Except(argUMset, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_9, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_9, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkUnique(n_9, res2, res2.size())); break;
        }

        TContainer empty{};
        std::cout << "except : empty" << std::endl;
        auto n_A_ = From(empty).Except(argLst, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_A_, { 0 })); break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_A_, {})); break;
        }
    }
    template <typename TContainer>
    inline void RunTestExceptKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        auto lmb_gt = [](const auto& lhs, const auto& rhs) {return lhs < rhs; };

        std::vector<val_type> res{ 3, 1, 4, 6, 9, 8, 7 };
        std::set<val_type>    res2{ 3, 1, 4, 6, 9, 8, 7 };

        std::cout << "except : and vector" << std::endl;
        auto n_1 = From(cont).Except(argVec, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "except : and list" << std::endl;
        auto n_2 = From(cont).Except(argLst, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "except : and forward_list" << std::endl;
        auto n_3 = From(cont).Except(argFlst, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "except : and deque" << std::endl;
        auto n_4 = From(cont).Except(argDqu, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "except : and array " << std::endl;
        auto n_5 = From(cont).Except(argAry, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "except : and set" << std::endl;
        auto n_6 = From(cont).Except(argSet, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }


        std::cout << "except : and unordered_set" << std::endl;
        auto n_7 = From(cont).Except(argUSet, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "except : and multiset" << std::endl;
        auto n_8 = From(cont).Except(argMset, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "except : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Except(argUMset, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        TContainer empty{};
        std::cout << "except : empty" << std::endl;
        auto n_A_ = From(empty).Except(argLst, lmb_gt);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }
    }
}
