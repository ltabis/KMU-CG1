// Breakpoint.hpp
// Breakpoint class definition.

#pragma once

#include <chrono>
#include <iostream>
#include "Logger.hpp"

namespace CG
{
	template<typename TimeResolution>
	class Breakpoint
	{
	public:

		Breakpoint(const std::string& name, const std::string &timeUnit)
			: _name     { name                                      }
			, _timeUnit { timeUnit                                  }
			, _start    { std::chrono::high_resolution_clock::now() }
		{
			CG_PROFILER_CRITICAL("breakpoint '{}' starting.", _name);
		}

		~Breakpoint()
		{
			auto t = std::chrono::duration_cast<TimeResolution>(std::chrono::high_resolution_clock::now() - _start).count();

			CG_PROFILER_CRITICAL("breakpoint '{}' done. Time: {}{}.", _name, t, _timeUnit);
		}

	private:
		std::string _name;
		std::string _timeUnit;
		std::chrono::high_resolution_clock::time_point _start;
	};
}