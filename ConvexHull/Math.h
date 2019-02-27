#ifndef _MATH_H
#define _MATH_H

#include <limits>
#include <cmath>

#define PI 3.1415926535897932384626433832795028841971693993751

namespace Math
{
	template<typename _T, typename _R = int>
	const _R sign(const _T& _data)
	{
		if (_data > _T(0)) return _R(1);
		if (_data < _T(0)) return _R(-1);
		return _R(0);
	}

	template<>
	const int sign(const float& _data)
	{
		if (_data > FLT_EPSILON) return 1;
		if (_data < -FLT_EPSILON) return -1;
		return 0;
	}

	template<>
	const int sign(const double& _data)
	{
		if (_data > DBL_EPSILON) return 1;
		if (_data < -DBL_EPSILON) return -1;
		return 0;
	}

}

#endif
