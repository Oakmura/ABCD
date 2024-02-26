#pragma once

#include "ABCD/Core/Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace abcd
{
    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
        static Ref<spdlog::logger>& GetClientLogger() { return sClientLogger; }

    private:
        static Ref<spdlog::logger> sCoreLogger;
        static Ref<spdlog::logger> sClientLogger;
    };
}

#define AB_CORE_TRACE(...) abcd::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AB_CORE_INFO(...) abcd::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AB_CORE_WARN(...) abcd::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AB_CORE_ERROR(...) abcd::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AB_CORE_CRITICAL(...) abcd::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define AB_TRACE(...) abcd::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AB_INFO(...) abcd::Log::GetClientLogger()->info(__VA_ARGS__)
#define AB_WARN(...) abcd::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AB_ERROR(...) abcd::Log::GetClientLogger()->error(__VA_ARGS__)
#define AB_CRITICAL(...) abcd::Log::GetClientLogger()->critical(__VA_ARGS__)