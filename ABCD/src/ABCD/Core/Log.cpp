#include "abpch.h"
#include "ABCD/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace abcd
{
    Ref<spdlog::logger> Log::sCoreLogger;
    Ref<spdlog::logger> Log::sClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        sCoreLogger = spdlog::stdout_color_mt("ABCD");
        sCoreLogger->set_level(spdlog::level::trace);

        sClientLogger = spdlog::stdout_color_mt("APP");
        sClientLogger->set_level(spdlog::level::trace);
    }
}