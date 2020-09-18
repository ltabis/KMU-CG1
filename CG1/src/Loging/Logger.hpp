#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace CG {
	class Logger
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& profiler() { return _profiler; };
		inline static std::shared_ptr<spdlog::logger>& logger() { return _logger; };
	private:
		static std::shared_ptr<spdlog::logger> _profiler;
		static std::shared_ptr<spdlog::logger> _logger;
	};
};

#ifdef _DEBUG
	#define CG_LOG_TRACE(...)          CG::Logger::logger()->trace(__VA_ARGS__);
	#define CG_LOG_INFO(...)           CG::Logger::logger()->info(__VA_ARGS__);
	#define CG_LOG_WARN(...)           CG::Logger::logger()->warn(__VA_ARGS__);
	#define CG_LOG_ERROR(...)          CG::Logger::logger()->error(__VA_ARGS__);
	#define CG_LOG_CRITICAL(...)       CG::Logger::logger()->critical(__VA_ARGS__);

	#define CG_PROFILER_TRACE(...)     CG::Logger::profiler()->trace(__VA_ARGS__);
	#define CG_PROFILER_INFO(...)      CG::Logger::profiler()->info(__VA_ARGS__);
	#define CG_PROFILER_WARN(...)      CG::Logger::profiler()->warn(__VA_ARGS__);
	#define CG_PROFILER_ERROR(...)     CG::Logger::profiler()->error(__VA_ARGS__);
	#define CG_PROFILER_CRITICAL(...)  CG::Logger::profiler()->critical(__VA_ARGS__);
#endif /* !DEBUG */