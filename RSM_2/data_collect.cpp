#include "data_collect.h"

//konstruktor bedzie tworzyl pliki z danymi czas,koszt,dystans
data_collect::data_collect(int vertex):time_data(vertex, vector<int>(vertex)), cost_data(vertex, vector<int>(vertex)), distance_data(vertex, vector<int>(vertex)),
										weight_data(vertex, vector<double>(vertex)) {
	srand(time(NULL));
	
	n = vertex;

	ifstream time_file("time.txt"); //odczyt z pliku
	ifstream distance_file("distance.txt"); //odczyt z pliku
	ifstream cost_file("cost.txt"); //odczyt z pliku
	
	if (!time_file) { //sprawdzenie czy plik istnieje, jesli nie dane sa generowane pseudo losowo
		vector<vector<int>> tab(n,vector<int>(n));
		ofstream collect;
		collect.open("time.txt");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					tab[i][j] = 100000;
				}
				else
				{
					tab[i][j] = ((rand() % 600) + 100);;
				}
				collect << tab[i][j]<<" ";
			}
			collect << endl;
		}
		collect.close();
	}
	time_file.close();

	if (!cost_file) { //sprawdzenie czy plik istnieje, jesli nie dane sa generowane pseudo losowo
		vector<vector<int>> tab(n, vector<int>(n));
		ofstream collect;
		collect.open("cost.txt");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					tab[i][j] = 100000;
				}
				else
				{
					tab[i][j] = ((rand() % 750) + 100);;
				}
				collect << tab[i][j] << " ";
			}
			collect << endl;
		}
		collect.close();
	}
	cost_file.close();

	if (!distance_file) { //sprawdzenie czy plik istnieje, jesli nie dane sa generowane pseudo losowo
		vector<vector<int>> tab(n, vector<int>(n));
		ofstream collect;
		collect.open("distance.txt");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					tab[i][j] = 100000;
				}
				else
				{
					tab[i][j] = ((rand() % 1000) + 100);;
				}
				collect << tab[i][j] << " ";
			}
			collect << endl;
		}
		collect.close();
	}
	distance_file.close();

}

void data_collect::time_data_read_from_file() {
	ifstream time_file("time.txt");
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) 
			time_file >> time_data[i][j];
	}
	time_file.close();
}

void data_collect::cost_data_read_from_file()
{
	ifstream cost_file("cost.txt");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cost_file >> cost_data[i][j];
	}
	cost_file.close();
}

void data_collect::distance_data_read_from_file()
{
	ifstream distance_file("distance.txt");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			distance_file >> distance_data[i][j];
	}
	distance_file.close();
}

void data_collect::weight_data_read_from_file()
{
	{
		ifstream weight_file("weight.txt");

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				weight_file >> weight_data[i][j];
		}
		weight_file.close();
	}
}

void data_collect::weight_data_write_to_file()
{
	ifstream weight_file("weight.txt"); //odczyt z pliku
	if (!weight_file) { //sprawdzenie czy plik istnieje, jesli nie dane sa generowane pseudo losowo
		vector<vector<double>> tab(n,vector<double>(n));
		ofstream collect;
		collect.open("weight.txt");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					tab[i][j] = 100000;
				}
				else
				{
					tab[i][j] = calcWt*time_data[i][j]/600 + calcWc*cost_data[i][j]/1000 + calcWd*distance_data[i][j]/1000;
				}
				collect << tab[i][j]<<" ";
			}
			collect << endl;
		}
		collect.close();
	}
	weight_file.close();
}

void data_collect::weight_calculate()
{
	double biggest = 0;
	if (Wt >= Wc)
		biggest = Wt;
	if (Wc > Wt)
		biggest = Wc;
	if (Wt >= Wd)
		biggest = Wt;
	if (Wd > Wt)
		biggest = Wd;
	if (Wc >= Wd)
		biggest = Wc;
	if (Wd > Wc)
		biggest = Wd;

	double Wti = biggest / Wt, Wci = biggest / Wc, Wdi = biggest / Wd;
	double sum = (100 / (Wti + Wci + Wdi)) / 100;

	calcWt = sum * Wti, calcWc = sum * Wci, calcWd = sum * Wdi;


}


