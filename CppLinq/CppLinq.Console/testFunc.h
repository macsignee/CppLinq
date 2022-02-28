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
#include "testData.h"

#include "test_distinct.h"
#include "test_reverse.h"
#include "test_skip.h"
#include "test_take.h"
#include "test_where.h"
#include "test_orderBy.h"
#include "test_select.h"
#include "test_countAnyAll.h"
#include "test_except.h"
#include "test_contains.h"
#include "test_first.h"
#include "test_last.h"
#include "test_elementAt.h"
#include "test_single.h"
#include "test_concat.h"
#include "test_intersect.h"
#include "test_union.h"
#include "test_join.h"
#include "test_zip.h"
#include "test_toCollection.h"

//// https://stackoverflow.com/questions/38199641/template-specialization-on-stdvectort

namespace simple_test
{
    using namespace macsignee::cppLinq;
    using namespace macsignee::cppLinq::container_test;

    template <typename TContainer>
    inline void RunTestSequenceEqual(TContainer& cont, std::string label, container_type target) {

        return; //not impllemented
        std::cout << "sequence all " << std::endl;
        //auto n_1 = From(cont).SequenceEqual(From(deq_));
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: break; //assert(checkBool(From(cont).SequenceEqual(From(set_)), true)); break;
        case container_type::multi      :
        case container_type::hash_multi :  break; //assert(checkBool(From(cont).SequenceEqual(From(mset_)), true)); break;
        case container_type::sequence   :
        case container_type::array      :
        default                         : assert(checkBool(From(cont).SequenceEqual(From(deq_)), true)); break;
        }

        std::cout << "sequence all " << std::endl;
        auto n_2 = From(cont).SequenceEqual(From(set_));
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : break; //assert(checkBool(From(cont).SequenceEqual(From(deq_)), false)); break;;
        case container_type::hash_multi :
        case container_type::multi      : break; //assert(checkBool(From(cont).SequenceEqual(From(deq_)), false)); break;;
        case container_type::sequence   :
        case container_type::array      :
        default                         : assert(checkBool(n_2, false)); break;
        }

    }

    template <typename TContainer>
    inline void RunTestSequenceEqualKV(TContainer& cont, std::string label, container_type target) {
#if FALSE
        return; //not impllemented
        std::cout << "sequence all " << std::endl;
        //auto n_1 = From(cont).SequenceEqual(From(deq_));
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::unique     :
        case container_type::hash_unique: break; //assert(checkBool(From(cont).SequenceEqual(From(set_)), true)); break;
        case container_type::multi      :
        case container_type::hash_multi :  break; //assert(checkBool(From(cont).SequenceEqual(From(mset_)), true)); break;
        case container_type::sequence   :
        case container_type::array      :
        default                         : assert(checkBool(From(cont).SequenceEqual(From(deq_)), true)); break;
        }

        std::cout << "sequence all " << std::endl;
        auto n_2 = From(cont).SequenceEqual(From(set_));
        switch (target) {
        case container_type::keyValue   :
        case container_type::multi_kv   :
        case container_type::hash_kv    :
        case container_type::hash_mul_kv: assert(false);  break;
        case container_type::hash_unique:
        case container_type::unique     : break; //assert(checkBool(From(cont).SequenceEqual(From(deq_)), false)); break;;
        case container_type::hash_multi :
        case container_type::multi      : break; //assert(checkBool(From(cont).SequenceEqual(From(deq_)), false)); break;;
        case container_type::sequence   :
        case container_type::array      :
        default                         : assert(checkBool(n_2, false)); break;
        }
#endif
    }
    template <typename TContainer>
    inline void RunTest(TContainer& cont, std::string label, container_type target) {
        RunWhereTest(cont, label, target);
        RunTestSkip(cont, label, target);
        RunTestTake(cont, label, target);
        //RunTestOrderBy(cont, label, target);
        RunTestSelect(cont, label, target);
        RunTestContains(cont, label, target);
        RunTestCount(cont, label, target);
        RunTestAny(cont, label, target);
        RunTestAll(cont, label, target);
        RunTestFirst(cont, label, target);
        RunTestLast(cont, label, target);
        RunTestSingle(cont, label, target);
        RunTestElementAt(cont, label, target);
        RunTestReverse(cont, label, target);
        RunTestDistinct(cont, label, target);
        RunTestConcat(cont, label, target);
        RunTestUnion(cont, label, target);
        RunTestIntersect(cont, label, target);
        RunTestExcept(cont, label, target);
        RunTestZip(cont, label, target);
        RunTestJoin(cont, label, target);
        //RunTestSequenceEqual(cont, label, target);
        RunTestToCollection(cont, label, target);
    }

    template <typename TContainer>
    inline void RunTestKV(TContainer& cont, std::string label, container_type target) {
        RunWhereTestKV(cont, label, target);
        RunTestSkipKV(cont, label, target);
        RunTestTakeKV(cont, label, target);
        //RunTestOrderByKV(cont, label, target);
        RunTestSelectKV(cont, label, target);
        RunTestContainsKV(cont, label, target);
        RunTestCountKV(cont, label, target);
        RunTestAnyKV(cont, label, target);
        RunTestAllKV(cont, label, target);
        RunTestFirstKV(cont, label, target);
        RunTestLastKV(cont, label, target);
        RunTestSingleKV(cont, label, target);
        RunTestElementAtKV(cont, label, target);
        RunTestReverseKV(cont, label, target);
        //RunTestDistinctKV(cont, label, target);
        //RunTestConcatKV(cont, label, target);
        //RunTestUnionKV(cont, label, target);
        //RunTestIntersectKV(cont, label, target);
        //RunTestExceptKV(cont, label, target);
        //RunTestZipKV(cont, label, target);
        //RunTestJoinKV(cont, label, target);
        //RunTestSequenceEqualKV(cont, label, target);
        RunTestToCollectionKV(cont, label, target);
    }
}
