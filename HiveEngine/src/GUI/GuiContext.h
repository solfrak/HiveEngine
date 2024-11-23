#pragma once
#include "hvpch.h"
#include "GuiRenderCommand.h"

namespace hive::gui
{
	struct HAPI GuiContext
	{
		//Can be adjusted depending on the need of the project
		GuiRenderCommand renderCommand[1024];
		int renderCommandCount;
	};
}
