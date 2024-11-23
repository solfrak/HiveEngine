#include "Core/Shape.h"
#include "Core/Color.h"
#include "Core/Vector.h"

namespace hive::gui
{
	enum class GuiRenderCommandType
	{
		Rectangle, Label
	};
	struct GuiRenderCommand
	{
		GuiRenderCommandType type;
		union
		{
			struct { Rectangle rect; ColorRGBA color;} rect;
			struct {const char* text; Vec2i position; int font_size; } label;
		};
	};
}
