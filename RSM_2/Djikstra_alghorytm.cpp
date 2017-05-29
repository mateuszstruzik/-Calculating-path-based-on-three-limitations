#include "Djikstra_alghorytm.h"
#include "data_collect.h"


Djikstra_alghorytm::Djikstra_alghorytm()
{
}

void Djikstra_alghorytm::djikstra(int n, double compare, int trackingid, list<int> notvisited, vector<vector<double>> graph, vector<vector<int>> pass, vector<vector<double>> &peak)
{
	
	bool condition_airport_number = false;
	double compare_backup = compare;
	int &refstart = start;
	peak[0][start] = 0;
	peak[1][start] = -1;

	vector<vector<int>> buckup_pass(pass);
	vector<vector<double>> buckup_peak(peak);
	vector<vector<double>> rememebr_start_peak(2,vector<double>(1));
	rememebr_start_peak[0][0] = start;//wierzcholek zapamietany
	rememebr_start_peak[1][0] = 0;//waga zapamietana do dodania
	list<int> buckup_notvisited(notvisited);
	
	//compare = 101; //bedzie sluzyc do porownania wartosci w tablicy peak
	//trackingid = n + 1; //bedzie sluzyc do zapisania w tablicy peak ostatniego odwiedzonego wierzcholka
	count_vertex.push_front(0);

	while (condition_airport_number == false) {
		while (!notvisited.empty()) {
			for (int i = 0; i < n; i++) {
				//porownujemy czy dana wartosc jest njmniejsza w tablicy w wierszu wartosci peak[0][n], a takze czy dany wierzcholek nie byl juz brany pod uwage, czy jest w liscie(zbiorze) wierzcholkow nie odwiedzonych
				if (peak[0][i] < compare && (find(notvisited.begin(), notvisited.end(), i) != notvisited.end())) {
					compare = peak[0][i];
					trackingid = i;

				}

			}
			//usuniecie z listy elementu o najmniejszej wartosci w tablicy [2][n]
			notvisited.remove(trackingid);
			//sprawdzenie czy z wierzcholka jest przejscie do innych a takze czy nie byl juz wczesniej odwiedzony
			for (int i = 0; i < n; i++) {
				if (graph[trackingid][i] < compare_backup && pass[trackingid][i] == 0) {
					//porownanie czy wartosc przypisana do wierzcholkow po ostatnim przejsciu jest wieksza od tej przy tym przejsciu
					if (peak[0][i] > (compare + graph[trackingid][i])) {
						peak[0][i] = compare + graph[trackingid][i]; //jesli poprzednia wartosc w wierszu tablicy [0][n] byla iweksza zamienienie nan nowa
						peak[1][i] = trackingid; //podmiana ostatnio odwiedzonego wierzcholka
						pass[trackingid][i] = 1;  //zapisanie w tablicy przejsc odwiedzonych wierzcholkow bez powtorzen
						pass[i][trackingid] = 1;
					}
				}
			}
			compare = compare_backup;//101;
		}
		//for (int i = 0; i < n; i++)
		//{
		
		int i = end;
		trackingid = i;//i;

		while (trackingid != -1) {
			notvisited.push_front(trackingid);
			trackingid = peak[1][trackingid];
		}
		condition_airport_number = condition_number_of_airport(notvisited);
		if (condition_airport_number==false) {
			list<int>::iterator it = notvisited.end();
			auto nx1 = prev(it, 1);
			auto nx2 = prev(nx1, 1);
//			auto nx3 = prev(nx2, 1);
			int it0 = *nx1, it1 = *nx2;// it3 = *nx3;
			if (notvisited.size() < 3) {
				pass = buckup_pass;
				peak = buckup_peak;
				notvisited = buckup_notvisited;
				//usuniecie pkt przed ponowna djikstra  nptvisited.ramove(0);

				pass[it1][it0] = 1;
				pass[it0][it1] = 1;
				buckup_pass = pass;
			}
			else {
				pass = buckup_pass;
				restore_value(peak, rememebr_start_peak, notvisited);
				save_peak(peak, buckup_peak, rememebr_start_peak, notvisited,refstart);
				peak = buckup_peak;
				peak[0][refstart] = 0;
				pass[it1][it0] = 1;
				pass[it0][it1] = 1;
				pass_blocked(pass,buckup_pass,notvisited, n);
				pass = buckup_pass;
				notvisited = buckup_notvisited;
			}
		}
		else {

			cout << "koszty przejscia sciezki " << i << ": " << endl;

			for (list<int>::iterator i = notvisited.begin(); i != notvisited.end(); ++i)
				cout << *i << "->";

			cout << endl;

			convert_track_to_time_value(n, notvisited);
			convert_track_to_distance_value(n, notvisited);
			convert_track_to_cost_value(n, notvisited);

			//cout << "waga :" << peak[0][i] << endl;
			
			notvisited.clear();
		}
	}
	/*QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*> (&counterStop));
	time_djikstry = (static_cast<long double> (counterStop) - counterStart) / freq * 1000;*/
	//cout << "liczba lotnisk :"<<notvisited.size()<<endl;


	//int i = 45;
	//trackingid = i;//i;

	//while (trackingid != -1) {
	//	notvisited.push_front(trackingid);
	//	trackingid = peak[1][trackingid];
	//}

	//cout << "koszty przejscia sciezki " << i << ": " << endl;

	//for (list<int>::iterator i = notvisited.begin(); i != notvisited.end(); ++i)
	//	cout << *i << "->";
	//cout << "koszt przejscia :" << peak[0][i] << endl;
	//notvisited.clear();
	//
	
	//}
	//cout << endl << time_djikstry << endl;



}

