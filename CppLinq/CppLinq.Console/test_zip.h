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
    inline void RunTestZip(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<std::tuple<val_type, val_type>> res{ {2, 99}, {3, 5}, {1, 954}, {4, 2}, {5, 1298} };
        std::set<std::tuple<val_type, val_type>>    res2{ {2, 99}, {3, 5}, {1, 954}, {4, 2}, {5, 1298} };

        std::cout << "zip : and vector" << std::endl;
        auto n_1 = From(cont).Zip(argVec);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "zip : and list" << std::endl;
        auto n_2 = From(cont).Zip(argLst);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "zip : and forward_list" << std::endl;
        auto n_3 = From(cont).Zip(argFlst);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "zip : and deque" << std::endl;
        auto n_4 = From(cont).Zip(argDqu);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "zip : and array " << std::endl;
        auto n_5 = From(cont).Zip(argAry);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_5, res)); break;
        }

        // todo
        //std::cout << "zip : and set" << std::endl;
        //auto n_6 = From(cont).Zip(argSet);
        //assert(checkUnique(n_6, res2));

        //std::cout << "zip : and unordered_set" << std::endl;
        //auto n_7 = From(cont).Zip(argUSet);
        //assert(checkUnique(n_7, res2));

        //std::cout << "zip : and multiset" << std::endl;
        //auto n_8 = From(cont).Zip(argMset);
        //assert(checkUnique(n_8, res2));

        //std::cout << "zip : and unordered_multiset" << std::endl;
        //auto n_9 = From(cont).Zip(argUMset);
        //assert(checkUnique(n_9, res2));

        TContainer empty{};
        std::cout << "zip : empty" << std::endl;
        {
            auto n_A_ = From(empty).Zip(argLst);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::array      : assert(checkArray(n_A_, { {0, 99},{0, 5},{0, 954},{0, 2},{0, 1298} })); break;
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::forward    :
            default                         : assert(checkArray(n_A_, {})); break;
            }
        }
        std::vector<std::tuple<int, int>> res3{ {2, 99}, {3,5}, {1,954}, {4,2}, {5,1298} };
        std::set<std::tuple<int, int>>   res4{ {2, 99}, {3,5}, {1,954}, {4,2}, {5,1298} };
        auto lmd_st = [](const auto& first, const auto& second) {return std::make_tuple(first, second); };
        std::cout << "zip : and vector" << std::endl;
        {
            auto n_1 = From(cont).Zip(argVec, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_1, res3)); break;
            }
        }

        std::cout << "zip : and list" << std::endl;
        {
            auto n_2 = From(cont).Zip(argLst, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_2, res3)); break;
            }
        }

        std::cout << "zip : and forward_list" << std::endl;
        {
            auto n_3 = From(cont).Zip(argFlst, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_3, res3)); break;
            }
        }
        std::cout << "zip : and deque" << std::endl;
        {
            auto n_4 = From(cont).Zip(argDqu, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_4, res3)); break;
            }
        }

        std::cout << "zip : and array " << std::endl;
        {
            auto n_5 = From(cont).Zip(argAry, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_5, res3)); break;
            }
        }

        // todo
        //std::cout << "zip : and set" << std::endl;
        //auto n_6 = From(cont).Zip(argSet, lmd_st);
        //assert(checkUnique(n_6, res4));

        //std::cout << "zip : and unordered_set" << std::endl;
        //auto n_7 = From(cont).Zip(argUSet, lmd_st);
        //assert(checkUnique(n_7, res4));

        //std::cout << "zip : and multiset" << std::endl;
        //auto n_8 = From(cont).Zip(argMset, lmd_st);
        //assert(checkUnique(n_8, res4));

        //std::cout << "zip : and unordered_multiset" << std::endl;
        //auto n_9 = From(cont).Zip(argUMset, lmd_st);
        //assert(checkUnique(n_9, res4));

        std::cout << "zip : empty" << std::endl;
        auto n_A_ = From(empty).Zip(argLst, lmd_st);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_A_, { {0,99},{0,5},{0,954},{0,2},{0,1298} })); break;
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
    inline void RunTestZipKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<std::tuple<val_type, val_type>> res{ {2, 99}, {3, 5}, {1, 954}, {4, 2}, {5, 1298} };
        std::set<std::tuple<val_type, val_type>>    res2{ {2, 99}, {3, 5}, {1, 954}, {4, 2}, {5, 1298} };

        std::cout << "zip : and vector" << std::endl;
        auto n_1 = From(cont).Zip(argVec);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "zip : and list" << std::endl;
        auto n_2 = From(cont).Zip(argLst);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "zip : and forward_list" << std::endl;
        auto n_3 = From(cont).Zip(argFlst);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "zip : and deque" << std::endl;
        auto n_4 = From(cont).Zip(argDqu);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }


        std::cout << "zip : and array " << std::endl;
        auto n_5 = From(cont).Zip(argAry);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        // todo
        //std::cout << "zip : and set" << std::endl;
        //auto n_6 = From(cont).Zip(argSet);
        //assert(checkUnique(n_6, res2));

        //std::cout << "zip : and unordered_set" << std::endl;
        //auto n_7 = From(cont).Zip(argUSet);
        //assert(checkUnique(n_7, res2));

        //std::cout << "zip : and multiset" << std::endl;
        //auto n_8 = From(cont).Zip(argMset);
        //assert(checkUnique(n_8, res2));

        //std::cout << "zip : and unordered_multiset" << std::endl;
        //auto n_9 = From(cont).Zip(argUMset);
        //assert(checkUnique(n_9, res2));

        TContainer empty{};
        std::cout << "zip : empty" << std::endl;
        {
            auto n_A_ = From(empty).Zip(argLst);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

        }
        std::vector<std::tuple<int, int>> res3{ {2, 99}, {3,5}, {1,954}, {4,2}, {5,1298} };
        std::set<std::tuple<int, int>>   res4{ {2, 99}, {3,5}, {1,954}, {4,2}, {5,1298} };
        auto lmd_st = [](const auto& first, const auto& second) {return std::make_tuple(first, second); };
        std::cout << "zip : and vector" << std::endl;
        {
            auto n_1 = From(cont).Zip(argVec, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

        }

        std::cout << "zip : and list" << std::endl;
        {
            auto n_2 = From(cont).Zip(argLst, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        std::cout << "zip : and forward_list" << std::endl;
        {
            auto n_3 = From(cont).Zip(argFlst, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }
        std::cout << "zip : and deque" << std::endl;
        {
            auto n_4 = From(cont).Zip(argDqu, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

        }

        std::cout << "zip : and array " << std::endl;
        {
            auto n_5 = From(cont).Zip(argAry, lmd_st);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        // todo
        //std::cout << "zip : and set" << std::endl;
        //auto n_6 = From(cont).Zip(argSet, lmd_st);
        //assert(checkUnique(n_6, res4));

        //std::cout << "zip : and unordered_set" << std::endl;
        //auto n_7 = From(cont).Zip(argUSet, lmd_st);
        //assert(checkUnique(n_7, res4));

        //std::cout << "zip : and multiset" << std::endl;
        //auto n_8 = From(cont).Zip(argMset, lmd_st);
        //assert(checkUnique(n_8, res4));

        //std::cout << "zip : and unordered_multiset" << std::endl;
        //auto n_9 = From(cont).Zip(argUMset, lmd_st);
        //assert(checkUnique(n_9, res4));

        std::cout << "zip : empty" << std::endl;
        auto n_A_ = From(empty).Zip(argLst, lmd_st);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

    }
}
