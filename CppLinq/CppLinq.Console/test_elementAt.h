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
    inline void RunTestElementAt(TContainer& cont, std::string label, container_type target) {
        TContainer empty{};

        using val_type = typename TContainer::value_type;
        {
            std::cout << "ElementAt : condition true" << std::endl;
            auto n_7 = From(cont).ElementAt(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     : assert(checkValue(n_7.value(), 3)); break;
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_7.value(), set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_7.value(), mset_)); break;
            case container_type::sequence   :
            case container_type::array      :
            case container_type::forward    :
            default                         : assert(checkValue(n_7.value(), 1)); break;
            }

            std::cout << "ElementAt : condition true empty" << std::endl;
            auto n_7_ = From(empty).ElementAt(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::array      : assert(checkValue(n_7_.value(), 0)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_7_.has_value()); break;
            }

            std::cout << "ElementAt : condition false" << std::endl;
            auto n_8 = From(cont).ElementAt(34);
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
            default                         : assert(!n_8.has_value()); break;
            }

            std::cout << "ElementAt : condition false empty" << std::endl;
            auto n_8_ = From(empty).ElementAt(10);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::array      : assert(checkValue(n_8_.value(), 0)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_8_.has_value()); break;
            }
        }

        {
            std::cout << "ElementAtOrDefault : condition true" << std::endl;
            auto n_7 = From(cont).ElementAtOrDefault(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     : assert(checkValue(n_7, 3)); break;
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_7, set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_7, mset_)); break;
            case container_type::sequence   :
            case container_type::array      :
            case container_type::forward    :
            default                         : assert(checkValue(n_7, 1)); break;
            }

            std::cout << "ElementAtOrDefault : condition true empty" << std::endl;
            auto n_7_ = From(empty).ElementAtOrDefault(2);
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
            default                         : assert(checkValue(n_7_, val_type())); break;
            }

            std::cout << "ElementAtOrDefault : condition false" << std::endl;
            auto n_8 = From(cont).ElementAtOrDefault(34);
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
            default                         : assert(checkValue(n_8, val_type())); break;
            }

            std::cout << "ElementAtOrDefault : condition false empty" << std::endl;
            auto n_8_ = From(empty).ElementAtOrDefault(10);
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
            default                         : assert(checkValue(n_8_, val_type())); break;
            }
        }
        //auto n_H = From(cont).DefaultIfEmpty();
        //std::for_each(n_H.begin(), n_H.end(), [](auto one) {std::cout << one << std::endl; });
    }

        template <typename TContainer>
    inline void RunTestElementAtKV(TContainer& cont, std::string label, container_type target) {
        TContainer empty{};

        using val_type = typename TContainer::value_type;
        {
            std::cout << "ElementAt : condition true" << std::endl;
            auto n_7 = From(cont).ElementAt(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

            std::cout << "ElementAt : condition true empty" << std::endl;
            auto n_7_ = From(empty).ElementAt(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

            std::cout << "ElementAt : condition false" << std::endl;
            auto n_8 = From(cont).ElementAt(34);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

            std::cout << "ElementAt : condition false empty" << std::endl;
            auto n_8_ = From(empty).ElementAt(10);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        {
            std::cout << "ElementAtOrDefault : condition true" << std::endl;
            auto n_7 = From(cont).ElementAtOrDefault(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

            std::cout << "ElementAtOrDefault : condition true empty" << std::endl;
            auto n_7_ = From(empty).ElementAtOrDefault(2);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

            std::cout << "ElementAtOrDefault : condition false" << std::endl;
            auto n_8 = From(cont).ElementAtOrDefault(34);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

            std::cout << "ElementAtOrDefault : condition false empty" << std::endl;
            auto n_8_ = From(empty).ElementAtOrDefault(10);
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }
        //auto n_H = From(cont).DefaultIfEmpty();
        //std::for_each(n_H.begin(), n_H.end(), [](auto one) {std::cout << one << std::endl; });
    }
}
