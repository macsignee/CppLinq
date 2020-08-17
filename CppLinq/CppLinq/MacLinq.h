#pragma once
//-----------------------------------------------------------------------------------------------
//	Title  : C++ LINQ super early test version
//	Module : LINQ Header
//	Author : Shigene makoto
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <array>
#include <deque>
#include <type_traits>
#include <tuple>
#include <initializer_list>
#if __cplusplus > 201402L
#include<optional>
#endif

namespace macsignee {
    namespace cppLinq {

#pragma region utilities
        //----------------------------------------
        // utilities
        template <class TData>
        inline auto inserter_bk(TData& data) { return  std::back_inserter(data); };

        template <class TData>
        inline auto inserter_fw(TData& data) { return std::inserter(data, std::begin(data)); };

        template<typename TItr>
        inline auto move_itr(TItr itr) { return std::make_move_iterator(itr); }

        template <class TData>
        inline void sort_n(TData& source,
            std::function<bool(const typename TData::value_type&, const typename TData::value_type&)> sorter) {
            std::sort(std::begin(source), std::end(source), sorter);
        }

        template <class TData>
        inline void sort_l(TData& source,
            std::function<bool(const typename TData::value_type&, const typename TData::value_type&)> sorter) {
            source.sort(sorter);
        }
        template<typename T>
        struct val_
        {
            using type = T;
        };
        // for map/mulitmap etc value_type conversion
        template<typename TKey, typename TValue>
        struct val_<std::pair<const TKey, TValue>>
        {
            using type = std::pair<TKey, TValue>;
        };
        template <typename T>
        using val_t = typename val_<T>::type;
#pragma endregion utilities

        //----------------------------------------
        // Enumerable_ operator class
        //----------------------------------------
        template <class TContainer>
        class Enumerable
        {
            //----------------------------------------
            // template specialization
#pragma region template specialization
        //-------------------
        // where
            template <class TSource, typename T>
            static auto copy_filtered_v(TSource&& source, std::function<bool(const T&)>&& predicate) {
                Enumerable<TSource> dest(std::forward<TSource>(source));
                dest.value.reserve(count_impl<TSource>()(source));
                auto last = std::remove_if(std::begin(dest.value), std::end(dest.value), std::not1(predicate));
                //auto itr = std::begin(dest.value);
                 //for (; itr != std::end(dest.value); ) {
                 //    if (!predicate(*itr)) itr = dest.value.erase(itr);
                 //    else ++itr;
                 //}
                dest.value.erase(last, dest.value.end());

                return dest;
            }
            template <class TSource, typename T>
            static auto copy_filtered_bk(TSource&& source, std::function<bool(const T&)>&& predicate) {
                Enumerable<TSource> dest(std::forward<TSource>(source));
                auto last = std::remove_if(std::begin(dest.value), std::end(dest.value), std::not1(predicate));
                dest.value.erase(last, dest.value.end());
                return dest;
            }

            template <class TSource, typename T>
            static auto copy_filtered_sp(TSource&& source, std::function<bool(const T&)>&& predicate) {
                Enumerable<std::vector<T>> dest;
                dest.value.reserve(count_impl<TSource>()(source));
                auto last = std::copy_if(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_bk(dest.value), predicate);
                return dest;
            }

            template <class TSource>
            static auto copy_filtered_fw(TSource&& source, std::function<bool(const typename TSource::value_type&)> predicate) {
                Enumerable<TSource> dest(std::forward<TSource>(source));
                for (auto itr = std::begin(dest.value); itr != std::end(dest.value); ) {
                    if (!predicate(*itr)) itr = dest.value.erase(itr);
                    else ++itr;
                }
                return dest;
            }

            template <class TSource>
            struct where_impl
            {
                auto operator()(TSource&& source, std::function<bool(const typename TSource::value_type&)> predicate) {
                    return copy_filtered_fw<TSource>(std::forward<TSource>(source), predicate);
                }
            };

            template <typename T, typename TAllocator>
            struct where_impl<std::vector<T, TAllocator>>
            {
                using cont_type = typename std::vector<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&)> predicate) {
                    return copy_filtered_v<cont_type, T>(std::forward<cont_type>(source), std::forward<std::function<bool(const T&)>>(predicate));
                }
            };

