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
//// https://stackoverflow.com/questions/38199641/template-specialization-on-stdvectort

namespace simple_test
{
    using namespace macsignee::cppLinq;
    using namespace macsignee::cppLinq::container_test;

    static constexpr size_t arraySize = 13;
    static const std::vector<int>                     vec_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::list<int>                       list_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::array<int, arraySize>           ary_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::forward_list<int>               flist_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::deque<int>                      deq_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::set<int>                        set_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7 };
    static const std::unordered_set<int>              uset_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7 };
    static const std::multiset<int>                   mset_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::unordered_multiset<int>         umset_ = { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };

    static const std::vector<int>                     argVec = { 99,5,954,2,1298 };
    static const std::list<int>                       argLst = { 99,5,954,2,1298 };
    static const std::forward_list<int>               argFlst = { 99,5,954,2,1298 };
    static const std::deque<int>                      argDqu = { 99,5,954,2,1298 };
    static const std::array<int, 5>                   argAry = { 99,5,954,2,1298 };
    static const std::set<int>                        argSet = { 99,5,954,2,1298 };
    static const std::unordered_set<int>              argUSet = { 99,5,954,2,1298 };
    static const std::multiset<int>                   argMset = { 99,5,954,2,1298 };
    static const std::unordered_multiset<int>         argUMset = { 99,5,954,2,1298 };

    static const std::vector<int>                     argVec2 = { 4,3,1,2,3,4,55 };
    static const std::list<int>                       argLst2 = { 4,3,1,2,3,4,55 };
    static const std::forward_list<int>               argFlst2 = { 4,3,1,2,3,4,55 };
    static const std::deque<int>                      argDqu2 = { 4,3,1,2,3,4,55 };
    static const std::array<int, 7>                   argAry2 = { 4,3,1,2,3,4,55 };
    static const std::set<int>                        argSet2 = { 1,2,3,4,55 };
    static const std::unordered_set<int>              argUSet2 = { 1,2,3,4,55 };
    static const std::multiset<int>                   argMset2 = { 4,3,1,2,3,4,55 };
    static const std::unordered_multiset<int>         argUMset2 = { 4,3,1,2,3,4,55 };

    //static auto lmb_ev = [](const typename TContainer::value_type& lhs, const typename TContainer::value_type& rhs) {return lhs < rhs; };

    static auto lmb_gt = [](const auto& lhs, const auto& rhs) {return lhs < rhs; };
    static auto lmb_lt = [](const auto& lhs, const auto& rhs) {return lhs > rhs; };
    static auto lmb_ev = [](const auto& elm) {return elm % 2 == 0; };
    static auto lmb_rt = [](const auto& elm) {return elm; };

    template <typename TContainer>
    inline void RunWhereTest(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        TContainer empty{};
        std::cout << "where " << std::endl;
        {
            auto n_1 = From(cont).Where(lmb_ev);
            switch (target) {
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
            //case target::sequence         :
            //case target::array            : 
            case container_type::unique     : assert(checkArray(n_1, { 2, 4, 6, 8 })); break;
            case container_type::hash_unique: assert(checkUnique(n_1, { 2, 4, 6, 8 })); break;
            case container_type::multi      : assert(checkArray(n_1, { 2, 2, 4, 6, 8, 8 })); break;
            case container_type::hash_multi : assert(checkUnique(n_1, { 2, 2, 4, 6, 8, 8 })); break;
            default                         : assert(checkArray(n_1, { 2, 4, 6, 8, 8, 2 })); break;
            }
            auto n_1_ = From(empty).Where(lmb_ev);
            switch (target) {
                //case target::sequence :
            case container_type::array: assert(checkArray(n_1_, { 0,0,0,0,0,0,0,0,0,0,0,0,0 })); break;
            case container_type::unique:
            case container_type::hash_unique:
            case container_type::multi:
            case container_type::hash_multi:
            default: assert(checkArray(n_1_, {}));                            break;
            }
        }

        std::cout << "where with index" << std::endl;
        {
            auto n_2 = From(cont).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
            switch (target) {
                //case target::sequence :
                //case target::array  : 
            case container_type::unique: assert(checkArray(n_2, { 1, 3, 5, 7, 9 })); break;
            case container_type::hash_unique: assert(checkUnique(n_2, { 1, 3, 5, 7, 9 })); break;
            case container_type::multi: assert(checkArray(n_2, { 1, 3, 3, 5, 5, 7, 9 })); break;
            case container_type::hash_multi: assert(checkUnique(n_2, { 1, 3, 3, 5, 5, 7, 9 })); break;
            default: assert(checkArray(n_2, { 3, 1, 5, 9, 7, 5, 3 })); break;
            }
        }

        std::cout << "where with index empty" << std::endl;
        {
            auto n_2_ = From(empty).Where([](const auto& elm, size_t index) {return elm % 2 == 1; });
            switch (target) {
                //case target::sequence   :
                //case target::array    : 
            case container_type::unique:
            case container_type::hash_unique:
            case container_type::multi:
            case container_type::hash_multi:
            default: assert(checkArray(n_2_, {})); break;
            }
        }
    }

    template <typename TContainer>
    inline void RunTestOrderBy(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        std::cout << "orderBy " << std::endl;
        auto n_1 = From(cont).OrderBy([](const auto& elm) {return (double)elm; }, [](const auto& lhs, const auto& rhs) {
            return lhs > rhs ? -1 : 1; });
        switch (target) {
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
    inline void RunTestSelect(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        std::cout << "select " << std::endl;
        auto n_1 = From(cont).Select([](const auto& elm) {return std::make_tuple(elm, std::to_string(elm)); });
        switch (target) {
        case container_type::unique     : assert(checkArray(n_1, { {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5,"5"}, {6, "6"}, {7, "7"}, {8, "8"}, {9, "9"} })); break;
        case container_type::hash_unique: assert(checkUnique(n_1, { {2, "2"}, {3, "3"}, {1, "1"}, {4, "4"}, {5,"5"}, {6, "6"}, {9, "9"}, {8, "8"}, {7, "7"} })); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_1, { {2, "2"}, {3, "3"}, {1, "1"}, {4, "4"}, {5,"5"}, {6, "6"}, {9, "9"}, {8, "8"}, {7, "7"}, {5, "5"}, {3,"3"}, {8, "8"}, {2, "2"} })); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default: assert(checkArray(n_1, { {2, "2"}, {3, "3"}, {1, "1"}, {4, "4"}, {5,"5"}, {6, "6"}, {9, "9"}, {8, "8"}, {7, "7"}, {5, "5"}, {3,"3"}, {8, "8"}, {2, "2"} })); break;
        }

        TContainer empty{};
        std::cout << "select empty" << std::endl;
        auto n_1_ = From(empty).Select([](const auto& elm) {return std::make_tuple(elm, std::to_string(elm)); });
        switch (target) {
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
    inline void RunTestSkipTake(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        auto tname = typeid(TContainer).name();
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << label << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;

        std::cout << "skip " << std::endl;
        auto n_1 = From(cont).Skip(2);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkUnique(n_1, set_, 7)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkUnique(n_1, set_, 11)); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_1, { 1,4,5,6,9,8,7, 5, 3, 8, 2 })); break;
        }

        TContainer empty{};
        std::cout << "skip empty" << std::endl;
        auto n_1_ = From(empty).Skip(2);
        switch (target) {
        case container_type::array      : assert(checkArray(n_1_, { 0,0,0,0,0,0,0,0,0,0, 0 })); break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_1_, {})); break;
        }

        std::cout << "Take " << std::endl;
        auto n_2 = From(cont).Take(2);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkUnique(n_2, set_, 2)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkUnique(n_2, set_, 2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_2, { 2,3 })); break;
        }
        std::cout << "Take empty" << std::endl;
        auto n_2_ = From(empty).Take(2);
        switch (target) {
        case container_type::array      : assert(checkArray(n_2_, { 0,0 })); break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_2_, {})); break;
        }
    }

    template <typename TContainer>
    inline void RunTestReverse(TContainer& cont, std::string label, container_type target) {
        std::cout << "reverse :" << std::endl;
        auto n_1 = From(cont).Reverse();
        switch (target) {
        case container_type::unique     : assert(checkArray(n_1, { 9,8,7,6,5,4,3,2,1 })); break;
        case container_type::hash_unique: assert(checkUnique(n_1, { 9,8,7,6,5,4,3,2,1 })); break;
        case container_type::multi      : assert(checkArray(n_1, { 9,8,8,7,6,5,5,4,3,3,2,2,1 })); break;
        case container_type::hash_multi : assert(checkUnique(n_1, { 9,8,8,7,6,5,5,4,3,3,2,2,1 })); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, { 2,8,3,5,7,8,9,6,5,4,1,3,2 })); break;
        }

        TContainer empty{};
        std::cout << "reverse : empty" << std::endl;
        auto n_1_ = From(empty).Reverse();
        switch (target) {
        case container_type::array      : assert(checkArray(n_1_, { 0,0,0,0,0,0,0,0,0,0,0,0,0 })); break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_1_, {})); break;
        }
    }

    template <typename TContainer>
    inline void RunTestDistinct(TContainer& cont, std::string label, container_type target) {
        std::cout << "distinct : no condition" << std::endl;
        auto n_1 = From(cont).Distinct();
        switch (target) {
        case container_type::unique     : assert(checkArray(n_1, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::hash_unique: assert(checkUnique(n_1, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::multi      : assert(checkArray(n_1, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::hash_multi : assert(checkUnique(n_1, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, { 2, 3, 1, 4, 5, 6, 9, 8, 7 })); break;
        }

        std::cout << "distinct : condition" << std::endl;
        auto n_2 = From(cont).Distinct([](const auto& lhs, const auto& rhs) {return lhs == rhs; });
        switch (target) {
        case container_type::unique     : assert(checkArray(n_2, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::hash_unique: assert(checkUnique(n_2, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::multi      : assert(checkArray(n_2, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::hash_multi : assert(checkUnique(n_2, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_2, { 2, 3, 1, 4, 5, 6, 9, 8, 7 })); break;
        }
    }

    template <typename TContainer>
    inline void RunTestCountAnyAll(TContainer& cont, std::string label, container_type target) {
        {
            std::cout << "count :" << std::endl;

            auto n_8 = From(cont).Count();
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: assert(checkNumber(set_.size(), n_8)); break;
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::array      :
            case container_type::forward    :
            default                         : assert(checkNumber(vec_.size(), n_8)); break;
            }
        }

        TContainer empty{};
        {
            std::cout << "count : empty" << std::endl;
            auto n_8_ = From(empty).Count();
            switch (target) {
            case container_type::array      : assert(checkNumber(arraySize, n_8_)); break;
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::forward    :
            default                         : assert(checkNumber(0, n_8_)); break;
            }
        }

        {
            std::cout << "Any : no Condition" << std::endl;
            auto n_A1 = From(cont).Any();
            switch (target) {
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

        {
            std::cout << "All : Condition true " << std::endl;
            auto n_A2 = From(cont).All([](const auto& elm) {return elm > 0; });
            switch (target) {
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
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      : //assert(checkBool(n_A2_, false)); break;
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
    inline void RunTestContains(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::cout << "Contains elm : no condition true " << std::endl;
        auto n_1 = From(cont).Contains(2);
        switch (target) {
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
        //case target::sequence   :
        //case target::array    : 
        case container_type::unique:
        case container_type::hash_unique:
        case container_type::multi:
        case container_type::hash_multi:
        default: assert(checkBool(n_3, true)); break;
        }

        std::cout << "Contains : true empty" << std::endl;
        auto n_3_ = From(empty).Contains(3, [](const auto& source, const auto& elm) {return elm == source; });
        switch (target) {
        //case target::sequence   :
        //case target::array    : 
        case container_type::unique:
        case container_type::hash_unique:
        case container_type::multi:
        case container_type::hash_multi:
        default: assert(checkBool(n_3_, false)); break;
        }

        std::cout << "Contains : false " << std::endl;
        auto n_4 = From(cont).Contains(14, [](const auto& source, const auto& elm) {return elm == source; });
        switch (target) {
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

    template <typename TContainer>
    inline void RunTestElementAt(TContainer& cont, std::string label, container_type target) {
        TContainer empty{};

        using val_type = typename TContainer::value_type;
        {
            std::cout << "ElementAt : condition true" << std::endl;
            auto n_7 = From(cont).ElementAt(2);
            switch (target) {
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
    inline void RunTestConcat(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<val_type>   res{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2, 99, 5, 954, 2, 1298 };
        std::multiset<val_type> res2{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2,99, 5, 954, 2, 1298 };
        std::multiset<val_type> res3{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 99, 5, 954, 2, 1298 };
        std::vector<val_type>   res4{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 99, 5, 954, 2, 1298 };
        std::vector<val_type>   res5{ 1, 2, 2, 3, 3, 4, 5, 5, 6, 7, 8, 8, 9, 99, 5, 954, 2, 1298 };

        std::cout << "concat : and vector" << std::endl;
        auto n_1 = From(cont).Concat(argVec);
        switch (target) {
        case container_type::unique     : assert(checkArray(n_1, res4)); break;
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      : assert(checkArray(n_1, res5)); break;
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "concat : and list" << std::endl;
        auto n_2 = From(cont).Concat(argLst);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "concat : and forward_list" << std::endl;
        auto n_3 = From(cont).Concat(argFlst);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "concat : and deque" << std::endl;
        auto n_4 = From(cont).Concat(argDqu);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "concat : and array" << std::endl;
        auto n_5 = From(cont).Concat(argAry);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_5, res)); break;
        }

        std::cout << "concat : and set" << std::endl;
        auto n_6 = From(cont).Concat(argSet);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkMulti(n_6, res2)); break;
        }

        std::cout << "concat : and unordered_set" << std::endl;
        auto n_7 = From(cont).Concat(argUSet);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkMulti(n_7, res2)); break;
        }

        std::cout << "concat : and multiset" << std::endl;
        auto n_8 = From(cont).Concat(argMset);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkMulti(n_8, res2)); break;
        }

        std::cout << "concat : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Concat(argUMset);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkMulti(n_1, res3)); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkMulti(n_1, res2)); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkMulti(n_9, res2)); break;
        }

        TContainer empty{};
        std::cout << "concat : empty" << std::endl;
        auto n_A_ = From(empty).Concat(argLst);;
        switch (target) {
        case container_type::array      : assert(checkArray(n_A_, { 0,0,0,0,0,0,0,0,0,0,0,0,0,99, 5, 954, 2, 1298 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_A_, { 99, 5, 954, 2, 1298 })); break;
        }
    }

    template <typename TContainer>
    inline void RunTestUnion(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;
        std::vector<val_type> res{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 99, 954, 1298 };
        std::set<val_type> res2{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 99, 954, 1298 };
        std::cout << "union : and vector " << std::endl;
        auto n_0 = From(cont).Union(argVec, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkUnique(n_0, res2, res2.size())); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkUnique(n_0, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_0, res)); break;
        }

        std::cout << "union : and list " << std::endl;
        auto n_1 = From(cont).Union(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_1, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_1, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "union : and forward_list " << std::endl;
        auto n_2 = From(cont).Union(argFlst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_2, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_2, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "union : and deque " << std::endl;
        auto n_3 = From(cont).Union(argDqu, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_3, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_3, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "union : and array " << std::endl;
        auto n_4 = From(cont).Union(argAry, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_4, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_4, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "union : and set" << std::endl;
        auto n_5 = From(cont).Union(argSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::multi      :
        case container_type::hash_multi : assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::array      :
        case container_type::forward    :
        default                         : assert(checkUnique(n_5, res2, res2.size())); break;
        }

        std::cout << "union : and unordered_set" << std::endl;
        auto n_6 = From(cont).Union(argUSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_6, res2, res2.size())); break;
        }

        std::cout << "union : and multiset" << std::endl;
        auto n_7 = From(cont).Union(argMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_7, res2, res2.size())); break;
        }

        std::cout << "union : and unordered_multiset" << std::endl;
        auto n_8 = From(cont).Union(argUMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_8, res2, res2.size())); break;
        }

        TContainer empty{};
        std::cout << "union : empty" << std::endl;
        auto n_9_ = From(empty).Union(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::array      : assert(checkArray(n_9_, { 0, 99, 5, 954, 2, 1298 })); break;
        case container_type::unique     : assert(checkUnique(n_9_, { 99, 5, 954, 2, 1298 })); break;
        case container_type::multi      : assert(checkUnique(n_9_, { 99, 5, 954, 2, 1298 })); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::hash_unique:
        case container_type::hash_multi :
        default                         : assert(checkArray(n_9_, { 99, 5, 954, 2, 1298 })); break;
        }
    }

    template <typename TContainer>
    inline void RunTestIntersect(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<val_type> res{ 5, 2 };
        std::set<val_type>    res2{ 5, 2 };

        std::cout << "intersect : and vector" << std::endl;
        auto n_1 = From(cont).Intersect(argVec, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_1, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "intersect : and list" << std::endl;
        auto n_2 = From(cont).Intersect(argLst, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_2, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "intersect : and forward_list" << std::endl;
        auto n_3 = From(cont).Intersect(argFlst, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_3, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "intersect : and deque" << std::endl;
        auto n_4 = From(cont).Intersect(argDqu, [](const auto& lhs, const auto& rhs) {return lhs < rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_4, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "intersect : and array " << std::endl;
        auto n_5 = From(cont).Intersect(argAry, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_5, res)); break;
        }

        std::cout << "intersect : and set" << std::endl;
        auto n_6 = From(cont).Intersect(argSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_6, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_6, res2, res2.size())); break;
        }

        std::cout << "intersect : and unordered_set" << std::endl;
        auto n_7 = From(cont).Intersect(argUSet, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_7, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_7, res2, res2.size())); break;
        }

        std::cout << "intersect : and multiset" << std::endl;
        auto n_8 = From(cont).Intersect(argMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_8, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_8, res2, res2.size())); break;
        }

        std::cout << "intersect : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Intersect(argUMset, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_9, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkUnique(n_9, res2, res2.size())); break;
        }

        TContainer empty{};
        std::cout << "intersect : empty" << std::endl;
        auto n_A_ = From(empty).Intersect(argLst, [](const auto& lhs, const auto& rhs) {return lhs > rhs; });
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        case container_type::multi      :
        case container_type::hash_multi :
        default                         : assert(checkArray(n_A_, {})); break;
        }
    }

    template <typename TContainer>
    inline void RunTestExcept(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<val_type> res{ 3, 1, 4, 6, 9, 8, 7 };
        std::set<val_type>    res2{ 3, 1, 4, 6, 9, 8, 7 };

        std::cout << "except : and vector" << std::endl;
        auto n_1 = From(cont).Except(argVec, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_1, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_1, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "except : and list" << std::endl;
        auto n_2 = From(cont).Except(argLst, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_2, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_2, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_2, res)); break;
        }

        std::cout << "except : and forward_list" << std::endl;
        auto n_3 = From(cont).Except(argFlst, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_3, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_3, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_3, res)); break;
        }

        std::cout << "except : and deque" << std::endl;
        auto n_4 = From(cont).Except(argDqu, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_4, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_4, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_4, res)); break;
        }

        std::cout << "except : and array " << std::endl;
        auto n_5 = From(cont).Except(argAry, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_5, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_5, res)); break;
        }

        std::cout << "except : and set" << std::endl;
        auto n_6 = From(cont).Except(argSet, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_6, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_6, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkUnique(n_6, res2, res2.size())); break;
        }

        std::cout << "except : and unordered_set" << std::endl;
        auto n_7 = From(cont).Except(argUSet, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_7, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_7, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkUnique(n_7, res2, res2.size())); break;
        }

        std::cout << "except : and multiset" << std::endl;
        auto n_8 = From(cont).Except(argMset, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_8, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_8, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkUnique(n_8, res2, res2.size())); break;
        }

        std::cout << "except : and unordered_multiset" << std::endl;
        auto n_9 = From(cont).Except(argUMset, lmb_gt);
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(n_9, res2, res2.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(n_9, res2, res2.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkUnique(n_9, res2, res2.size())); break;
        }

        TContainer empty{};
        std::cout << "except : empty" << std::endl;
        auto n_A_ = From(empty).Except(argLst, lmb_gt);
        switch (target) {
        case container_type::array      : assert(checkArray(n_A_, { 0 })); break;
        case container_type::unique     :
        case container_type::hash_unique:
        case container_type::multi      :
        case container_type::hash_multi :
        case container_type::sequence   :
        case container_type::forward    :
        default                         : assert(checkArray(n_A_, {})); break;
        }
    }

    template <typename TContainer>
    inline void RunTestZip(TContainer& cont, std::string label, container_type target) {
        using val_type = typename TContainer::value_type;

        std::vector<std::tuple<val_type, val_type>> res{ {2, 99}, {3, 5}, {1, 954}, {4, 2}, {5, 1298} };
        std::set<std::tuple<val_type, val_type>>    res2{ {2, 99}, {3, 5}, {1, 954}, {4, 2}, {5, 1298} };

        std::cout << "zip : and vector" << std::endl;
        auto n_1 = From(cont).Zip(argVec);
        switch (target) {
        case container_type::unique     :
        case container_type::hash_unique: break; // todo
        case container_type::multi      :
        case container_type::hash_multi : break; // todo
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(n_1, res)); break;
        }

        std::cout << "zip : and list" << std::endl;
        auto n_2 = From(cont).Zip(argLst);
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

        std::cout << "zip : and forward_list" << std::endl;
        auto n_3 = From(cont).Zip(argFlst);
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

        std::cout << "zip : and deque" << std::endl;
        auto n_4 = From(cont).Zip(argDqu);
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

        std::cout << "zip : and array " << std::endl;
        auto n_5 = From(cont).Zip(argAry);
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
        //std::cout << "zip : and set" << std::endl;
        //auto n_6 = From(cont).Zip(argSet);
        //assert(checkUnique(n_6, res2));

        //std::cout << "zip : and unordered_set" << std::endl;
        //auto n_7 = From(cont).Zip(argUSet);
        //assert(checkUnique(n_7, res2));

        //std::cout << "zip : and multiset" << std::endl;
        //auto n_8 = From(cont).Zip(argMset);
        //assert(checkUnique(n_8, res2));

        //std::cout << "zip : and unordered_multiset" << std::endl;
        //auto n_9 = From(cont).Zip(argUMset);
        //assert(checkUnique(n_9, res2));

        TContainer empty{};
        std::cout << "zip : empty" << std::endl;
        {
            auto n_A_ = From(empty).Zip(argLst);
            switch (target) {
            case container_type::array      : assert(checkArray(n_A_, { {0, 99},{0, 5},{0, 954},{0, 2},{0, 1298} })); break;
            case container_type::unique     :
            case container_type::hash_unique:
            case container_type::multi      :
            case container_type::hash_multi :
            case container_type::sequence   :
            case container_type::forward    :
            default                         : assert(checkArray(n_A_, {})); break;
            }
        }
        std::vector<std::tuple<int, int>> res3{ {2, 99}, {3,5}, {1,954}, {4,2}, {5,1298} };
        std::set<std::tuple<int, int>>   res4{ {2, 99}, {3,5}, {1,954}, {4,2}, {5,1298} };
        auto lmd_st = [](const auto& first, const auto& second) {return std::make_tuple(first, second); };
        std::cout << "zip : and vector" << std::endl;
        {
            auto n_1 = From(cont).Zip(argVec, lmd_st);
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_1, res3)); break;
            }
        }

        std::cout << "zip : and list" << std::endl;
        {
            auto n_2 = From(cont).Zip(argLst, lmd_st);
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_2, res3)); break;
            }
        }

        std::cout << "zip : and forward_list" << std::endl;
        {
            auto n_3 = From(cont).Zip(argFlst, lmd_st);
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_3, res3)); break;
            }
        }
        std::cout << "zip : and deque" << std::endl;
        {
            auto n_4 = From(cont).Zip(argDqu, lmd_st);
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_4, res3)); break;
            }
        }

        std::cout << "zip : and array " << std::endl;
        {
            auto n_5 = From(cont).Zip(argAry, lmd_st);
            switch (target) {
            case container_type::unique     :
            case container_type::hash_unique: break; // todo
            case container_type::multi      :
            case container_type::hash_multi : break; // todo
            case container_type::sequence   :
            case container_type::forward    :
            case container_type::array      :
            default                         : assert(checkArray(n_5, res3)); break;
            }
        }

        // todo
        //std::cout << "zip : and set" << std::endl;
        //auto n_6 = From(cont).Zip(argSet, lmd_st);
        //assert(checkUnique(n_6, res4));

        //std::cout << "zip : and unordered_set" << std::endl;
        //auto n_7 = From(cont).Zip(argUSet, lmd_st);
        //assert(checkUnique(n_7, res4));

        //std::cout << "zip : and multiset" << std::endl;
        //auto n_8 = From(cont).Zip(argMset, lmd_st);
        //assert(checkUnique(n_8, res4));

        //std::cout << "zip : and unordered_multiset" << std::endl;
        //auto n_9 = From(cont).Zip(argUMset, lmd_st);
        //assert(checkUnique(n_9, res4));

        std::cout << "zip : empty" << std::endl;
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
    }

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

    template <typename TContainer>
    inline void RunTestSequenceEqual(TContainer& cont, std::string label, container_type target) {
#if FALSE
        return; //not impllemented
        std::cout << "sequence all " << std::endl;
        //auto n_1 = From(cont).SequenceEqual(From(deq_));
        switch (target) {
        //case target::sequence   :
        //case target::array    : 
        case container_type::unique:
        case container_type::hash_unique: break; //assert(checkBool(From(cont).SequenceEqual(From(set_)), true)); break;
        case container_type::multi:
        case container_type::hash_multi:  break; //assert(checkBool(From(cont).SequenceEqual(From(mset_)), true)); break;
        default: assert(checkBool(From(cont).SequenceEqual(From(deq_)), true)); break;
        }

        std::cout << "sequence all " << std::endl;
        auto n_2 = From(cont).SequenceEqual(From(set_));
        switch (target) {
        //case target::sequence   :
        //case target::array    : 
        case container_type::hash_unique:
        case container_type::unique: break; //assert(checkBool(From(cont).SequenceEqual(From(deq_)), false)); break;;
        case container_type::hash_multi:
        case container_type::multi: break; //assert(checkBool(From(cont).SequenceEqual(From(deq_)), false)); break;;
        default: assert(checkBool(n_2, false)); break;
        }
#endif
    }

    template <typename TContainer>
    inline void RunTestToCollection(TContainer& cont, std::string label, container_type target) {
        std::cout << "toVector " << std::endl;
        auto n_ZA = From(cont).ToVector();
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(From(n_ZA), set_, set_.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(From(n_ZA), mset_, mset_.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(From(n_ZA), { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 })); break;
        }

        std::cout << "tolist :" << std::endl;
        auto n_ZB = From(cont).ToList();
        switch (target) {
        case container_type::hash_unique:
        case container_type::unique     : assert(checkUnique(From(n_ZB), set_, set_.size())); break;
        case container_type::hash_multi :
        case container_type::multi      : assert(checkUnique(From(n_ZA), mset_, mset_.size())); break;
        case container_type::sequence   :
        case container_type::forward    :
        case container_type::array      :
        default                         : assert(checkArray(From(n_ZB), { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 })); break;
        }
    }

    template <typename TContainer>
    void RunTest(TContainer& cont, std::string label, container_type target) {
        RunWhereTest(cont, label, target);
        RunTestSkipTake(cont, label, target);
        RunTestOrderBy(cont, label, target);
        RunTestSelect(cont, label, target);
        RunTestContains(cont, label, target);
        RunTestCountAnyAll(cont, label, target);
        RunTestFirst(cont, label, target);
        RunTestLast(cont, label, target);
        RunTestElementAt(cont, label, target);
        RunTestReverse(cont, label, target);
        RunTestDistinct(cont, label, target);
        RunTestConcat(cont, label, target);
        RunTestUnion(cont, label, target);
        RunTestIntersect(cont, label, target);
        RunTestExcept(cont, label, target);
        RunTestZip(cont, label, target);
        RunTestJoin(cont, label, target);
        RunTestSequenceEqual(cont, label, target);
        RunTestToCollection(cont, label, target);
    }
}
