#ifndef _ROTATINGCALIPER_H
#define _ROTATINGCALIPER_H

#include <vector>
#include "Math.h"
#include "Vector2D.h"
#include "ConvexHull.h"
#include "Line2D.h"
#include "CircularIndex.h"

namespace RotatingCaliper
{
	using namespace std;
	using namespace Math;
	using namespace Vector2D;
	using namespace ConvexHull;
	using namespace Line2D;

	//计算凸包的最小面积外接长方形
	//_set为凸包顶点，推荐使用getConvexHull()函数的返回结果(或者保证凸包中的点逆时针排序,且不存在共线的点)
	//_result记录结果，四边形的四个顶点，按照逆时针排序
	// 返回值为面积，面积为负表示计算失败
	float getMinAreaBoundingRectOfConvexHull(const vector<Vec2f>& _set, vector<Vec2f>& _result)
	{
		int _size = _set.size();
		CircularIndex _edgeIndex(_size);
		CircularIndex _minAreaEdgeIndex(_size);  //记录矩形的一条边
		Vec2f _farthestPoint;    //记录离_maxAreaEdgeIndex最远的点
		Vec2f _upStreamPoint;    //记录_maxAreaEdgeIndex方向决定最大凸包宽度的上游点
		Vec2f _downStreamPoint;  //记录_maxAreaEdgeIndex方向决定最大凸包宽度的下游点
		float _minArea = FLT_MAX;

		CircularIndex _ci(_size);
		for (int i = 0; i < _size; i++)
		{
			_ci = _edgeIndex + i;

			Vec2f _fp;
			float _w = getFarthestPointToEgde(_set, _ci, _fp);

			Vec2f _up, _dp;
			float _l = getConvexHullWidth(_set, _set[_ci+1]-_set[_ci], _up, _dp);

			float _area = _w * _l;
			if (_area < _minArea)
			{
				_minArea = _area;
				_farthestPoint = _fp;
				_upStreamPoint = _up;
				_downStreamPoint = _dp;
				_minAreaEdgeIndex = _ci;
			}
		}

		Line2f _pl;
		Line2f _edge(_set[_minAreaEdgeIndex], _set[_minAreaEdgeIndex+1]);
		_edge.getParallelLine(_farthestPoint, _pl); 

		Vec2f _temp;
		_edge.getFootPoint(_downStreamPoint, _temp);
		_result.push_back(_temp);
		_pl.getFootPoint(_downStreamPoint, _temp);
		_result.push_back(_temp); 
		_pl.getFootPoint(_upStreamPoint, _temp);
		_result.push_back(_temp);
		_edge.getFootPoint(_upStreamPoint, _temp);
		_result.push_back(_temp);

		return _minArea;
	}
}

#endif