            template <typename T, typename TAllocator>
            struct where_impl<std::list<T, TAllocator>>
            {
                using cont_type = typename std::list<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&)> predicate) {
                    return copy_filtered_bk<cont_type, T>(std::forward<cont_type>(source), std::forward< std::function<bool(const T&)> >(predicate));

                }
            };

            template <typename T, typename TAllocator>
            struct where_impl<std::deque<T, TAllocator>>
            {
                using cont_type = typename std::deque<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&)> predicate) {
                    return copy_filtered_bk<cont_type, T>(std::forward<cont_type>(source), std::forward<std::function<bool(const T&)>>(predicate));
                }
            };

            template <typename T, typename TAllocator>
            struct where_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&)> predicate) {
                    Enumerable<cont_type> dest(std::forward<cont_type>(source));
                    auto litr = std::begin(dest.value);
                    auto prev = litr;
                    for (; litr != std::end(dest.value); ) {
                        if (predicate(*litr)) { prev = litr; ++litr; }
                        else
                            litr = dest.value.erase_after(prev);
                    }
                    return dest;
                }
            };

            template <typename T, std::size_t N>
            struct where_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(cont_type&& source, std::function<bool(const T&)> predicate) {
                    return copy_filtered_sp<cont_type, T>(std::forward<cont_type>(source), std::forward<std::function<bool(const T&)>>(predicate));
                }
            };

            //-------------------
            // where with index 
            template <class TSource>
            static auto copy_filtered_index(TSource&& source, std::function<bool(const typename TSource::value_type&, std::size_t)> predicate) {
                Enumerable<TSource> dest(std::forward<TSource>(source));
                std::size_t index = 0;
                for (auto itr = std::begin(dest.value); itr != std::end(dest.value); ) {
                    if (predicate(*itr, index)) {
                        ++itr; ++index;
                    }
                    else
                        itr = dest.value.erase(itr);
                }
                return dest;
            }

            template <class TSource, typename T>
            static auto filter_copy_toV_index(TSource&& source, std::size_t size, std::function<bool(const typename TSource::value_type&, std::size_t)> predicate) {
                Enumerable<std::vector<T, std::allocator<T>>> dest;
                dest.value.reserve(size);
                std::size_t index = 0;
                auto itr_ss = move_itr(std::begin(source));
                const auto itr_se = move_itr(std::end(source));
                auto itr_d = inserter_bk(dest.value);
                for (; itr_ss != itr_se; ++itr_ss) {
                    if (predicate(*itr_ss, index)) {
                        *itr_d = *itr_ss;
                        ++itr_d;
                        ++index;
                    }
                }
                dest.value.shrink_to_fit();
                return dest;
            }

            template <class TSource>
            struct where_index_impl
            {
                auto operator()(TSource&& source, std::function<bool(const typename TSource::value_type&, std::size_t)>  predicate) {
                    return copy_filtered_index<TSource>(std::forward<TSource>(source), predicate);
                }
            };

            template <typename T, typename TAllocator>
            struct where_index_impl<std::vector<T, TAllocator>>
            {
                using cont_type = typename std::vector<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const typename T&, std::size_t)> predicate) {
                    return filter_copy_toV_index<cont_type, T>(std::forward<cont_type>(source), std::size(source), predicate);
                }
            };

            template <typename T, typename TAllocator>
            struct where_index_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&, std::size_t)> predicate) {
                    return filter_copy_toV_index<cont_type, T>(std::forward<cont_type>(source), count_impl<cont_type>()(source), predicate);
                }
            };

            template <typename T, std::size_t N>
            struct where_index_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(cont_type&& source, std::function<bool(const T&, std::size_t index)> predicate) {
                    return filter_copy_toV_index<cont_type, T>(std::forward<cont_type>(source), N, predicate);
                }
            };

            //-------------------
            // sort_by
            template <class TSource, typename T>
            static auto copy_sort_to_v(TSource&& source, std::function<bool(const T&, const T&)> sorter) {
                Enumerable<std::vector<T>> dest;
                dest.value.reserve(std::size(source));
                std::copy(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_bk(dest.value));
                sort_n(dest.value, sorter);
                return dest;
            }

            template <class TSource>
            struct sort_by_impl
            {
                using val_type = typename TSource::value_type;
                auto operator()(TSource&& source, std::function<bool(const val_type&, const val_type&)> sorter) {
                    return copy_sort_to_v<TSource, val_t<val_type>>(std::forward<TSource>(source), sorter);
                }
            };

            template <typename T, typename TAllocator>
            struct sort_by_impl<std::deque<T, TAllocator>>
            {
                using cont_type = typename std::deque<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&, const T&)> sorter) {
                    Enumerable<cont_type> dest(std::forward<cont_type>(source));
                    sort_n(dest.value, sorter);
                    return dest;
                }
            };

            template <typename T, typename TAllocator>
            struct sort_by_impl<std::list<T, TAllocator>>
            {
                using cont_type = typename std::list<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&, const T&)> sorter) {
                    Enumerable<cont_type> dest(std::forward<cont_type>(source));
                    sort_l(dest.value, sorter);
                    return dest;
                }
            };

            template <typename T, typename TAllocator>
            struct sort_by_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&, const T&)> sorter) {
                    Enumerable<cont_type> dest(std::forward<cont_type>(source));
                    sort_l(dest.value, sorter);
                    return dest;
                }
            };

            //-------------------
            // order_by
            template <class TSource, typename TGenKey, typename TComparer>
            struct order_by_impl
            {
                using val_type = typename val_t<typename TSource::value_type>;
                auto operator()(TSource&& source, TGenKey&& genKey, TComparer&& comparer) {
                    auto compare_key = [&](const auto& lhs, const auto& rhs) {return comparer(genKey(lhs), genKey(rhs)); };
                    return copy_sort_to_v<TSource, val_t<val_type>>(std::forward<TSource>(source), compare_key);
                }
            };

            template <typename T, typename TAllocator, typename TGenKey, typename TComparer>
            struct order_by_impl<std::deque<T, TAllocator>, TGenKey, TComparer>
            {
                using cont_type = typename std::deque<T, TAllocator>;
                auto operator()(cont_type&& source, TGenKey&& genKey, TComparer&& comparer) {
                    auto compare_key = [&](const auto& lhs, const auto& rhs) {return comparer(genKey(lhs), genKey(rhs)); };
                    Enumerable<cont_type> dest(std::forward<cont_type>(source));
                    sort_n(dest.value, compare_key);
                    return dest;
                }
            };

            template <typename T, typename TAllocator, typename TGenKey, typename TComparer>
            struct order_by_impl<std::list<T, TAllocator>, TGenKey, TComparer>
            {
                using cont_type = typename std::list<T, TAllocator>;
                auto operator()(cont_type&& source, TGenKey&& genKey, TComparer&& comparer) {
                    auto compare_key = [&](const auto& lhs, const auto& rhs) {return comparer(genKey(lhs), genKey(rhs)); };
                    Enumerable<cont_type> dest(std::forward<cont_type>(source));
                    sort_l(dest.value, comparer);
                    return dest;
                }
            };

            template <typename T, typename TAllocator, typename TGenKey, typename TComparer>
            struct order_by_impl<std::forward_list<T, TAllocator>, TGenKey, TComparer>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(cont_type&& source, TGenKey&& genKey, TComparer&& comparer) {
                    auto compare_key = [&](const auto& lhs, const auto& rhs) {return comparer(genKey(lhs), genKey(rhs)); };
                    Enumerable<cont_type> dest(std::forward<cont_type>(source));
                    sort_l(dest.value, comparer);
                    return dest;
                }
            };

            //-------------------
            // select
            template <class TSource, class TDest, typename TFunction>
            static auto transform_copy(TSource&& source, TFunction&& copyer) {
                Enumerable<TDest> dest;
                dest.value.reserve(count_impl<TSource>()(source));
                std::transform(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_bk(dest.value), std::forward<TFunction>(copyer));
                return dest;
            };

            //-------------------
            // skip
            template <typename TSrcItr, class TDest>
            static auto range_copy(TSrcItr itrBegin, TSrcItr itrEnd) {
                Enumerable<TDest> dest;
                dest.value = { move_itr(itrBegin), move_itr(itrEnd) };
                return dest;
            }

            template <class TSource>
            struct skip_impl
            {
                auto operator()(TSource&& source, std::size_t count) {
                    std::size_t data_size = count_impl<TSource>()(source);
                    if (data_size == 0 || count == 0 || data_size < count) return Enumerable<TSource>();
                    return range_copy<TSource::iterator, TSource>(std::next(std::begin(source), count), std::end(source));
                }
            };

            template <typename T, std::size_t N>
            struct skip_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(cont_type&& source, std::size_t count) {
                    if (N == 0 || count == 0 || N < count) return Enumerable<std::vector<T>>();
                    return range_copy<cont_type::iterator, std::vector<T>>(std::next(std::begin(source), count), std::end(source));
                }
            };

            //-------------------
            // take
            template <class TSource>
            struct take_impl
            {
                auto operator()(TSource&& source, std::size_t count) {
                    std::size_t data_size = count_impl<TSource>()(source);
                    if (data_size == 0 || count == 0) return Enumerable<TSource>();
                    return range_copy<TSource::iterator, TSource>(std::begin(source), data_size < count ? std::end(source) : std::next(std::begin(source), count));
                };
            };

            template <typename T, std::size_t N>
            struct take_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(cont_type&& source, std::size_t count) {
                    if (N == 0 || count == 0) return Enumerable<std::vector<T>>();
                    return range_copy<cont_type::iterator, std::vector<T>>(std::begin(source), N < count ? std::end(source) : std::next(std::begin(source), count));
                };
            };

            //-------------------
            // reverse
            template <class TSource>
            static auto copy_reverse(TSource&& source) {
                Enumerable<TSource> dest(std::forward<TSource>(source));
                std::reverse(std::begin(dest.value), std::end(dest.value));
                return dest;
            }

            template <class TData, typename T>
            static auto copy_reverse_to_v(TData&& source) {
                Enumerable<std::vector<T>> dest;
                dest.value.reserve(count_impl<TData>()(source));
                std::copy(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_bk(dest.value));
                std::reverse(dest.value.begin(), dest.value.end());
                return dest;
            }

            template <class TData>
            struct reverse_impl
            {
                auto operator()(TData&& source) {
                    return copy_reverse_to_v<TData, val_t<typename TData::value_type>>(std::forward<TData>(source));
                };
            };

            template <typename T, typename TAllocator>
            struct reverse_impl<std::vector<T, TAllocator>>
            {
                using cont_type = std::vector<T, TAllocator>;
                auto operator()(cont_type&& source) {
                    return copy_reverse<cont_type>(std::forward<cont_type>(source));
                };
            };

            template <typename T, typename TAllocator>
            struct reverse_impl<std::list<T, TAllocator>>
            {
                using cont_type = std::list<T, TAllocator>;
                auto operator()(cont_type&& source) {
                    return copy_reverse<cont_type>(std::forward<cont_type>(source));
                };
            };

            template <typename T, typename TAllocator>
            struct reverse_impl<std::deque<T, TAllocator>>
            {
                using cont_type = std::deque<T, TAllocator>;
                auto operator()(cont_type&& source) {
                    return copy_reverse<cont_type>(std::forward<cont_type>(source));
                };
            };

            template <typename T, std::size_t N>
            struct reverse_impl<std::array<T, N>>
            {
                using cont_type = std::array<T, N>;
                auto operator()(cont_type&& source) {
                    return copy_reverse<cont_type>(std::forward<cont_type>(source));
                };
            };

            template <typename T, typename TAllocator>
            struct reverse_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(cont_type&& source) {
                    Enumerable<cont_type> dest;
                    for (auto itr = move_itr(std::begin<cont_type>(source)); itr != move_itr(std::end(source)); ++itr)
                        dest.value.push_front(*itr);
                    return dest;
                }
            };

            //-------------------
            // distinct
            template <class TSource, class TDest>
            static void copy_distinct(TSource&& source, TDest& dest, std::function<bool(const typename TSource::value_type&, const typename TSource::value_type&)> predicate) {
                std::set<value_type, decltype(predicate)> temp(predicate);
                for (auto elm : source) if (temp.find(elm) == temp.end()) { temp.insert(elm); dest.emplace_back(elm); }
            }

            // distinct
            template <class TSource, class TDest>
            static void copy_distinct_s(TSource&& source, TDest& dest, std::function<bool(const typename TSource::value_type&, const typename TSource::value_type&)> predicate) {
                std::set<value_type, decltype(predicate)> temp(predicate);
                for (auto elm : source) if (temp.find(elm) == temp.end()) { temp.insert(elm); dest.emplace(elm); }
            }

            template <class TSource>
            struct distinct_impl
            {
                using val_type = typename val_t<typename TSource::value_type>;
                auto operator()(TSource&& source, std::function<bool(const val_type&, const val_type&)> predicate) {
                    Enumerable<TContainer> dest;
                    copy_distinct(std::forward<TContainer>(source), dest.value, predicate);
                    return dest;
                }
            };

            template <typename T, typename TAllocator>
            struct distinct_impl<std::deque<T, TAllocator>>
            {
                auto operator()(std::deque<T, TAllocator>&& source, std::function<bool(const T&, const T&)> predicate) {
                    Enumerable<std::deque<T, TAllocator>> dest;
                    copy_distinct(std::forward<std::deque<T, TAllocator>>(source), dest.value, predicate);
                    return dest;
                }
            };

            template <typename T, typename TAllocator>
            struct distinct_impl<std::forward_list<T, TAllocator>>
            {
                auto operator()(std::forward_list<T, TAllocator>&& source, std::function<bool(const T&, const T&)> predicate) {
                    Enumerable<std::forward_list<T, TAllocator>> dest(std::forward<std::forward_list<T, TAllocator>>(source));
                    std::set<T, decltype(predicate)> temp(predicate);
                    auto litr = std::begin(dest.value);
                    auto prev = litr;
                    for (; litr != std::end(dest.value); ) {
                        if (temp.find(*litr) == temp.end()) { temp.insert(*litr); prev = litr; ++litr; }
                        else
                            litr = dest.value.erase_after(prev);
                    }
                    return dest;
                }
            };

            template <typename T, size_t N>
            struct distinct_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(std::array<T, N>&& source, std::function<bool(const T&, const T&)> predicate) {
                    Enumerable<std::vector<T>> dest;
                    dest.value.reserve(N);
                    copy_distinct(std::forward<std::array<T, N>>(source), dest.value, predicate);
                    return dest;
                }
            };

            template <typename T, typename TComperer, typename TAllocator>
            struct distinct_impl<std::multiset<T, TComperer, TAllocator>> {
                using cont_type = typename std::multiset<T, TComperer, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&, const T&)> predicate) {
                    Enumerable<cont_type> dest;
                    copy_distinct_s(std::forward<cont_type>(source), dest.value, predicate);
                    return dest;
                }
            };

            template <typename T, typename THash, typename TComperer, typename TAllocator>
            struct distinct_impl<std::unordered_multiset<T, THash, TComperer, TAllocator>> {
                using cont_type = typename std::unordered_multiset<T, THash, TComperer, TAllocator>;
                auto operator()(cont_type&& source, std::function<bool(const T&, const T&)> predicate) {
                    Enumerable<cont_type> dest;
                    copy_distinct_s(std::forward<cont_type>(source), dest.value, predicate);
                    return dest;
                }
            };

            template <typename TKey, typename TValue, typename TComperer, typename TAllocator>
            struct distinct_impl<std::multimap<TKey, TValue, TComperer, TAllocator>> {
                using cont_type = typename std::map<TKey, TValue, TComperer, TAllocator>;
                using val_type = typename cont_type::value_type;
                auto operator()(cont_type&& source, std::function<bool(const val_t<val_type>&, const val_t<val_type>&)> predicate) {
                    Enumerable<cont_type> dest;
                    copy_distinct_s(std::forward<cont_type>(source), dest.value, predicate);
                    return dest;
                }
            };

            template <typename TKey, typename TValue, typename THash, typename TComperer, typename TAllocator>
            struct distinct_impl<std::unordered_multimap<TKey, TValue, THash, TComperer, TAllocator>> {
                using cont_type = typename std::unordered_map<TKey, TValue, THash, TComperer, TAllocator>;
                using val_type = typename cont_type::value_type;
                auto operator()(cont_type&& source, std::function<bool(const val_t<val_type>&, const val_t<val_type>&)> predicate) {
                    Enumerable<cont_type> dest;
                    copy_distinct_s(cont_type > (source), dest.value, predicate);
                    return dest;
                }
            };

            template <typename T, typename TComperer, typename TAllocator>
            struct distinct_impl<std::set<T, TComperer, TAllocator>> {
                auto operator()(std::set<T, TComperer, TAllocator>&& source, std::function<bool(const T&, const T&)> predicate) {
                    return Enumerable<std::set<T, TComperer, TAllocator>>(std::forward<std::set<T, TComperer, TAllocator>>(source));
                }
            };

            template <typename T, typename THash, typename TComperer, typename TAllocator>
            struct distinct_impl<std::unordered_set<T, THash, TComperer, TAllocator>> {
                auto operator()(std::unordered_set<T, THash, TComperer, TAllocator>&& source, std::function<bool(const T&, const T&)> predicate) {
                    return Enumerable<std::unordered_set<T, THash, TComperer, TAllocator>>(std::forward<std::unordered_set<T, THash, TComperer, TAllocator>>(source));
                }
            };

            template <typename TKey, typename TValue, typename TComperer, typename TAllocator>
            struct distinct_impl<std::map<TKey, TValue, TComperer, TAllocator>> {
                using value_type = typename val_t<typename std::map<TKey, TValue, TComperer, TAllocator>::value_type>;
                auto operator()(std::map<TKey, TValue, TComperer, TAllocator>&& source, std::function<bool(const value_type&, const value_type&)> predicate) {
                    return Enumerable<std::map<TKey, TValue, TComperer, TAllocator>>(std::forward<std::map<TKey, TValue, TComperer, TAllocator>>(source));
                }
            };

            template <typename TKey, typename TValue, typename THash, typename TComperer, typename TAllocator>
            struct distinct_impl<std::unordered_map<TKey, TValue, THash, TComperer, TAllocator>> {
                using value_type = typename val_t<typename std::unordered_map<TKey, TValue, THash, TComperer, TAllocator>::value_type>;
                auto operator()(std::unordered_map<TKey, TValue, THash, TComperer, TAllocator>&& source, std::function<bool(const value_type&, const value_type&)> predicate) {
                    return Enumerable<std::unordered_map<TKey, TValue, THash, TComperer, TAllocator>>(std::forward<std::unordered_map<TKey, TValue, THash, TComperer, TAllocator>>(source));
                }
            };

            //-------------------
            // count
            template <class TData>
            struct count_impl
            {
                std::size_t operator()(const TData& data) const { return data.size(); }
            };

            template <typename T, typename TAllocator>
            struct count_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                std::size_t operator()(const cont_type& data) const {
                    return std::distance(std::cbegin(data), std::cend(data));
                }
            };

            //-------------------
            // last / last_or_default
