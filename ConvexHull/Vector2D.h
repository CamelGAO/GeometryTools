#ifndef _VECTOR2D_H
#define _VECTOR2D_H

#include <cmath>

namespace Vector2D
{
	template<typename T>
	class Vec2
	{
	public:
		Vec2(void) {}
		Vec2(const T& _x, const T& _y) { data[0] = _x; data[1] = _y; }
		Vec2(const Vec2<typename T>& _vec)
		{
			for (size_t i = 0; i < 2; i++)
				data[i] = _vec.data[i];
		}

		T& operator[] (int _i)
		{
			return data[_i];
		}

		const T& operator[] (int _i) const
		{
			return data[_i];
		}

		bool operator== (const Vec2<typename T>& _vec) const
		{
			bool _ret = true;

			for (size_t i = 0; i < 2; i++)
			{
				if (data[i] != _vec.data[i])
				{
					_ret = false;
					break;
				}
			}

			return _ret;
		}

		const Vec2<typename T> operator- (const Vec2<typename T>& _vec) const
		{
			return Vec2<T>(data[0] - _vec.data[0], data[1] - _vec.data[1]);
		}

		const Vec2<typename T> operator+ (const Vec2<typename T>& _vec) const
		{
			return Vec2<T>(data[0] + _vec.data[0], data[1] + _vec.data[1]);
		}

		// this 点乘 _vec
		const T dot(const Vec2<typename T>& _vec) const  
		{
			return (data[0] * _vec.data[0] + data[1] * _vec.data[1]);
		}

		// this 叉乘 _vec， 二维叉积是个值，
		// 其绝对值是两个向量确定的平行四边形面积，
		// 其符号表示_vec的末端点在this向量的哪一侧，正表示左侧
		const T cross(const Vec2<typename T>& _vec) const 
		{
			return data[0] * _vec.data[1] - data[1] * _vec.data[0];
		}

		const T distance(const Vec2<typename T>& _vec) const
		{
			T _n1 = data[0] - _vec.data[0];
			T _n2 = data[1] - _vec.data[1];
			return sqrt(_n1*_n1 + _n2 * _n2);
		}

		const T distanceSq(const Vec2<typename T>& _vec) const
		{
			T _n1 = data[0] - _vec.data[0];
			T _n2 = data[1] - _vec.data[1];
			return _n1 * _n1 + _n2 * _n2;
		}

		const T length(void) const
		{
			return sqrt(dot(*this));
		}

		const T lengthSq(void) const
		{
			return dot(*this);
		}

	protected:
	private:
		T data[2];
	};

	template<typename T>
	const T getCosSlantAngle(const Vec2<typename T>& _vec) //倾斜角，与x轴正向夹角
	{
		T _ret;
		Vec2<T> _v(1.0f, 0.0f);
		_ret = _v.dot(_vec) / _vec.length();

		return _ret;
	}

}

typedef Vector2D::Vec2<float> Vec2f;
typedef Vector2D::Vec2<double> Vec2d;

#endif

