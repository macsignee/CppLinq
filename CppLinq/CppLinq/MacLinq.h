#pragma once
//-----------------------------------------------------------------------------------------------
//	Title  : C++ LINQ super early test version
//	Module : LINQ Header
//	Author : Shigene makoto
#include <algorithm>
#include <numeric>
#include <functional>
#include <type_traits>
#include <utility>
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
#include <tuple>
#include <initializer_list>
#include <memory> 
#include <string>
#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L) && (_MSC_VER >= 1913))
#define maclinq_cpp17 1
#include<optional>
#else
#define maclinq_cpp17 0
#endif
#include <cassert>

namespace macsignee {
    namespace cppLinq {

        template<typename T>
        struct val_impl {
            using type = T;
        };
        // for map/mulitmap etc value_type conversion
        template<typename TKey, typename TValue>
        struct val_impl<std::pair<const TKey, TValue> > {
            using type = std::pair<TKey, TValue>;
        };

        template <typename T>
        using value_t = typename val_impl<T>::type;

#if maclinq_cpp17
        template <typename T>
        using nullable_t = std::optional<T>;
#else
        template <typename T>
        struct nullopt_t {};

        template <typename T>
        static constexpr nullopt_t<T> nullopt{  };
#pragma region optional compatible class
        template <typename T>
        struct nullable_t
        {
        private:
            std::unique_ptr<T> value_;
        public:
            explicit nullable_t() {}
            /*explicit */nullable_t(const T& val) : value_(std::make_unique<T>(val)) {}
            /*explicit*/ nullable_t(const nullable_t<T>& source){
                if (source.value_)
                    value_ = std::make_unique<T>(*source.value_);
            }
            explicit nullable_t(T&& val) noexcept                 : value_(std::make_unique<T>(val)) {}
            explicit nullable_t(nullable_t<T>&& source)  noexcept : value_(std::move(source.value_)) {}

            auto& operator=(std::nullptr_t)&              { value_.reset();                      return *this; }
            auto& operator=(nullopt_t<T>)&                { value_.reset();                      return *this; }
            auto& operator=(const T& source)&             { value_ = std::make_unique<T>(source); return *this; }
            auto& operator=(const nullable_t<T>& source)& { if (source.value_){value_ = std::make_unique<T>(*source.value_);} return *this; }
            auto& operator=(T&& source)&&             noexcept { value_ = std::move(source.value_);  return *this;}
            auto& operator=(nullable_t<T>&& source)&& noexcept { value_ = std::move(source);         return *this;}
 
            const auto&  operator*() const& { return *value_; }
                  auto&  operator*()&       { return *value_; }
            const auto&& operator*() const&&{ return std::move(value_); }
                  auto&& operator*()&&      { return std::move(value_); }

            const auto&  value() const&     { return operator*(); }
                  auto&  value()&           { return operator*(); }
            const auto&& value() const&&    { return operator*(); }
                  auto&& value()&&          { return operator*(); }

            explicit operator T() const { return value(); }

            bool has_value() const { return (bool)value_; }
        };
        template <typename T, typename U>
        constexpr bool operator==(const nullable_t<T>& x, const nullable_t<U>& y) { return x.has_value() == y.has_value() && x.value() == y.value(); }
        template <typename T>
        constexpr bool operator==(const nullable_t<T>& x, nullopt_t<T>) noexcept  { return !x.has_value(); }
        template <typename T>
        constexpr bool operator==(nullopt_t<T>, const nullable_t<T>& y) noexcept  { return operator==(y, nullopt_t); }
        template <typename T, typename U>
        constexpr bool operator==(const nullable_t<T>& x, const U& y)             { return x.has_value() && y == x.value(); }
        template <typename T, typename U>
        constexpr bool operator==(const U& x, const nullable_t<T>& y)             { return operator==(y, x); }
        template <typename T, typename U>
        constexpr bool operator!=(const nullable_t<T>& x, const nullable_t<U>& y) { return !operator==(x, y); }
        template <typename T>
        constexpr bool operator!=(const nullable_t<T>& x, nullopt_t<T>) noexcept  { return !operator==(x, nullopt_t); }
        template <typename T>
        constexpr bool operator!=(nullopt_t<T>, const nullable_t<T>& y) noexcept  { return !operator==(nullopt_t, y); }
        template <typename T, typename U>
        constexpr bool operator!=(const nullable_t<T>& x, const U& y)             { return !operator==(x, y); }
        template <typename T, typename U>
        constexpr bool operator!=(const U& x, const nullable_t<T>& y)             { return !operator==(x, y); }
#pragma endregion
#endif
        //----------------------------------------
        // Enumerable_ operator class
        //----------------------------------------
        template <class TContainer>
        class Enumerable
        {
       private:
            template <typename T>   // Func<TSource,Boolean> function type
            using pred_fn_type     = std::function<bool(const T&)>;
            template <typename T>   // Func<TSource,Int32,Boolean> function type
            using pred_idx_fn_type = std::function<bool(const T&, std::size_t)>;
            template <typename T>   // IEqualityComparer.Equals function type(Func<TSource,TSource,Boolean>)
            using ieq_comp_fn_type = std::function<bool(const T&, const T&)>;
            template <typename T>   // IComparer.Compare function type(Func<TSource,TSource,Int32>)
            using icomp_fn_type    = std::function<int(const T&, const T&)>;
            template <typename T>   // less than comparer(std::less) function type : IComparer.Compare(...) < 0 = true
            using less_fn_type     = std::function<bool(const T&, const T&)>;

        public:
            //-------------------------------------
            // attributes
            using value_type = typename TContainer::value_type;
            TContainer value;
        private:
            //----------------------------------------
            // utilities
            template<typename TItr>
            static inline auto move_itr(TItr itr) { return std::make_move_iterator(itr); }

            template <typename T>
            struct has_itr {
                using dummy_type = int;
            private:
                template <typename U> static auto test(dummy_type) -> decltype(std::begin(std::declval<U>()), std::true_type());
                template <typename U> static auto test(...) -> decltype(std::false_type());
            public:
                static constexpr bool value = decltype(test<T>(0))::value || std::is_array<T>::value;
            };

            template <typename T>
            struct has_push_back {
            private:
                template <typename U, int = (&U::push_back, 0)>
                static std::true_type test(U*);
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test((T*)nullptr))::value;
            };

            template <typename T>
            struct has_push_front {
            private:
                template <typename U, int = (&U::push_front, 0)>
                static std::true_type test(U*);
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test((T*)nullptr))::value;
            };

            template <typename T>
            struct has_emplace_back {
            private:
                template <typename U, int = (&U::emplace_back, 0)>
                static std::true_type test(U*);
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test((T*)nullptr))::value;
            };

            template <typename T>
            struct has_emplace {
            private:
                template <typename U, int = (&U::emplace, 0)>
                static std::true_type test(U*);
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test((T*)nullptr))::value;
            };

            template <typename T>
            struct has_insert {
            private:
                template <typename U, int = (&U::insert, 0)>
                static std::true_type test(U*);
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test((T*)nullptr))::value;
            };

            template <typename TData, std::enable_if_t<has_push_back<TData>::value, bool> = true>
            static inline auto inserter_(TData& data) { return  std::back_inserter(data); };
            template <typename TData, std::enable_if_t<!has_push_back<TData>::value && has_insert<TData>::value && has_itr<TData>::value, bool> = true>
            static inline auto inserter_(TData& data) { return  std::inserter(data, std::begin(data)); };

            template <typename T>
            struct has_reserve {
            private:
                template <typename U, int = (&U::reserve, 0)>
                static std::true_type test(U*);
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test((T*)nullptr))::value;
            };

            template <typename TData, std::enable_if_t<has_reserve<TData>::value, bool> = true>
            static inline auto reserve_(TData& container, size_t size) {
                if (size > 0) container.reserve(size);
            }

            template <typename TData, std::enable_if_t<!has_reserve<TData>::value, bool> = true>
            static inline auto reserve_(TData& container, size_t size) {
                //container.reserve(size);
            }

            template <typename T>
            struct EqualityComparer
            {
            private:
                //using val_type = value_t<T>;
                using val_type = T;
                ieq_comp_fn_type<val_type> comparer;
                std::unordered_set<val_type> work{};
            public:
                enum then{
                    do_nothing = 0,
                    add_if_not_found = 1,
                    remeove_if_found = 2
                };
                EqualityComparer(ieq_comp_fn_type<val_type>&& cmp) : comparer(std::forward<ieq_comp_fn_type<val_type>>(cmp)) {}

                bool equals(T& value, then action = do_nothing) {
                    auto first = std::begin(work);
                    auto last = std::end(work);
                    for (; first != last; ++first)
                        if (comparer(*first, value)) {
                            if (action == remeove_if_found)
                                work.erase(value);
                            return true;
                        }
                    if (action == add_if_not_found)
                        work.insert(value);
                    return false; 
                }
            };
#pragma region contructors and so
        public:
            //-------------------------------------
            // ctor / dtor
            Enumerable() = default;
            Enumerable(const Enumerable& con) = default;
            Enumerable(Enumerable&& container) noexcept : value{ std::forward<TContainer>(container.value) } {}
            template<typename TElement>
            explicit Enumerable(std::initializer_list<TElement> initialList) :value{ initialList.begin(), initialList.end() } {}
            explicit Enumerable(const TContainer& raw_value) : value{ raw_value } {}
            explicit Enumerable(TContainer&& raw_value) : value{ std::forward<TContainer>(raw_value) } {}

        public:
            ~Enumerable() = default;

            //-------------------------------------
            // operators
            Enumerable& operator=(const Enumerable& container) = default;
            Enumerable& operator=(Enumerable&& container) noexcept{
                value = std::forward<TContainer>(container.value);
                return *this;
            }

            //-------------------------------------
            // iterators
            auto begin() { return std::begin(value); }
            auto end() { return std::end(value); }
            auto cbegin() { return std::cbegin(value); }
            auto cend() { return std::cend(value); }

#pragma endregion
            //-------------------
            // where / where with index 
