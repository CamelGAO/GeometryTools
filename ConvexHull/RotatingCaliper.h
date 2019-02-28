#ifndef _ROTATINGCALIPER_H
#define _ROTATINGCALIPER_H

#include <vector>
#include "Math.h"
#include "Vector2D.h"
#include "ConvexHull.h"

namespace RotatingCaliper
{
	using namespace std;
	using namespace Math;
	using namespace Vector2D;
	using namespace ConvexHull;

	//计算凸包的最小面积外接长方形
	//_set为凸包顶点，推荐使用getConvexHull()函数的返回结果(或者保证凸包中的点逆时针排序,且不存在共线的点)
	//_result记录结果，四边形的四个顶点，y值最小且x值最小的点是第一个，随后按照逆时针排序
	// 返回值为面积，面积为负表示计算失败
	float getMinAreaBoundingRectOfConvexHull(const vector<Vec2f>& _set, vector<Vec2f>& _result)
	{

	}
}

#endif