#if __cplusplus > 201402L
            template <class TData>
            struct last_impl
            {
                auto operator()(const TData& data, std::size_t size) const {
                    std::optional<TData::value_type> dest = size > 0 ? *(--std::end(data)) : std::nullopt;
                    return dest;
                }
            };

            template <typename T, typename TAllocator>
            struct last_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(const cont_type& data, std::size_t size) const {
                    std::optional<T> dest = size > 0 ? *(std::next(std::begin(data), size - 1)) : std::nullopt;
                    return dest;
                }
            };
#else
            template <class TData>
            static auto find_last(const TData& data, std::function<bool(const typename TData::value_type&)> predicate) {
                auto itr = std::find_if(data.crbegin(), data.crend(), predicate);
                return itr != data.crend() ? *itr : value_type();
            }

            template <class TData>
            static auto find_last_forwardly(const TData& data, std::function<bool(const typename TData::value_type&)> predicate) {
                auto find_itr = std::cend(data);
                for (auto itr = std::cbegin(data); itr != std::cend(data); itr++) {
                    if (predicate(*itr)) find_itr = itr;
                }
                return find_itr != std::cend(data) ? *find_itr : typename TData::value_type();
            }

            template <class TData>
            struct last_or_default_impl
            {
                auto operator()(const TData& data, std::size_t size) const {
                    return size > 0 ? *(--std::end(data)) : TData::value_type();
                }
            };

            template <typename T, typename TAllocator>
            struct last_or_default_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(const cont_type& data, std::size_t size) const {
                    return size > 0 ? *(std::next(std::begin(data), size - 1)) : T();
                }
            };

            template <class TData>
            struct last_or_default_func_impl
            {
                auto operator()(const TData& data, std::function<bool(const typename TData::value_type&)> predicate) const {
                    return find_last_forwardly<TData>(data, predicate);
                }
            };

            template <typename T, typename TAllocator>
            struct last_or_default_func_impl<std::vector<T, TAllocator>>
            {
                using cont_type = typename std::vector<T, TAllocator>;
                auto operator()(const cont_type& data, std::function<bool(const typename T&)> predicate) const {
                    return find_last(data, predicate);
                }
            };

            template <typename T, typename TAllocator>
            struct last_or_default_func_impl<std::list<T, TAllocator>>
            {
                using cont_type = typename std::list<T, TAllocator>;
                auto operator()(const cont_type& data, std::function<bool(const typename T&)> predicate) const {
                    return find_last(data, predicate);
                }
            };

            template <typename T, typename TAllocator>
            struct last_or_default_func_impl<std::deque<T, TAllocator>>
            {
                using cont_type = typename std::deque<T, TAllocator>;
                auto operator()(const cont_type& data, std::function<bool(const typename T&)> predicate) const {
                    return find_last(data, predicate);
                }
            };
