// ConvexHull.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "ConvexHull.h"
#include "CircularIndex.h"
#include "RotatingCaliper.h"
#include "Line2D.h"

using namespace std;
using namespace Vector2D;
using namespace Math;
using namespace ConvexHull;
using namespace RotatingCaliper;
using namespace Line2D;

int main()
{
	vector<Vec2f> in, out;
	  
	in.push_back(Vec2f(0, -1));
	in.push_back(Vec2f(1, 0));
	in.push_back(Vec2f(0, 1));
	in.push_back(Vec2f(-1, 0));
	in.push_back(Vec2f(0.5, 0.5));
	in.push_back(Vec2f(-2.0, 0));

	ConvexHull::getConvexHull(in, out);

	for (vector<Vec2f>::iterator it = out.begin(); it != out.end(); it++)
	{
		cout << "ConvexHull point: " << (*it)[0] << " " << (*it)[1] << endl;
	}

	vector<Vec2f> farthest;
	cout << "farthest length: " << getFarthestPointToEgde(out, 0, farthest) << endl;
	for (vector<Vec2f>::iterator it = farthest.begin(); it != farthest.end(); it++)
	{
		cout << "farthest point: " << (*it)[0] << " " << (*it)[1] << endl;
	}

	Vec2f up, down;
	cout << "ConvexHull width: " << getConvexHullWidth(out, out[1] - out[0], up, down) << endl;
	cout << "Upstream Point: " << up[0] << " " << up[1] << endl;
	cout << "Downstream Point: " << down[0] << " " << down[1] << endl;

	Vec2f p;
	Line2f l1(Vec2f(1, 0), Vec2f(1, 1));
	Line2f l2(Vec2f(2, 1), Vec2f(-2, -1));
	if (l1.getCrossoverPoint(l2, p))
		cout << "Crossover Point: " << p[0] << " " << p[1] << endl;
	else
		cout << "Parallel!" << endl;

	Vec2f p1(0,1), p2;
	Line2f l3( Vec2f(-2, -1), Vec2f(2, 1) );
	l3.getFootPoint(p1, p2);
	cout << "Foot Point: " << p2[0] << " " << p2[1] << endl;

	vector<Vec2f> rect;
	cout << "MaxArea: " << getMinAreaBoundingRectOfConvexHull(out, rect) << endl;
	for (vector<Vec2f>::iterator it = rect.begin(); it != rect.end(); it++)
	{
		cout << "rect point: " << (*it)[0] << " " << (*it)[1] << endl;
	}

// 	CircularIndex ci(10, 0, 1);
// 	for (int i = 0; i < 1000; i++)
// 	{
// 		static int a = 0;
// 	
// 		cout << i << " " << ci << endl;
// 
// 		ci -= 101;
// 	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
