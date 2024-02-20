#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace abcd
{
    class AB_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return sClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> sCoreLogger;
        static std::shared_ptr<spdlog::logger> sClientLogger;
    };
}

#define AB_CORE_TRACE(...) abcd::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AB_CORE_INFO(...) abcd::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AB_CORE_WARN(...) abcd::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AB_CORE_ERROR(...) abcd::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AB_CORE_FATAL(...) abcd::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define AB_TRACE(...) abcd::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AB_INFO(...) abcd::Log::GetClientLogger()->info(__VA_ARGS__)
#define AB_WARN(...) abcd::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AB_ERROR(...) abcd::Log::GetClientLogger()->error(__VA_ARGS__)
#define AB_FATAL(...) abcd::Log::GetClientLogger()->critical(__VA_ARGS__)