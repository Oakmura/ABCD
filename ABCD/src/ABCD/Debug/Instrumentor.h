#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>

namespace abcd 
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        std::thread::id ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    private:
        std::mutex mMutex;
        InstrumentationSession* mCurrentSession;
        std::ofstream mOutputStream;
    public:
        Instrumentor()
            : mCurrentSession(nullptr)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            std::lock_guard lock(mMutex);
            if (mCurrentSession) 
            {
                // If there is already a current session, then close it before beginning new one.
                // Subsequent profiling output meant for the original session will end up in the
                // newly opened session instead.  That's better than having badly formatted
                // profiling output.
                if (Log::GetCoreLogger()) 
                { // Edge case: BeginSession() might be before Log::Init()
                    AB_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, mCurrentSession->Name);
                }
                internalEndSession();
            }
            mOutputStream.open(filepath);
            if (mOutputStream.is_open()) 
            {
                mCurrentSession = new InstrumentationSession({ name });
                writeHeader();
            }
            else {
                if (Log::GetCoreLogger()) 
                { // Edge case: BeginSession() might be before Log::Init()
                    AB_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
                }
            }
        }

        void EndSession()
        {
            std::lock_guard lock(mMutex);
            internalEndSession();
        }

        void WriteProfile(const ProfileResult& result)
        {
            std::stringstream json;

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            json << ",{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << (result.End - result.Start) << ',';
            json << "\"name\":\"" << name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.ThreadID << ",";
            json << "\"ts\":" << result.Start;
            json << "}";

            std::lock_guard lock(mMutex);
            if (mCurrentSession) 
            {
                mOutputStream << json.str();
                mOutputStream.flush();
            }
        }

        static Instrumentor& Get() 
        {
            static Instrumentor instance;
            return instance;
        }

    private:
        void writeHeader()
        {
            mOutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
            mOutputStream.flush();
        }

        void writeFooter()
        {
            mOutputStream << "]}";
            mOutputStream.flush();
        }

        // Note: you must already own lock on mMutex before
        // calling InternalEndSession()
        void internalEndSession() 
        {
            if (mCurrentSession) 
            {
                writeFooter();
                mOutputStream.close();
                delete mCurrentSession;
                mCurrentSession = nullptr;
            }
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
            {
                Stop();
            }
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            Instrumentor::Get().WriteProfile({ mName, start, end, std::this_thread::get_id() });

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