#pragma region where / where with index implementation
        private:
            template <class TSource, typename T>
            static auto copy_filtered_v(TSource&& source, pred_fn_type<T>&& predicate) {
                Enumerable<TSource> dest(std::forward<TSource>(source));
#if maclinq_cpp17
                auto last = std::remove_if(std::begin(dest.value), std::end(dest.value), std::not_fn(predicate));
#else
                auto last = std::remove_if(std::begin(dest.value), std::end(dest.value), std::not1(predicate));
#endif
                dest.value.erase(last, dest.value.end());

                return dest;
            }

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
                auto dest = Enumerable::CreateVectorEnumerable<T>(size);
                std::size_t index = 0;
                auto itr_ss = move_itr(std::begin(source));
                auto itr_d = inserter_(dest.value);
                for (; itr_ss != move_itr(std::end(source)); ++itr_ss) {
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
            struct where_impl
            {
                auto operator()(TSource&& source, pred_fn_type<typename TSource::value_type>&& predicate) {
                    Enumerable<TSource> dest(std::forward<TSource>(source));
                    for (auto itr = std::begin(dest.value); itr != std::end(dest.value); ) {
                        if (!predicate(*itr)) itr = dest.value.erase(itr);
                        else ++itr;
                    }
                    return dest;
                }
            };

            template <typename T, typename TAllocator>
            struct where_impl<std::vector<T, TAllocator>>
            {
                using cont_type = typename std::vector<T, TAllocator>;
                auto operator()(cont_type&& source, pred_fn_type<T>&& predicate) {
                    return copy_filtered_v<cont_type, T>(std::forward<cont_type>(source), std::forward<pred_fn_type<T> >(predicate));
                }
            };

            template <typename T, typename TAllocator>
            struct where_impl<std::list<T, TAllocator>>
            {
                using cont_type = typename std::list<T, TAllocator>;
                auto operator()(cont_type&& source, pred_fn_type<T>&& predicate) {
                    return copy_filtered_v<cont_type, T>(std::forward<cont_type>(source), std::forward<pred_fn_type<T> >(predicate));

                }
            };

            template <typename T, typename TAllocator>
            struct where_impl<std::deque<T, TAllocator>>
            {
                using cont_type = typename std::deque<T, TAllocator>;
                auto operator()(cont_type&& source, pred_fn_type<T>&& predicate) {
                    return copy_filtered_v<cont_type, T>(std::forward<cont_type>(source), std::forward<pred_fn_type<T> >(predicate));
                }
            };

            template <typename T, typename TAllocator>
            struct where_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(cont_type&& source, pred_fn_type<T>&& predicate) {
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
                auto operator()(cont_type&& source, pred_fn_type<T>&& predicate) {
                    return Enumerable::CreateFilteredCopy<cont_type, std::vector<T, std::allocator<T> > >(
                        std::forward<cont_type>(source), std::forward<pred_fn_type<T>&&>(predicate));
                }
            };

            //-------------------
            // where with index 
            template <class TSource>
            struct where_index_impl
            {
                auto operator()(TSource&& source, pred_idx_fn_type<typename TSource::value_type>&& predicate) {
                    return copy_filtered_index<TSource>(std::forward<TSource>(source), predicate);
                }
            };

            template <typename T, typename TAllocator>
            struct where_index_impl<std::vector<T, TAllocator>>
            {
                using cont_type = typename std::vector<T, TAllocator>;
                auto operator()(cont_type&& source, pred_idx_fn_type<T>&& predicate) {
                    return filter_copy_toV_index<cont_type, T>(std::forward<cont_type>(source), std::size(source), predicate);
                }
            };

            template <typename T, typename TAllocator>
            struct where_index_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(cont_type&& source, pred_idx_fn_type<T>&& predicate) {
                    return filter_copy_toV_index<cont_type, T>(std::forward<cont_type>(source), size_(source), predicate);
                }
            };

            template <typename T, std::size_t N>
            struct where_index_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(cont_type&& source, pred_idx_fn_type<T>&& predicate) {
                    return filter_copy_toV_index<cont_type, T>(std::forward<cont_type>(source), N, predicate);
                }
            };
#pragma endregion
        public:
            // Where<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)
            auto Where(pred_fn_type<value_type>&& predicate) {
                auto where = where_impl<std::decay_t<decltype(value)>>();
                return where(std::move(value), std::forward<pred_fn_type<value_type> >(predicate));
            }

            // Where<TSource>(IEnumerable<TSource>, Func<TSource,Int32,Boolean>)
            auto Where(pred_idx_fn_type<value_type>&& predicate) {
                auto where = where_index_impl<std::decay_t<decltype(value)>>();
                return where(std::move(value), std::forward<pred_idx_fn_type<value_type> >(predicate));
            }
            //-------------------
            // order by
            // sort by
#pragma region order by implementation
        private:
            template <typename T>
            struct has_sort {
            private:
                template <typename U, int = (&U::sort, 0)>
                static std::true_type test(U*);
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test((T*)nullptr))::value;
            };

            template <typename TData, std::enable_if_t<has_sort<TData>::value, bool> = true>
            static inline auto sort_(TData& source,
                std::function<bool(const typename TData::value_type&, const typename TData::value_type&)> sorter) {
                source.sort(sorter);
            }

            template <typename TData, std::enable_if_t<!has_sort<TData>::value, bool> = true>
            static inline auto sort_(TData& source,
                std::function<bool(const typename TData::value_type&, const typename TData::value_type&)> sorter) {
                std::sort(std::begin(source), std::end(source), sorter);
            }

            //-------------------
            // order_by
            template <class TSource, typename TKey>
            struct sort_impl
            {
                //using val_type = typename value_t<typename TSource::value_type>;
                using val_type = typename TSource::value_type;
                auto operator()(TSource&& source, less_fn_type<TKey>&& less_comparer) {
                    auto dest = Enumerable::CreateVectorEnumerable<val_type, TSource>(std::forward<TSource>(source));
                    sort_(dest.value, less_comparer);
                    return dest;
                }
            };

            //template <typename T, typename TAllocator, typename TKey>
            //struct sort_impl<std::deque<T, TAllocator>, TKey>
            //{
            //    using cont_type = typename std::deque<T, TAllocator>;
            //    auto operator()(cont_type&& source, less_fn_type<TKey>&& less_comparer) {
            //        Enumerable<cont_type> dest(std::forward<cont_type>(source));
            //        sort_(dest.value, less_comparer);
            //        return dest;
            //    }
            //};

            //template <typename T, typename TAllocator, typename TKey>
            //struct sort_impl<std::list<T, TAllocator>, TKey>
            //{
            //    using cont_type = typename std::list<T, TAllocator>;
            //    auto operator()(cont_type&& source, less_fn_type<TKey>&& less_comparer) {
            //        Enumerable<cont_type> dest(std::forward<cont_type>(source));
            //        sort_(dest.value, less_comparer);
            //        return dest;
            //    }
            //};

            //template <typename T, typename TAllocator, typename TKey>
            //struct sort_impl<std::forward_list<T, TAllocator>, TKey>
            //{
            //    using cont_type = typename std::forward_list<T, TAllocator>;
            //    auto operator()(cont_type&& source, less_fn_type<TKey>&& less_comparer) {
            //        Enumerable<cont_type> dest(std::forward<cont_type>(source));
            //        sort_(dest.value, less_comparer);
            //        return dest;
            //    }
            //};

            template <typename TKey, typename TValue, typename TComparer, typename TAllocator, typename TKeyValue>
            struct sort_impl<std::map<TKey, TValue, TComparer, TAllocator>, TKeyValue>
            {
                using cont_type = typename std::map<TKey, TValue, TComparer, TAllocator>;
                using val_type = std::pair<TKey, TValue>;
                auto operator()(cont_type&& source, less_fn_type<TKeyValue>&& less_comparer) {
                    auto dest = Enumerable::CreateVectorEnumerable<val_type, cont_type>(std::forward<cont_type>(source));
                    sort_(dest.value, less_comparer);
                    return dest;
                }
            };
