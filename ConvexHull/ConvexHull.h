#ifndef _CONVEXHULL_H
#define _CONVEXHULL_H

#include "Math.h"
#include "Vector2D.h"
#include "CircularIndex.h"
#include <vector>
#include <stack>
#include <algorithm>

namespace ConvexHull
{
	using namespace std;
	using namespace Math;
	using namespace Vector2D;

	class Vec2fYLess
	{
	public:
		bool operator() (const Vec2f& _a, const Vec2f& _b)
		{
			if (_a[1] < _b[1]) return true;
			if (_a[1] == _b[1] && _a[0] < _b[0]) return true;
			return false;
		}
	};

	class Vec2fSlantAngleLess
	{
	public:
		Vec2fSlantAngleLess(const Vec2f& _p) { _vec = _p; }
		bool operator() (const Vec2f& _a, const Vec2f& _b)
		{
			Vec2f temp1 = _a - _vec;
			Vec2f temp2 = _b - _vec;

			float _sa1 = getCosSlantAngle(temp1);
			float _sa2 = getCosSlantAngle(temp2);

			if (_sa1 > _sa2) return true;
			if (abs(_sa1 - _sa2) < FLT_EPSILON  && temp1.lengthSq() < temp2.lengthSq()) return true;
			return false;
		}
	private:
		Vec2f _vec;
	};

	void findMinY(vector<Vec2f>& _data)  //把最小y值的向量放在容器的第一个位置
	{
		if (_data.size() < 2) return;

		vector<Vec2f>::iterator _itb = _data.begin();
		vector<Vec2f>::iterator _it = min_element(_data.begin(), _data.end(), Vec2fYLess());

		if (_itb == _it) return;
		
		Vec2f _temp = *_itb;
		*_itb = *_it;
		*_it = _temp;
	}

	void sortBySlantAngle(vector<Vec2f>& _data) //将容器中第二到末尾的所有元素按照各自与第一个元素连线的倾斜角排序
	{
		if (_data.size() < 3) return;
		sort(_data.begin() + 1, _data.end(), Vec2fSlantAngleLess(_data[0]));
	}

	bool isNotAtRight(const Vec2f& _vec1, const Vec2f& _vec2)  //判断_vec2是否不在_vec1的右侧
	{
		float _c = _vec1.cross(_vec2);

		if (sign(_c) < 0) return false;
		return true;
	}

	bool isAtLeft(const Vec2f& _vec1, const Vec2f& _vec2)  //判断_vec2是否在_vec1的左侧
	{
		float _c = _vec1.cross(_vec2);

		if (sign(_c) <= 0) return false;
		return true;
	}

	void removeDuplicate(const vector<Vec2f>& _data, vector<Vec2f>& _result)
	{
		for (vector<Vec2f>::const_iterator it = _data.begin(); it != _data.end(); it++)
		{
			if (find(_result.begin(), _result.end(), *it) == _result.end())
			{
				_result.push_back(*it);
			}
		}
	}


	void getConvexHull(const vector<Vec2f>& _data, vector<Vec2f>& _result)  //输出结果为从最小y值点开始到最后一个点的逆时针排序，输入数据支持重复点，输出结果不会包含两点共线的情况
	{
		vector<Vec2f> _point;

		removeDuplicate(_data, _point);
		if (_point.size() < 3) return;
		findMinY(_point);
		sortBySlantAngle(_point);

		vector<Vec2f> _s;
		_s.push_back(_point[0]);
		_s.push_back(_point[1]);
		Vec2f _temp = _point.back();
		vector<Vec2f>::iterator _it = _point.begin()+2;
		while (_it != _point.end())
		{
			Vec2f _vec2 = *(_s.rbegin() + 1);
			Vec2f _vec1 = *_s.rbegin() - _vec2;
			_vec2 = *_it - _vec2;

			if (isAtLeft(_vec1, _vec2))   //使用isAtLeft时凸包上不会出现共线情况，使用isNotAtRight会出现共线情况
			{
				_s.push_back(*_it);
				_it++;
			}
			else
			{
				_s.pop_back();
			}
		}

		_result = _s;
	}

