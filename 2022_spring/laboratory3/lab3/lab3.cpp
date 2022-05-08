#include "fordbellman.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    AdjMatrix graph;
    ifstream fin;
    const char filename[] = "cities_list.txt";

    fin.open(filename);
    if (fin.good()) fin >> graph;
    else return 5;

    cout << "Initial graph's adjecent matrix is\n" << graph << "\n";
    cout << "After applying Bellman-Ford algorithm:\n" << graph.FordBellman() << endl;

    fin.close();
    return 0;
}