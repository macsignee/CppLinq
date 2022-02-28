#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include "../CppLinq/MacLinq.h"

namespace macsignee
{
    namespace cppLinq
    {
        namespace performance_test
        {
            using namespace std;

            class Checker
            {
                class Stopwatch
                {
                    chrono::time_point<chrono::steady_clock> startTime;
                public:
                    void Start() {
                        startTime = chrono::high_resolution_clock::now();
                    }

                    double Lap() {
                        auto now = chrono::high_resolution_clock::now();
                        return chrono::duration_cast<chrono::milliseconds>(now - startTime).count() / 1000.0;
                    }
                };

                Stopwatch stopwatch;
            public:
                Checker(function<void(void)>action, int times = 1, ostream& stream = std::cout) {
                    stopwatch.Start();
                    for (auto count = 0; count < times; count++)
                        action();
                    stream << stopwatch.Lap() / times << "s." << std::endl;
                }
            };

            // testdata
            struct Data {
                int intData_;
                std::string strData_;
            };
            constexpr int max_count = 1000000;
        }

        namespace container_test
        {
            using namespace macsignee::cppLinq;
         
            enum class container_type
            {
                sequence    =  1,    // vector, list, 
                forward     =  2,    // forward_list
                array       =  3,    // array [c style array]
                unique      =  4,    // set
                multi       =  5,    // multiset
                hash_unique =  6,    // unordered_set
                hash_multi  =  7,    // unordered_multiset

                keyValue    =  8,    // map
                multi_kv    =  9,    // multimap
                hash_kv     = 10,    // unordered_map
                hash_mul_kv = 11,    // unordered_multimap
            };

            template <typename TContainer>
            constexpr bool checkArray(const Enumerable<TContainer>& result, std::vector<typename TContainer::value_type> vec, std::ostream& stream = std::cout) {
                if (vec.size() != result.Count()) return false;
                auto itr = std::begin(result.value);
                auto last = std::end(result.value);
                stream << "container:" << typeid(result.value).name() << std::endl;
                for (size_t idx = 0; itr != last; ++itr, idx++) {
                    if (vec[idx] != *itr) return false;
                }
                stream << "test: passed." << std::endl;
                return true;
            }

            template <typename TContainer, typename TCorrect>
            constexpr bool checkUnique(const Enumerable<TContainer>& result, TCorrect lst, size_t count, std::ostream& stream = std::cout) {
                if (count != result.Count()) return false;
                auto itr = std::begin(result.value);
                auto last = std::end(result.value);
                stream << "container:" << typeid(result.value).name() << std::endl;
                size_t dblcheck = 0;
                for (; itr != last; ++itr) {
                    if (lst.find(*itr) == std::end(lst)) return false;
                    ++dblcheck;
                }
                if (dblcheck != count) return false;
                stream << "test: passed." << std::endl;
                return true;
            }

            template <typename TContainer>
            constexpr bool checkUnique(const Enumerable<TContainer>& result, std::set<typename TContainer::value_type> lst, size_t count, std::ostream& stream = std::cout) {
                return checkUnique<TContainer, std::set<typename TContainer::value_type>>(result, lst, count, stream);
            }

            template <typename TContainer>
            constexpr bool checkUnique(const Enumerable<TContainer>& result, std::multiset<typename TContainer::value_type> lst, size_t count, std::ostream& stream = std::cout) {
                return checkUnique<TContainer, std::multiset<typename TContainer::value_type>>(result, lst, count, stream);
            }

            template <typename TContainer>
            constexpr bool checkUnique(const Enumerable<TContainer>& result, std::initializer_list<typename TContainer::value_type> lst, std::ostream& stream = std::cout) {
                const std::set<typename TContainer::value_type> res{ lst.begin(), lst.end() };
                return checkUnique<TContainer, std::set<typename TContainer::value_type>>(result, res, lst.size(), stream);
            }

            template <typename T>
            constexpr bool checkValue(const T& isWanted, const T& result, std::ostream& stream = std::cout) {
                if (isWanted == result)
                    stream << "test: passed." << std::endl;
                return isWanted == result;
            }

            template <typename TContainer>
            constexpr bool checkUniqueValue(const typename TContainer::value_type& result, std::set<typename TContainer::value_type> lst, std::ostream& stream = std::cout) {
                if (lst.find(result) == std::end(lst)) return false;
                stream << "test: passed." << std::endl;
                return true;
            }

            template <typename TContainer>
            constexpr bool checkUniqueValue(const typename TContainer::value_type& result, std::multiset<typename TContainer::value_type> lst, std::ostream& stream = std::cout) {
                if (lst.find(result) == std::end(lst)) return false;
                stream << "test: passed." << std::endl;
                return true;
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
        }
    }
}
