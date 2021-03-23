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
    inline void RunTestLast(TContainer& cont, std::string label, container_type target) {
        TContainer empty{};

        using val_type = typename TContainer::value_type;
        {
            std::cout << "Last : no condition" << std::endl;
            auto n_1 = From(cont).Last();
            switch (target) {
            case container_type::hash_unique:
            case container_type::hash_multi : assert(checkValue(n_1.value(), 7)); break;
            case container_type::unique     :
            case container_type::multi      : assert(checkValue(n_1.value(), 9)); break;
            case container_type::forward    : 
            case container_type::sequence   :
            case container_type::array      :
            default                         : assert(checkValue(n_1.value(), 2)); break;
            }

            std::cout << "Last : no condition empty" << std::endl;
            auto n_2 = From(empty).Last();
            switch (target) {
            case container_type::array      : assert(n_2.value() == 0); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_2.has_value()); break;
            }

            std::cout << "Last : condition true" << std::endl;
            auto n_5 = From(cont).Last([](const auto& elm) {return elm == 3; });
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_5.value(), set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_5.value(), mset_)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkValue(n_5.value(), *std::next(std::begin(cont), 1))); break;
            }

            std::cout << "Last : condition true empty" << std::endl;
            auto n_2_ = From(empty).Last([](const auto& elm) {return elm == 3; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_2_.has_value()); break;
            }

            std::cout << "Last : condition false" << std::endl;
            auto n_6 = From(cont).Last([](const auto& elm) {return elm == -1; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_6.has_value()); break;
            }

            std::cout << "Last : condition false empty" << std::endl;
            auto n_3_ = From(empty).Last([](const auto& elm) {return elm == 65; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         :  assert(!n_3_.has_value()); break;
            }
        }

        {
            std::cout << "LastOrDefault : no condition" << std::endl;
            auto n_1 = From(cont).LastOrDefault();
            switch (target) {
            case container_type::unique     : assert(checkValue(n_1, 9)); break;
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_1, set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_1, mset_)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkValue(n_1, 2)); break;
            }

            std::cout << "LastOrDefault : no condition empty" << std::endl;
            auto n_2 = From(empty).LastOrDefault();
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_2, val_type())); break;
            }

            std::cout << "LastOrDefault : condition true" << std::endl;
            auto n_5 = From(cont).LastOrDefault([](const auto& elm) {return elm == 3; });
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_5, set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_5, mset_)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkValue(n_5, *std::next(std::begin(cont), 1))); break;
            }

            std::cout << "LastOrDefault : condition true empty" << std::endl;
            auto n_2_ = From(empty).LastOrDefault([](const auto& elm) {return elm == 3; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_2_, val_type())); break;
            }


            std::cout << "LastOrDefault : condition false" << std::endl;
            auto n_6 = From(cont).LastOrDefault([](const auto& elm) {return elm == -1; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_6, val_type())); break;
            }

            std::cout << "LastOrDefault : condition false empty" << std::endl;
            auto n_3_ = From(empty).LastOrDefault([](const auto& elm) {return elm == 65; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_3_, val_type())); break;
            }
        }
    }
}
