#ifndef MATH_HELPER_H
#define MATH_HELPER_H

namespace MathHelper
{
	#define PI 3.141592

	inline float DegressToRadians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}
}
#endif