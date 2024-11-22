#pragma once
#include "Core/Color.h"

namespace hive
{
	class RenderCommand
	{
	public:
		static void ClearBuffer();
		static void SetClearColor(ColorRGBA color);
		static void BeginFrame();
		static void EndFrame();
	};
}