#endif
            //-------------------
            // to_vector
            template <class TSource>
            struct to_vector_impl
            {
                using val_type = typename TSource::value_type;
                std::vector<val_type> operator()(TSource&& source) {
                    return std::vector<val_type>{move_itr(std::begin(source)), move_itr(std::end(source))};
                }
            };

            template <typename T, typename TAllocator>
            struct to_vector_impl<std::vector<T, TAllocator>>
            {
                std::vector<T, TAllocator> operator()(std::vector<T, TAllocator>&& source) {
                    return source;
                }
            };

            //-------------------
            // to_list
            template <class TSource>
            struct to_list_impl
            {
                using val_type = typename TSource::value_type;
                std::list<val_type> operator()(TSource&& source) {
                    return std::list<val_type>{move_itr(std::begin(source)), move_itr(std::end(source))};
                }
            };

            template <typename T, typename TAllocator>
            struct to_list_impl<std::list<T, TAllocator>>
            {
                std::list<T, TAllocator> operator()(std::list<T, TAllocator>&& source) {
                    return source;
                }
            };
#pragma endregion // template specialization

#pragma region contructors and so
        private:
            //const TContainer* pSource = nullptr;
        public:
            //-------------------------------------
            // attributes
            using value_type = typename TContainer::value_type;
            TContainer value;

            //-------------------------------------
            // ctor / dtor
            Enumerable() = default;
            Enumerable(const Enumerable& con) = default;
            Enumerable(Enumerable&& container) noexcept = default;

            template<typename TElement>
            explicit Enumerable(std::initializer_list<TElement> initialList) :value{ initialList.begin(), initialList.end() } {}
            explicit Enumerable(const TContainer& raw_value) : value{ raw_value } {}
            explicit Enumerable(TContainer&& raw_value) : value{ std::forward<TContainer>(raw_value) } {}
        public:
            ~Enumerable() = default;

            //-------------------------------------
            // operators
            Enumerable& operator=(const Enumerable& container) = default;
            Enumerable& operator=(Enumerable&& container) = default;

            //-------------------------------------
            // iterators
            auto begin() { return std::begin(value); }
            auto end() { return std::end(value); }
            auto cbegin() { return std::cbegin(value); }
            auto cend() { return std::cend(value); }

