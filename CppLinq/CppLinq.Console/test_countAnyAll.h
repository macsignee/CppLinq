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
    inline void RunTestCount(TContainer& cont, std::string label, container_type target) {
        {
            std::cout << "count :" << std::endl;

            auto n_ = From(cont).Count();
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::unique     :
            case container_type::hash_unique: assert(checkNumber(set_.size(), n_)); break;
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::array      :
            case container_type::forward    :
            default                         : assert(checkNumber(vec_.size(), n_)); break;
            }
        }

        TContainer empty{};
        {
            std::cout << "count : empty" << std::endl;
            auto n_ = From(empty).Count();
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::array      : assert(checkNumber(arraySize, n_)); break;
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::forward    :
            default                         : assert(checkNumber(0, n_)); break;
            }
        }
    }

    template <typename TContainer>
    inline void RunTestAny(TContainer& cont, std::string label, container_type target) {

        TContainer empty{};
        {
            std::cout << "Any : no Condition" << std::endl;
            auto n_A1 = From(cont).Any();
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
            default                         : assert(checkBool(n_A1, true)); break;
            }
        }

        {
            std::cout << "Any : no Condition empty" << std::endl;
            auto n_A1_ = From(empty).Any();
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            case container_type::array      : assert(checkBool(n_A1_, true)); break;
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::forward    :
            default                         : assert(checkBool(n_A1_, false)); break;
            }
        }

        {
            std::cout << "Any : Condition true " << std::endl;
            auto n_A2 = From(cont).Any([](const auto& elm) {return elm == 2; });
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
            default                         : assert(checkBool(n_A2, true)); break;
            }
        }

        {
            std::cout << "Any : Condition true empty" << std::endl;
            auto n_A2_ = From(empty).Any([](const auto& elm) {return elm == 2; });
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
            default                         : assert(checkBool(n_A2_, false)); break;
            }
        }

        {
            std::cout << "Any : Condition false" << std::endl;
            auto n_A3 = From(cont).Any([](const auto& elm) {return elm == 31; });
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
            default                         : assert(checkBool(n_A3, false)); break;
            }
        }
    }

    template <typename TContainer>
    inline void RunTestAll(TContainer& cont, std::string label, container_type target) {

        TContainer empty{};
        {
            std::cout << "All : Condition true " << std::endl;
            auto n_A2 = From(cont).All([](const auto& elm) {return elm > 0; });
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
            default                         : assert(checkBool(n_A2, true)); break;
            }
        }

        {
            std::cout << "All : Condition true empty" << std::endl;
            auto n_A2_ = From(empty).All([](const auto& elm) {return elm > 0; });
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
            default                         : assert(checkBool(n_A2_, false)); break;
            }
        }

        {
            std::cout << "All : Condition false" << std::endl;
            auto n_A3 = From(cont).All([](const auto& elm) {return elm < 0; });
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
            default                         : assert(checkBool(n_A3, false)); break;
            }
        }
    }

    // -- KetValue
    template <typename TContainer>
    inline void RunTestCountKV(TContainer& cont, std::string label, container_type target) {
        {
            std::cout << "count :" << std::endl;

            auto n_ = From(cont).Count();
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        TContainer empty{};
        {
            std::cout << "count : empty" << std::endl;
            auto n_ = From(empty).Count();
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }
    }

    template <typename TContainer>
    inline void RunTestAnyKV(TContainer& cont, std::string label, container_type target) {

        TContainer empty{};
        {
            std::cout << "Any : no Condition" << std::endl;
            auto n_A1 = From(cont).Any();
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        {
            std::cout << "Any : no Condition empty" << std::endl;
            auto n_A1_ = From(empty).Any();
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        {
            std::cout << "Any : Condition true " << std::endl;
            auto n_A2 = From(cont).Any([](const auto& elm) {return elm.first == 2; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }

        }

        {
            std::cout << "Any : Condition true empty" << std::endl;
            auto n_A2_ = From(empty).Any([](const auto& elm) {return elm.first == 2; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        {
            std::cout << "Any : Condition false" << std::endl;
            auto n_A3 = From(cont).Any([](const auto& elm) {return elm.first == 31; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }
    }

    template <typename TContainer>
    inline void RunTestAllKV(TContainer& cont, std::string label, container_type target) {

        TContainer empty{};
        {
            std::cout << "All : Condition true " << std::endl;
            auto n_A2 = From(cont).All([](const auto& elm) {return elm.first > 0; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        {
            std::cout << "All : Condition true empty" << std::endl;
            auto n_A2_ = From(empty).All([](const auto& elm) {return elm.first > 0; });
            switch (target) {
            case container_type::keyValue   :
            case container_type::multi_kv   :
            case container_type::hash_kv    :
            case container_type::hash_mul_kv: assert(false);  break;
            default                         : assert(false);  break;
            }
        }

        {
            std::cout << "All : Condition false" << std::endl;
            auto n_A3 = From(cont).All([](const auto& elm) {return elm.first < 0; });
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