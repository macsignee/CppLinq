#include "CppLinq.test.h"

#include <strstream>
int main() {
	using namespace std;

	// performance test
	{
		using namespace macsignee::cppLinq::performance_test;
		strstream inout;
		Checker chk([&]() {
			}, max_count, inout);
	}
}