#pragma endregion
        public:
            // OrderBy<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>, IComparer<TKey>)
            template <typename TKeySelector>
            auto OrderBy(TKeySelector&& keySelector, icomp_fn_type<decltype(keySelector(std::declval<value_type>()))>&& comparer) {
                using key_type = decltype(keySelector(std::declval<value_type>()));
                auto compare_key = [&](const auto& lhs, const auto& rhs) {return comparer(keySelector(lhs), keySelector(rhs)) < 0; };
                auto order_by = sort_impl<std::decay_t<decltype(value)>, key_type>();
                return order_by(std::move(value),compare_key);
            }

            // OrderBy<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>)
            template <typename TKeySelector>
            auto OrderBy(TKeySelector&& keySelector) {
                using key_type = decltype(keySelector(std::declval<value_type>()));
                auto order_by = sort_impl<std::decay_t<decltype(value)>, key_type>();
                return order_by(std::move(value), std::less<key_type>());
            }

            // OrderByDescending<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>, IComparer<TKey>)
            template <typename TKeySelector>
            auto OrderByDescending(TKeySelector&& keySelector, icomp_fn_type<decltype(keySelector(std::declval<value_type>()))>&& comparer) {
                using key_type = decltype(keySelector(std::declval<value_type>()));
                auto compare_key = [&](const auto& lhs, const auto& rhs) {return comparer(keySelector(lhs), keySelector(rhs)) > 0; };
                auto order_by = sort_impl<std::decay_t<decltype(value)>, key_type>();
                return order_by(std::move(value), compare_key);
            }

            // OrderByDescending<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>)
            template <typename TKeySelector>
            auto OrderByDescending(TKeySelector&& keySelector) {
                using key_type = decltype(keySelector(std::declval<value_type>()));
                auto order_by = sort_impl<std::decay_t<decltype(value)>, key_type>();
                return order_by(std::move(value), std::greater<key_type>());
            }

            // ThenBy<TSource, TKey>(IOrderedEnumerable<TSource>, Func<TSource, TKey>, IComparer<TKey>)
            template <typename TKeySelector>
            auto ThenBy(TKeySelector&& keySelector, icomp_fn_type<decltype(keySelector(std::declval<value_type>()))>&& comparer) {
                return OrderBy(std::forward<TKeySelector>(keySelector), comparer);
            }

            // ThenBy<TSource,TKey>(IOrderedEnumerable<TSource>, Func<TSource,TKey>)
            template <typename TKeySelector>
            auto ThenBy(TKeySelector&& keySelector) {
                return OrderBy(std::forward<TKeySelector>(keySelector));
            }

            // ThenByDescending<TSource,TKey>(IOrderedEnumerable<TSource>, Func<TSource,TKey>, IComparer<TKey>)
            template <typename TKeySelector>
            auto ThenByDescending(TKeySelector&& keySelector, icomp_fn_type<decltype(keySelector(std::declval<value_type>()))>&& comparer) {
                return OrderByDescending(std::forward<TKeySelector>(keySelector), comparer);
            }

            // ThenByDescending<TSource,TKey>(IOrderedEnumerable<TSource>, Func<TSource,TKey>)
            template <typename TKeySelector>
            auto ThenByDescending(TKeySelector&& keySelector) {
                return OrderByDescending(std::forward<TKeySelector>(keySelector));
            }

            auto SortBy(less_fn_type<value_type>&& predicate = std::less<value_type>) {
                auto sort_by = sort_impl<std::decay_t<decltype(value)>, value_type>();
                return sort_by(std::move(value), std::forward<less_fn_type<value_type> >(predicate));
            }

            //-------------------
            // Select
        private:
            template <class TSource, class TDest, typename TFunction>
            static auto transform(TSource&& source, TFunction&& copyer) {
                //Enumerable::copy<decltype<TSource>::iterator,TDest>(move_itr(std::begin(source)), move_itr(std::end(source) >
                //Enumerable<TDest> dest;
                //reserve(dest, size_(source));
                //dest.value.reserve(size_(source));
                //dest.reserve(size_(source));
                auto dest = Enumerable::Create<TDest>(size_(source));
                std::transform(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_(dest.value), std::forward<TFunction>(copyer));
                return dest;
            };
        public:
            // Select<TSource,TResult>(IEnumerable<TSource>, Func<TSource,TResult>)
            template <typename TSelector>
            auto Select(TSelector selector) {
                using dest_type = decltype(selector(std::declval<value_type>()));
                return  transform<TContainer, std::vector<dest_type>>
                    (std::move(value), [&](const auto& elm) {return selector(elm); });
            }

            // template <typename TResultElement>
            // auto Select(std::function<TResultElement(const element_type&)> converter) {
            //    return  transform_copy<TContainer, std::vector<TResultElement>>
            //        (std::move(value), [&](const auto& elm) {return converter(elm); });
            //}

            // Select<TSource, TResult>(IEnumerable<TSource>, Func<TSource, Int32, TResult>)
            template <typename TResult>
            auto Select(std::function<TResult(const value_type&, std::size_t index)> selector) {
                auto result = Enumerable::CreateVectorEnumerable<TResult>(Count());
                std::size_t index = 0;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)),
                    [&](auto&& elm) {result.value.emplace_back(selector(elm, index)); index++; });
                return result;
            }

            // ------------------------------------------------------------------------------------------------
            // no impl
            
            // SelectMany<TSource, TCollection, TResult>(IEnumerable<TSource>, Func<TSource, IEnumerable<TCollection>>, Func<TSource, TCollection, TResult>)
            // �V�[�P���X�̊e�v�f�� IEnumerable<T> �Ɏˉe���A���ʂ̃V�[�P���X�� 1 �̃V�[�P���X�ɕ��R�����āA���̊e�v�f�ɑ΂��Č��ʂ̃Z���N�^�[�֐����Ăяo���܂��B
            template <typename TResult, typename TCollectionElement>
            auto SelectMany(std::function<std::vector<TCollectionElement, std::allocator<TCollectionElement> >(const value_type&)> collector,
                std::function<std::vector<TResult, std::allocator<TResult> >(const value_type&, const TCollectionElement&, TResult/*& , &&*/ )> selector){
                assert(false);

            }

            // SelectMany<TSource, TCollection, TResult>(IEnumerable<TSource>, Func<TSource, Int32, IEnumerable<TCollection>>, Func<TSource, TCollection, TResult>)
            // �V�[�P���X�̊e�v�f�� IEnumerable<T> �Ɏˉe���A���ʂ̃V�[�P���X�� 1 �̃V�[�P���X�ɕ��R�����āA���̊e�v�f�ɑ΂��Č��ʂ̃Z���N�^�[�֐����Ăяo���܂��B �e�\�[�X�v�f�̃C���f�b�N�X�́A���̗v�f�̒��Ԃ̎ˉe���ꂽ�t�H�[���Ŏg�p����܂��B
            template <typename TResult, typename TCollection>
            auto SelectMany(std::function<std::vector<TCollection, std::allocator<TCollection> >(const value_type&, std::size_t index)> collector,
                std::function<std::vector<TResult, std::allocator<TResult> >(const value_type&, const TCollection&, TResult/*& , &&*/)> selector) {
                assert(false);
            }

            // SelectMany<TSource, TResult>(IEnumerable<TSource>, Func<TSource, IEnumerable<TResult>>)
            // �V�[�P���X�̊e�v�f�� IEnumerable<T> �Ɏˉe���A���ʂ̃V�[�P���X�� 1 �̃V�[�P���X�ɕ��R�����܂��B
            template <typename TResult>
            auto SelectMany(std::function<std::vector<TResult, std::allocator<TResult> >(const value_type&)> selector) {
                assert(false);
            }

            // SelectMany<TSource, TResult>(IEnumerable<TSource>, Func<TSource, Int32, IEnumerable<TResult>>)
            // �V�[�P���X�̊e�v�f�� IEnumerable<T> �Ɏˉe���A���ʂ̃V�[�P���X�� 1 �̃V�[�P���X�ɕ��R�����܂��B �e�\�[�X�v�f�̃C���f�b�N�X�́A���̗v�f�̎ˉe���ꂽ�t�H�[���Ŏg�p����܂��B
            template <typename TResult>
            auto SelectMany(std::function<std::vector< TResult, std::allocator<TResult> >(const value_type&, std::size_t index)> selector) {
                assert(false);
            }
            // no impl
            // ------------------------------------------------------------------------------------------------
        private:
            //-------------------
            // skip
#pragma region skip implementation
            template <typename TSrcItr, class TDest>
            static auto copy_range(TSrcItr itrBegin, TSrcItr itrEnd) {
                Enumerable<TDest> dest;
                dest.value = { move_itr(itrBegin), move_itr(itrEnd) };
                return dest;
            }

            template <class TSource>
            struct skip_impl
            {
                auto operator()(TSource&& source, std::size_t count) {
                    std::size_t data_size = size_(source);
                    if (data_size == 0 || count == 0 || data_size < count) return Enumerable<TSource>();
                    return copy_range<TSource::iterator, TSource>(std::next(std::begin(source), count), std::end(source));
                }
            };

            template <typename T, std::size_t N>
            struct skip_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(cont_type&& source, std::size_t count) {
                    if (N == 0 || count == 0 || N < count) return Enumerable<std::vector<T>>();
                    return copy_range<cont_type::iterator, std::vector<T>>(std::next(std::begin(source), count), std::end(source));
                }
            };
#pragma endregion
        public:
            // Skip<TSource>(IEnumerable<TSource>, Int32)
            auto Skip(std::size_t count) {
                auto skip = skip_impl<std::decay_t<decltype(value)>>();
                return skip(std::move(value), count);
            }

            // no test
            // SkipWhile<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
            auto SkipWhile(pred_fn_type<value_type>&& predicate) {
                Enumerable<TContainer> result;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)), [&](auto&& elm) {
                    if (!predicate(elm)) result.value.emplace_back(elm);
                    });
                return result;
            }

            // no test
            // SkipWhile<TSource>(IEnumerable<TSource>, Func<TSource,Int32,Boolean>)
            auto SkipWhile(pred_idx_fn_type<value_type>&& predicate) {
                Enumerable<TContainer> result;
                size_t index = 0;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)), [&](auto&& elm) {
                    if (!predicate(elm, index)) result.value.emplace_back(elm);
                    ++index;
                    });
                return result;
            }
            // ------------------------------------------------------------------------------------------------
            // no impl
            // SkipLast<TSource>(IEnumerable<TSource>, Int32)
            // source �̗v�f�ƁA�ȗ����ꂽ�\�[�X �R���N�V�����̍Ō�� count �v�f���܂ށA�񋓉\�ȐV�����R���N�V������Ԃ��܂��B
            auto SkipLast(const TContainer& source, size_t count) {
                assert(false);
            }
            // ------------------------------------------------------------------------------------------------
        private:
            //-------------------
            // take
#pragma region take implementation
            template <class TSource>
            struct take_impl
            {
                auto operator()(TSource&& source, std::size_t count) {
                    if (size_<TSource>(source) == 0 || count == 0) return Enumerable<TSource>();
                    return copy_range<TSource::iterator, TSource>(std::begin(source), size_(source) < count ? std::end(source) : std::next(std::begin(source), count));
                };
            };

            template <typename T, std::size_t N>
            struct take_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(cont_type&& source, std::size_t count) {
                    if (N == 0 || count == 0) return Enumerable<std::vector<T>>();
                    return copy_range<cont_type::iterator, std::vector<T>>(std::begin(source), N < count ? std::end(source) : std::next(std::begin(source), count));
                };
            };
#pragma endregion
        public:
            // Take<TSource>(IEnumerable<TSource>, Int32)
            auto Take(std::size_t count) {
                auto take = take_impl<std::decay_t<decltype(value)>>();
                return take(std::move(value), count);
            }
 
            // no test
            // TakeWhile<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)
            auto TakeWhile(pred_fn_type<value_type>&& predicate) {
                Enumerable<TContainer> result;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)), [&](auto&& elm) {
                    if (predicate(elm))
                        result.value.emplace_back(elm);
                    });
                return result;
            }

            // no test
            // TakeWhile<TSource>(IEnumerable<TSource>, Func<TSource,Int32,Boolean>)
            auto TakeWhile(pred_idx_fn_type<value_type>&& predicate) {
                Enumerable<TContainer> result;
                size_t index = 0;
                std::for_each(move_itr(std::begin(value)), move_itr(std::end(value)), [&](auto&& elm) {
                    if (predicate(elm, index)) result.value.emplace_back(elm);
                    ++index;
                    });
                return result;
            }
        private:
            //-------------------
            // reverse
