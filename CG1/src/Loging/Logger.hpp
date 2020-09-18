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
	// secure the fmt var.
	// ## __VA_ARGS__ deletes the ',' if there is no args.
	#define CG_LOG_TRACE(fmt, ...)          CG::Logger::logger()->trace(fmt, ## __VA_ARGS__);
	#define CG_LOG_INFO(fmt, ...)           CG::Logger::logger()->info(fmt, ##__VA_ARGS__);
	#define CG_LOG_WARN(fmt, ...)           CG::Logger::logger()->warn(fmt, ##__VA_ARGS__);
	#define CG_LOG_ERROR(fmt, ...)          CG::Logger::logger()->error(fmt, ##__VA_ARGS__);
	#define CG_LOG_CRITICAL(fmt, ...)       CG::Logger::logger()->critical(fmt, ##__VA_ARGS__);

	#define CG_PROFILER_TRACE(fmt, ...)     CG::Logger::profiler()->trace(fmt, ##__VA_ARGS__);
	#define CG_PROFILER_INFO(fmt, ...)      CG::Logger::profiler()->info(fmt, ##__VA_ARGS__);
	#define CG_PROFILER_WARN(fmt, ...)      CG::Logger::profiler()->warn(fmt, ##__VA_ARGS__);
	#define CG_PROFILER_ERROR(fmt, ...)     CG::Logger::profiler()->error(fmt, ##__VA_ARGS__);
	#define CG_PROFILER_CRITICAL(fmt, ...)  CG::Logger::profiler()->critical(fmt, ##__VA_ARGS__);
#endif /* !DEBUG */