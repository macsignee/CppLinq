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

    static const std::map<int, int>                   map_     = { {2,2} , {3,3}, {1,1}, {4,4}, {5,5}, {6,6}, {9,9}, {8,8}, {7, 7}, {15,5}, {13,3}, {18,8}, {12,2} };
    static const std::unordered_map<int, int>         umap_    = { {2,2} , {3,3}, {1,1}, {4,4}, {5,5}, {6,6}, {9,9}, {8,8}, {7, 7}, {15,5}, {13,3}, {18,8}, {12,2} };
    static const std::map<int, int>                   argMap   = { {99,99},{5,5},{954,954},{2,2},{1298,1298} };
    static const std::unordered_map<int,int>          argUMap  = { {99,99},{5,5},{954,954},{2,2},{1298,1298} };
    static const std::map<int, int>                   argMap2  = { {4,4},{3,3},{1,1},{2,2},{3,3},{4,4},{55,55} };
    static const std::unordered_map<int,int>          argUMap2 = { {4,4},{3,3},{1,1},{2,2},{3,3},{4,4},{55,55} };
};