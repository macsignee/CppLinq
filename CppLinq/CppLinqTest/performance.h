#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <functional>

namespace CppLinqTest
{
    using namespace std;

    namespace Performance
    {
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
            template<class TElm>
            Checker(function<void(void)>action, int times = 1, ostream& stream = std::cout) {
                stopwatch.Start();
                for (auto count = 0; count < times; count++)
                    action();
                stream << stopwatch.Lap() / times << "s." << std::endl;
            }
        };
    }
    // testdata
    struct Data {
        int intData_;
        std::string strData_;
    };
    constexpr int max_count = 1000000;
}
