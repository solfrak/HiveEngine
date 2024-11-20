//
// Created by samuel on 11/14/24.
//
#pragma once

#include "hvpch.h"
namespace hive
{
	struct Vec3
	{
		union
		{
			struct {float x, y, z;};
			struct {float r, g, b;};
		};
	};

	struct Vec2
	{
		union
		{
			struct
			{
				float x, y;
			};

			struct
			{
				float w, h;
			};
		};
	};

	struct Color4
	{
		struct
		{
			unsigned char r, g, b, a;
		};
	};
	struct Rectangle
	{
		Vec2 position;
		Vec2 size;
	};
}