#include "performance.h"

#include <strstream>
int main() {
	using namespace std;
	strstream inout;
	CppLinqTest::Performance::Checker chk([&]() {
        }, CppLinqTest::max_count, inout);
}