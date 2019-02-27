#ifndef _CONVEXHULL_H
#define _CONVEXHULL_H

#include "Math.h"
#include "Vector.h"
#include "CircularIndex.h"
#include <vector>
#include <stack>
#include <algorithm>

namespace ConvexHull
{
	using namespace std;
	using namespace Math;
	using namespace Vector;

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

	//给定凸包上的一条边，找到凸包上到此边距离最远的点
	//_set为凸包，推荐使用getConvexHull函数的返回结果，或者保证凸包中的点逆时针排序,且不存在共线的点
	//_start是线段的起点索引，终点是下一个点，_set最后一个点的下一个点是第一个点
	//_result记录结果，相同结果按照逆时针顺序以此记录
	//返回值为距离，返回值为负表示计算失败
	float getFarthestPointToEgde(const vector<Vec2f>& _set, const int _start, vector<Vec2f>& _result)
	{
		float _ret = -1;
		int _size = _set.size();
		if (_size < 3 || _start >= _size || _start < 0) return _ret;

		int _end = _start == (_size - 1) ? 0 : (_start + 1);
		Vec2f _edge = _set[_end] - _set[_start];

		int i = _start + _size / 2; //由于是逆时针排序的凸包，从_end开始逆时针判定，距离必定先增后减，取折半位置开始判定
		while (1)    
		{

		}
	}
}

#endif

