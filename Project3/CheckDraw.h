//IDE: Viusal Studio latest version.
//GUIlib: EasyX
//Encoding: UTF-8


#ifndef CHECKDRAW_H
#define CHECHDRAW_H
#include "Vertex.h"
#include <vector>
#include <iostream>


bool findVertex(std::vector<Vertex> &vertex, int &temp, int &temp2);//判断是否有相应的节点表存在，有则将当前节点存入
bool isDrawFinished(std::vector<Vertex> &vertex);//判断着色是否完成
bool checkDraw(std::vector<Vertex> &vertex, Vertex &vv, int color);//检查是否满足着色条件
int getVertexColor(std::vector<Vertex> &vertex, int ID);//取出顶点的颜色



bool findVertex(std::vector<Vertex> &vertex, int &temp, int &temp2)
{
	std::vector<Vertex>::iterator it;
	for (it = vertex.begin(); it != vertex.end(); it++)
	{
		if (temp == it->vertexID)
		{
			(it->vertex).push_back(temp2);
			return true;
		}
	}
	return false;
}


int getVertexColor(std::vector<Vertex> &vertex, int ID)
{
	std::vector<Vertex>::iterator it;
	for (it = vertex.begin(); it != vertex.end(); it++)
	{
		if (ID == it->vertexID)
			return it->Color;
	}
	std::cout << "Cant find such a vertex: " << it->vertexID << std::endl;
	return NULL;
}

bool checkDraw(std::vector<Vertex> &vertex, Vertex &vv, int color)
{
	std::vector<int>::iterator it;
	for (it = vv.vertex.begin(); it != vv.vertex.end(); it++)
	{
		if (color == getVertexColor(vertex, *it))
			return false;
	}
	return true;
}

bool isDrawFinished(std::vector<Vertex> &vertex)
{
	std::vector<Vertex>::iterator it;
	for (it = vertex.begin(); it != vertex.end(); ++it)
	{
		if (false == it->isDraw)
			return false;
	}
	return true;
}


bool compare(Vertex a, Vertex b) //这个比较函数的参数类型也要写成结构体
{
	return a.vertexID<b.vertexID;//">"是进行降序排序，如果要升序改成<，其实sort默认是升序
}
#endif // !CHECKDRAW_H
