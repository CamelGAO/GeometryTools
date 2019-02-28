// ConvexHull.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "ConvexHull.h"
#include "CircularIndex.h"
#include "RotatingCaliper.h"

using namespace std;
using namespace Vector2D;
using namespace Math;
using namespace ConvexHull;
using namespace RotatingCaliper;

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

	cout << "ConvexHull width: " << getConvexHullWidthInDirection(out, out[1] - out[0]) << endl;

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
