#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int>> Input_Graph(const string& our_file, vector<pair<int, int>>& edges_note, vector<int>& counter)
{
    ifstream fin;
    fin.open(our_file);
    vector<vector<int>> graph;
    int ver, edges;
    vector<pair<int, int>> pairs;
    edges_note.clear();
    counter.clear();
    return graph;
}

int main()
{
    cout << "Hello Max!" << endl;
    return 0;
}
