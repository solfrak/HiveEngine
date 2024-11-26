#pragma once

#include "hvpch.h"
#include "GuiRenderCommand.h"
#include "Ressource/StackAllocator.h"

namespace hive
{
	namespace gui
	{
		//Can be adjusted depending on the need of the project
		const int MAX_RENDER_COMMAND = 1024;
		const int MAX_CONTAINERS = 32;

		struct Container
		{
			Rectangle rect;
		};

		class HAPI GuiContext
		{
		public:
			GuiRenderCommand renderCommand[MAX_RENDER_COMMAND] = {};
			int renderCommandCount = 0;

			std::stack<Container*> containerStack;
			std::unordered_map<size_t, int> containerMapping;
			Container containers[MAX_CONTAINERS];

		};

	}
}
