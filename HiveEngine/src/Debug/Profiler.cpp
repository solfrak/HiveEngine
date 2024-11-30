//
// Created by samuel on 11/29/24.
//

#include "Profiler.h"
#include <fstream>

#include "Engine/Logger.h"
#ifdef PROFILER_ENABLED
//Define some tracing categories


std::unique_ptr<perfetto::TracingSession> g_profiler_session = nullptr;

void perfetto_log_callback(perfetto::LogMessageCallbackArgs args)
{
	switch (args.level)
	{
	case perfetto::LogLev::kLogDebug:
		break;
	case perfetto::LogLev::kLogInfo:
		break;
	case perfetto::LogLev::kLogImportant:
		break;
	case perfetto::LogLev::kLogError:
		HLOG_ERROR(args.message);
		break;
	}
}

void hive::profiler::InitPerfetto()
{
	perfetto::TracingInitArgs args;
	args.backends = perfetto::kInProcessBackend;
	args.log_message_callback = perfetto_log_callback;

	perfetto::Tracing::Initialize(args);
	perfetto::TrackEvent::Register();

	perfetto::TraceConfig cfg;
	cfg.add_buffers()->set_size_kb(1024);
	auto* ds_cfg = cfg.add_data_sources()->mutable_config();
	ds_cfg->set_name("track_event");

	g_profiler_session = perfetto::Tracing::NewTrace();

	g_profiler_session->Setup(cfg);
	g_profiler_session->StartBlocking();

	perfetto::ProcessTrack process_track = perfetto::ProcessTrack::Current();
	perfetto::protos::gen::TrackDescriptor desc = process_track.Serialize();
	desc.mutable_process()->set_process_name("HiveEngine");
	perfetto::TrackEvent::SetTrackDescriptor(process_track, desc);
}

void hive::profiler::EndPerfetto()
{
	perfetto::TrackEvent::Flush();

	g_profiler_session->StopBlocking();
	std::vector<char> trace_data(g_profiler_session->ReadTraceBlocking());

	std::ofstream output;
	output.open("HiveEngineTrace.pftrace", std::ios::out | std::ios::binary);
	output.write(&trace_data[0], std::streamsize(trace_data.size()));
	output.close();
}


#endif

PERFETTO_TRACK_EVENT_STATIC_STORAGE();

