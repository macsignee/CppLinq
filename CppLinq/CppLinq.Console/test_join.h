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
    inline void RunTestJoin(TContainer& cont, std::string label, container_type target) {
        std::vector<std::tuple<int, int>> res{ {2, 99}, {3,5}, {1,954}, {4,2}, {5,1298} };
        std::set<std::tuple<int, int>>   res2{ {2, 99}, {3,5}, {1,954}, {4,2}, {5,1298} };
        auto lmd_st = [](const auto& first, const auto& second) {return std::make_tuple(first, second); };
        std::cout << "join : and vector" << std::endl;
        //{
        //    auto n_1 = From(cont);
        //    switch (target) {
        //        //case target::sequence         :
        //        //case target::array            : 
        //    case container_type::unique:
        //    case container_type::hash_unique: break; // todo
        //    case container_type::multi:
        //    case container_type::hash_multi:  break; // todo
        //    default: assert(checkArray(n_1, res)); break;
        //    }
        //}

        std::cout << "join : and list" << std::endl;
        auto n_2 = From(cont).Zip(argLst, lmd_st);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "join : and forward_list" << std::endl;
        auto n_3 = From(cont).Zip(argFlst, lmd_st);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "join : and deque" << std::endl;
        auto n_4 = From(cont).Zip(argDqu, lmd_st);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "join : and array " << std::endl;
        auto n_5 = From(cont).Zip(argAry, lmd_st);
        switch (target) {
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
        //std::cout << "join : and set" << std::endl;
        //auto n_6 = From(cont).Zip(argSet, lmd_st);
        //assert(checkUnique(n_6, res2));

        //std::cout << "join : and unordered_set" << std::endl;
        //auto n_7 = From(cont).Zip(argUSet, lmd_st);
        //assert(checkUnique(n_7, res2));

        //std::cout << "join : and multiset" << std::endl;
        //auto n_8 = From(cont).Zip(argMset, lmd_st);
        //assert(checkUnique(n_8, res2));

        //std::cout << "join : and unordered_multiset" << std::endl;
        //auto n_9 = From(cont).Zip(argUMset, lmd_st);
        //assert(checkUnique(n_9, res2));

        TContainer empty{};
        std::cout << "join : empty" << std::endl;
        auto n_A_ = From(empty).Zip(argLst, lmd_st);
        switch (target) {
        case container_type::array      : assert(checkArray(n_A_, { {0,99},{0,5},{0,954},{0,2},{0,1298} })); break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_A_, {})); break;
        }
        std::cout << "join " << std::endl;
        {
            auto n_1 = From(cont).Join(
                argVec2,
                [](const auto& inner) {return inner; },
                [](const auto& outer) {return outer; },
                [](const auto& inner, const auto& outer) {return std::make_tuple(inner, outer); }
            );
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : break;
            }
        }
        //assert(checkArray(From(n_1), { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 }));
    }

}
