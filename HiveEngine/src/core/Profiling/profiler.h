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
#define HPROFILE
#ifdef HPROFILE
#define HPROFILE_BEGIN_SESSION() hive::Instrumentor::Get().BeginSession()
#define HPROFILE_END_SESSION() hive::Instrumentor::Get().EndSession()
#define HPROFILE_FUNCTION() hive::InstrumentationTimer t(__PRETTY_FUNCTION__)
#else
#define BeginSession(x)
#define EndSession()
#define OL_PROFILE_FUNCTION(x)
#endif