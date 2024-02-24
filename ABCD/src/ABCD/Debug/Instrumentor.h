#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace abcd 
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    private:
        InstrumentationSession* mCurrentSession;
        std::ofstream mOutputStream;
        int mProfileCount;
    public:
        Instrumentor()
            : mCurrentSession(nullptr), mProfileCount(0)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            mOutputStream.open(filepath);
            WriteHeader();
            mCurrentSession = new InstrumentationSession{ name };
        }

        void EndSession()
        {
            WriteFooter();
            mOutputStream.close();
            delete mCurrentSession;
            mCurrentSession = nullptr;
            mProfileCount = 0;
        }

        void WriteProfile(const ProfileResult& result)
        {
            if (mProfileCount++ > 0)
            {
                mOutputStream << ",";
            }

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            mOutputStream << "{";
            mOutputStream << "\"cat\":\"function\",";
            mOutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            mOutputStream << "\"name\":\"" << name << "\",";
            mOutputStream << "\"ph\":\"X\",";
            mOutputStream << "\"pid\":0,";
            mOutputStream << "\"tid\":" << result.ThreadID << ",";
            mOutputStream << "\"ts\":" << result.Start;
            mOutputStream << "}";

            mOutputStream.flush();
        }

        void WriteHeader()
        {
            mOutputStream << "{\"otherData\": {},\"traceEvents\":[";
            mOutputStream.flush();
        }

        void WriteFooter()
        {
            mOutputStream << "]}";
            mOutputStream.flush();
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
            : mName(name), mStopped(false)
        {
            mStartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!mStopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::Get().WriteProfile({ mName, start, end, threadID });

            mStopped = true;
        }
    private:
        const char* mName;
        std::chrono::time_point<std::chrono::high_resolution_clock> mStartTimepoint;
        bool mStopped;
    };
}

#define AB_PROFILE 1
#if AB_PROFILE
    // Resolve which function signature macro will be used. Note that this only
    // is resolved when the (pre)compiler starts, so the syntax highlighting
    // could mark the wrong one in your editor!
    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
        #define AB_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(__DMC__) && (__DMC__ >= 0x810)
        #define AB_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(__FUNCSIG__)
        #define AB_FUNC_SIG __FUNCSIG__
    #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
        #define AB_FUNC_SIG __FUNCTION__
    #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
        #define AB_FUNC_SIG __FUNC__
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
        #define AB_FUNC_SIG __func__
    #elif defined(__cplusplus) && (__cplusplus >= 201103)
        #define AB_FUNC_SIG __func__
    #else
        #define AB_FUNC_SIG "AB_FUNC_SIG unknown!"
    #endif

    #define AB_PROFILE_BEGIN_SESSION(name, filepath) ::abcd::Instrumentor::Get().BeginSession(name, filepath)
    #define AB_PROFILE_END_SESSION() ::abcd::Instrumentor::Get().EndSession()
    #define AB_PROFILE_SCOPE(name) ::abcd::InstrumentationTimer timer##__LINE__(name);
    #define AB_PROFILE_FUNCTION() AB_PROFILE_SCOPE(AB_FUNC_SIG)
#else
    #define AB_PROFILE_BEGIN_SESSION(name, filepath)
    #define AB_PROFILE_END_SESSION()
    #define AB_PROFILE_SCOPE(name)
    #define AB_PROFILE_FUNCTION()
#endif