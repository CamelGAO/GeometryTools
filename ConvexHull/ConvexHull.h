#ifndef _CONVEXHULL_H
#define _CONVEXHULL_H

#include "Math.h"
#include "Vector2D.h"
#include "CircularIndex.h"
#include "Line2D.h"
#include <vector>
#include <stack>
#include <algorithm>

namespace ConvexHull
{
	using namespace std;
	using namespace Math;
	using namespace Vector2D;
	using namespace Line2D;

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

	void findMinY(vector<Vec2f>& _data)  //����Сyֵ���������������ĵ�һ��λ��
	{
		if (_data.size() < 2) return;

		vector<Vec2f>::iterator _itb = _data.begin();
		vector<Vec2f>::iterator _it = min_element(_data.begin(), _data.end(), Vec2fYLess());

		if (_itb == _it) return;
		
		Vec2f _temp = *_itb;
		*_itb = *_it;
		*_it = _temp;
	}

	void sortBySlantAngle(vector<Vec2f>& _data) //�������еڶ���ĩβ������Ԫ�ذ��ո������һ��Ԫ�����ߵ���б������
	{
		if (_data.size() < 3) return;
		sort(_data.begin() + 1, _data.end(), Vec2fSlantAngleLess(_data[0]));
	}

	bool isNotAtRight(const Vec2f& _vec1, const Vec2f& _vec2)  //�ж�_vec2�Ƿ���_vec1���Ҳ�
	{
		float _c = _vec1.cross(_vec2);

		if (sign(_c) < 0) return false;
		return true;
	}

	bool isAtLeft(const Vec2f& _vec1, const Vec2f& _vec2)  //�ж�_vec2�Ƿ���_vec1�����
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


	void getConvexHull(const vector<Vec2f>& _data, vector<Vec2f>& _result)  //������Ϊ����Сyֵ�㿪ʼ�����һ�������ʱ��������������֧���ظ��㣬����������������㹲�ߵ����
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

			if (isAtLeft(_vec1, _vec2))   //ʹ��isAtLeftʱ͹���ϲ�����ֹ��������ʹ��isNotAtRight����ֹ������
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

