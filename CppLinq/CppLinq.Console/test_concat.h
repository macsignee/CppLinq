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
    inline void RunTestConcat(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<val_type>   res{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2, 99, 5, 954, 2, 1298 };
        std::multiset<val_type> res2{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2,99, 5, 954, 2, 1298 };
        std::multiset<val_type> res3{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 99, 5, 954, 2, 1298 };
        std::vector<val_type>   res4{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 99, 5, 954, 2, 1298 };
        std::vector<val_type>   res5{ 1, 2, 2, 3, 3, 4, 5, 5, 6, 7, 8, 8, 9, 99, 5, 954, 2, 1298 };

        std::cout << "concat : and vector" << std::endl;
        auto n_1 = From(cont).Concat(argVec);
        switch (target) {
            case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     : assert(checkArray(n_1, res4)); break;
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      : assert(checkArray(n_1, res5)); break;
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "concat : and list" << std::endl;
        auto n_2 = From(cont).Concat(argLst);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "concat : and forward_list" << std::endl;
        auto n_3 = From(cont).Concat(argFlst);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "concat : and deque" << std::endl;
        auto n_4 = From(cont).Concat(argDqu);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "concat : and array" << std::endl;
        auto n_5 = From(cont).Concat(argAry);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_5, res)); break;
        }

        std::cout << "concat : and set" << std::endl;
        auto n_6 = From(cont).Concat(argSet);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkMulti(n_6, res2)); break;
        }

        std::cout << "concat : and unordered_set" << std::endl;
        auto n_7 = From(cont).Concat(argUSet);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkMulti(n_7, res2)); break;
        }

        std::cout << "concat : and multiset" << std::endl;
        auto n_8 = From(cont).Concat(argMset);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkMulti(n_8, res2)); break;
        }

        std::cout << "concat : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Concat(argUMset);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkMulti(n_9, res2)); break;
        }

        TContainer empty{};
        std::cout << "concat : empty" << std::endl;
        auto n_A_ = From(empty).Concat(argLst);;
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_A_, { 0,0,0,0,0,0,0,0,0,0,0,0,0,99, 5, 954, 2, 1298 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_A_, { 99, 5, 954, 2, 1298 })); break;
        }
    }

    template <typename TContainer>
    inline void RunTestConcatKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        //std::vector<val_type>   res{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2, 99, 5, 954, 2, 1298 };
        //std::multiset<val_type> res2{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2,99, 5, 954, 2, 1298 };
        //std::multiset<val_type> res3{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 99, 5, 954, 2, 1298 };
        //std::vector<val_type>   res4{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 99, 5, 954, 2, 1298 };
        //std::vector<val_type>   res5{ 1, 2, 2, 3, 3, 4, 5, 5, 6, 7, 8, 8, 9, 99, 5, 954, 2, 1298 };

        std::cout << "concat : and vector" << std::endl;
        auto n_1 = From(cont).Concat(argVec);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "concat : and list" << std::endl;
        auto n_2 = From(cont).Concat(argLst);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "concat : and forward_list" << std::endl;
        auto n_3 = From(cont).Concat(argFlst);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "concat : and deque" << std::endl;
        auto n_4 = From(cont).Concat(argDqu);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "concat : and array" << std::endl;
        auto n_5 = From(cont).Concat(argAry);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "concat : and set" << std::endl;
        auto n_6 = From(cont).Concat(argSet);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "concat : and unordered_set" << std::endl;
        auto n_7 = From(cont).Concat(argUSet);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "concat : and multiset" << std::endl;
        auto n_8 = From(cont).Concat(argMset);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "concat : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Concat(argUMset);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        TContainer empty{};
        std::cout << "concat : empty" << std::endl;
        auto n_A_ = From(empty).Concat(argLst);;
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }
    }
}
