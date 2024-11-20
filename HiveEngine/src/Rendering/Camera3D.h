//
// Created by samuel on 11/14/24.
//

#pragma once

#include "hvpch.h"
#include <Core/Vector.h>
namespace hive
{

	class HAPI Camera3D
	{
	public:
		//Position
		Vec3f position;

		//Target
		Vec3f target;

		//Up
		Vec3f up;
	};
}