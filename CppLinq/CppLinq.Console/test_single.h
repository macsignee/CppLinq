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
    inline void RunTestSingle(TContainer& cont, std::string label, container_type target) {
        TContainer empty{};

        using val_type = typename TContainer::value_type;
        TContainer single { val_type() };
        {
            std::cout << "Single : no condition false any " << std::endl;
            auto n_1 = From(cont).Single();
            switch (target) {
            case container_type::unique     : 
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::array      :
            case container_type::forward    :
            default                         : assert(!n_1.has_value()); break;
            }

            std::cout << "Single : no condition false empty" << std::endl;
            auto n_2 = From(empty).Single();
            switch (target) {
            case container_type::array      :
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_2.has_value()); break;
            }

            std::cout << "Single : condition true" << std::endl;
            auto n_3 = From(single).Single();
            switch (target) {
            case container_type::array      : assert(!n_3.has_value()); break;  // how 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_3.value(), val_type())); break;
            }

            std::cout << "Single : condition false empty" << std::endl;
            auto n_4 = From(empty).Single([](const auto& elm) {return elm == 3; });
            switch (target) {
            case container_type::array      : 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_4.has_value()); break;
            }

            std::cout << "Single : condition true" << std::endl;
            auto n_5 = From(cont).Single([](const auto& elm) {return elm == 7; });
            switch (target) {
            case container_type::array      : 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_5.value(), 7)); break;
            }


            std::cout << "Single : condition true none" << std::endl;
            auto n_6 = From(empty).Single([](const auto& elm) {return elm == 99; });
            switch (target) {
            case container_type::array      : 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_6.has_value()); break;
            }

            std::cout << "Single : condition true any" << std::endl;
            auto n_7 = From(cont).Single([](const auto& elm) {return elm == 3; });
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: assert(checkValue(n_7.value(), 3)); break;
            case container_type::array      : 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_7.has_value()); break;
            }
        }

        {
            std::cout << "SingleOrDefault : no condition false any " << std::endl;
            auto n_1 = From(cont).SingleOrDefault();
            switch (target) {
            case container_type::unique     : 
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::array      :
            case container_type::forward    :
            default                         : assert(checkValue(n_1, val_type())); break;
            }

            std::cout << "SingleOrDefault : no condition false empty" << std::endl;
            auto n_2 = From(empty).SingleOrDefault();
            switch (target) {
            case container_type::array      :
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_2, val_type())); break;
            }

            std::cout << "SingleOrDefault : condition true" << std::endl;
            auto n_3 = From(single).SingleOrDefault();
            switch (target) {
            case container_type::array      : assert(checkValue(n_3, val_type())); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_3, val_type())); break;
            }

            std::cout << "SingleOrDefault : condition false empty" << std::endl;
            auto n_4 = From(empty).SingleOrDefault([](const auto& elm) {return elm == 3; });
            switch (target) {
            case container_type::array      : 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_4, val_type())); break;
            }

            std::cout << "SingleOrDefault : condition true" << std::endl;
            auto n_5 = From(cont).SingleOrDefault([](const auto& elm) {return elm == 7; });
            switch (target) {
            case container_type::array      : 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_5, 7)); break;
            }

            std::cout << "SingleOrDefault : condition true none" << std::endl;
            auto n_6 = From(empty).SingleOrDefault([](const auto& elm) {return elm == 99; });
            switch (target) {
            case container_type::array      : 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_6, val_type())); break;
            }

            std::cout << "SingleOrDefault : condition true any" << std::endl;
            auto n_7 = From(cont).SingleOrDefault([](const auto& elm) {return elm == 3; });
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: assert(checkValue(n_7, 3)); break;
            case container_type::array      : 
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_7, val_type())); break;
            }
        }
    }
}