#pragma endregion
            //-------------------------------------
            // Linq like functions - non constant
            auto Where(std::function<bool(const value_type&)> predicate) {
                auto where = where_impl<std::decay_t<decltype(value)>>();
                return where(std::move(value), predicate);
            }

            auto Where(std::function<bool(const value_type&, std::size_t)> predicate) {
                auto where = where_index_impl<std::decay_t<decltype(value)>>();
                return where(std::move(value), predicate);
            }

            auto SortBy(std::function<bool(const value_type&, const value_type&)> predicate) {
                auto sort_by = sort_by_impl<std::decay_t<decltype(value)>>();
                return sort_by(std::move(value), predicate);
            }

            template <typename TGenKey, typename TComparer>
            auto OrderBy(TGenKey&& genereteKey, TComparer&& comparer) {
                auto order_by = order_by_impl<std::decay_t<decltype(value)>, TGenKey, TComparer>();
                return order_by(std::move(value), std::forward<TGenKey>(genereteKey), std::forward<TComparer>(comparer));
            }

            template <typename TGenKey>
            auto OrderBy(TGenKey&& genereteKey) {
                return OrderBy(std::forward<TGenKey>(genereteKey), std::less<>());
            }

            template <typename TGenKey, typename TComparer>
            auto OrderByDescending(TGenKey&& genereteKey, TComparer&& comparer) {
                auto order_by = order_by_impl<std::decay_t<decltype(value)>, TGenKey, TComparer>();
                return order_by(std::move(value), std::forward<TGenKey>(genereteKey), std::forward<TComparer>(comparer));
            }

            template <typename TGenKey>
            auto OrderByDescending(TGenKey&& genereteKey) {
                return OrderBy(std::forward<TGenKey>(genereteKey), std::greater<>());
            }

            template <typename TGenKey, typename TComparer>
            auto ThenBy(TGenKey&& generateKey, TComparer&& comparer) {
                return OrderBy(generateKey, comparer);
            }

            template <typename TGenKey>
            auto ThenBy(TGenKey&& genereteKey) {
                return OrderBy(std::forward<TGenKey>(genereteKey), std::less<>());
            }

            template <typename TGenKey, typename TComparer>
            auto ThenByDescending(TGenKey&& genereteKey, TComparer&& comparer) {
                return OrderByDescending(genereteKey, comparer);
            }

            template <typename TGenKey>
            auto ThenByDescending(TGenKey&& genereteKey) {
                return OrderByDescending(genereteKey);
            }

            // select
            template <typename TConverter>
            auto Select(TConverter converter) {
                using dest_type = decltype(converter(value_type()));
                return  transform_copy<TContainer, std::vector<dest_type>>
                    (std::move(value), [&](const auto& elm) {return converter(elm); });
            }

            //template <typename TResultElement>
            //auto Select(std::function<TResultElement(const value_type&)> converter) {
            //    return  transform_copy<TContainer, std::vector<TResultElement>>
            //        (std::move(value), [&](const auto& elm) {return converter(elm); });
            //}

            template <typename TResultElement>
            auto Select(std::function<TResultElement(const value_type&, std::size_t index)> converter) {
                Enumerable<std::vector<TResultElement>> result;
                result.value.reserve(Count());
                std::size_t index = 0;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)),
                    [&](const auto& elm) {result.value.emplace_back(converter(elm, index)); index++; });
                return result;
            }

            //SelectMany<TSource, TCollection, TResult>(IEnumerable<TSource>, Func<TSource, IEnumerable<TCollection>>, Func<TSource, TCollection, TResult>)
            //シーケンスの各要素を IEnumerable<T> に射影し、結果のシーケンスを 1 つのシーケンスに平坦化して、その各要素に対して結果のセレクター関数を呼び出します。
            //SelectMany<TSource, TCollection, TResult>(IEnumerable<TSource>, Func<TSource, Int32, IEnumerable<TCollection>>, Func<TSource, TCollection, TResult>)
            //シーケンスの各要素を IEnumerable<T> に射影し、結果のシーケンスを 1 つのシーケンスに平坦化して、その各要素に対して結果のセレクター関数を呼び出します。 各ソース要素のインデックスは、その要素の中間の射影されたフォームで使用されます。
            //SelectMany<TSource, TResult>(IEnumerable<TSource>, Func<TSource, IEnumerable<TResult>>)
            //シーケンスの各要素を IEnumerable<T> に射影し、結果のシーケンスを 1 つのシーケンスに平坦化します。
            //SelectMany<TSource, TResult>(IEnumerable<TSource>, Func<TSource, Int32, IEnumerable<TResult>>)
            //シーケンスの各要素を IEnumerable<T> に射影し、結果のシーケンスを 1 つのシーケンスに平坦化します。 各ソース要素のインデックスは、その要素の射影されたフォームで使用されます。

            auto Skip(std::size_t count) {
                auto skip = skip_impl<std::decay_t<decltype(value)>>();
                return skip(std::move(value), count);
            }

            auto SkipWhile(std::function<bool(value_type)> predicate) {
                Enumerable<TContainer> result;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)), [&](const auto& elm) {
                    if (!predicate(elm)) result.value.emplace_back(elm);
                    });
                return result;
            }

            auto SkipWhile(std::function<bool(value_type, size_t)> predicate) {
                Enumerable<TContainer> result;
                size_t index = 0;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)), [&](const auto& elm) {
                    if (!predicate(elm, index)) result.value.emplace_back(elm);
                    ++index;
                    });
                return result;
            }

            //SkipLast<TSource>(IEnumerable<TSource>, Int32)
            //    source の要素と、省略されたソース コレクションの最後の count 要素を含む、列挙可能な新しいコレクションを返します。

            auto Take(std::size_t count) {
                auto take = take_impl<std::decay_t<decltype(value)>>();
                return take(std::move(value), count);
            }

            auto TakeWhile(std::function<bool(value_type)> predicate) {
                Enumerable<TContainer> result;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)), [&](const auto& elm) {
                    if (predicate(elm))
                        result.value.emplace_back(elm);
                    });
                return result;
            }

            auto TakeWhile(std::function<bool(value_type, size_t)> predicate) {
                Enumerable<TContainer> result;
                size_t index = 0;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)), [&](const auto& elm) {
                    if (predicate(elm, index)) result.value.emplace_back(elm);
                    ++index;
                    });
                return result;
            }
            //TakeLast<TSource>(IEnumerable<TSource>, Int32)
            //    source の最後の count 要素を含む、列挙可能な新しいコレクションを返します。

            //Append<TSource>(IEnumerable<TSource>, TSource)
            //    シーケンスの末尾に値を追加します。
            //Prepend<TSource>(IEnumerable<TSource>, TSource)
            //    シーケンスの先頭に値を追加します。

            //GroupBy<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>)
            //    指定されたキー セレクター関数に従ってシーケンスの要素をグループ化し、指定された関数を使用して各グループの要素を射影します。
            template<typename TKey, typename TValue>
            auto GroupBy(std::function<TKey(const value_type&)> makeKey, std::function<TKey(const value_type&)> makeValue) {
                std::unordered_multimap<TKey, TValue> map;
                //using keyType = decltype(makeKey(const value_type&));
                std::for_each(std::begin(value), std::end(value), [&](const auto& elm) {
                    map.emplace(makeKey(elm), makeValue(elm));
                    });
                return Enumerable<decltype(map)>(map);
            }
            //GroupBy<TSource, TKey, TElement, TResult>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, Func<TKey, IEnumerable<TElement>, TResult>)
            //    指定されたキー セレクター関数に従ってシーケンスの要素をグループ化し、各グループとそのキーから結果値を作成します。 各グループの要素は、指定された関数を使用して射影されます。
            //GroupBy<TSource, TKey, TElement, TResult>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, Func<TKey, IEnumerable<TElement>, TResult>, IEqualityComparer<TKey>)
            //    指定されたキー セレクター関数に従ってシーケンスの要素をグループ化し、各グループとそのキーから結果値を作成します。 キー値の比較には、指定された比較子を使用し、各グループの要素の射影には、指定された関数を使用します。
            //GroupBy<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, IEqualityComparer<TKey>)
            //    キー セレクター関数に従ってシーケンスの要素をグループ化します。 キーの比較には、比較子を使用し、各グループの要素の射影には、指定された関数を使用します。
            //GroupBy<TSource, TKey, TResult>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TKey, IEnumerable<TSource>, TResult>)
            //    指定されたキー セレクター関数に従ってシーケンスの要素をグループ化し、各グループとそのキーから結果値を作成します。
            //GroupBy<TSource, TKey, TResult>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TKey, IEnumerable<TSource>, TResult>, IEqualityComparer<TKey>)
            //    指定されたキー セレクター関数に従ってシーケンスの要素をグループ化し、各グループとそのキーから結果値を作成します。 キーの比較には、指定された比較子を使用します。
            //GroupBy<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>)
            //    指定されたキー セレクター関数に従ってシーケンスの要素をグループ化します。
            //GroupBy<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>, IEqualityComparer<TKey>)
            //    指定されたキー セレクター関数に従ってシーケンスの要素をグループ化し、指定された比較子を使用してキーを比較します。

            auto Reverse() {
                auto reverse = reverse_impl<std::decay_t<decltype(value)>>();
                return reverse(std::move(value));
            }

            // 指定された IEqualityComparer<T> を使用して値を比較することにより、シーケンスから一意の要素を返します。
            auto Distinct(std::function<bool(const value_type&, const value_type&)> predicate = std::less<value_type>()) {
                auto distinct = distinct_impl<std::decay_t<decltype(value)>>();
                return distinct(std::move(value), predicate);
            }

            // below container will be converted to vector if elements collision
            // map, unordered_map, set, unordered_set
            // below container will be converted to vector if container size cannot set
            // array
            // another container will be into vector
            // multimap, unordered_multimap, multiset, unordered_multiset
            template <class TOther>
            auto Concat(const TOther& another) {
                static_assert(std::is_same_v<val_t<value_type>, val_t<TOther::value_type>>, "cannnot concatinate ");
                Enumerable<std::vector<val_t<value_type>>> result;
                result.value.reserve(Count() + count_impl<TOther>()(another));
                std::copy(move_itr(std::begin(value)), move_itr(std::end(value)), inserter_bk(result.value));
                std::copy(move_itr(std::begin(another)), move_itr(std::end(another)), inserter_bk(result.value));

                return result;
            }

            template <class TOther>
            auto Concat(const Enumerable<TOther>& another) {
                return Concat(another.value);
            }

            template <class TOther>
            auto Union(const TOther& another,
                std::function<bool(const value_type&, const value_type&)> predicate = std::less<val_t<value_type>>()) {
                static_assert(std::is_same_v<val_t<value_type>, val_t<TOther::value_type>>, "cannnot union ");
                Enumerable<std::vector<val_t<value_type>>> result;
                result.value.reserve(Count() + count_impl<TOther>()(another));
                std::set<value_type, decltype(predicate)> temp(predicate);
                for (auto elm : value)if (temp.find(elm) == temp.end()) { temp.insert(elm); result.value.emplace_back(elm); }
                for (auto elm : another)if (temp.find(elm) == temp.end()) { temp.insert(elm); result.value.emplace_back(elm); }
                result.value.shrink_to_fit();
                return result;
            }

            template <class TOther>
            auto Union(const Enumerable<TOther>& another, std::function<bool(const value_type&, const value_type&)> predicate = std::less<val_t<value_type>>()) {
                return Union(another.value, predicate);
            }

            template <class TOther>
            auto Intersect(const TOther& another, std::function<bool(const value_type&, const value_type&)> predicate = std::less<value_type>()) {
                static_assert(std::is_same_v<val_t<value_type>, val_t<TOther::value_type>>, "cannnot intersect ");
                Enumerable<std::vector<val_t<value_type>>> result;
                result.value.reserve(Count() + count_impl<TOther>()(another));
                std::set<value_type, decltype(predicate)> temp(predicate);
                for (auto elm : value) if (temp.find(elm) == temp.end()) { temp.insert(elm); }
                for (auto elm : another) if (temp.find(elm) != temp.end()) { result.value.emplace_back(elm); temp.erase(elm); }
                result.value.shrink_to_fit();
                return result;
            }

            template <class TOther>
            auto Interesect(const Enumerable<TOther>& another, std::function<bool(const value_type&, const value_type&)> predicate = std::less<value_type>()) {
                return Interesect(another.value, predicate);
            }

            template <class TOther>
            auto Except(const TOther& another, std::function<bool(const value_type&, const value_type&)> predicate = std::less<value_type>) {
                static_assert(std::is_same_v<val_t<value_type>, val_t<TOther::value_type>>, "cannnot except ");
                Enumerable<std::vector<val_t<value_type>>> result;
                result.value.reserve(Count() + count_impl<TOther>()(another));
                std::set<value_type, decltype(predicate)> temp(predicate);
                for (auto elm : another) temp.insert(elm);
                for (auto elm : value)
                    if (temp.find(elm) == temp.end()) { temp.insert(elm); result.value.emplace_back(elm); }
                result.value.shrink_to_fit();
                return result;
            }

            template <class TOther>
            auto Except(const Enumerable<TOther>& another, std::function<bool(const value_type&, const value_type&)> predicate = std::less<value_type>()) {
                return Except(another.value, predicate);
            }

            template <class TOther>
            auto Zip(const TOther& another) {
                auto itr_f = move_itr(std::begin(value));
                auto itr_s = std::cbegin(another);
                using tup_type = std::tuple<val_t<value_type>, val_<typename TOther::value_type>::type>;
                Enumerable<std::vector<tup_type>> dest;
                dest.value.reserve(Count() < count_impl<TOther>()(another) ? Count() : count_impl<TOther>()(another));
                for (; itr_f != move_itr(std::end(value)) && itr_s != std::cend(another); ++itr_f, ++itr_s) {
                    dest.value.emplace_back(std::make_tuple(*itr_f, *itr_s));
                }
                return dest;
            }

            template <class TOther, typename TZipper>
            auto Zip(const TOther& another, TZipper&& zipper) {
                using dest_type = decltype(zipper(value_type(), typename TOther::value_type()));
                auto itr_f = move_itr(std::begin(value));
                auto itr_s = std::begin(another);
                Enumerable<std::vector<dest_type>> dest;
                dest.value.reserve(Count() < count_impl<TOther>()(another) ? Count() : count_impl<TOther>()(another));
                for (; itr_f != move_itr(std::end(value)) && itr_s != std::end(another); ++itr_f, ++itr_s) {
                    dest.value.emplace_back(zipper(*itr_f, *itr_s));
                }
                return  dest;
            }

            template <class TOther>
            auto Zip(const Enumerable<TOther>& another) {
                return Zip(another.value);
            }

            template <class TOther, typename TZipper>
            auto Zip(const Enumerable<TOther>& another, TZipper&& zipper) {
                return Zip(another.value, zipper);
            }

            template <class TOuter, typename TGetInnerKey, typename TGetOuterKey, typename TJoiner, typename TComparer>
            auto Join(const TOuter& outer, TGetInnerKey&& getInnerKey, TGetOuterKey&& getOuterKey, TJoiner&& joiner, TComparer&& comparer) {
                using dest_type = decltype(joiner(value_type(), typename TOuter::value_type()));
                using key_type = decltype(getInnerKey(value_type()));
                static_assert(std::is_same_v<key_type, decltype(getOuterKey(typename TOuter::value_type()))>, "key type mismatch");

                Enumerable<std::vector<dest_type>> dest;
                dest.value.reserve(Count() + count_impl<TOuter>()(outer));
                std::multimap<key_type, decltype(std::cbegin(outer))> outerKeys(std::forward<TComparer>(comparer));

                auto itr_o = std::cbegin(outer);
                for (; itr_o != std::cend(outer); ++itr_o)
                    outerKeys.insert(std::make_pair(getOuterKey(*itr_o), itr_o));

                for (auto itr_i = std::begin(value); itr_i != std::end(value); ++itr_i) {
                    auto key_range = outerKeys.equal_range(getInnerKey(*itr_i));
                    for (auto mapItr = key_range.first; mapItr != key_range.second; ++mapItr) {
                        dest.value.emplace_back(joiner(*itr_i, *(mapItr->second)));
                    }
                }
                dest.value.shrink_to_fit();
                return  dest;
            }

            template <class TOuter, typename TGetInnerKey, typename TGetOuterKey, typename TJoiner>
            auto Join(const TOuter& outer, TGetInnerKey&& getInnerKey, TGetOuterKey&& getOuterKey, TJoiner&& joiner) {
                return Join(outer, std::forward<TGetInnerKey>(getInnerKey), std::forward<TGetOuterKey>(getOuterKey),
                    std::forward<TJoiner>(joiner), std::less<decltype(getInnerKey(value_type()))>());
            }

            template <class TOuter, typename TGetInnerKey, typename TGetOuterKey, typename TJoiner, typename TComparer>
            auto Join(const Enumerable<TOuter>& outer, TGetInnerKey&& getInnerKey, TGetOuterKey&& getOuterKey, TJoiner&& joiner, TComparer&& comparer) {
                return Join(outer.value, std::forward<TGetInnerKey>(getInnerKey), std::forward<TGetOuterKey>(getOuterKey),
                    std::forward<TJoiner>(joiner), std::forward<TComparer>(comparer));
            }

            template <class TOuter, typename TGetInnerKey, typename TGetOuterKey, typename TJoiner>
            auto Join(const Enumerable<TOuter>& outer, TGetInnerKey&& getInnerKey, TGetOuterKey&& getOuterKey, TJoiner&& joiner) {
                return Join(outer.value, std::forward<TGetInnerKey>(getInnerKey), std::forward<TGetOuterKey>(getOuterKey),
                    std::forward<TJoiner>(joiner));
            }

            //GroupJoin<TOuter, TInner, TKey, TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter, TKey>, Func<TInner, TKey>, Func<TOuter, IEnumerable<TInner>, TResult>)
            //    キーが等しいかどうかに基づいて 2 つのシーケンスの要素を相互に関連付け、その結果をグループ化します。 キーの比較には既定の等値比較子が使用されます。
            //GroupJoin<TOuter, TInner, TKey, TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter, TKey>, Func<TInner, TKey>, Func<TOuter, IEnumerable<TInner>, TResult>, IEqualityComparer<TKey>)
            //    キーが等しいかどうかに基づいて 2 つのシーケンスの要素を相互に関連付け、その結果をグループ化します。 指定された IEqualityComparer<T> を使用してキーを比較します。

