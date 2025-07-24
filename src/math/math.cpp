#include "mint/math/math.hpp"

#include <cmath>

namespace mnt::math
{
	f32 cos(f32 x)
	{
		return std::cos(x);
	}

	f32 sin(f32 x)
	{
		return std::sin(x);
	}

	f32 tan(f32 x)
	{
		return std::tan(x);
	}


	f32 inv_cos(f32 x)
	{
		return std::acos(x);
	}

	f32 inv_sin(f32 x)
	{
		return std::asin(x);
	}

	f32 inv_tan(f32 x)
	{
		return std::atan(x);
	}


	f32 sqrt(f32 x)
	{
		return std::sqrt(x);
	}

}