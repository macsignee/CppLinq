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
    inline void RunWhereTest(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        TContainer empty{};
        auto lmb_ev = [](const auto& elm) {return elm % 2 == 0; };

        std::cout << "where " << std::endl;
        {
            auto n_1 = From(cont).Where(lmb_ev);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     : assert(checkArray(n_1, { 2, 4, 6, 8 })); break;
            case container_type::hash_unique: assert(checkUnique(n_1, { 2, 4, 6, 8 })); break;
            case container_type::multi      : assert(checkArray(n_1, { 2, 2, 4, 6, 8, 8 })); break;
            case container_type::hash_multi : assert(checkUnique(n_1, { 2, 2, 4, 6, 8, 8 })); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_1, { 2, 4, 6, 8, 8, 2 })); break;
            }

            auto n_1_ = From(empty).Where(lmb_ev);
            switch (target) {
            case container_type::keyValue   :
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
            default                         : assert(checkArray(n_1_, {}));                            break;
            }
        }

        std::cout << "where with index" << std::endl;
        {
            auto n_2 = From(cont).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     : assert(checkArray(n_2, { 1, 3, 5, 7, 9 })); break;
            case container_type::hash_unique: assert(checkUnique(n_2, { 1, 3, 5, 7, 9 })); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUnique(n_2, { 1, 3, 3, 5, 5, 7, 9 })); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_2, { 3, 1, 5, 9, 7, 5, 3 })); break;
            }
        }

        std::cout << "where with index empty" << std::endl;
        {
            auto n_2_ = From(empty).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
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
            default: assert(checkArray(n_2_, {})); break;
            }
        }

        std::cout << "where " << std::endl;
        {
            auto n_1 = From(cont).Where(lmb_ev);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     : assert(checkArray(n_1, { 2, 4, 6, 8 })); break;
            case container_type::hash_unique: assert(checkUnique(n_1, { 2, 4, 6, 8 })); break;
            case container_type::multi      : assert(checkArray(n_1, { 2, 2, 4, 6, 8, 8 })); break;
            case container_type::hash_multi : assert(checkUnique(n_1, { 2, 2, 4, 6, 8, 8 })); break;
            case container_type::sequence   :
            case container_type::array      :
            default                         : assert(checkArray(n_1, { 2, 4, 6, 8, 8, 2 })); break;
            }
            auto n_1_ = From(empty).Where(lmb_ev);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::array      : assert(checkArray(n_1_, { 0,0,0,0,0,0,0,0,0,0,0,0,0 })); break;
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            default                         : assert(checkArray(n_1_, {}));                            break;
            }
        }

        std::cout << "where with index" << std::endl;
        {
            auto n_2 = From(cont).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     : assert(checkArray(n_2, { 1, 3, 5, 7, 9 })); break;
            case container_type::hash_unique: assert(checkUnique(n_2, { 1, 3, 5, 7, 9 })); break;
            case container_type::multi      : assert(checkArray(n_2, { 1, 3, 3, 5, 5, 7, 9 })); break;
            case container_type::hash_multi : assert(checkUnique(n_2, { 1, 3, 3, 5, 5, 7, 9 })); break;
            case container_type::sequence   :
            case container_type::array      :
            default                         : assert(checkArray(n_2, { 3, 1, 5, 9, 7, 5, 3 })); break;
            }
        }

        std::cout << "where with index empty" << std::endl;
        {
            auto n_2_ = From(empty).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
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
            case container_type::array      :
            default                         : assert(checkArray(n_2_, {})); break;
            }
        }
    }

    template <typename TContainer>
    inline void RunWhereTestKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        TContainer empty{};
        auto lmb_ev = [](const auto& elm) {return elm % 2 == 0; };

        std::cout << "where " << std::endl;
        {
            auto n_1 = From(cont).Where(lmb_ev);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

            auto n_1_ = From(empty).Where(lmb_ev);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        std::cout << "where with index" << std::endl;
        {
            auto n_2 = From(cont).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        std::cout << "where with index empty" << std::endl;
        {
            auto n_2_ = From(empty).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        std::cout << "where " << std::endl;
        {
            auto n_1 = From(cont).Where(lmb_ev);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
            
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        std::cout << "where with index" << std::endl;
        {
            auto n_2 = From(cont).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        std::cout << "where with index empty" << std::endl;
        {
            auto n_2_ = From(empty).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
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