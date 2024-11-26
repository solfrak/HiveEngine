#pragma once

#include "hvpch.h"
#include "GuiRenderCommand.h"

namespace hive
{
	namespace gui
	{
		struct Container
		{
			Rectangle rect;
		};

		class HAPI GuiContext
		{
		public:
			//Can be adjusted depending on the need of the project
			GuiRenderCommand renderCommand[1024] = {};
			int renderCommandCount = 0;


			std::stack<Container *> containerStack;
			std::unordered_map<int, Container> containerPool;
		};

	}
}
