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

	//����͹������С�����ӳ�����
	//_setΪ͹�����㣬�Ƽ�ʹ��getConvexHull()�����ķ��ؽ��(���߱�֤͹���еĵ���ʱ������,�Ҳ����ڹ��ߵĵ�)
	//_result��¼������ı��ε��ĸ����㣬yֵ��С��xֵ��С�ĵ��ǵ�һ�����������ʱ������
	// ����ֵΪ��������Ϊ����ʾ����ʧ��
	float getMinAreaBoundingRectOfConvexHull(const vector<Vec2f>& _set, vector<Vec2f>& _result)
	{

	}
}

#endif
