#pragma once
#include <iostream>
//#include "../CppLinq/MacLinq.h"
//using namespace macsignee::cppLinq;
//
//namespace CppLinqTest
//{
//    template <typename TContainer>
//    constexpr bool checkArray(const Enumerable<TContainer>& result, std::vector<typename TContainer::value_type> vec, std::ostream& stream = std::cout) {
//        if (vec.size() != result.Count()) return false;
//        auto itr = std::begin(result.value);
//        auto last = std::end(result.value);
//        stream << "container:" << typeid(result.value).name() << std::endl;
//        for (size_t idx = 0; itr != last; ++itr, idx++) {
//            if (vec[idx] != *itr) return false;
//        }
//        stream << "test: passed." << std::endl;
//        return true;
//    }
//
//    template <typename TContainer>
//    constexpr bool checkArray(const Enumerable<TContainer>& result, std::initializer_list<typename TContainer::value_type> lst, std::ostream& stream = std::cout) {
//        std::vector<typename TContainer::value_type>res = { lst.begin(), lst.end() };
//        return checkArray<std::vector<typename TContainer::value_type>, TElm, Traits>(result, res, stream);
//    }
//
//    template <typename TContainer, typename TCorrect>
//    constexpr bool checkUnique(const Enumerable<TContainer>& result, TCorrect lst, size_t count, std::ostream& stream = std::cout) {
//        if (count != result.Count()) return false;
//        auto itr = std::begin(result.value);
//        auto last = std::end(result.value);
//        stream << "container:" << typeid(result.value).name() << std::endl;
//        size_t dblcheck = 0;
//        for (; itr != last; ++itr) {
//            if (lst.find(*itr) == std::end(lst)) return false;
//            ++dblcheck;
//        }
//        if (dblcheck != count) return false;
//        stream << "test: passed." << std::endl;
//        return true;
//    }
//
//    template <typename TContainer>
//    constexpr bool checkUnique(const Enumerable<TContainer>& result, std::set<typename TContainer::value_type> lst, size_t count, std::ostream& stream = std::cout) {
//        return checkUnique<TContainer, std::set<typename TContainer::value_type>, TElm, Traits>(result, lst, count, stream);
//    }
//
//    template <typename TContainer>
//    constexpr bool checkUnique(const Enumerable<TContainer>& result, std::multiset<typename TContainer::value_type> lst, size_t count, std::ostream& stream = std::cout) {
//        return checkUnique<TContainer, std::multiset<typename TContainer::value_type>, TElm, Traits>(result, lst, count, stream);
//    }
//
//    template <typename TContainer>
//    constexpr bool checkUnique(const Enumerable<TContainer>& result, std::initializer_list<typename TContainer::value_type> lst, std::ostream& stream = std::cout) {
//        const std::set<typename TContainer::value_type> res{ lst.begin(), lst.end() };
//        return checkUnique<TContainer, std::set<typename TContainer::value_type>>(result, res, lst.size(), stream);
//    }
//
//    template <typename T>
//    constexpr bool checkValue(const T& isWanted, const T& result, std::ostream& stream = std::cout) {
//        if (isWanted == result)
//            stream << "test: passed." << std::endl;
//        return isWanted == result;
//    }
//
//    template <typename TContainer>
//    constexpr bool checkUniqueValue(const typename TContainer::value_type& result, std::set<typename TContainer::value_type> lst, std::ostream& stream = std::cout) {
//        if (lst.find(result) == std::end(lst)) return false;
//        stream << "test: passed." << std::endl;
//        return true;
//    }
//
//    template <typename TContainer>
//    constexpr bool checkUniqueValue(const typename TContainer::value_type& result, std::multiset<typename TContainer::value_type> lst, std::ostream& stream = std::cout) {
//        if (lst.find(result) == std::end(lst)) return false;
//        stream << "test: passed." << std::endl;
//        return true;
//    }
//}
