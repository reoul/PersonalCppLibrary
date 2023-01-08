#pragma once
#pragma warning(disable:4996)
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>

#define HIDE_LOG

namespace Logger
{

#ifndef LOGGER_FOLDER_NAME
#define LOGGER_FOLDER_NAME "Logger"
#endif

	inline void LogInit()
	{
		std::shared_ptr<spdlog::logger> consoleLogger = spdlog::stdout_color_mt("console");
	}

	inline void AddLogger(const std::string& loggerName, const std::string& fileName)
	{
		std::shared_ptr<spdlog::logger> logger = spdlog::daily_logger_mt(loggerName, LOGGER_FOLDER_NAME + fileName, 0, 0);
	}

#ifdef HIDE_LOG

	template<typename ... Arguments>
	inline void LogWrite(const std::string& loggerName, const char* format, Arguments... args)
	{}

#else

	template<typename ... Arguments>
	inline void LogWrite(const std::string& loggerName, const char* format, Arguments... args)
	{
		const auto logger = spdlog::get(loggerName);
		if (logger)
		{
			logger->info(format, args...);
			logger->flush();
		}
	}

#endif

#ifdef HIDE_LOG

	template<typename ... Arguments>
	inline void LogWriteTest(const std::string& loggerName, const char* format, Arguments... args)
	{}

#else

	template<typename ... Arguments>
	inline void LogWriteTest(const std::string& loggerName, const char* format, Arguments... args)
	{
		const auto logger = spdlog::get(loggerName);
		if (logger)
		{
			logger->info(format, args...);
			logger->flush();
		}
	}

#endif

#ifdef HIDE_LOG

	template<typename ... Arguments>
	inline void LogWriteWarning(const std::string& loggerName, const char* format, Arguments... args)
	{}

#else

	template<typename ... Arguments>
	inline void LogWriteWarning(const std::string& loggerName, const char* format, Arguments... args)
	{
		const auto logger = spdlog::get(loggerName);
		if (logger)
		{
			logger->warn(format, args...);
			logger->flush();
		}
	}

#endif

#ifdef HIDE_LOG

	template<typename ... Arguments>
	inline void LogWriteError(const std::string& loggerName, const char* format, Arguments... args)
	{}

#else

	template<typename ... Arguments>
	inline void LogWriteError(const std::string& loggerName, const char* format, Arguments... args)
	{
		const auto logger = spdlog::get(loggerName);
		if (logger)
		{
			logger->error(format, args...);
			logger->flush();
		}
	}

#endif

#ifdef HIDE_LOG

	inline bool _assertion_log_error_write(const char* message, const char* file, unsigned int line)
	{}

#else

	inline bool _assertion_log_error_write(const char* message, const char* file, unsigned int line)
	{
		LogWriteError("Assertion failed: {0}, {1}, line {2}", message, file, line);
		return false;
	}

#endif

#ifdef HIDE_LOG

	template<typename ... Arguments>
	void LogPrintf(const char* format, Arguments... args)
	{}

#else

	template<typename ... Arguments>
	void LogPrintf(const char* format, Arguments... args)
	{
		spdlog::get("console")->info(format, args...);
	}

#endif

#ifdef HIDE_LOG

	template<typename ... Arguments>
	void Log(const std::string& loggerName, const char* format, Arguments... args)
	{}

#else

	template<typename ... Arguments>
	void Log(const std::string& loggerName, const char* format, Arguments... args)
	{
		spdlog::get("console")->info(format, args...);
		LogWrite(loggerName, format, args...);
	}

#endif

	template<typename ... Arguments>
	void LogByRelease(const std::string& loggerName, const char* format, Arguments... args)
	{
		spdlog::get("console")->info(format, args...);
		const auto logger = spdlog::get(loggerName);
		if (logger)
		{
			logger->info(format, args...);
			logger->flush();
		}
	}

#ifdef HIDE_LOG

	template<typename ... Arguments>
	void LogWarning(const std::string& loggerName, const char* format, Arguments... args)
	{}

#else

	template<typename ... Arguments>
	void LogWarning(const std::string& loggerName, const char* format, Arguments... args)
	{
		spdlog::get("console")->warn(format, args...);
		LogWriteWarning(loggerName, format, args...);
	}

#endif

#ifdef HIDE_LOG

#define log_assert(expression) ((void)0)

#else
#define log_assert(expression) ((void)0)
//#define log_assert(expression) (void)(																						\
//            (!!(expression)) || _assertion_log_error_write(#expression, __FILE__, (unsigned)(__LINE__)) ||	\
//            (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0)								\
//        )

#endif

}
