//IDE: Viusal Studio latest version.
//GUIlib: EasyX
//Encoding: UTF-8


#ifndef VERTEX_H
#define VERTEX_H
#include <vector>


//声明顶点类
class Vertex
{
public:
	std::vector<int> vertex;//存储当前顶点所连接的顶点
	int vertexID;//存储当前顶点的编号
	bool isDraw;//是否被着色，false则当前顶点未着色
	unsigned short int Color;//当前顶点的颜色
	Vertex()
	{
		vertexID = 0;
		isDraw = false;
		Color = 0;
	}
	~Vertex() {};
	void clear()
	{
		vertexID = 0;
		isDraw = false;
		Color = 0;
		vertex.clear();
	}
};

#endif // !VERTEX_H

