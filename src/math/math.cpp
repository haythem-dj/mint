#include "mint/math/math.hpp"

#include <cmath>

namespace mnt::math
{
	f32 cos(f32 x)
	{
		return std::cos(M_DEG2RAD(x));
	}

	f32 sin(f32 x)
	{
		return std::sin(M_DEG2RAD(x));
	}

	f32 tan(f32 x)
	{
		return std::tan(M_DEG2RAD(x));
	}


	f32 inv_cos(f32 x)
	{
		return M_RAD2DEG(std::acos(x));
	}

	f32 inv_sin(f32 x)
	{
		return M_RAD2DEG(std::asin(x));
	}

	f32 inv_tan(f32 x)
	{
		return M_RAD2DEG(std::atan(x));
	}


	f32 sqrt(f32 x)
	{
		return std::sqrt(x);
	}

}