//
// Created by samuel on 11/20/24.
//

#ifndef COLOR_H
#define COLOR_H

namespace hive
{
	struct ColorRGB
	{
		unsigned char r, g, b;
	};

	struct ColorRGBA
	{
		unsigned char r, g, b, a;
	};

#define COLOR_WHITE	 ColorRGB(255, 255, 255, 255)
#define COLOR_RED	 ColorRGB(255, 0, 0, 255)
#define COLOR_GREEN	 ColorRGB(0, 255, 0, 255)
#define COLOR_BLUE	 ColorRGB(0, 0, 255, 255)

}
#endif //COLOR_H