bool Djikstra_alghorytm::condition_number_of_airport(list<int> count)
{
	if (count.size() < 4)
		return false;
	//else if (count.size() > 8)
		//return false;
	else
		return true;
}

void Djikstra_alghorytm::convert_track_to_time_value(int n, list<int> collect)
{
	vector<vector<int>> time_data(n, vector<int>(n));

	ifstream time_file("time.txt");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			time_file >> time_data[i][j];
	}
	time_file.close();
	
	for (list<int>::iterator i = collect.begin(); i != collect.end(); ++i)
		cout << *i << "->";
	double convert_path_time=0;

	for (list<int>::iterator it = collect.begin(); it != collect.end(); ++it)
	{
		auto inext = next(it, 1);

		if(inext!=collect.end())
		convert_path_time = convert_path_time + time_data[*it][*inext];
	}
	cout << "czas przejscia sciezki :" << convert_path_time << " min" << endl;

	

}

void Djikstra_alghorytm::convert_track_to_distance_value(int n, list<int> collect)
{
	vector<vector<int>> time_data(n, vector<int>(n));

	ifstream distance_file("distance.txt");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			distance_file >> time_data[i][j];
	}
	distance_file.close();

	for (list<int>::iterator i = collect.begin(); i != collect.end(); ++i)
		cout << *i << "->";
	double convert_path_time = 0;

	for (list<int>::iterator it = collect.begin(); it != collect.end(); ++it)
	{
		auto inext = next(it, 1);

		if (inext != collect.end())
			convert_path_time = convert_path_time + time_data[*it][*inext];
	}
	cout << "czas przejscia sciezki :" << convert_path_time << " km" << endl;

	
}

void Djikstra_alghorytm::convert_track_to_cost_value(int n, list<int> collect)
{
	vector<vector<int>> time_data(n, vector<int>(n));

	ifstream cost_file("cost.txt");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cost_file >> time_data[i][j];
	}
	cost_file.close();

	for (list<int>::iterator i = collect.begin(); i != collect.end(); ++i)
		cout << *i << "->";
	double convert_path_time = 0;

	for (list<int>::iterator it = collect.begin(); it != collect.end(); ++it)
	{
		auto inext = next(it, 1);

		if (inext != collect.end())
			convert_path_time = convert_path_time + time_data[*it][*inext];
	}
	cout << "czas przejscia sciezki :" << convert_path_time << " $" << endl;

}

void Djikstra_alghorytm::get_start_and_end()
{
	cout << "podaj pkt startowy ";
	cin >> start;
	cout << endl << "podaj pkt koncowy "<<endl;
	cin >> end;
}


void pass_blocked(vector<vector<int>> pass, vector<vector<int>> &buckup_pass,list<int>count, int n)
{
	list<int>::iterator koniec = count.end();
	auto wskaz = prev(koniec, 2);

	for (list<int>::iterator it = count.begin(); it!=wskaz/*(it != count.end()) && ((it++) != count.end())*/; ++it)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) {
				if (i == *it)
					pass[i][j] = 1;
				else if (j == *it)
					pass[i][j] = 1;
			}
		}

	}

	buckup_pass = pass;
}

void save_peak(vector<vector<double>> peak, vector<vector<double>>& buckup_peak, vector<vector<double>>& rememebr_start_peak, list<int> count,int &refstart)
{
	list<int>::iterator koniec = count.end();
	auto wskaz = prev(koniec, 2);
	auto koncz = prev(koniec, 1);
	for (list<int>::iterator it = count.begin(); it !=koncz /*count.end()) && ((it++) != count.end())*/; ++it)
	{
		buckup_peak[0][*it] = peak[0][*it];
		buckup_peak[1][*it] = peak[1][*it];
		if (it==wskaz) {
			rememebr_start_peak[0][0] = peak[0][*it];
			rememebr_start_peak[1][0] = *it;
			refstart = *it;
		}
	}
}

void restore_value(vector<vector<double>> &peak, vector<vector<double>>& rememebr_start_peak, list<int> count)
{
	for (list<int>::iterator i = count.begin(); i != count.end(); ++i) {
		if (*i == rememebr_start_peak[1][0]) {
			for (list<int>::iterator j = i; j != count.end();j++)
			peak[0][*j] = peak[0][*j] + rememebr_start_peak[0][0];

			break;
		}
	}
}