#pragma region STL Algorithm Implementations -- NOT IN USE --
#if FALSE
        // STL algorithm implementation all method need sort previously
            auto SortedDistinct(std::function<bool(const value_type&, const value_type&)> predicate = std::less<value_type>()) {
                Enumerable<TContainer> result;
                std::unique_copy(move_itr(std::begin(value)), move_itr(std::end(value)), inserter_fw(result.value), predicate);
                return result;
            }
            template <class TOther>
            auto SortedUnion(const TOther& another, std::function<bool(const value_type&, const value_type&)> predicate) {
                static_assert(std::is_same_v<val_t<value_type>, val_t<TOther::value_type>>, "cannnot union ");
                Enumerable<std::vector<val_t<value_type>>> result;
                std::set_union(move_itr(std::begin(value)), move_itr(std::end(value)), move_itr(std::begin(another)), move_itr(std::end(another)), inserter_bk(result.value), predicate);
                return result;
            }

            template <class TOther>
            auto SortedIntersect(const TOther& another, std::function<bool(const value_type&, const value_type&)> predicate) {
                static_assert(std::is_same_v<val_t<value_type>, val_t<TOther::value_type>>, "cannnot union ");
                Enumerable<std::vector<val_t<value_type>>> result;
                std::set_intersection(move_itr(std::begin(value)), move_itr(std::end(value)), std::begin(another), std::end(another), inserter_bk(result.value), predicate);
                return result;
            }

            template <class TOther>
            auto SortedExcept(const TOther& another, std::function<bool(const value_type&, const value_type&)> predicate) {
                static_assert(std::is_same_v<val_t<value_type>, val_<TOther::value_type>::type>, "cannnot union ");
                Enumerable<std::vector<val_t<value_type>>> result;
                std::set_difference(move_itr(std::begin(value)), move_itr(std::end(value)), std::begin(another), std::end(another), inserter_bk(result.value), predicate);
                return result;
            }
