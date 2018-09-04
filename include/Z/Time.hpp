#pragma once
#include <chrono>

namespace Z {
	using namespace std;
	using namespace chrono;

	static time_point<steady_clock, milliseconds> StartTime = time_point_cast<milliseconds>(steady_clock::now());

	template <typename T >
	T GetDeltaTime() {
		time_point<steady_clock, milliseconds> now = time_point_cast<milliseconds>(steady_clock::now());
		duration<T, ratio<1, 1000> > d = duration_cast<milliseconds>(now - StartTime);
		return d.count();
	}

}