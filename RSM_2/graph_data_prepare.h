#pragma once
#ifndef graph_data_prepare_h
#define graph_data_prepare_h


#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<cstdlib>
#include<ctime>

#include "Djikstra_alghorytm.h"

using namespace std;

class graph_data_prepare
{

public:
	double compare; 
	int trackingid, n;
	graph_data_prepare(int vert);

	list<int>notvisited;
	vector<vector<int>> pass;
	vector<vector<double>> peak;

	void vertexcount(int vert);
	void graph_pass();
	void peak_fill();
	void list_fill();

	friend void restore_value(vector<vector<double>> peak, vector<vector<double>>& rememebr_start_peak, list<int> count);
};

#endif