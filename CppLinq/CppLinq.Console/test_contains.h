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
    inline void RunTestContains(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::cout << "Contains elm : no condition true " << std::endl;
        auto n_1 = From(cont).Contains(2);
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
        default                         : assert(checkBool(n_1, true)); break;
        }

        TContainer empty{};
        std::cout << "Contains elm : no condition true empty" << std::endl;
        auto n_1_ = From(empty).Contains(2);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkBool(n_1_, false)); break;
        }

        std::cout << "Contains elm : no condition false " << std::endl;
        auto n_2 = From(cont).Contains(99);
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
        default                         : assert(checkBool(n_2, false)); break;
        }

        std::cout << "Contains elm : no condition false empty" << std::endl;
        auto n_2_ = From(empty).Contains(99);
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
        default                         : assert(checkBool(n_2_, false)); break;
        }

        std::cout << "Contains : true " << std::endl;
        auto n_3 = From(cont).Contains(3, [](const auto& source, const auto& elm) {return elm == source; });
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
        default                         : assert(checkBool(n_3, true)); break;
        }

        std::cout << "Contains : true empty" << std::endl;
        auto n_3_ = From(empty).Contains(3, [](const auto& source, const auto& elm) {return elm == source; });
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
        default                         : assert(checkBool(n_3_, false)); break;
        }

        std::cout << "Contains : false " << std::endl;
        auto n_4 = From(cont).Contains(14, [](const auto& source, const auto& elm) {return elm == source; });
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
        default                         : assert(checkBool(n_4, false)); break;
        }

        std::cout << "Contains : false empty" << std::endl;
        auto n_4_ = From(cont).Contains(14, [](const auto& source, const auto& elm) {return elm == source; });
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
        default                         : assert(checkBool(n_4_, false)); break;
        }
    }

        template <typename TContainer>
    inline void RunTestContainsKV(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::cout << "Contains elm : no condition true " << std::endl;
        auto n_1 = From(cont).Contains(2);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        TContainer empty{};
        std::cout << "Contains elm : no condition true empty" << std::endl;
        auto n_1_ = From(empty).Contains(2);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "Contains elm : no condition false " << std::endl;
        auto n_2 = From(cont).Contains(99);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "Contains elm : no condition false empty" << std::endl;
        auto n_2_ = From(empty).Contains(99);
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "Contains : true " << std::endl;
        auto n_3 = From(cont).Contains(3, [](const auto& source, const auto& elm) {return elm == source; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "Contains : true empty" << std::endl;
        auto n_3_ = From(empty).Contains(3, [](const auto& source, const auto& elm) {return elm == source; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "Contains : false " << std::endl;
        auto n_4 = From(cont).Contains(14, [](const auto& source, const auto& elm) {return elm == source; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }

        std::cout << "Contains : false empty" << std::endl;
        auto n_4_ = From(cont).Contains(14, [](const auto& source, const auto& elm) {return elm == source; });
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        default                         : assert(false);  break;
        }
    }
}
