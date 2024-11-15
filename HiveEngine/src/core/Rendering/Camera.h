//
// Created by samuel on 11/14/24.
//

#pragma once

#include "hvpch.h"
#include "core/Math/MathType.h"
namespace hive
{

	class HAPI Camera
	{
	public:
		//Position
		Vec3 position;

		//Target
		Vec3 target;

		//Up
		Vec3 up;
	};
}