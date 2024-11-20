#pragma once

#include <hvpch.h>
#include <chrono>
#include <fstream>
#include <thread>

namespace hive
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

    class HAPI Instrumentor
    {
    private:
        std::ofstream m_OutputStream;
        int m_ProfileCount;
    public:
        Instrumentor()
                : m_ProfileCount(0)
        {
        }

        void BeginSession(const std::string& filepath = "results.json");
        void EndSession();

        void WriteProfile(const ProfileResult& result);
        void WriteHeader();
        void WriteFooter();

        static Instrumentor& Get();

    };

    class HAPI InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name);


        ~InstrumentationTimer();


        void Stop();
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
    };
}

//TODO: Add feature to profile with multiple thread or categories
#ifdef _MSC_VER
#define FUNCTION_NAME __func__
#else
#define FUNCTION_NAME __PRETTY_FUNCTION__
#endif

#define HPROFILE
#ifdef HPROFILE
#define HPROFILE_BEGIN_SESSION() hive::Instrumentor::Get().BeginSession()
#define HPROFILE_END_SESSION() hive::Instrumentor::Get().EndSession()
#define HPROFILE_SCOPE(name) hive::InstrumentationTimer t(name)
#define HPROFILE_FUNCTION() HPROFILE_SCOPE(FUNCTION_NAME)
#else
#define HPROFILE_BEGIN_SESSION()
#define HPROFILE_END_SESSION()
#define HPROFILE_SCOPE(name)
#define HPROFILE_FUNCTION()
#endif

// #define HPROFILE_START EASY_PROFILER_ENABLE
// #define HPROFILE_END profiler::dumpBlocksToFile("test_profile.prof");
// #define HPROFILE_FUNCTION() EASY_FUNCTION()