	//����͹���ϵ�һ���ߣ��ҵ�͹���ϵ��˱߾�����Զ�ĵ㣬��������Ǵ�ֱ����
	//_setΪ͹�����Ƽ�ʹ��getConvexHull�����ķ��ؽ��(���߱�֤͹���еĵ���ʱ������,�Ҳ����ڹ��ߵĵ�)
	//_start���߶ε�����������յ�����һ���㣬_set���һ�������һ�����ǵ�һ����
	//_result��¼�������ͬ���������ʱ��˳���Դ˼�¼, �������������
	//����ֵΪ���룬����ֵΪ����ʾ����ʧ��
	float getFarthestPointToEgde(const vector<Vec2f>& _set, const int _start, vector<Vec2f>& _result)
	{
		float _ret = -1;
		int _size = _set.size();
		if (_size < 3 || _start >= _size || _start < 0) return _ret;

		CircularIndex _edgeStartIndex(_size, 0, _start);
		Vec2f _edgeStartPoint = _set[_edgeStartIndex];
		Vec2f _edgeVector = _set[_edgeStartIndex + 1] - _edgeStartPoint;

		int _direction = 1; //1Ϊ��ʱ���ƶ�  -1Ϊ˳ʱ���ƶ� ��������ʱ���˶�
		bool _equalFlag = false;
		CircularIndex _ci(_size, 0, _size / 2); //��������ʱ�������͹������_end��ʼ��ʱ���ж�������ض����������ȡ�۰�λ�ÿ�ʼ�ж�
		while (1)
		{
			Vec2f _currentPoint(_set[_ci]);
			Vec2f _nextPoint(_set[_ci + _direction]);

			float _currentArea = abs(_edgeVector.cross(_currentPoint - _edgeStartPoint));
			float _nextArea = abs(_edgeVector.cross(_nextPoint - _edgeStartPoint));

			int _sign = sign(_nextArea - _currentArea);

			if (_sign > 0)   //����ʲô���򣬷�����������������˶�
			{
				_ci += _direction;
				continue;
			}
			if (_sign < 0)
			{
				if (_direction == 1)   //��ʱ�뷢������½���������
				{
					_direction = -1;
					continue;
				}
				break;     //˳ʱ�뷢������½��������������ǰ����
			}
			_equalFlag = true; //�����ȣ���������Ҫ�����ǰ������˶������ϵ���һ������
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

	float getFarthestPointToEgde(const vector<Vec2f>& _set, const int _start, Vec2f& _result)
	{
		float _ret = -1;
		int _size = _set.size();
		if (_size < 3 || _start >= _size || _start < 0) return _ret;

		CircularIndex _edgeStartIndex(_size, 0, _start);
		Vec2f _edgeStartPoint = _set[_edgeStartIndex];
		Vec2f _edgeVector = _set[_edgeStartIndex + 1] - _edgeStartPoint;

		int _direction = 1; //1Ϊ��ʱ���ƶ�  -1Ϊ˳ʱ���ƶ� ��������ʱ���˶�
		CircularIndex _ci(_size, 0, _size / 2 + _start); //��������ʱ�������͹������_end��ʼ��ʱ���ж�������ض����������ȡ�۰�λ�ÿ�ʼ�ж�
		while (1)
		{
			Vec2f _currentPoint(_set[_ci]);
			Vec2f _nextPoint(_set[_ci + _direction]);

			float _currentArea = abs(_edgeVector.cross(_currentPoint - _edgeStartPoint));
			float _nextArea = abs(_edgeVector.cross(_nextPoint - _edgeStartPoint));

			int _sign = sign(_nextArea - _currentArea);

			if (_sign > 0)   //����ʲô���򣬷�����������������˶�
			{
				_ci += _direction;
				continue;
			}
			if (_sign < 0)
			{
				if (_direction == 1)   //��ʱ�뷢������½���������
				{
					_direction = -1;
					continue;
				}
				break;     //˳ʱ�뷢������½��������������ǰ����
			}
			break;
		}

		_result = _set[_ci];

		_ret = abs(_edgeVector.cross(_set[_ci] - _edgeStartPoint)) / _edgeVector.length();
		return _ret;
	}

	//����͹���ϵ�һ���ߣ��ҵ�͹���ڸ��������ϵĿ��
	//_setΪ͹�����Ƽ�ʹ��getConvexHull�����ķ��ؽ��(���߱�֤͹���еĵ���ʱ������,�Ҳ����ڹ��ߵĵ�)
	//_vec��ʾ����,���ڼ���˷����ϵĿ��
	//����ֵΪ��ȣ����Ϊ����ʾ����ʧ��
	float getConvexHullWidth(const vector<Vec2f>& _set, const Vec2f& _vec)
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

	//����͹���ϵ�һ���ߣ��ҵ�͹���ڸ��������ϵĿ��
	//_setΪ͹�����Ƽ�ʹ��getConvexHull�����ķ��ؽ��(���߱�֤͹���еĵ���ʱ������,�Ҳ����ڹ��ߵĵ�)
	//_vec��ʾ����,���ڼ���˷����ϵĿ��
	//_upStreamPoint��_downStreamPoint�ֱ��¼�ڸ����������εľ���������εľ����㡣���ܲ�Ψһ�������ᳬ���������˴�ֻ��¼һ����
	//����ֵΪ��ȣ����Ϊ����ʾ����ʧ��
	float getConvexHullWidth(const vector<Vec2f>& _set, const Vec2f& _vec, Vec2f& _upStreamPoint, Vec2f& _downStreamPoint)
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

		vector<float>::iterator _minDotIterator = min_element(_dotResult.begin(), _dotResult.end());
		vector<float>::iterator _maxDotIterator = max_element(_dotResult.begin(), _dotResult.end());

		_upStreamPoint = _set[_minDotIterator - _dotResult.begin()];
		_downStreamPoint = _set[_maxDotIterator - _dotResult.begin()];

		float _minDot = *_minDotIterator;
		float _maxDot = *_maxDotIterator;
		_ret = (_maxDot - _minDot) / _vec.length();
		return _ret;
	}

	//����͹����������ȷ����ֱ�ߣ��ж�ֱ����͹���Ƿ��ཻ
	//_setΪ͹�����Ƽ�ʹ��getConvexHull�����ķ��ؽ��(���߱�֤͹���еĵ���ʱ������,�Ҳ����ڹ��ߵĵ�)
	//_point1, _point2�Ǿ���ֱ�ߵ�������
	//_intersections�ǽ��㣬�����������������������ʱ�����ȼ�¼���Ǵ�_point1ָ��_point2���������δ��Ľ��㡣����һ�����غ�ʱ��ֻ��¼��ߵ������˵�
	//����true�ཻ��false���ཻ��
	bool getConvexHullIntersectWithLine(const vector<Vec2f>& _set, const Vec2f& _point1, const Vec2f& _point2, vector<Vec2f>& _intersections)
	{
		int _size = _set.size();
		if (_size < 3 || _point1 == _point2)  return false;

		Vec2f _vec = _point2 - _point1;
		Line2f _line(_point1, _point2);
		vector<float > _cross;

		for (int i = 0; i < _size; i++)
		{
			Vec2f _temp = _set[i] - _point1;
			_cross.push_back(_vec.cross(_temp));
		}

		vector<Vec2f> _tempPoints;
		CircularIndex _ci(_size);
		for (int i = 0; i < _size; i++, _ci++)
		{
			int _currentSign = sign(_cross[_ci]);

			if (_currentSign == 0)
			{
				_tempPoints.push_back(_set[_ci]);
				continue;
			}

			int _nextSign = sign(_cross[_ci + 1]);

			if (_currentSign * _nextSign < 0)  //���ڽ���
			{
				Line2f _temp(_set[_ci], _set[_ci + 1]);
				Vec2f _p;
				_line.getCrossoverPoint(_temp, _p);  //���ﲻ�����ƽ�е����
				_tempPoints.push_back(_p);
			}
		}

		size_t _tempSize = _tempPoints.size();
		if (_tempSize == 0)
		{
			return false;
		}
		if (_tempSize > 2)
		{
			cout << "ConvexHull::getConvexHullIntersectWithLine(): Too many points!" << endl; //�������
			return false;
		}
		if (_tempSize == 2)
		{
			Vec2f _temp(_tempPoints[1] - _tempPoints[0]);
			float _cos = _vec.cosAngle(_temp);
			if (_cos < 0)
			{
				Vec2f _t(_tempPoints[1]);
				_tempPoints[1] = _tempPoints[0];
				_tempPoints[0] = _t;
			}
		}

		for (size_t i = 0; i < _tempSize; i++)
			_intersections.push_back(_tempPoints[i]);

		return true;

	}
}



#endif

