#ifndef _CIRCULARINDEX_H
#define _CIRCULARINDEX_H

class CircularIndex
{
public:
	explicit CircularIndex(int _length, int _start = 0, int _offset = 0)  //_length是模，也即offset的数量，_start是最小的offset值，_offset给定相对_start的偏移
	{
		start = _start;
		length = _length;
		offset = _offset;
	}

	CircularIndex(const CircularIndex& _temp)
	{
		start = _temp.start;
		length = _temp.length;
		offset = _temp.offset;
	}

	CircularIndex& operator = (const CircularIndex& _temp)
	{
		start = _temp.start;
		length = _temp.length;
		offset = _temp.offset;

		return *this;
	}

	const CircularIndex operator + (const int& _temp) const
	{
		CircularIndex _obj(*this);
		_obj.offsetAdd(_temp);
		return _obj;
	}

	const CircularIndex operator - (const int& _temp) const
	{
		CircularIndex _obj(*this);
		_obj.offsetAdd(-_temp);
		return _obj;
	}

	const CircularIndex operator += (const int& _temp)
	{
		offsetAdd(_temp);
		return *this;
	}

	const CircularIndex operator -= (const int& _temp)
	{
		offsetAdd(-_temp);
		return *this;
	}

	CircularIndex& operator ++ ()   //前置形式
	{
		offsetAdd(1);
		return *this;
	}

	const CircularIndex operator ++ (int)   //后置形式
	{
		CircularIndex _temp(*this);
		offsetAdd(1);
		return _temp;
	}

	CircularIndex& operator -- ()   //前置形式
	{
		offsetAdd(-1);
		return *this;
	}

	const CircularIndex operator -- (int)   //后置形式
	{
		CircularIndex _temp(*this);
		offsetAdd(-1);
		return _temp;
	}

	operator int() const { return start + offset; }

protected:
private:
	void offsetAdd(int _n)
	{
		offset += _n;
		if (offset < 0)
		{
			offset = length - (-offset) % length;
		}
		offset = offset % length;
	}

	int start;
	int length;
	int offset;
};

#endif
