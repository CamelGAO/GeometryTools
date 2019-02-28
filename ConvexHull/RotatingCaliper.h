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

	//����͹������С�����ӳ�����
	//_setΪ͹�����㣬�Ƽ�ʹ��getConvexHull()�����ķ��ؽ��(���߱�֤͹���еĵ���ʱ������,�Ҳ����ڹ��ߵĵ�)
	//_result��¼������ı��ε��ĸ����㣬������ʱ������
	// ����ֵΪ��������Ϊ����ʾ����ʧ��
	float getMinAreaBoundingRectOfConvexHull(const vector<Vec2f>& _set, vector<Vec2f>& _result)
	{
		int _size = _set.size();
		CircularIndex _edgeIndex(_size);
		CircularIndex _minAreaEdgeIndex(_size);  //��¼���ε�һ����
		Vec2f _farthestPoint;    //��¼��_maxAreaEdgeIndex��Զ�ĵ�
		Vec2f _upStreamPoint;    //��¼_maxAreaEdgeIndex����������͹����ȵ����ε�
		Vec2f _downStreamPoint;  //��¼_maxAreaEdgeIndex����������͹����ȵ����ε�
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
