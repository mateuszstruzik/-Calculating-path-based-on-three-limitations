#include "data_collect.h"
#include "graph_data_prepare.h"
#include "Djikstra_alghorytm.h"

int main() {
	int vertex = 50;
	data_collect proba(vertex); //wywolanie konstruktira z parametrem oznaczajacym wierzcholki
	graph_data_prepare proba2(vertex);
	Djikstra_alghorytm proba3;

	proba.time_data_read_from_file();
	proba.cost_data_read_from_file();
	proba.distance_data_read_from_file();
	cout << endl << proba.time_data[45][5] << endl;

	proba.weight_calculate();
	proba.weight_data_write_to_file();
	proba.weight_data_read_from_file();

	proba2.vertexcount(vertex);
	proba2.graph_pass();
	proba2.peak_fill();
	proba2.list_fill();

	proba3.get_start_and_end();
	proba3.djikstra(proba2.n, proba2.compare, proba2.trackingid, proba2.notvisited, proba.weight_data, proba2.pass, proba2.peak);

	proba3.count_vertex;
	
	
	

	system("pause");
}