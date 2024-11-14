#include "profiler.h"

void hive::Instrumentor::BeginSession(const std::string& filepath)
{
	m_OutputStream.open(filepath);
	WriteHeader();
}

void hive::Instrumentor::EndSession()
{
	WriteFooter();
	m_OutputStream.close();
	m_ProfileCount = 0;
}

void hive::Instrumentor::WriteProfile(const ProfileResult& result)
{
	if (m_ProfileCount++ > 0)
		m_OutputStream << ",";

	std::string name = result.Name;
	std::replace(name.begin(), name.end(), '"', '\'');

	m_OutputStream << "{";
	m_OutputStream << "\"cat\":\"function\",";
	m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
	m_OutputStream << "\"name\":\"" << name << "\",";
	m_OutputStream << "\"ph\":\"X\",";
	m_OutputStream << "\"pid\":0,";
	m_OutputStream << "\"tid\":" << result.ThreadID << ",";
	m_OutputStream << "\"ts\":" << result.Start;
	m_OutputStream << "}";

	m_OutputStream.flush();
}

void hive::Instrumentor::WriteHeader()
{
	m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
	m_OutputStream.flush();
}

void hive::Instrumentor::WriteFooter()
{
	m_OutputStream << "]}";
	m_OutputStream.flush();
}

hive::Instrumentor& hive::Instrumentor::Get()
{
	static Instrumentor instance;
	return instance;
}

hive::InstrumentationTimer::InstrumentationTimer(const char* name)
	: m_Name(name), m_Stopped(false)
{
	m_StartTimepoint = std::chrono::high_resolution_clock::now();
}

hive::InstrumentationTimer::~InstrumentationTimer()
{
	if (!m_Stopped)
		Stop();
}

void hive::InstrumentationTimer::Stop()
{
	auto endTimepoint = std::chrono::high_resolution_clock::now();

	long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().
		count();
	long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

	uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
	Instrumentor::Get().WriteProfile({m_Name, start, end, threadID});

	m_Stopped = true;
}