#endif
#pragma endregion 

            auto ToVector() {
                auto to_vector = to_vector_impl<std::decay_t<decltype(value)>>();
                return to_vector(std::move(value));
            }

            auto ToList() {
                auto to_list = to_list_impl<std::decay_t<decltype(value)>>();
                return to_list(std::move(value));
            }
            // ToDictionary<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>)
            //    指定されたキー セレクター関数および要素セレクター関数に従って、Dictionary<TKey, TValue> から IEnumerable<T> を作成します。
            // ToDictionary<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, IEqualityComparer<TKey>)
            //    指定されたキー セレクター関数、比較子、および要素セレクター関数に従って、Dictionary<TKey, TValue> から IEnumerable<T> を作成します。
            // ToDictionary<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>)
            //    指定されたキー セレクター関数に従って、Dictionary<TKey, TValue> から IEnumerable<T> を作成します。
            // ToDictionary<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>, IEqualityComparer<TKey>)
            //    指定されたキー セレクター関数およびキーの比較子に従って、Dictionary<TKey, TValue> から IEnumerable<T> を作成します。
            // ToHashSet<TSource>(IEnumerable<TSource>)
            //    IEnumerable<T> から HashSet<T> を作成します。
            // ToHashSet<TSource>(IEnumerable<TSource>, IEqualityComparer<TSource>)
            //    comparer を使用して IEnumerable<T>から HashSet<T> を作成し、キーを比較します。
            // ToLookup<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>)
            //    指定されたキー セレクター関数および要素セレクター関数に従って、Lookup<TKey, TElement> から IEnumerable<T> を作成します。
            // ToLookup<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, IEqualityComparer<TKey>)
            //    指定されたキー セレクター関数、比較子、および要素セレクター関数に従って、Lookup<TKey, TElement> から IEnumerable<T> を作成します。
            // ToLookup<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>)
            //    指定されたキー セレクター関数に従って、Lookup<TKey, TElement> から IEnumerable<T> を作成します。
            // ToLookup<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>, IEqualityComparer<TKey>)
            //    指定されたキー セレクター関数およびキーの比較子に従って、Lookup<TKey, TElement> から IEnumerable<T> を作成します。


            //-------------------------------------
            // Linq like functions constant
            auto Empty() const {
                return Enumerable<TContainer>();
            }

            auto& ForEach(std::function<void(const value_type&)> predicate) { // データが変わらないので参照で返す
                std::for_each(std::cbegin(value), std::cend(value), predicate);
                return *this;
            }

            bool Contains(const value_type& elm, std::function<bool(const value_type&, const value_type&)> predicate
                = std::equal_to<value_type>()) const {
                if (!Any()) { return false; }
                return std::find_if(std::cbegin(value), std::cend(value),
                    [&](const auto& item) {return predicate(elm, item); }) != std::cend(value);
            }

            std::size_t Count() const {
                auto count = count_impl<std::decay_t<decltype(value)>>();
                return count(value);
            }

            std::size_t Count(std::function<bool(const value_type&)> predicate) const {
                return std::count_if(std::cbegin(value), std::cend(value), predicate);
            }
            // will be not implemented
            //LongCount<TSource>(IEnumerable<TSource>)
            //LongCount<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)

            bool Any() const { return Count() > 0; }

            bool Any(std::function<bool(const value_type&)> predicate) const {
                return find_if(std::cbegin(value), std::cend(value), predicate) != std::cend(value);
            }

            bool All(std::function<bool(const value_type&)> predicate) const {
                return std::all_of(std::cbegin(value), std::cend(value), predicate);
            }

            //SequenceEqual<TSource>(IEnumerable<TSource>, IEnumerable<TSource>)
            //要素の型に対して既定の等値比較子を使用して要素を比較することで、2 つのシーケンスが等しいかどうかを判断します。
            //SequenceEqual<TSource>(IEnumerable<TSource>, IEnumerable<TSource>, IEqualityComparer<TSource>)
            //指定された IEqualityComparer<T> を使用して要素を比較することで、2 つのシーケンスが等しいかどうかを判断します。

