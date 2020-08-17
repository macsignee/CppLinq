#pragma once
#include <iostream>
#include "..\CppLinq\MacLinq.h"
//// https://stackoverflow.com/questions/38199641/template-specialization-on-stdvectort

using namespace macsignee::cppLinq;

enum class target
{
    sequence = 1,
    array = 2,
    unique = 3,
    multi = 4
};

template <typename TContainer>
constexpr bool checkArray(const Enumerable<TContainer>& result, std::vector<typename TContainer::value_type> vec) {
    if (vec.size() != result.Count()) return false;
    auto itr = std::begin(result.value);
    auto last = std::end(result.value);
    std::cout << "container:" << typeid(result.value).name() << std::endl;
    for (size_t idx = 0; itr != last; ++itr, idx++) {
        if (vec[idx] != *itr) return false;
    }
    std::cout << "test: passed." << std::endl;
    return true;
}

template <typename TContainer>
constexpr bool checkArray(const Enumerable<TContainer>& result, std::initializer_list<typename TContainer::value_type> lst) {
    std::vector<typename TContainer::value_type>res = { lst.begin(), lst.end() };
    return checkArray(result, res);
}

template <typename TContainer, typename TCorrect>
constexpr bool checkUnique(const Enumerable<TContainer>& result, TCorrect lst, size_t count) {
    if (count != result.Count()) return false;
    auto itr = std::begin(result.value);
    auto last = std::end(result.value);
    std::cout << "container:" << typeid(result.value).name() << std::endl;
    size_t dblcheck = 0;
    for (; itr != last; ++itr) {
        if (lst.find(*itr) == std::end(lst)) return false;
        ++dblcheck;
    }
    if (dblcheck != count) return false;
    std::cout << "test: passed." << std::endl;
    return true;
}

template <typename TContainer>
constexpr bool checkUnique(const Enumerable<TContainer>& result, std::set<typename TContainer::value_type> lst, size_t count) {
    return checkUnique<TContainer, std::set<typename TContainer::value_type>>(result, lst, count);
}

template <typename TContainer>
constexpr bool checkUnique(const Enumerable<TContainer>& result, std::multiset<typename TContainer::value_type> lst, size_t count) {
    return checkUnique<TContainer, std::multiset<typename TContainer::value_type>>(result, lst, count);
}

template <typename TContainer>
constexpr bool checkUnique(const Enumerable<TContainer>& result, std::initializer_list<typename TContainer::value_type> lst) {
    const std::set<typename TContainer::value_type> res{ lst.begin(), lst.end() };
    return checkUnique<TContainer, std::set<typename TContainer::value_type>>(result, res, lst.size());
}

template <typename TContainer>
constexpr bool checkMulti(const Enumerable<TContainer>& result, const std::multiset<typename TContainer::value_type> res) {
    if (res.size() != result.Count()) return false;

    auto itr = std::begin(result.value);
    auto last = std::end(result.value);
    std::cout << "container:" << typeid(result.value).name() << std::endl;
    for (; itr != last; ++itr) {
        if (res.find(*itr) == std::end(res)) return false;
    }
    std::cout << "test: passed." << std::endl;
    return true;
}

template <typename TContainer>
constexpr bool checkMulti(const Enumerable<TContainer>& result, std::initializer_list<typename TContainer::value_type> lst) {
    const std::multiset<typename TContainer::value_type> res{ lst.begin(), lst.end() };
    return checkMulti(result, res);
}

constexpr bool checkNumber(size_t correct, size_t count) {
    if (correct == count)
        std::cout << "test: passed." << std::endl;
    return correct == count;
}

constexpr bool checkBool(bool isWanted, bool result) {
    if (isWanted == result)
        std::cout << "test: passed." << std::endl;
    return isWanted == result;
}

template <typename T>
constexpr bool checkValue(const T& isWanted, const T& result) {
    if (isWanted == result)
        std::cout << "test: passed." << std::endl;
    return isWanted == result;
}

template <typename TContainer>
constexpr bool checkUniqueValue(const typename TContainer::value_type& result, std::set<typename TContainer::value_type> lst) {
    if (lst.find(result) == std::end(lst)) return false;
    std::cout << "test: passed." << std::endl;
    return true;
}

template <typename TContainer>
constexpr bool checkUniqueValue(const typename TContainer::value_type& result, std::multiset<typename TContainer::value_type> lst) {
    if (lst.find(result) == std::end(lst)) return false;
    std::cout << "test: passed." << std::endl;
    return true;
}
#pragma once
