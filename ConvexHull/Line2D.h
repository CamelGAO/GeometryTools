#ifndef _LINE2D_H
#define _LINE2D_H

#include "Math.h"
#include "Vector2D.h"

namespace Line2D
{
	using namespace Vector2D;
	using namespace Math;

	template<typename T>
	class Line2
	{
	public:
		Line2(void) {}

		Line2(const T _a, const T _b, const T _c)
		{
			a = _a;
			b = _b;
			c = _c;
		}

		Line2(const Vec2<typename T>& _point1, const Vec2<typename T>& _point2)
		{
			a = _point2[1] - _point1[1];
			b = _point1[0] - _point2[0];
			c = _point2[0]*_point1[1] - _point1[0]*_point2[1];
		}

		Line2(const Line2<typename T>& _line)
		{
			a = _line.a;
			b = _line.b;
			c = _line.c;
		}
		

		//ֱ��ƽ�л��غ�ʱû�����
		bool isParallel(const Line2<typename T>& _line) const
		{
			T _la = _line.a;
			T _lb = _line.b;
			T _lc = _line.c;
			int _sb = sign(b);
			int _slb = sign(_lb);

			if ((_sb == 0 && _slb == 0) || (_sb != 0 && _slb != 0 && sign(a / b - _la / _lb) == 0))  //�ж�ƽ��
				return true;

			return false;
		}

		//ƽ�з���false��_result���䣻��ƽ�з���true
		bool getCrossoverPoint(const Line2<typename T>& _line, Vec2<typename T>& _result) const
		{
			if ( isParallel(_line) )  //�ж�ƽ��
				return false;

			T _la = _line.a;
			T _lb = _line.b;
			T _lc = _line.c;

			_result[0] = (c*_lb - _lc*b) / (_la*b - a*_lb);
			_result[1] = (_la*c - a*_lc) / (a*_lb - _la*b);

			return true;
		}

		//��ù���(_x, _y), ���뵱ǰֱ�ߴ�ֱ��ֱ�ߣ�bx - ay +a*_y - b*_x = 0
		//_pointΪ���߾����ĵ�
		void getVerticalLine(const Vec2<typename T>& _point, Line2<typename T>& _result) const
		{
			_result.a = b;
			_result.b = -a;
			_result.c = a * _point[1] - b * _point[0];
		}

		//��ù���(_x, _y), ���뵱ǰֱ��ƽ�е�ֱ�ߣ�ax + by -a*_x - b*_y = 0
		//_pointΪƽ���߾����ĵ�
		void getParallelLine(const Vec2<typename T>& _point, Line2<typename T>& _result) const
		{
			_result.a = a;
			_result.b = b;
			_result.c = -(a * _point[0] + b * _point[1]);
		}

		//���ĳ�㵽ֱ�ߵĴ�������
		void getFootPoint(const Vec2<typename T>& _point, Vec2<typename T>& _result) const
		{
			Line2<T> _verticalLine;
			getVerticalLine(_point, _verticalLine);
			getCrossoverPoint(_verticalLine, _result);
		}

		T a, b, c; //ax+by+c=0
	protected:
	private:
	};

	typedef Line2<float> Line2f;
	typedef Line2<double> Line2d;
}

#endif
