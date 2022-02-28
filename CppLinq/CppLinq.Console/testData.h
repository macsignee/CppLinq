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
    static const std::vector<int>                     vec_  { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::list<int>                       list_ { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::array<int, arraySize>           ary_  { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::forward_list<int>               flist_{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::deque<int>                      deq_  { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::set<int>                        set_  { 2, 3, 1, 4, 5, 6, 9, 8, 7 };
    static const std::unordered_set<int>              uset_ { 2, 3, 1, 4, 5, 6, 9, 8, 7 };
    static const std::multiset<int>                   mset_ { 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };
    static const std::unordered_multiset<int>         umset_{ 2, 3, 1, 4, 5, 6, 9, 8, 7, 5, 3, 8, 2 };

    static const std::vector<int>                     argVec  { 99,5,954,2,1298 };
    static const std::list<int>                       argLst  { 99,5,954,2,1298 };
    static const std::forward_list<int>               argFlst { 99,5,954,2,1298 };
    static const std::deque<int>                      argDqu  { 99,5,954,2,1298 };
    static const std::array<int, 5>                   argAry  { 99,5,954,2,1298 };
    static const std::set<int>                        argSet  { 99,5,954,2,1298 };
    static const std::unordered_set<int>              argUSet { 99,5,954,2,1298 };
    static const std::multiset<int>                   argMset { 99,5,954,2,1298 };
    static const std::unordered_multiset<int>         argUMset{ 99,5,954,2,1298 };

    static const std::vector<int>                     argVec2  { 4,3,1,2,3,4,55 };
    static const std::list<int>                       argLst2  { 4,3,1,2,3,4,55 };
    static const std::forward_list<int>               argFlst2 { 4,3,1,2,3,4,55 };
    static const std::deque<int>                      argDqu2  { 4,3,1,2,3,4,55 };
    static const std::array<int, 7>                   argAry2  { 4,3,1,2,3,4,55 };
    static const std::set<int>                        argSet2  { 1,2,3,4,55 };
    static const std::unordered_set<int>              argUSet2 { 1,2,3,4,55 };
    static const std::multiset<int>                   argMset2 { 4,3,1,2,3,4,55 };
    static const std::unordered_multiset<int>         argUMset2{ 4,3,1,2,3,4,55 };

    static const std::map<int, int>                   map_     { {2,2} , {3,3}, {1,1}, {4,4}, {5,5}, {6,6}, {9,9}, {8,8}, {7, 7}, {15,5}, {13,3}, {18,8}, {12,2} };
    static const std::unordered_map<int, int>         umap_    { {2,2} , {3,3}, {1,1}, {4,4}, {5,5}, {6,6}, {9,9}, {8,8}, {7, 7}, {15,5}, {13,3}, {18,8}, {12,2} };
    static const std::map<int, int>                   argMap   { {99,99},{5,5},{954,954},{2,2},{1298,1298} };
    static const std::unordered_map<int,int>          argUMap  { {99,99},{5,5},{954,954},{2,2},{1298,1298} };
    static const std::map<int, int>                   argMap2  { {4,4},{3,3},{1,1},{2,2},{3,3},{4,4},{55,55} };
    static const std::unordered_map<int,int>          argUMap2 { {4,4},{3,3},{1,1},{2,2},{3,3},{4,4},{55,55} };

    using pair_t = std::pair<const int, int>;
    static const std::vector<pair_t>             argVecKV  { std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };
    static const std::list<pair_t>               argLstKV  { std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };
    static const std::forward_list<pair_t>       argFlstKV { std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };
    static const std::deque<pair_t>              argDquKV  { std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };
    static const std::array<pair_t, 5>           argAryKV  { std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };
    static const std::set<pair_t>                argSetKV  { std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };
    //static const std::unordered_set<pair_t>      argUSetKV { std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };
    static const std::multiset<pair_t>           argMsetKV { std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };
    //static const std::unordered_multiset<pair_t> argUMsetKV{ std::make_pair(99,3) ,std::make_pair(5,102),std::make_pair(954,15),std::make_pair(2,44),std::make_pair(1298,87) };

    static const std::vector<pair_t>                     argVec2KV  { std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
    static const std::list<pair_t>                       argLst2KV  { std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
    static const std::forward_list<pair_t>               argFlst2KV { std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
    static const std::deque<pair_t>                      argDqu2KV  { std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
    static const std::array<pair_t, 7>                   argAry2KV  { std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
    static const std::set<pair_t>                        argSet2KV  { std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
    //static const std::unordered_set<pair_t>              argUSet2KV { std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
    static const std::multiset<pair_t>                   argMset2KV { std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
    //static const std::unordered_multiset<pair_t>         argUMset2KV{ std::make_pair(4,32),std::make_pair(3,85),std::make_pair(1,104),std::make_pair(2,22),std::make_pair(3,11),std::make_pair(4,1024),std::make_pair(55,32) };
};