#if __cplusplus > 201402L
            auto First() const {
                std::optional<value_type> result = Count() ? *std::cbegin(value) : std::nullopt;
                return result;
            }

            auto First(std::function<bool(const value_type&)> predicate) {
                std::optional<value_type> result = std::nullopt;
                if (Count() == 0) return result;
                auto itr = find_if(std::cbegin(value), std::cend(value), predicate) != std::cend(value);
                result = itr != std::cend(value) ? std::optional<value_type>(*itr) : std::nullopt;
                return result;
            }

            auto Last() const {
                return last(value, Count());
            }

            auto ElementAt(std::size_t index) const {
                if (Count() == 0 || Count() <= index) return std::nullopt;
                return std::optional<value_type>(*std::next(std::cbegin(value), index));
            }

            auto Single() const {
                if (Count() != 1) return std::nullopt;
                return std::optional<value_type>(*std::cbegin(value));
            }

            auto Single(std::function<bool(const value_type&)> predicate) {
                if (Count() == 0) return std::nullopt;
                auto itr = std::find_if(std::cbegin(value), std::cend(value), predicate);
                return itr != std::cend(value) ? std::optional<value_type>(*itr) : std::nullopt;
            }
#endif
            auto FirstOrDefault() const {
                return Count() ? *std::cbegin(value) : value_type();
            }

            auto FirstOrDefault(std::function<bool(const value_type&)> predicate) const {
                if (Count() == 0) return value_type();
                auto itr = std::find_if(std::cbegin(value), std::cend(value), predicate);
                return itr != std::cend(value) ? *itr : value_type();
            }

            auto LastOrDefault() const {
                auto last_or_default = last_or_default_impl<std::decay_t<decltype(value)>>();
                return last_or_default(value, Count());
            }

            auto LastOrDefault(std::function<bool(const value_type&)> predicate) const {
                if (Count() == 0) return value_type();
                auto last_or_default = last_or_default_func_impl<std::decay_t<decltype(value)>>();
                return last_or_default(value, predicate);
            }

            // below SingleOrDefault do not throw InvalidOperationException
            // just return default value
            auto SingleOrDefault() const {
                if (Count() != 1) return value_type();
                return *std::cbegin(value);
            }

            auto SingleOrDefault(std::function<bool(const value_type&)> predicate) const {
                if (Count() == 0)
                    return value_type();
                auto itr = std::find_if(std::cbegin(value), std::cend(value), predicate);
                return itr != std::cend(value) ? *itr : value_type();
            }

            auto ElementAtOrDefault(std::size_t index) const {
                if (Count() == 0 || Count() <= index) return value_type();
                return *std::next(std::cbegin(value), index);
            }

            value_type Aggregate(std::function<value_type(const value_type&, const value_type&)> accumulator) const {
                return std::accumulate(std::cbegin(value), std::cend(value), value_type(), accumulator);
            }

            template <typename TAccumulate>
            TAccumulate Aggregate(TAccumulate seed, std::function<TAccumulate(const TAccumulate&, const value_type&)> accumulater) const {
                TAccumulate result = seed;
                for (auto itr = std::cbegin(value); itr != std::cend(value); ++itr)
                    result = accumulater(result, *itr);
                return result;
            }

            template <typename TAccumulate, typename TSelector>
            auto Aggregate(TAccumulate seed, std::function<TAccumulate(value_type, TAccumulate)> accumulater, TSelector&& selector) const {
                TAccumulate result = seed;
                for (auto itr = std::cbegin(value); itr != std::cend(value); ++itr)
                    result = accumulater(result, *itr);
                return selector(result);
            }

#if FALSE
            auto DefaultIfEmpty() {
                if (Count() == 0) {
                    value.push_back(value_type());
                }
                return this;
            }
            auto DefaultIfEmpty(const value_type& init) {
                if (Count() == 0) {
                    value.push_back(init);
                }
                return this;
            }
#endif
            //-------------------------------------
            // Linq like functions - numeric functions
            auto Min() const {
                return std::accumulate(std::cbegin(value), std::cend(value), value_type(), std::min<value_type>);
            }

            auto Max() const {
                return std::accumulate(std::cbegin(value), std::cend(value), value_type(), std::max<value_type>);
            }

            auto Sum() const {
                return std::accumulate(std::cbegin(value), std::cend(value), value_type());
            }

            auto Average() const {
                return Count() > 0 ? static_cast<value_type>(Sum()) / static_cast<value_type>(Count()) : value_type();
            }

            //---------------------------------
            // will be not implemented
            // Cast<TResult>(IEnumerable)
            // OfType<TResult>(IEnumerable)

            // TContainer not set version
            // below Range not throw "out of range exception"
            static auto Range(int start, int count) {
                if (count <= 0) return Enumerable<std::vector<int>>();
                std::vector<int> vec(count);
                std::iota(std::begin(vec), std::end(vec), start);
                return Enumerable<std::vector<int>>(std::move(vec));
            }

            template <typename T>
            static auto Repeat(const T& init, int times) {
                if (times == 0) return Enumerable<std::vector<T>>();
                std::vector<T> vec(times, init);
                return Enumerable<std::vector<T>>(std::move(vec));
            }
        };

        //----------------------------------------
        // Entry functions
#pragma region entry functions
        template <class TContainer>
        inline auto From() {
            return Enumerable<TContainer>();
        }

        template <class TContainer>
        inline auto From(const TContainer& container) {
            return Enumerable<TContainer>(container);
        }

        template <class TContainer>
        inline auto From(std::initializer_list<typename TContainer::value_type> initialList) {
            return Enumerable<TContainer>(initialList);
        }

#pragma region C-style array implementation
        template <typename T, std::size_t N>
        inline auto From(const T(&array)[N]) {
            Enumerable<std::array<T, N>> result;
            std::copy(std::begin(array), std::end(array), std::begin(result.value));
            return result;
        }

        template <typename T>
        inline auto From(const T* ary_ptr, std::size_t size) {
            Enumerable<std::vector<T>> result;
            result.value.reserve(size);
            if (ary_ptr != nullptr && size > 0)
                std::copy(ary_ptr, ary_ptr + size, std::back_inserter(result.value));
            return result;
        }
#pragma endregion

#pragma region MFC CArray implementation
#if _MSC_VER >= 1600
#ifdef _AFX
        template<typename T, typename TArg>
        const T* cbegin(const CArray<T, TArg>& carray) {
            return (&carray.GetAt(0));
        }

        template<typename T, typename TArg>
        const T* cend(const CArray<T, TArg>& carray) {
            const T* last = &carray.GetAt(carray.GetSize() - 1);
            return (last + 1);
        }

        template <typename T, typename TArg>
        inline auto From(const CArray<T, TArg>& carray) {
            Enumerable<std::vector<T>> result;
            result.value.reserve(carray.GetSize());
            if (carray.GetSize() > 0)
                std::copy(cbegin(carray), cend(carray), std::back_inserter(result.value));
            return result;
        }
#endif
#endif
#pragma endregion 

        inline auto Enumerable_Range(int start, int end) {
            return Enumerable<std::vector<int>>::Range(start, end);
        }

        template <typename T>
        inline auto Enumerable_Repeat(const T& init, int times) {
            return Enumerable<std::vector<T>>::Repeat(init, times);
        }

#pragma endregion  // entry functions
    }// cppLinq
}// macsignee