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
    inline void RunTestSelect(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        std::cout << "select " << std::endl;
        auto n_1 = From(cont).Select([](const auto& elm) {return std::make_tuple(elm, std::to_string(elm)); });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     : assert(checkArray(n_1, { {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5,"5"}, {6, "6"}, {7, "7"}, {8, "8"}, {9, "9"} })); break;
        case container_type::hash_unique: assert(checkUnique(n_1, { {2, "2"}, {3, "3"}, {1, "1"}, {4, "4"}, {5,"5"}, {6, "6"}, {9, "9"}, {8, "8"}, {7, "7"} })); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_1, { {2, "2"}, {3, "3"}, {1, "1"}, {4, "4"}, {5,"5"}, {6, "6"}, {9, "9"}, {8, "8"}, {7, "7"}, {5, "5"}, {3,"3"}, {8, "8"}, {2, "2"} })); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, { {2, "2"}, {3, "3"}, {1, "1"}, {4, "4"}, {5,"5"}, {6, "6"}, {9, "9"}, {8, "8"}, {7, "7"}, {5, "5"}, {3,"3"}, {8, "8"}, {2, "2"} })); break;
        }

        TContainer empty{};
        std::cout << "select empty" << std::endl;
        auto n_1_ = From(empty).Select([](const auto& elm) {return std::make_tuple(elm, std::to_string(elm)); });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_1_, { {0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"},{0, "0"} })); break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_1_, {})); break;
        }

        std::cout << "select with index" << std::endl;
        auto n_2 = From(cont).Select<std::tuple<size_t, val_type>>([](const auto& elm, size_t index) {return std::make_tuple(index, elm); });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique: assert(checkArray(n_2, { {0, 1}, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 8 }, { 8, 9 } })); break;
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_2, { {0, 2}, { 1, 3 }, { 2, 1 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 6, 9 }, { 7, 8 }, { 8, 7 }, {9, 5}, {10,3}, {11, 8}, {12, 2} })); break;
        }

        std::cout << "select with index empty" << std::endl;
        auto n_2_ = From(empty).Select<std::tuple<size_t, val_type>>([](const auto& elm, size_t index) {return std::make_tuple(index, elm); });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::array      : assert(checkArray(n_2_, { {0, 0},{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0} })); break;
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_2_, {})); break;
        }

        std::cout << "foreach " << std::endl;
        size_t cnt = 0;
        From(cont).ForEach([&](const auto& elm) {cnt++; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkNumber(From(cont).Count(), cnt)); break;
        }
    }

    template <typename TContainer>
    inline void RunTestSelectKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        std::cout << "select " << std::endl;
        auto n_1 = From(cont).Select([](const auto& elm) {return std::make_tuple(elm.first, elm.second, std::to_string(elm.second)); });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        TContainer empty{};
        std::cout << "select empty" << std::endl;
        auto n_1_ = From(empty).Select([](const auto& elm) {return std::make_tuple(elm.first, elm.second, std::to_string(elm.second)); });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "select with index" << std::endl;
        auto n_2 = From(cont).Select<std::tuple<size_t, val_type>>([](const auto& elm, size_t index) {return std::make_tuple(index, elm); });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "select with index empty" << std::endl;
        auto n_2_ = From(empty).Select<std::tuple<size_t, val_type>>([](const auto& elm, size_t index) {return std::make_tuple(index, elm); });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "foreach " << std::endl;
        size_t cnt = 0;
        From(cont).ForEach([&](const auto& elm) {cnt++; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }
    }
}
