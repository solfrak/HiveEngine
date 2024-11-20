//
// Created by samuel on 11/14/24.
//
#pragma once

#include <hvpch.h>

namespace hive
{
	struct Vec3f
	{
		union
		{
			struct {float x, y, z;};
			struct {float r, g, b;};
		};
	};

	struct Vec2f
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

	struct Vec3i
	{
		union
		{
			struct {int x, y, z;};
			struct {int r, g, b;};
		};
	};

	struct Vec2i
	{
		union
		{
			struct {int x, y;};
			struct {int w, h;};
		};
	};



}