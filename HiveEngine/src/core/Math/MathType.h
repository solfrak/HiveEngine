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
}