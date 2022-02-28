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
    inline void RunTestOrderBy(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        auto lmb_rt = [](const auto& elm) {return elm; };
        auto lmb_lt = [](const auto& lhs, const auto& rhs) {return lhs > rhs; };

        std::cout << "orderBy " << std::endl;
        auto n_1 = From(cont).OrderBy([](const auto& elm) {return (double)elm; }, [](const auto& lhs, const auto& rhs) {
            return lhs > rhs ? -1 : 1; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkArray(n_1, { 9,8,7,6,5,4,3,2,1 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_1, { 9,8,8,7,6,5,5,4,3,3,2,2,1 })); break;
        }

        TContainer empty{};
        std::cout << "orderBy Empty" << std::endl;
        auto n_1_ = From(empty).OrderBy([](const auto& elm) {return (double)elm; }, [](const auto& lhs, const auto& rhs) {
            return lhs > rhs; });
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_1_, { 0,0,0,0,0,0,0,0,0,0,0,0,0 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_1_, {})); break;
        }

        std::cout << "orderBy elm" << std::endl;
        auto n_2 = From(cont).OrderBy(lmb_rt);
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkArray(n_2, { 1,2,3,4,5,6,7,8,9 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_2, { 1,2,2,3,3,4,5,5,6,7,8,8,9 })); break;
        }

        std::cout << "orderBy elm empty" << std::endl;
        auto n_2_ = From(empty).OrderBy(lmb_rt);
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_2_, { 0,0,0,0,0,0,0,0,0,0,0,0,0 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_2_, {})); break;
        }
        
        std::cout << "orderByDescending elm" << std::endl;
        auto n_3 = From(cont).OrderByDescending(lmb_rt);
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkArray(n_3, { 9,8,7,6,5,4,3,2,1 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_3, { 9, 8, 8, 7, 6, 5, 5, 4, 3, 3, 2, 2, 1 })); break;
        } 

        std::cout << "orderByDescending elm empty" << std::endl;
        auto n_3_ = From(empty).OrderByDescending(lmb_rt);
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_3_, { 0,0,0,0,0,0,0,0,0,0,0,0,0 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_3_, {})); break;
        }

        std::cout << "thenBy elm" << std::endl;
        auto n_4 = From(cont).ThenBy(lmb_rt);
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkArray(n_4, { 1,2,3,4,5,6,7,8,9 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_4, { 1,2,2,3,3,4,5,5,6,7,8,8,9 })); break;
        }

        std::cout << "thenByDescending elm" << std::endl;
        auto n_5 = From(cont).ThenByDescending(lmb_rt);
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkArray(n_5, { 9,8,7,6,5,4,3,2,1 }));  break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_5, { 9,8,8,7,6,5,5,4,3,3,2,2,1 }));  break;
        }

        std::cout << "sortBy " << std::endl;
        auto n_6 = From(cont).SortBy(lmb_lt);
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: assert(checkArray(n_6, { 9,8,7,6,5,4,3,2,1 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_6, { 9,8,8,7,6,5,5,4,3,3,2,2,1 })); break;
        }

        std::cout << "sortBy empty" << std::endl;
        auto n_6_ = From(empty).SortBy(lmb_lt);
        switch (target) {
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_6_, { 0,0,0,0,0,0,0,0,0,0,0,0,0 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_6_, {})); break;
        }
    }

    template <typename TContainer>
    inline void RunTestOrderByKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        auto lmb_rt = [](const auto& elm) {return elm; };
        auto lmb_lt = [](const auto& lhs, const auto& rhs) {return lhs.first < rhs.first; };

        std::cout << "orderBy " << std::endl;
        auto n_1 = From(cont).OrderBy(
            [&](const auto& elm) {return (double)elm.second; },
            [&](const auto& lhs, const auto& rhs) { return lhs > rhs ? -1 : 1; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        //TContainer empty{};
        //std::cout << "orderBy Empty" << std::endl;
        //auto n_1_ = From(empty).OrderBy([](const auto& elm) {return (double)elm.second; }, [](const auto& lhs, const auto& rhs) {
        //    return lhs > rhs ? -1 : 1; });
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}

        //std::cout << "orderBy elm" << std::endl;
        //auto n_2 = From(cont).OrderBy(lmb_rt);
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}

        //std::cout << "orderBy elm empty" << std::endl;
        //auto n_2_ = From(empty).OrderBy(lmb_rt);
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}
        //
        //std::cout << "orderByDescending elm" << std::endl;
        //auto n_3 = From(cont).OrderByDescending(lmb_rt);
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}


        //std::cout << "orderByDescending elm empty" << std::endl;
        //auto n_3_ = From(empty).OrderByDescending(lmb_rt);
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}

        //std::cout << "thenBy elm" << std::endl;
        //auto n_4 = From(cont).ThenBy(lmb_rt);
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}

        //std::cout << "thenByDescending elm" << std::endl;
        //auto n_5 = From(cont).ThenByDescending(lmb_rt);
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}

        //std::cout << "sortBy " << std::endl;
        //auto n_6 = From(cont).SortBy(lmb_lt);
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}

        //std::cout << "sortBy empty" << std::endl;
        //auto n_6_ = From(empty).SortBy(lmb_lt);
        //switch (target) {
        //case container_type::keyValue   :
        //case container_type::multi_kv   :
        //case container_type::hash_kv    :
        //case container_type::hash_mul_kv: assert(false);  break;
        //default                         : assert(false);  break;
        //}
    }
}