#pragma region reverse implementation
            template <typename T>
            struct has_reverse{
                using dummy_type = int;
            private:
                template <typename U> static auto test(dummy_type) -> decltype(std::reverse(std::begin(std::declval<U>()), std::end(std::declval<U>())), std::true_type());
                template <typename U> static auto test(...) -> decltype(std::false_type());
            public:
                static constexpr bool value = decltype(test<T>(0))::value || std::is_array<T>::value;
            };

            template <class TSource>
            static auto copy_reverse(TSource&& source) {
                Enumerable<TSource> dest(std::forward<TSource>(source));
                std::reverse(std::begin(dest.value), std::end(dest.value));
                return dest;
            }

            template <class TData, typename T>
            static auto copy_reverse_to_v(TData&& source) {
                auto dest = Enumerable::CreateVectorEnumerable<T>(size_(source));
                std::copy(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_(dest.value));
                std::reverse(dest.value.begin(), dest.value.end());
                return dest;
            }

            template <class TData>
            struct reverse_impl
            {
                auto operator()(TData&& source) {
                    //return copy_reverse_to_v<TData, value_t<typename TData::value_type>>(std::forward<TData>(source));
                    return copy_reverse_to_v<TData, typename TData::value_type>(std::forward<TData>(source));
                };
            };

            template <typename TKey, typename TValue, typename TComparer, typename TAllocator>
            struct reverse_impl<std::map<TKey, TValue, TComparer, TAllocator> >
            {
                using cont_type = std::map<TKey, TValue, TComparer, TAllocator>;
                auto operator()(cont_type&& source) {
                    Enumerable<std::vector<cont_type::value_type>> dest;
                    reserve_(dest.value, size_(source));
                    std::reverse_iterator<cont_type::iterator> first(source.end());
                    std::reverse_iterator<cont_type::iterator> last(source.begin());
                    std::for_each(first, last, [&](auto v) { dest.value.emplace_back(v);});
                    return dest;
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
#pragma endregion
        public:
            // Reverse<TSource>(IEnumerable<TSource>) 
            auto Reverse() {
                auto reverse = reverse_impl<std::decay_t<decltype(value)>>();
                return reverse(std::move(value));
            }

            // ------------------------------------------------------------------------------------------------
            // no impl
            
            // TakeLast<TSource>(IEnumerable<TSource>, Int32)
            // source �̍Ō�� count �v�f���܂ށA�񋓉\�ȐV�����R���N�V������Ԃ��܂��B
            auto TakeLast(std::size_t count) {
                assert(false);
            }

            // Append<TSource>(IEnumerable<TSource>, TSource)
            // �V�[�P���X�̖����ɒl��ǉ����܂��B
            auto Append(const value_type& element) {
                assert(false);
            }

            // Prepend<TSource>(IEnumerable<TSource>, TSource)
            // �V�[�P���X�̐擪�ɒl��ǉ����܂��B
            auto Prepend(const value_type& element) {
                assert(false);
            }

            // no impl
            // ------------------------------------------------------------------------------------------------

            // GroupBy<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���ăV�[�P���X�̗v�f���O���[�v�����܂��B
            template<typename TKey, typename TValue>
            auto GroupBy(std::function<TKey(const value_type&)> keySelector, std::function<TValue(const value_type&)> elementSelector) {
                std::unordered_multimap<TKey, TValue> map;
                //using keyType = decltype(makeKey(const element_type&));
                std::for_each(std::begin(value), std::end(value), [&](const auto& elm) {
                    map.emplace(keySelector(elm), elementSelector(elm));
                    });
                return Enumerable<decltype(map)>(map);
            }

            // ------------------------------------------------------------------------------------------------
            // no impl

            // GroupBy<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, IEqualityComparer<TKey>)
            // �L�[ �Z���N�^�[�֐��ɏ]���ăV�[�P���X�̗v�f���O���[�v�����܂��B �L�[�̔�r�ɂ́A��r�q���g�p���A�e�O���[�v�̗v�f�̎ˉe�ɂ́A�w�肳�ꂽ�֐����g�p���܂��B
            template<typename TKey, typename TValue, typename TComparer>
            auto GroupBy(std::function<TKey(const value_type&)> keySelector, std::function<TValue(const value_type&)> elementSelector, TComparer&& comparer) {
                assert(false);
            }

            // GroupBy<TSource, TKey, TElement, TResult>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, Func<TKey, IEnumerable<TElement>, TResult>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���ăV�[�P���X�̗v�f���O���[�v�����A�e�O���[�v�Ƃ��̃L�[���猋�ʒl���쐬���܂��B �e�O���[�v�̗v�f�́A�w�肳�ꂽ�֐����g�p���Ďˉe����܂��B
            template<typename TResult, typename TKey, typename TValue>
            auto GroupBy(std::function<TKey(const value_type&)> keySelector, std::function<TKey(const value_type&)> elementSelector,
                std::function<TResult(const TKey&, std::vector<TValue, std::allocator<TValue>>)> resultSelector) {
                assert(false);
            }

            // GroupBy<TSource, TKey, TElement, TResult>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, Func<TKey, IEnumerable<TElement>, TResult>, IEqualityComparer<TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���ăV�[�P���X�̗v�f���O���[�v�����A�e�O���[�v�Ƃ��̃L�[���猋�ʒl���쐬���܂��B �L�[�l�̔�r�ɂ́A�w�肳�ꂽ��r�q���g�p���A�e�O���[�v�̗v�f�̎ˉe�ɂ́A�w�肳�ꂽ�֐����g�p���܂��B
            template<typename TResult, typename TKey, typename TValue, typename TComparer>
            auto GroupBy(std::function<TKey(const value_type&)> keySelector, std::function<TKey(const value_type&)> elementSelector,
                std::function<TResult(const TKey&, std::vector < TValue, std::allocator<TValue>>)> resultSelector, TComparer&& comparer) {
                assert(false);
            }

            // GroupBy<TSource, TKey,           TResult>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TKey, IEnumerable<TSource>, TResult>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���ăV�[�P���X�̗v�f���O���[�v�����A�e�O���[�v�Ƃ��̃L�[���猋�ʒl���쐬���܂��B
            template<typename TResult, typename TKey, typename TValue>
            auto GroupBy(std::function<TKey(const value_type&)> keySelector, std::function<TResult(const TKey&, std::vector<value_type, std::allocator<value_type>>)> resultSelector) {
                assert(false);
            }

            // GroupBy<TSource, TKey, TResult>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TKey, IEnumerable<TSource>, TResult>, IEqualityComparer<TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���ăV�[�P���X�̗v�f���O���[�v�����A�e�O���[�v�Ƃ��̃L�[���猋�ʒl���쐬���܂��B �L�[�̔�r�ɂ́A�w�肳�ꂽ��r�q���g�p���܂��B
            template<typename TResult, typename TKey, typename TValue, typename TComparer>
            auto GroupBy(std::function<TKey(const value_type&)> keySelector, std::function<TResult(const TKey&, std::vector<value_type, std::allocator<value_type>>)> resultSelector, TComparer&& comparer) {
                assert(false);
            }

            // GroupBy<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���ăV�[�P���X�̗v�f���O���[�v�����܂��B
            template<typename TKey>
            auto GroupBy(std::function<TKey(const value_type&)> keySelector) {
                assert(false);
            }

            // GroupBy<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>, IEqualityComparer<TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���ăV�[�P���X�̗v�f���O���[�v�����A�w�肳�ꂽ��r�q���g�p���ăL�[���r���܂��B
            template<typename TResult, typename TKey, typename TComparer>
            auto GroupBy(std::function<TKey(const value_type&)> keySelector, TComparer&& comparer) {
                assert(false);
            }

            // no impl
            // ------------------------------------------------------------------------------------------------
        private:
            //-------------------
            // distinct
#pragma region distinct implementation
            struct distinct_inner
            {
            private:

                using work_type = std::set<value_type, std::less<value_type> >;

                // distinct
                template <class TDest, std::enable_if_t<has_emplace_back<TDest>::value, bool> = true>
                static void emplace_(TDest& dest, value_type&& elm) {
                    dest.emplace_back(elm);
                }

                template <class TDest, std::enable_if_t<!has_emplace_back<TDest>::value && has_emplace<TDest>::value, bool> = true>
                static void emplace_(TDest& dest, value_type&& elm) {
                    dest.emplace(elm);
                }

                template <class TSource, class TDest, std::enable_if_t<!has_emplace_back<TDest>::value && !has_emplace<TDest>::value, bool> = true>
                static void emplace_(TDest& dest, value_type&& elm) {
                    assert(false);
                }

            public:
                template <class TSource, class TDest>
                static void copy_distinct(TSource&& source, TDest& dest, ieq_comp_fn_type<typename TSource::value_type>&& comparer) {
                    if (comparer == nullptr) {
                        std::unordered_set<value_type> temp{};
                        for (auto elm : source) {
                            if (temp.find(elm) == temp.end()) {
                                temp.insert(elm); emplace_(dest, std::forward<value_type>(elm));
                            }
                        }
                    }
                    else {
                        EqualityComparer<typename TSource::value_type> eq(std::forward<ieq_comp_fn_type<typename TSource::value_type>>(comparer));
                        for (auto elm : source) {
                            if (!eq.equals(elm, EqualityComparer<typename TSource::value_type>::add_if_not_found)) {
                                emplace_(dest, std::forward<typename TSource::value_type>(elm));
                            }
                        }
                    }
                }
            };

            template <class TSource>
            struct distinct_impl
            {
                //using val_type = typename value_t<typename TSource::value_type>;
                using val_type = typename TSource::value_type;
                auto operator()(TSource&& source, ieq_comp_fn_type<val_type>&& comparer) {
                    Enumerable<TContainer> dest;
                    distinct_inner::copy_distinct(std::forward<TContainer>(source), dest.value, std::forward<ieq_comp_fn_type<val_type> >(comparer));
                    return dest;
                }
            };

            template <typename T, size_t N>
            struct distinct_impl<std::array<T, N>>
            {
                using cont_type = typename std::array<T, N>;
                auto operator()(std::array<T, N>&& source, ieq_comp_fn_type<T>&& comparer = nullptr) {
                    auto dest = Enumerable::CreateVectorEnumerable<T>(N);
                    distinct_inner::copy_distinct(std::forward<std::array<T, N>>(source), dest.value, std::forward<ieq_comp_fn_type<T> >(comparer));
                    return dest;
                }
            };

            template <typename T, typename TComparer, typename TAllocator>
            struct distinct_impl<std::set<T, TComparer, TAllocator>> {
                auto operator()(std::set<T, TComparer, TAllocator>&& source, ieq_comp_fn_type<T>&& comparer = nullptr) {
                    return Enumerable<std::set<T, TComparer, TAllocator>>(std::forward<std::set<T, TComparer, TAllocator>>(source));
                }
            };

            template <typename T, typename THash, typename TComparer, typename TAllocator>
            struct distinct_impl<std::unordered_set<T, THash, TComparer, TAllocator>> {
                auto operator()(std::unordered_set<T, THash, TComparer, TAllocator>&& source, ieq_comp_fn_type<T>&& comparer = nullptr) {
                    return Enumerable<std::unordered_set<T, THash, TComparer, TAllocator>>(std::forward<std::unordered_set<T, THash, TComparer, TAllocator>>(source));
                }
            };

            template <typename TKey, typename TValue, typename TComparer, typename TAllocator>
            struct distinct_impl<std::map<TKey, TValue, TComparer, TAllocator>> {
                //using val_type = typename value_t<typename std::map<TKey, TValue, TComparer, TAllocator>::value_type>;
                using val_type = typename std::map<TKey, TValue, TComparer, TAllocator>::value_type;
                auto operator()(std::map<TKey, TValue, TComparer, TAllocator>&& source, ieq_comp_fn_type<val_type>&& comparer = nullptr) {
                    return comparer == nullptr
                        ? Enumerable<std::map<TKey, TValue, TComparer, TAllocator>>(std::forward<std::map<TKey, TValue, TComparer, TAllocator>>(source))
                        : source;
                }
            };

            template <typename TKey, typename TValue, typename THash, typename TComparer, typename TAllocator>
            struct distinct_impl<std::unordered_map<TKey, TValue, THash, TComparer, TAllocator>> {
                //using val_type = typename value_t<typename std::unordered_map<TKey, TValue, THash, TComparer, TAllocator>::value_type>;
                using val_type = typename std::unordered_map<TKey, TValue, THash, TComparer, TAllocator>::value_type;
                auto operator()(std::unordered_map<TKey, TValue, THash, TComparer, TAllocator>&& source, ieq_comp_fn_type<val_type>&& comparer = nullptr) {
                    return comparer == nullptr
                        ? Enumerable<std::unordered_map<TKey, TValue, THash, TComparer, TAllocator>>(std::forward<std::unordered_map<TKey, TValue, THash, TComparer, TAllocator>>(source))
                        : source;
                }
            };

            template <typename T, typename TAllocator>
            struct distinct_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = std::forward_list<T, TAllocator>;
                auto operator()(cont_type&& source, ieq_comp_fn_type<T>&& comparer) {
                    Enumerable<std::forward_list<T, TAllocator>> dest(std::forward<cont_type>(source));
                    auto prev = std::begin(dest.value);
                    auto litr = prev;

                    if (comparer == nullptr) {
                        std::unordered_set<value_type> temp{};
                        for (; litr != std::end(dest.value); ) {
                            if (temp.find(*litr) == temp.end()) { 
                                temp.insert(*litr); prev = litr; ++litr; 
                            }
                            else
                                litr = dest.value.erase_after(prev);
                        }
                    }
                    else {
                        EqualityComparer<T> eq(std::forward<ieq_comp_fn_type<T> >(comparer));
                        for (; litr != std::end(dest.value); ) {
                            if (!eq.equals(*litr, EqualityComparer<T>::add_if_not_found)) {
                                prev = litr; ++litr;
                            }
                            else
                                litr = dest.value.erase_after(prev);
                        }
                    }
                    return dest;
                }
            };
#pragma endregion 
        public:
            // Distinct<TSource>(IEnumerable<TSource>)
            // Distinct<TSource>(IEnumerable<TSource>, IEqualityComparer<TSource>)
            auto Distinct(ieq_comp_fn_type<value_type>&& comparer = nullptr) {
                auto distinct = distinct_impl<std::decay_t<decltype(value)>>();
                return distinct(std::move(value), std::forward<ieq_comp_fn_type<value_type> >(comparer));
            }

            // below container will be converted to vector if elements collision
            // map, unordered_map, set, unordered_set
            // below container will be converted to vector if container size cannot set
            // array
            // another container will be into vector
            // multimap, unordered_multimap, multiset, unordered_multiset
            // Concat<TSource>(IEnumerable<TSource>, IEnumerable<TSource>)
            template <class TSecond>
            auto Concat(const TSecond& second) {
                //static_assert(std::is_same_v<value_t<value_type>, value_t<TSecond::value_type>>, "cannnot concatinate ");
                static_assert(std::is_same_v<value_type, TSecond::value_type>, "cannnot concatinate ");
                auto result = Enumerable::CreateVectorEnumerable<value_t<value_type>>(Count() + size_(second));
                std::copy(move_itr(std::begin(value)), move_itr(std::end(value)), inserter_(result.value));
                std::copy(move_itr(std::begin(second)), move_itr(std::end(second)), inserter_(result.value));

                return result;
            }

            template <class TSecond>
            auto Concat(const Enumerable<TSecond>& second) {
                return Concat(second.value);
            }

            // Union<TSource>(IEnumerable<TSource>, IEnumerable<TSource>, IEqualityComparer<TSource>)
            // Union<TSource>(IEnumerable<TSource>, IEnumerable<TSource>)
            using union_comparer = std::function<bool(const value_type&, const value_type&)>;

            template <class TSecond>
            auto Union(const TSecond& second, union_comparer comparer = std::less<value_t<value_type>>()) {
                //static_assert(std::is_same_v<value_t<value_type>, value_t<TSecond::value_type>>, "cannnot union ");
                static_assert(std::is_same_v<value_type, TSecond::value_type>, "cannnot union ");
                auto result = Enumerable::CreateVectorEnumerable<value_t<value_type>>(Count() + size_(second));
                std::set<value_type, decltype(comparer)> temp(comparer);
                for (auto elm : value)if (temp.find(elm) == temp.end()) { temp.insert(elm); result.value.emplace_back(elm); }
                for (auto elm : second)if (temp.find(elm) == temp.end()) { temp.insert(elm); result.value.emplace_back(elm); }
                result.value.shrink_to_fit();
                return result;
            }

            template <class TSecond>
            //auto Union(const Enumerable<TSecond>& second, union_comparer predicate = std::less<value_t<value_type>>()) {
            auto Union(const Enumerable<TSecond>& second, union_comparer predicate = std::less<value_type>()) {
                return Union(second.value, predicate);
            }

            // Intersect<TSource>(IEnumerable<TSource>, IEnumerable<TSource>, IEqualityComparer<TSource>)
            template <class TSecond>
            auto Intersect(const TSecond& second, std::function<bool(const value_type&, const value_type&)> comparer = std::less<value_type>()) {
                //static_assert(std::is_same_v<value_t<value_type>, value_t<TSecond::value_type>>, "cannnot intersect ");
                //auto result = Enumerable::CreateVectorEnumerable<value_t<value_type>>(Count() + size_(second));
                static_assert(std::is_same_v<value_type, TSecond::value_type>, "cannnot intersect ");
                auto result = Enumerable::CreateVectorEnumerable<value_type>(Count() + size_(second));
                std::set<value_type, decltype(comparer)> temp(comparer);
                for (auto elm : value) if (temp.find(elm) == temp.end()) { temp.insert(elm); }
                for (auto elm : second) if (temp.find(elm) != temp.end()) { result.value.emplace_back(elm); temp.erase(elm); }
                result.value.shrink_to_fit();
                return result;
            }

            // Intersect<TSource>(IEnumerable<TSource>, IEnumerable<TSource>)
            template <class TSecond>
            auto Intersect(const Enumerable<TSecond>& second, std::function<bool(const value_type&, const value_type&)> comparer = std::less<value_type>()) {
                return Intersect(second.value, comparer);
            }

            // Except<TSource>(IEnumerable<TSource>, IEnumerable<TSource>, IEqualityComparer<TSource>)
            // Except<TSource>(IEnumerable<TSource>, IEnumerable<TSource>)
            template <class TSecond>
            auto Except(const TSecond& second, std::function<bool(const value_type&, const value_type&)> comparer = std::less<value_type>) {
                //static_assert(std::is_same_v<value_t<value_type>, value_t<TSecond::value_type>>, "cannnot except ");
                //auto result = Enumerable::CreateVectorEnumerable<value_t<value_type>>(Count() + size_(second));
                static_assert(std::is_same_v<value_type, TSecond::value_type>, "cannnot except ");
                auto result = Enumerable::CreateVectorEnumerable<value_type>(Count() + size_(second));
                std::set<value_type, decltype(comparer)> temp(comparer);
                for (auto elm : second) temp.insert(elm);
                for (auto elm : value)
                    if (temp.find(elm) == temp.end()) { temp.insert(elm); result.value.emplace_back(elm); }
                result.value.shrink_to_fit();
                return result;
            }

            template <class TSecond>
            auto Except(const Enumerable<TSecond>& second, std::function<bool(const value_type&, const value_type&)> predicate = std::less<value_type>()) {
                return Except(second.value, predicate);
            }

            // Zip<TFirst,TSecond>(IEnumerable<TFirst>, IEnumerable<TSecond>)
            template <class TSecond>
            auto Zip(const TSecond& another) {
                auto itr_f = move_itr(std::begin(value));
                auto itr_s = std::cbegin(another);
                //using tup_type = std::tuple<value_t<value_type>, val_impl<typename TSecond::value_type>::type>;
                using tup_type = std::tuple<value_type, typename TSecond::value_type>;
                //Enumerable<std::vector<tup_type>> dest;
                //dest.reserve(Count() < size_(another) ? Count() : size_(another));
                auto dest = Enumerable::CreateVectorEnumerable<tup_type>(Count() < size_(another) ? Count() : size_(another));

                for (; itr_f != move_itr(std::end(value)) && itr_s != std::end(another); ++itr_f, ++itr_s) {
                    dest.value.emplace_back(std::make_tuple(*itr_f, *itr_s));
                }
                return dest;
            }

            // Zip<TFirst, TSecond, TResult>(IEnumerable<TFirst>, IEnumerable<TSecond>, Func<TFirst, TSecond, TResult>)
            template <class TSecond, typename TResultSelector>
            auto Zip(const TSecond& second, TResultSelector&& resultSelector) {
                using dest_type = decltype(resultSelector(value_type(), typename TSecond::value_type()));
                auto itr_f = move_itr(std::begin(value));
                auto itr_s = std::begin(second);
                auto dest = Enumerable::CreateVectorEnumerable<dest_type>(Count() < size_(second) ? Count() : size_(second));
                for (; itr_f != move_itr(std::end(value)) && itr_s != std::end(second); ++itr_f, ++itr_s) {
                    dest.value.emplace_back(resultSelector(*itr_f, *itr_s));
                }
                return  dest;
            }

            template <class TSecond>
            auto Zip(const Enumerable<TSecond>& second) {
                return Zip(second.value);
            }

            template <class TSecond, typename TResultSelector>
            auto Zip(const Enumerable<TSecond>& second, TResultSelector&& resultSelector) {
                return Zip(second.value, resultSelector);
            }
            // Join<TOuter, TInner, TKey, TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter, TKey>, Func<TInner, TKey>, Func<TOuter, TInner, TResult>, IEqualityComparer<TKey>)
            template <class TInner, typename TGetOuterKey, typename TGetInnerKey, typename TResultSelector, typename TComparer>
            auto Join(const TInner& inner, TGetOuterKey&& getOuterKey, TGetInnerKey&& getInnerKey, TResultSelector&& resultSelector, TComparer&& comparer) {
                using dest_type = decltype(resultSelector(value_type(), typename TInner::value_type()));
                using key_type = decltype(getInnerKey(value_type()));
                static_assert(std::is_same_v<key_type, decltype(getOuterKey(typename TInner::value_type()))>, "key type mismatch");

                auto dest = Enumerable::CreateVectorEnumerable<dest_type>(Count() + size_(inner));
                std::multimap<key_type, decltype(std::cbegin(inner))> outerKeys(std::forward<TComparer>(comparer));

                auto itr_o = std::cbegin(inner);
                for (; itr_o != std::cend(inner); ++itr_o)
                    outerKeys.insert(std::make_pair(getOuterKey(*itr_o), itr_o));

                for (auto itr_i = std::begin(value); itr_i != std::end(value); ++itr_i) {
                    auto key_range = outerKeys.equal_range(getInnerKey(*itr_i));
                    for (auto mapItr = key_range.first; mapItr != key_range.second; ++mapItr) {
                        dest.value.emplace_back(resultSelector(*itr_i, *(mapItr->second)));
                    }
                }
                dest.value.shrink_to_fit();
                return  dest;
            }

            // must be re-test
            // Join<TOuter, TInner, TKey, TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter, TKey>, Func<TInner, TKey>, Func<TOuter, TInner, TResult>)
            template <class TInner, typename TGetOuterKey, typename TGetInnerKey, typename TResultSelector>
            auto Join(const TInner& inner, TGetOuterKey&& getOuterKey, TGetInnerKey&& getInnerKey, TResultSelector&& resultSelector) {
                return Join(inner, std::forward<TGetInnerKey>(getInnerKey), std::forward<TGetOuterKey>(getOuterKey),
                    std::forward<TResultSelector>(resultSelector), std::less<decltype(getInnerKey(value_type()))>());
            }

            template <class TInner, typename TGetOuterKey, typename TGetInnerKey, typename TResultSelector, typename TComparer>
            auto Join(const Enumerable<TInner>& inner, TGetInnerKey&& getInnerKey, TGetOuterKey&& getOuterKey, TResultSelector&& resultSelector, TComparer&& comparer) {
                return Join(inner.value, std::forward<TGetInnerKey>(getInnerKey), std::forward<TGetOuterKey>(getOuterKey),
                    std::forward<TResultSelector>(resultSelector), std::forward<TComparer>(comparer));
            }

            template <class TInner, typename TGetOuterKey, typename TGetInnerKey, typename TResultSelector>
            auto Join(const Enumerable<TInner>& inner, TGetInnerKey&& getInnerKey, TGetOuterKey&& getOuterKey, TResultSelector&& resultSelector) {
                return Join(inner.value, std::forward<TGetInnerKey>(getInnerKey), std::forward<TGetOuterKey>(getOuterKey),
                    std::forward<TResultSelector>(resultSelector));
            }

            // ------------------------------------------------------------------------------------------------
            // no impl

            // GroupJoin<TOuter, TInner, TKey, TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter, TKey>, Func<TInner, TKey>, Func<TOuter, IEnumerable<TInner>, TResult>)
            // �L�[�����������ǂ����Ɋ�Â��� 2 �̃V�[�P���X�̗v�f�𑊌݂Ɋ֘A�t���A���̌��ʂ��O���[�v�����܂��B �L�[�̔�r�ɂ͊���̓��l��r�q���g�p����܂��B
            template <typename TKey, class TInner, typename TResultSelector>
            auto GroupJoin(const TInner& inner, std::function<TKey(const value_type&)> outerKeySelector,
                std::function<TKey(const typename TInner::value_type&)>innerKeySelector, TResultSelector&& resultSelector) {
                assert(false);
            }
          
            //// GroupJoin<TOuter, TInner, TKey, TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter, TKey>, Func<TInner, TKey>, Func<TOuter, IEnumerable<TInner>, TResult>, IEqualityComparer<TKey>)
            //// �L�[�����������ǂ����Ɋ�Â��� 2 �̃V�[�P���X�̗v�f�𑊌݂Ɋ֘A�t���A���̌��ʂ��O���[�v�����܂��B �w�肳�ꂽ IEqualityComparer<T> ���g�p���ăL�[���r���܂��B
            template <typename TKey, class TInner, typename TResultSelector, typename TComparer>
            auto GroupJoin(const TInner& inner, std::function<TKey(const value_type&)> outerKeySelector,
                std::function<TKey(const typename TInner::value_type&)> innerKeySelector, TResultSelector&& resultSelector, TComparer&& comparer) {
                assert(false);
            }

            template <typename TKey, class TInner, typename TResultSelector>
            auto GroupJoin(const Enumerable<TInner>& inner, std::function<TKey(const value_type&)> outerKeySelector,
                std::function<TKey(const typename TInner::value_type&)>innerKeySelector, TResultSelector&& resultSelector) {
                return GroupJoin(inner.value, outerKeySelector, innerKeySelector, std::forward<TResultSelector>(resultSelector));
            }

            //// GroupJoin<TOuter, TInner, TKey, TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter, TKey>, Func<TInner, TKey>, Func<TOuter, IEnumerable<TInner>, TResult>, IEqualityComparer<TKey>)
            //// �L�[�����������ǂ����Ɋ�Â��� 2 �̃V�[�P���X�̗v�f�𑊌݂Ɋ֘A�t���A���̌��ʂ��O���[�v�����܂��B �w�肳�ꂽ IEqualityComparer<T> ���g�p���ăL�[���r���܂��B
            template <typename TKey, class TInner, typename TResultSelector, typename TComparer>
            auto GroupJoin(const Enumerable<TInner>& inner, std::function<TKey(const value_type&)> outerKeySelector,
                std::function<TKey(const typename TInner::value_type&)>innerKeySelector, TResultSelector&& resultSelector, TComparer&& comparer) {
                return GroupJoin(inner.value, outerKeySelector, innerKeySelector, std::forward<TResultSelector>(resultSelector), std::forward<TComparer>(comparer));
            }

            // no impl
            // ------------------------------------------------------------------------------------------------

#pragma region STL Algorithm Implementations -- NOT IN USE --
#if FALSE
        // STL algorithm implementation all method need sort previously
            auto SortedDistinct(std::function<bool(const value_type&, const value_type&)> predicate = std::less<value_type>()) {
                Enumerable<TContainer> result;
                std::unique_copy(move_itr(std::begin(value)), move_itr(std::end(value)), inserter_(result.value), predicate);
                return result;
            }
            template <class TOther>
            auto SortedUnion(const TOther& another, std::function<bool(const value_type&, const value_type&)> predicate) {
                static_assert(std::is_same_v<value_t<value_type>, value_t<TOther::value_type>>, "cannnot union ");
                Enumerable<std::vector<value_t<value_type>>> result;
                std::set_union(move_itr(std::begin(value)), move_itr(std::end(value)), move_itr(std::begin(another)), move_itr(std::end(another)), inserter_bk(result.value), predicate);
                return result;
            }

            template <class TOther>
            auto SortedIntersect(const TOther& another, std::function<bool(const value_type&, const value_type&)> predicate) {
                static_assert(std::is_same_v<value_t<value_type>, value_t<TOther::value_type>>, "cannnot union ");
                Enumerable<std::vector<value_t<value_type>>> result;
                std::set_intersection(move_itr(std::begin(value)), move_itr(std::end(value)), std::begin(another), std::end(another), inserter_bk(result.value), predicate);
                return result;
            }

            template <class TOther>
            auto SortedExcept(const TOther& another, std::function<bool(const value_type&, const value_type&)> predicate) {
                static_assert(std::is_same_v<value_t<value_type>, val_impl<TOther::value_type>::type>, "cannnot union ");
                Enumerable<std::vector<value_t<value_type>>> result;
                std::set_difference(move_itr(std::begin(value)), move_itr(std::end(value)), std::begin(another), std::end(another), inserter_bk(result.value), predicate);
                return result;
            }
#endif
#pragma endregion 
        private:
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
        public:
            auto ToVector()&& {
                auto to_vector = to_vector_impl<std::decay_t<decltype(value)> >();
                return to_vector(std::move(value));
            }
        private:
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
        public:
            auto ToList()&& {
                auto to_list = to_list_impl<std::decay_t<decltype(value)> >();
                return to_list(std::move(value));
            }

            // ToDictionary<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐�����їv�f�Z���N�^�[�֐��ɏ]���āADictionary<TKey, TValue> ���� IEnumerable<T> ���쐬���܂��B
            // ToDictionary<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, IEqualityComparer<TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��A��r�q�A����їv�f�Z���N�^�[�֐��ɏ]���āADictionary<TKey, TValue> ���� IEnumerable<T> ���쐬���܂��B
            template <typename TGetKey, typename TGetValue, typename TComparer>
            auto ToDictionary(TGetKey&& keySelector, TGetValue&& elementSelector, TComparer&& comparer = std::less<decltype(keySelector(std::declval<value_type>()))>) {
                assert(false);
                using key_type = decltype(keySelector(std::declval<value_type>()));
                using val_type = decltype(elementSelector(std::declval<value_type>()));
                std::unordered_map<key_type, val_type> result(size_(value));
                //for (auto elm : value) {
                //    result.emplace(getKey(elm), getValue(elm));
                //}
                //result.size_to_fit();
                return result;
            }

            // ToDictionary<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���āADictionary<TKey, TValue> ���� IEnumerable<T> ���쐬���܂��B
            //// ToDictionary<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>, IEqualityComparer<TKey>)
            //// �w�肳�ꂽ�L�[ �Z���N�^�[�֐�����уL�[�̔�r�q�ɏ]���āADictionary<TKey, TValue> ���� IEnumerable<T> ���쐬���܂��B
            template <typename TGetKey, typename TComparer>
            auto ToDictionary(TGetKey&& keySelector, TComparer&& comaprer = [](const decltype(keySelector(std::declval<value_type>()))& lhs, const decltype(keySelector(std::declval<value_type>()))& rhs) { return lhs == rhs; }) {
                assert(false);
                using key_type = decltype(keySelector(std::declval<value_type>()));
                //std::unordered_map<key_type, value_t<value_type>> result(size_(value));
                std::unordered_map<key_type, value_type> result(size_(value));
                //for (auto elm : value) {
                //    result.emplace(getKey(elm), getValue(elm));
                //}
                //result.size_to_fit();
                return result;
            }

            // no test
            auto ToHashSet() {
                return std::unordered_set<value_type>(move_itr(std::begin(value)), move_itr(std::end(value)));
            }

            // no impl
            // ToHashSet<TSource>(IEnumerable<TSource>, IEqualityComparer<TSource>)
            // comparer ���g�p���� IEnumerable<T>���� HashSet<T> ���쐬���A�L�[���r���܂��B
            template <typename TComparer>
            auto ToHashSet(TComparer&& comaprer) {
                assert(false);
            }

            // ToLookup<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>, IEqualityComparer<TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��A��r�q�A����їv�f�Z���N�^�[�֐��ɏ]���āALookup<TKey, TElement> ���� IEnumerable<T> ���쐬���܂��B
            template <typename TGetKey, typename TGetElement>
            auto  ToLookup(TGetKey&& keySelector, TGetElement&& elementSelector, 
                std::function<bool(const decltype(keySelector(std::declval<value_type>()))& , 
                   const decltype(keySelector(std::declval<value_type>()))&)> comaprer) {
                assert(false);
            }

            // ToLookup<TSource, TKey, TElement>(IEnumerable<TSource>, Func<TSource, TKey>, Func<TSource, TElement>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐�����їv�f�Z���N�^�[�֐��ɏ]���āALookup<TKey, TElement> ���� IEnumerable<T> ���쐬���܂��B
            template <typename TGetKey, typename TGetElement>
            auto  ToLookup(TGetKey&& keySelector, TGetElement&& elementSelector) {
                using key_type = decltype(keySelector(std::declval<value_type>()));
                return ToLookup(std::forward<TGetKey>(keySelector), std::forward<TGetElement>(elementSelector),
                                [](const key_type& lhs, const key_type& rhs) {return lhs == rhs; });
            }
            // TO DO:
            // ToLookup<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>, IEqualityComparer<TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐�����уL�[�̔�r�q�ɏ]���āALookup<TKey, TElement> ���� IEnumerable<T> ���쐬���܂��B
            template <typename TGetKey>
            auto ToLookup(TGetKey&& keySelector) {
                using key_type = decltype(keySelector(std::declval<value_type>()));
                return ToLookup(std::forward<TGetKey>(keySelector), [](const key_type& lhs, const key_type& rhs) {return lhs == rhs; });
            }

            // TO DO:
            // ToLookup<TSource, TKey>(IEnumerable<TSource>, Func<TSource, TKey>)
            // �w�肳�ꂽ�L�[ �Z���N�^�[�֐��ɏ]���āALookup<TKey, TElement> ���� IEnumerable<T> ���쐬���܂��B
            //template <typename TGetKey, typename TComparer>
            //auto  ToLookup(TGetKey&& keySelector, TComparer&& comaprer) {
            //    using key_type = decltype(keySelector(std::declval<value_type>()));
            //    return ToLookup(std::forward<TGetKey>(keySelector), [](const value_type& elm) {return elm; },
            //        std::forward<TComparer>(comaprer));
            //}

            template <typename TChar>
            auto ToString(std::function<const std::basic_string<TChar>(const value_type&)> converter) {
                std::basic_string<TChar> result;
                for (auto val : value)
                    result.append(converter(val));
                return result;
            }

            //-------------------------------------
            // Linq like functions constant
            // Empty<TResult> ()
            auto Empty() const {
                return Enumerable<TContainer>();
            }

            const auto& ForEach(std::function<void(const value_type&)> predicate) { // �f�[�^���ς��Ȃ��̂ŎQ�ƂŕԂ�
                std::for_each(std::cbegin(value), std::cend(value), predicate);
                return *this;
            }

            // Contains<TSource>(IEnumerable<TSource>, TSource)
            // Contains<TSource>(IEnumerable<TSource>, TSource, IEqualityComparer<TSource>)
            bool Contains(const value_type& elm, ieq_comp_fn_type<value_type>&& comparer
                = std::equal_to<value_type>()) const {
                if (!Any()) { return false; }
                return std::find_if(std::cbegin(value), std::cend(value),
                    [&](const auto& item) {return comparer(elm, item); }) != std::cend(value);
            }
        private:
            //-------------------
            // count
            template <typename T>
            struct has_size {
            private:
                template <typename U, int = (&U::size, 0)>
                static std::true_type test(U*);
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test((T*)nullptr))::value;
            };
            //template <typename T>
            //struct has_size {
            //    using dummy_type = int;
            //private:
            //    template <typename U> static auto test(U u) -> decltype(u.size(), std::true_type());
            //    template <typename U> static auto test(...) -> decltype(std::false_type());
            //public:
            //    static bool const value = decltype(test(std::declval<T>()))::value;
            //};

            template <typename T, std::enable_if_t<has_size<T>::value, bool> = true>
            static inline std::size_t size_(const T& data) {
                return data.size();
            };

            template <typename T, std::enable_if_t<!has_size<T>::value && has_itr<T>::value, bool> = true>
            static inline std::size_t size_(const T& data) {
                return std::distance(std::begin(data), std::end(data));
            };

            template <typename T, std::enable_if_t<!has_size<T>::value && !has_itr<T>::value, bool> = true>
            static inline std::size_t size_(const T& data) {
                return sizeof(data);
            };
        public:
            // Count<TSource>(IEnumerable<TSource>)
            std::size_t Count() const {
                //auto count = size_impl<std::decay_t<decltype(value)>>();
                //return count(value);
                return size_(value);
            }

            // Count<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)
            std::size_t Count(std::function<bool(const value_type&)> predicate) const {
                return std::count_if(std::cbegin(value), std::cend(value), predicate);
            }

            // will be not implemented
            // LongCount<TSource>(IEnumerable<TSource>)
            // LongCount<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)

            // Any<TSource>(IEnumerable<TSource>)
            bool Any() const { return Count() > 0; }

            // Any<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)
            bool Any(pred_fn_type<value_type>&& predicate) const {
                return find_if(std::cbegin(value), std::cend(value), predicate) != std::cend(value);
            }

            // All<TSource>(IEnumerable<TSource>, Func<TSource,bool>);
            bool All(pred_fn_type<value_type>&& predicate) const {
                return Count() > 0 && std::all_of(std::cbegin(value), std::cend(value), predicate);
            }

            // ------------------------------------------------------------------------------------------------
            // no impl

            // SequenceEqual<TSource>(IEnumerable<TSource>, IEnumerable<TSource>)
            template<class TSecond>
            auto SequenceEqual(const TSecond& second) {
                assert(false);
            }

            // SequenceEqual<TSource>(IEnumerable<TSource>, IEnumerable<TSource>, IEqualityComparer<TSource>)
            template<class TSecond>
            auto SequenceEqual(const TSecond& second, std::function<bool(value_type, typename TSecond::value_type)> comparer) {
                assert(false);
            }

            // no impl
            // ------------------------------------------------------------------------------------------------
        private:
            template <class TData>
            struct last_impl
            {
                auto operator()(const TData& data, std::size_t size) const {
                    nullable_t< TData::value_type> result;
                    if (size > 0)
                        result = *(--std::end(data));
                    return result;
                }
            };

            template <typename T, typename TAllocator>
            struct last_impl<std::forward_list<T, TAllocator>>
            {
                using cont_type = typename std::forward_list<T, TAllocator>;
                auto operator()(const cont_type& data, std::size_t size) const {
                    nullable_t<T> result;
                    if (size > 0)
                        result = *(std::next(std::begin(data), size - 1));
                    return result;
                }
            };

            template <class TData>
            static auto find_last(const TData& data, pred_fn_type<typename TData::value_type>&& predicate) {
                nullable_t<TData::value_type> result;
                if (size_(data) == 0)
                    return result;
                auto itr = std::find_if(data.crbegin(), data.crend(), predicate);
                if (itr != data.crend())
                    result = *itr;
                return result;
            }

            template <class TData>
            static auto find_last_forwardly(const TData& data, pred_fn_type<typename TData::value_type>&& predicate) {
                nullable_t< TData::value_type> result;
                if (size_(data) == 0)
                    return result;

                auto find_itr = std::cend(data);
                for (auto itr = std::cbegin(data); itr != std::cend(data); itr++) {
                    if (predicate(*itr)) find_itr = itr;
                }
                if (find_itr != std::cend(data))
                    result = *find_itr;
                return result;
            }

            template <class TData>
            struct last_func_impl
            {
                auto operator()(const TData& data, pred_fn_type<typename TData::value_type>&& predicate) const {
                    return find_last_forwardly<TData>(data, std::forward<pred_fn_type<value_type> >(predicate));
                }
            };

            template <typename T, typename TAllocator>
            struct last_func_impl<std::vector<T, TAllocator>>
            {
                using cont_type = typename std::vector<T, TAllocator>;
                auto operator()(const cont_type& data, pred_fn_type<T>&& predicate) const {
                    return find_last(data, std::forward<pred_fn_type<value_type> >(predicate));
                }
            };

            template <typename T, typename TAllocator>
            struct last_func_impl<std::list<T, TAllocator>>
            {
                using cont_type = typename std::list<T, TAllocator>;
                auto operator()(const cont_type& data, pred_fn_type<T>&& predicate) const {
                    return find_last(data, std::forward<pred_fn_type<value_type> >(predicate));
                }
            };

            template <typename T, typename TAllocator>
            struct last_func_impl<std::deque<T, TAllocator>>
            {
                using cont_type = typename std::deque<T, TAllocator>;
                auto operator()(const cont_type& data, pred_fn_type<T>&& predicate) const {
                    return find_last(data, std::forward<pred_fn_type<value_type> >(predicate));
                }
            };
        public:
            // first / first_or_default
            // First<TSource>(IEnumerable<TSource>)
            auto First() const {
                //nullable_t<value_t<value_type> > result{};
                nullable_t<value_type> result{};
                if (Count())
                    result = *std::cbegin(value);
                return result;
            }

            // First<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)
            auto First(pred_fn_type<value_type>&& predicate) const {
                //nullable_t<value_t<value_type> > result{};
                nullable_t<value_type> result{};
                if (Count() == 0)
                    return result;

                auto itr = std::find_if(std::cbegin(value), std::cend(value), predicate);
                if (itr != std::cend(value))
                    result = *itr;
                return result;
            }

            // FirstOrDefault<TSource>(IEnumerable<TSource>)
            auto FirstOrDefault() const {
                auto result = First();
                //return result.has_value() ? result.value() : value_t<value_type>();
                return result.has_value() ? result.value() : value_type();
            }

            // FirstOrDefault<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
            auto FirstOrDefault(pred_fn_type<value_type>&& predicate) const {
                auto result = First(std::forward<pred_fn_type<value_type> >(predicate));
                //return result.has_value() ? result.value() : value_t<value_type>();// todo 
                return result.has_value() ? result.value() : value_type();// todo 
            }

            // last / last_or_default
            // Last<TSource>(IEnumerable<TSource>)
            auto Last() const {
                auto last = last_impl<std::decay_t<decltype(value)>>();
                return last(value, Count());
            }

            // Last<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)
            auto Last(pred_fn_type<value_type>&& predicate) const {
                auto last = last_func_impl<std::decay_t<decltype(value)>>();
                return last(value, std::forward<pred_fn_type<value_type> >(predicate));
            }

            // LastOrDefault<TSource>(IEnumerable<TSource>)
            auto LastOrDefault() const {
                auto result = Last();
                return result.has_value() ? result.value() : value_type();
            }

            // LastOrDefault<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
            auto LastOrDefault(pred_fn_type<value_type>&& predicate) const {
                auto result = Last(std::forward<pred_fn_type<value_type> >(predicate));
                return result.has_value() ? result.value() : value_type();
            }

            // single / single_or_default
            // Single<TSource>(IEnumerable<TSource>)
            auto Single() const {
                nullable_t<value_type> result{};
                if (Count() != 1)
                    return result;
 
                result = *std::cbegin(value);
                return result;
            }

            // Single<TSource>(IEnumerable<TSource>, Func<TSource, Boolean>)
            auto Single(pred_fn_type<value_type>&& predicate) const {
                nullable_t<value_type> result{};
                if (Count() == 0)
                    return result;
                const auto end = std::cend(value);
                auto itr = std::find_if(std::cbegin(value), end, predicate);
                while (itr != end) {
                    if (!result.has_value())
                        result = *itr;
                    else
                        return nullable_t<value_type>();
                    itr = std::find_if(++itr, end, predicate);
                }
                return result;
            }

            // just return default value
            // no test
            // SingleOrDefault<TSource>(IEnumerable<TSource>)
            auto SingleOrDefault() const {
                auto result = Single();
                return result.has_value() ? result.value() : value_type();
            }

            // SingleOrDefault<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
            auto SingleOrDefault(pred_fn_type<value_type>&& predicate) const {
                auto result = Single(std::forward<pred_fn_type<value_type> >(predicate));
                return result.has_value() ? result.value() : value_type();
            }

            // ElementAt<TSource> (IEnumerable<TSource> source, int index);
            auto ElementAt(std::size_t index) const {
                nullable_t<value_type> result{};
                if (Count() == 0 || Count() <= index)
                    return result;
                result = *std::next(std::cbegin(value), index);
                return result;
            }

            // ElementAtOrDefault<TSource> (IEnumerable<TSource> source, int index);
            auto ElementAtOrDefault(std::size_t index) const {
                auto result = ElementAt(index);
                return result.has_value() ? result.value() : value_type();
            }

            // no test
            auto Aggregate(std::function<value_type(const value_type&, const value_type&)> accumulator) const {
                return std::accumulate(std::cbegin(value), std::cend(value), value_type(), accumulator);
            }

            // no test
            template <typename TAccumulate>
            auto Aggregate(TAccumulate seed, std::function<TAccumulate(const TAccumulate&, const value_type&)> accumulater) const {
                TAccumulate result = seed;
                for (auto itr = std::cbegin(value); itr != std::cend(value); ++itr)
                    result = accumulater(result, *itr);
                return result;
            }

            // no test
            template <typename TAccumulate, typename TSelector>
            auto Aggregate(TAccumulate seed, std::function<TAccumulate(value_type, TAccumulate)> accumulater, TSelector&& selector) const {
                TAccumulate result = seed;
                for (auto itr = std::cbegin(value); itr != std::cend(value); ++itr)
                    result = accumulater(result, *itr);
                return selector(result);
            }

            // ------------------------------------------------------------------------------------------------
            // no impl

            // DefaultIfEmpty<TSource>(IEnumerable<TSource>)
            // �w�肵���V�[�P���X�̗v�f��Ԃ��܂��B�V�[�P���X����̏ꍇ�̓V���O���g�� �R���N�V�����ɂ���^�p�����[�^�[�̊���l��Ԃ��܂��B
            auto DefaultIfEmpty() {
                //if (Count() == 0) {
                //    value.push_back(value_type());
                //}
                //return this;
                assert(false);
            }

            // DefaultIfEmpty<TSource>(IEnumerable<TSource>, TSource)
            // �w�肳�ꂽ�V�[�P���X�̗v�f��Ԃ��܂��B�V�[�P���X����̏ꍇ�̓V���O���g�� �R���N�V�����ɂ���^�p�����[�^�[�̊���l��Ԃ��܂��B
            auto DefaultIfEmpty(const value_type& defaultValue) {
                //if (Count() == 0) {
                //    value.push_back(init);
                //}
                //return this;
                assert(false);
            }

            // no impl
            // ------------------------------------------------------------------------------------------------

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
        private:
            template <typename T>
            static Enumerable<std::vector<T>> CreateVectorEnumerable(size_t reserve = 0) {
                Enumerable<std::vector<T>> result;
                reserve_(result.value, reserve);
                return result;
            }

            template <class T, class TSource>
            static Enumerable<std::vector<T>> CreateVectorEnumerable(TSource&& source) {
                Enumerable<std::vector<T>> result;
                reserve_(result.value, size_<TSource>(source));
                std::copy(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_(result.value));
                return result;
            }

            template <class TDst>
            static Enumerable<TDst> Create(std::size_t reserve = 0) {
                Enumerable<TDst> result;
                reserve_(result.value, reserve);
                return result;
            }

            template <class TSrc, class TDst>
            static Enumerable<TDst> CreateCopy(TSrc&& source) {
                auto result = Create<TDst>(size_(source));
                auto last = std::copy(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_(result.value));
                return result;
            }

            template <class TSrc, class TDst>
            static auto CreateFilteredCopy(TSrc&& source, pred_fn_type<typename TSrc::value_type>&& predicate) {
                auto result = Create<TDst>(size_(source));
                auto last = std::copy_if(move_itr(std::begin(source)), move_itr(std::end(source)), inserter_(result.value), predicate);

                return result;
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
        inline auto From(std::initializer_list<typename TContainer::element_type> initialList) {
            return Enumerable<TContainer>(initialList);
        }

        template <typename TChar>
        inline auto From(const std::basic_string<TChar>& string) {
            Enumerable<std::vector<TChar>> result;
            result.value.reserve(string.length());
            std::copy(std::cbegin(string), std::cend(string), std::begin(result.value));
            return result;
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
        template <typename T, typename TArg>
        inline auto From(const CArray<T, TArg>& carray) {
            auto cbegin = [](const CArray<T, TArg>& cary) {return (&cary.GetAt(0)); };
            auto cend = [](const CArray<T, TArg>& cary) {return (&cary.GetAt(cary.GetSize() - 1) + 1); };

            Enumerable<std::vector<T>> dest;
            //dest.value.reserve(carray.GetSize());
            //if (carray.GetSize() > 0)
            //    std::copy(cbegin(carray), cend(carray), std::back_inserter(dest.value));
            return dest;
        }

        //template <typename TKey, typename TValue, typename TKeyArg, typename TValueArg>
        //inline auto From(const CMap<T, TArg>& carray) {
        //    auto cbegin = [](const CArray<T, TArg>& cary) {return (&cary.GetAt(0)); };
        //    auto cend = [](const CArray<T, TArg>& cary) {return (&cary.GetAt(cary.GetSize() - 1) + 1); };

        //    Enumerable<std::vector<T>> dest;
        //    dest.value.reserve(carray.GetSize());
        //    if (carray.GetSize() > 0)
        //        std::copy(cbegin(carray), cend(carray), std::back_inserter(dest.value));
        //    return dest;
        //}
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

#undef HAS_METHOD
#undef maclinq_cpp17
