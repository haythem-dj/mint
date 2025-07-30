#pragma once

#include "mint/common/defines.hpp"

#define M_PI 3.14159265358979
#define M_2PI 6.28318530717958

namespace mnt::math
{
	MINT_API f32 cos(f32 x);
	MINT_API f32 sin(f32 x);
	MINT_API f32 tan(f32 x);

	MINT_API f32 inv_cos(f32 x);
	MINT_API f32 inv_sin(f32 x);
	MINT_API f32 inv_tan(f32 x);

	MINT_API f32 sqrt(f32 x);
}