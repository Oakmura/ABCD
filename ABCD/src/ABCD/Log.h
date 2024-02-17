#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace abcd
{
    class AB_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define AB_CORE_TRACE(...) abcd::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AB_CORE_INFO(...) abcd::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AB_CORE_WARN(...) abcd::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AB_CORE_ERROR(...) abcd::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AB_CORE_FATAL(...) abcd::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define AB_TRACE(...) abcd::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AB_INFO(...) abcd::Log::GetClientLogger()->info(__VA_ARGS__)
#define AB_WARN(...) abcd::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AB_ERROR(...) abcd::Log::GetClientLogger()->error(__VA_ARGS__)
#define AB_FATAL(...) abcd::Log::GetClientLogger()->fatal(__VA_ARGS__)