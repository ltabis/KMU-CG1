// Breakpoint.hpp
// Breakpoint class definition.

#pragma once

#include <chrono>
#include <iostream>

namespace CG
{
	template<typename Resolution = std::chrono::milliseconds>
	class Breakpoint
	{
	public:

		Breakpoint(const std::string& name)
			: _name  { name                                      }
			, _start { std::chrono::high_resolution_clock::now() }
		{}

		~Breakpoint()
		{
			auto t = std::chrono::duration_cast<Resolution>(std::chrono::high_resolution_clock::now() - _start).count();

			std::cout << "[*] '" << _name << "' => " << t << std::endl;
		}

	private:
		std::string _name;
		std::chrono::high_resolution_clock::time_point _start;
	};
}