#pragma once
#ifndef data_h
#define data_h


#include<iostream>
#include<vector>
#include<list>
#include<iterator>
#include<fstream>

using namespace std;

void pass_blocked(vector < vector<int>> pass,vector<vector<int>> &buckup_pass, list<int> count, int n);
void save_peak(vector<vector<double>> peak, vector<vector<double>>& buckup_peak, vector<vector<double>>& rememebr_start_peak, list<int> count, int &refstart);
void restore_value(vector<vector<double>> &peak, vector<vector<double>>& rememebr_start_peak, list<int> count);

class Djikstra_alghorytm
{
public:
	int start, end;
	Djikstra_alghorytm();
	void djikstra(int n, double compare, int trackingid, list<int> notvisited, vector<vector<double>> graph, vector<vector<int>> pass, vector<vector<double>> &peak);

	list<int> count_vertex;

	bool condition_number_of_airport(list<int> count);
	void convert_track_to_time_value(int n, list<int> collect);
	void convert_track_to_distance_value(int n, list<int> collect);
	void convert_track_to_cost_value(int n, list<int> collect);
	void get_start_and_end();

	friend void restore_value(vector<vector<double>> &peak, vector<vector<double>>& rememebr_start_peak, list<int> count);
	
	
};

#endif