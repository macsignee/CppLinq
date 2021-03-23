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
    inline void RunTestFirst(TContainer& cont, std::string label, container_type target) {
        TContainer empty{};

        using val_type = typename TContainer::value_type;
        {
            std::cout << "First : no condition" << std::endl;
            auto n_1 = From(cont).First();
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_1.value(), *std::begin(cont))); break;
            }

            std::cout << "First : no condition empty" << std::endl;
            auto n_0_ = From(empty).First();
            switch (target) {
            case container_type::array      : assert(n_0_.value() == 0); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_0_.has_value()); break;
            }

            std::cout << "First : condition true" << std::endl;
            auto n_2 = From(cont).First([](const auto& elm) {return elm == 5; });
            switch (target) {
            case container_type::unique     : assert(checkValue(n_2.value(), *std::next(std::cbegin(cont), 4))); break;
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_2.value(), set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_2.value(), mset_)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkValue(n_2.value(), *std::next(std::cbegin(cont), 4))); break;
            }

            std::cout << "First : condition true empty" << std::endl;
            auto n_2_ = From(empty).First([](const auto& elm) {return elm == 5; });
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

            std::cout << "First : condition false" << std::endl;
            auto n_3 = From(cont).First([](const auto& elm) {return elm == 65; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_3.has_value()); break;
            }

            std::cout << "First : condition false empty" << std::endl;
            auto n_3_ = From(empty).First([](const auto& elm) {return elm == 65; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_3_.has_value()); break;
            }
        }

        {
            std::cout << "FirstOrDefault : no condition" << std::endl;
            auto n_1 = From(cont).FirstOrDefault();
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_1, *std::begin(cont))); break;
            }

            std::cout << "FirstOrDefault : no condition empty" << std::endl;
            auto n_1_ = From(empty).FirstOrDefault();
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_1_, val_type())); break;
            }

            std::cout << "FirstOrDefault : condition true" << std::endl;
            auto n_2 = From(cont).FirstOrDefault([](const auto& elm) {return elm == 5; });
            switch (target) {
            case container_type::unique     : assert(checkValue(n_2, *std::next(std::cbegin(cont), 4))); break;
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_2, set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_2, mset_)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkValue(n_2, *std::next(std::cbegin(cont), 4))); break;
            }

            std::cout << "FirstOrDefault : condition true empty" << std::endl;
            auto n_2_ = From(empty).FirstOrDefault([](const auto& elm) {return elm == 5; });
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

            std::cout << "FirstOrDefault : condition false" << std::endl;
            auto n_3 = From(cont).FirstOrDefault([](const auto& elm) {return elm == 65; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_3, val_type())); break;
            }

            std::cout << "FirstOrDefault : condition false empty" << std::endl;
            auto n_3_ = From(empty).FirstOrDefault([](const auto& elm) {return elm == 65; });
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

        template <typename TContainer>
    inline void RunTestFirstKV(TContainer& cont, std::string label, container_type target) {
        TContainer empty{};

        using val_type = typename TContainer::value_type;
        {
            std::cout << "First : no condition" << std::endl;
            auto n_1 = From(cont).First();
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_1.value(), *std::begin(cont))); break;
            }

            std::cout << "First : no condition empty" << std::endl;
            auto n_0_ = From(empty).First();
            switch (target) {
            case container_type::array      : assert(n_0_.value() == 0); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_0_.has_value()); break;
            }

            std::cout << "First : condition true" << std::endl;
            auto n_2 = From(cont).First([](const auto& elm) {return elm == 5; });
            switch (target) {
            case container_type::unique     : assert(checkValue(n_2.value(), *std::next(std::cbegin(cont), 4))); break;
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_2.value(), set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_2.value(), mset_)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkValue(n_2.value(), *std::next(std::cbegin(cont), 4))); break;
            }

            std::cout << "First : condition true empty" << std::endl;
            auto n_2_ = From(empty).First([](const auto& elm) {return elm == 5; });
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

            std::cout << "First : condition false" << std::endl;
            auto n_3 = From(cont).First([](const auto& elm) {return elm == 65; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_3.has_value()); break;
            }

            std::cout << "First : condition false empty" << std::endl;
            auto n_3_ = From(empty).First([](const auto& elm) {return elm == 65; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(!n_3_.has_value()); break;
            }
        }

        {
            std::cout << "FirstOrDefault : no condition" << std::endl;
            auto n_1 = From(cont).FirstOrDefault();
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_1, *std::begin(cont))); break;
            }

            std::cout << "FirstOrDefault : no condition empty" << std::endl;
            auto n_1_ = From(empty).FirstOrDefault();
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_1_, val_type())); break;
            }

            std::cout << "FirstOrDefault : condition true" << std::endl;
            auto n_2 = From(cont).FirstOrDefault([](const auto& elm) {return elm == 5; });
            switch (target) {
            case container_type::unique     : assert(checkValue(n_2, *std::next(std::cbegin(cont), 4))); break;
            case container_type::hash_unique: assert(checkUniqueValue<TContainer>(n_2, set_)); break;
            case container_type::multi      :
            case container_type::hash_multi : assert(checkUniqueValue<TContainer>(n_2, mset_)); break;
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkValue(n_2, *std::next(std::cbegin(cont), 4))); break;
            }

            std::cout << "FirstOrDefault : condition true empty" << std::endl;
            auto n_2_ = From(empty).FirstOrDefault([](const auto& elm) {return elm == 5; });
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

            std::cout << "FirstOrDefault : condition false" << std::endl;
            auto n_3 = From(cont).FirstOrDefault([](const auto& elm) {return elm == 65; });
            switch (target) {
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            default                         : assert(checkValue(n_3, val_type())); break;
            }

            std::cout << "FirstOrDefault : condition false empty" << std::endl;
            auto n_3_ = From(empty).FirstOrDefault([](const auto& elm) {return elm == 65; });
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
