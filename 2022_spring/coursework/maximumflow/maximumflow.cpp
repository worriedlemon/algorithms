#include "flownetwork.h"

double FordFulkerson(FlowNetwork& graph);

int main()
{
    setlocale(LC_ALL, "Russian");

    FlowNetwork graph;
    ifstream fin;
    const char filename[] = "network.txt";

    fin.open(filename);
    if (fin.good()) fin >> graph;
    else return 5;

    fin.close();

    cout << "Initial flow network is\n" << graph << "\n";
    cout << "Maximum flow is " << FordFulkerson(graph) << "\n";

    return 0;
}