	//给定凸包上的一条边，找到凸包上到此边距离最远的点，这个距离是垂直距离
	//_set为凸包，推荐使用getConvexHull函数的返回结果(或者保证凸包中的点逆时针排序,且不存在共线的点)
	//_start是线段的起点索引，终点是下一个点，_set最后一个点的下一个点是第一个点
	//_result记录结果，相同结果按照逆时针顺序以此记录, 最多输出两个结果
	//返回值为距离，返回值为负表示计算失败
	float getFarthestPointToEgde(const vector<Vec2f>& _set, const int _start, vector<Vec2f>& _result)
	{
		float _ret = -1;
		int _size = _set.size();
		if (_size < 3 || _start >= _size || _start < 0) return _ret;

		CircularIndex _edgeStartIndex(_size, 0, _start);
		Vec2f _edgeStartPoint = _set[_edgeStartIndex];
		Vec2f _edgeVector = _set[_edgeStartIndex + 1] - _edgeStartPoint;

		int _direction = 1; //1为逆时针移动  -1为顺时针移动 ，首先逆时针运动
		bool _equalFlag = false;
		CircularIndex _ci(_size, 0, _size / 2); //由于是逆时针排序的凸包，从_end开始逆时针判定，距离必定先增后减，取折半位置开始判定
		while (1)
		{
			Vec2f _currentPoint(_set[_ci]);
			Vec2f _nextPoint(_set[_ci + _direction]);

			float _currentArea = abs(_edgeVector.cross(_currentPoint - _edgeStartPoint));
			float _nextArea = abs(_edgeVector.cross(_nextPoint - _edgeStartPoint));

			int _sign = sign(_nextArea - _currentArea);

			if (_sign > 0)   //不管什么方向，发现面积上升，继续运动
			{
				_ci += _direction;
				continue;
			}
			if (_sign < 0)
			{
				if (_direction == 1)   //逆时针发现面积下降，换方向
				{
					_direction = -1;
					continue;
				}
				break;     //顺时针发现面积下降，结束，输出当前顶点
			}
			_equalFlag = true; //面积相等，结束，需要输出当前顶点和运动方向上的下一个顶点
			break;
		}

		if (!_equalFlag)
		{
			_result.push_back(_set[_ci]);
		}
		else if (_direction == 1)
		{
			_result.push_back(_set[_ci]);
			_result.push_back(_set[_ci + 1]);
		}
		else
		{
			_result.push_back(_set[_ci - 1]);
			_result.push_back(_set[_ci]);
		}

		_ret = abs(_edgeVector.cross(_set[_ci] - _edgeStartPoint)) / _edgeVector.length();

		return _ret;
	}

	//给定凸包上的一条边，找到凸包在给定方向上的宽度
	//_set为凸包，推荐使用getConvexHull函数的返回结果(或者保证凸包中的点逆时针排序,且不存在共线的点)
	//_vec表示方向
	//返回值为宽度，宽度为负表示计算失败
	float getConvexHullWidthInDirection(const vector<Vec2f>& _set, const Vec2f& _vec)
	{
		float _ret = -1;
		int _size = _set.size();
		if (_size < 3) return _ret;

		vector<float> _dotResult;
		for (vector<Vec2f>::const_iterator it = _set.begin(); it != _set.end(); it++)
		{
			float _dot = (*it).dot(_vec);
			_dotResult.push_back(_dot);
		}

		float _minDot = *min_element(_dotResult.begin(), _dotResult.end());
		float _maxDot = *max_element(_dotResult.begin(), _dotResult.end());

		_ret = (_maxDot - _minDot) / _vec.length();
		return _ret;
	}
}

#endif

