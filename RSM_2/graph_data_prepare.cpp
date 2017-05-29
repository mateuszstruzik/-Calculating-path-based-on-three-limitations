#include "graph_data_prepare.h"



graph_data_prepare::graph_data_prepare(int vert):pass(vert, vector<int>(vert)), peak(2, vector<double>(vert)) 
{
}

void graph_data_prepare::vertexcount(int vert)
{
	n = vert;
	compare = 100001;
	trackingid = vert + 1;
}

void graph_data_prepare::graph_pass()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				pass[i][j] = 1;
			else
				pass[i][j] = 0;
		}
	}
}

void graph_data_prepare::peak_fill()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == 0)
				peak[i][j] = compare;
			else
			{
				peak[i][j] = -1;
			}
		}

	}
}

void graph_data_prepare::list_fill()
{
	for (int i = 0; i < n; i++)
		notvisited.push_back(i);
}


