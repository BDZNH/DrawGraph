//IDE: Viusal Studio latest version.
//GUIlib: EasyX
//Encoding: UTF-8


#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <graphics.h>
#include <algorithm>

#include "Vertex.h"
#include "CheckDraw.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const double Pi = 3.1415926;

void getData(std::vector<Vertex> &thevertex);//数据读取函数声明
void drawVertex(std::vector<Vertex> &thevertex, int &color);
void drawGraph(std::vector<Vertex> &thevertex, int &color);


int main()
{

	std::vector<Vertex> thevertex;
	getData(thevertex);
	std::sort(thevertex.begin(),thevertex.end(),compare);

	//着色开始
	//这一段也是核心逻辑段
	/*选择一种颜色，以任意顶点作为开始顶点，依次考察图中的未被着色的每个顶点，如果一个顶点可以用颜色1着色，
	换言之，该顶点的邻接点都还未被着色，则用颜色1为该顶点着色，当没有顶点能以这种颜色着色时，选择颜色2和一
	个未被着色的顶点作为开始顶点，用第二种颜色为尽可能多的顶点着色，如果还有未着色的顶点，则选取颜色3
	并为尽可能多的顶点着色，依此类推。*/
	int color=0;
	drawVertex(thevertex, color);
	//着色完成
	
	
	
	
	//std::vector<Vertex>::iterator it;
	//for (it = thevertex.begin(); it != thevertex.end(); ++it)
	//{
	//	std::cout << "Vertex ID is: " << it->vertexID << ", Color is : " << it->Color << std::endl;
	//}


	//绘制图形界面
	drawGraph(thevertex, color);
	

	std::cout << "\n\n" << std::endl;
	system("pause");
	return 0;
}

void getData(std::vector<Vertex> &thevertex)
{
	//数据读取,严格来说还要检查数据是否符合输入规范才对
	//输入数据格式为一行两个数字，分别代表顶点，一行则为一条边，读入整个文件，生成无向图
	int temp, temp2, color = 0;
	std::ifstream inFile("data.txt");//指定输入数据文件
	if (!inFile.is_open())//检查是否成功打开文件
	{
		std::cout << "can't open the file data.txt. There is not such a file" << std::endl;
		system("pause");
		return ;
	}
	Vertex tt;
	//vector<Vertex> thevertex;

	//这里建立邻接矩阵的时候是按照不知道顶点数和边数来建立的
	//也就是这里的while循环，每次读入两个数，代表相连的两个顶点，直到不能再读入数据为止(需要注意的是，这里并没有对数据的有效性进行检查)
	while (inFile >> temp >> temp2)//不断读入边以建立邻接表
	{
		//inFile >> temp2;
		//下面这个if语句参考发给你的文档
		if (!findVertex(thevertex, temp, temp2))
		{
			tt.vertexID = temp;
			tt.vertex.push_back(temp2);
			thevertex.push_back(tt);
			tt.clear();
		}
		if (!findVertex(thevertex, temp2, temp))
		{
			tt.vertexID = temp2;
			tt.vertex.push_back(temp);
			thevertex.push_back(tt);
			tt.clear();
		}
	}
}

void drawVertex(std::vector<Vertex> &thevertex, int &color)
{
	color = 0;//color为零表示没有颜色，也就是说，最后着色过的顶点的颜色都不会是0
	std::vector<Vertex>::iterator it;
	while (!isDrawFinished(thevertex))
	{
		color++;
		for (it = thevertex.begin(); it != thevertex.end(); ++it)
		{
			if (false == it->isDraw)//如果当前节点未着色
			{
				if (checkDraw(thevertex, *it, color))//检查是否符合着色条件
				{
					it->Color = color;
					it->isDraw = true;
				}
			}
		}
	}
}


void drawGraph(std::vector<Vertex> &thevertex, int &color)
{
	struct Coordinates //用于存储顶点对应的坐标
	{
		int x;
		int y;
	}temp;
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, SHOWCONSOLE);//初始化绘图窗口
	setfillcolor(WHITE);
	
	bar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	setlinecolor(BLACK);
	//circle(400, 400, 50);

	int radius = min(WINDOW_HEIGHT, WINDOW_WIDTH) / 3;//
	int cenCircleY = WINDOW_HEIGHT / 2, cenCircleX = WINDOW_WIDTH / 2;//圆心坐标
	setorigin(cenCircleX, cenCircleY);//重置坐标原点到窗口的中央
	//circle(-200, -200, 50);

	//确定第一个顶点的坐标
	int initX = 0 - radius;
	int initY = 0 / 2;
	radius = radius / 5;

	//定义颜色要填充的颜色数组
	COLORREF cc[] = {
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHTGRAY
	};


	int x2, y2, x1, y1;
	x1 = x2 = initX;
	y1 = y2 = initY;
	double Theta = (360.0 / thevertex.size())*Pi / 180;//每次旋转的角度
	
	int i = 1;
	std::vector<Coordinates> Coor;//用来保存每个顶点的圆心所对应的坐标

	std::vector<Vertex>::iterator it;
	for (it = thevertex.begin(); it != thevertex.end(); it++)
	{
		temp.x = x1;
		temp.y = y1;
		Coor.push_back(temp);
		x1 = (int)(x2 * cos(Theta) + y2 * sin(Theta));//逆时针旋转theta角度
		y1 = (int)(y2 * cos(Theta) - x2 * sin(Theta));
		x2 = x1;
		y2 = y1;
	}

	std::vector<int>::iterator iter;
	for (it = thevertex.begin(); it != thevertex.end(); it++)
	{
		for (iter = it->vertex.begin(); iter != it->vertex.end(); iter++)
		{
			x1 = Coor[it->vertexID-1].x;
			y1 = Coor[it->vertexID-1].y;
			x2 = Coor[*iter-1].x;
			y2 = Coor[*iter-1].y;
			line(x1, y1, x2, y2);
		}
		setfillcolor(cc[it->Color-1]);
		fillcircle(x1 , y1 , radius);
		settextstyle(60, 50, ("msyh"));
		outtextxy(x1-25, y1-30, (char)it->vertexID + 48);
	}

	std::cout << "最少着色数为 :" << color << std::endl;

	for (int i = 1; i <= color; i++)
	{
		std::cout << "被着色颜色" << i << "的顶点为 :" << std::flush;
		for (it=thevertex.begin() ; it!=thevertex.end() ; it++)
		{
			if (it->Color == i)
				std::cout << " " << it->vertexID << std::flush;
		}
		std::cout << std::endl;
	}

}