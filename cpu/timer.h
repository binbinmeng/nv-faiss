
#include <ctime>  
#include <vector>  
#include <algorithm>   
#include <iomanip>
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

template <typename F>
double benchmark(const F &fun, int n = 10)
{
	    double duration = 0.0;
	    std::vector<double> timings;
        for (int i = 0; i < n; i++)
        {
		auto start = std::chrono::high_resolution_clock::now();
		fun();
		auto end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		timings.push_back(duration);
	}

		        std::sort(timings.begin(), timings.end());
			    return timings[timings.size() / 2] / 1000;
}
