#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;

vector<vector<int>> Input_Graph(const string& our_file, vector<pair<int, int>>& Edges_note, vector<int>& Ecounter)
{
    ifstream fin;
    fin.open(our_file);
    vector<vector<int>> Graph;

    int Verr, Edges;
    vector<pair<int, int>> pairs;
    Edges_note.clear();
    Ecounter.clear();

    if (fin.is_open())
    {
        fin >> Verr >> Edges;
        vector <int> V(Verr, 0);
        Graph.resize(Verr, V);

        auto zero = make_pair(0, 0);

        pairs.resize(Graph.size(), zero);

        for (int k = 0; k < Edges; k++)
        {
            int first, last;

            fin >> first >> last;
            auto p1 = make_pair(first, last);
            Edges_note.push_back(p1);
            Graph[first][last] = 1;
            Graph[last][first] = 1;
            pairs[first].first += 1;
            pairs[last].first += 1;
            pairs[first].second = first;
            pairs[last].second = last;
        }
    }
    else    cout << "Error" << endl;

    sort(pairs.begin(), pairs.end());

    for(int i = pairs.size()-1; i>=0; i--)
        Ecounter.push_back(pairs[i].second);

    return Graph;
}

vector<int> solve(vector<vector<int>>& Graph, const vector<int>& Ecounter)
{
    vector<int> V_Col(Graph.size(), -1);

    for(auto it : Ecounter)
    {
        int i = it;
        vector<bool> Is_Col(Graph.size(), 0);
        for (int j = 0; j < Graph.size(); j++)
            if (Graph[i][j] == 1)
                if(V_Col[j] > -1)
                    Is_Col[V_Col[j]] = 1;

        for (int k = 0; k < Graph.size(); k++)
            if (!Is_Col[k])
            {
                V_Col[i] = k;
                break;
            }
    }
    return V_Col;
}

int main()
{
    return 0;
}
