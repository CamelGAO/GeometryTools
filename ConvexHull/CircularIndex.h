#ifndef _CIRCULARINDEX_H
#define _CIRCULARINDEX_H

class CircularIndex     //�����±�ѭ�������õ���Խ�磬����ѭ������
{
public:
	explicit CircularIndex(int _length, int _start = 0, int _offset = 0)  //_length��ģ��Ҳ��index��������_start����С��indexֵ��_offset�������_start��ƫ��
	{
		start = _start;
		length = _length;
		offset = 0;
		offsetAdd(_offset);
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

	CircularIndex& operator ++ ()   //ǰ����ʽ
	{
		offsetAdd(1);
		return *this;
	}

	const CircularIndex operator ++ (int)   //������ʽ
	{
		CircularIndex _temp(*this);
		offsetAdd(1);
		return _temp;
	}

	CircularIndex& operator -- ()   //ǰ����ʽ
	{
		offsetAdd(-1);
		return *this;
	}

	const CircularIndex operator -- (int)   //������ʽ
	{
		CircularIndex _temp(*this);
		offsetAdd(-1);
		return _temp;
	}

	operator int() const { return start + offset; }   //����int��

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
