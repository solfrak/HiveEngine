#pragma once
#include <hvpch.h>

#include "RenderTexture.h"
#include "Core/Color.h"

namespace hive
{
	class HAPI RenderCommand
	{
	public:
		static void ClearBuffer();
		static void SetClearColor(ColorRGBA color);
		static void BeginFrame();
		static void EndFrame();

		static void BeginRenderTexture(RenderTexture render_texture);
		static void EndRenderTexture();
	};
}




