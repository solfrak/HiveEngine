#pragma once

#include "hvpch.h"
#include "Core/Shape.h"
#include "Core/Color.h"
#include "Core/Vector.h"

namespace hive
{
	namespace gui
	{
		enum class GuiRenderCommandType
		{
			Rectangle, Label
		};

		struct HAPI GuiRenderCommand
		{
			GuiRenderCommandType type;

			struct
			{
				Rectangle rect;
				ColorRGBA color;
			} rect;

			struct
			{
				const char *text;
				Vec2i position;
				int font_size;
			} label;
		};

	}
}
