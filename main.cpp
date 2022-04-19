#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;

vector<vector<int>> Input_Graph(const string& our_file, vector<pair<int, int>>& Edges_note, vector<int>& e_counter) {
    ifstream fin;
    fin.open(our_file);
    vector<vector<int>> Graph;
    int ver, edg;
    vector<pair<int, int>> pairs;
    Edges_note.clear();
    e_counter.clear();
    if (fin.is_open()) {
        fin >> ver >> edg;
        vector <int> v(ver, 0);
        Graph.resize(ver, v);
        auto zero = make_pair(0, 0);
        pairs.resize(Graph.size(), zero);
        for (int k = 0; k < edg; k++) {
            int start, end;
            fin >> start >> end;
            auto p1 = make_pair(start, end);
            Edges_note.push_back(p1);
            Graph[start][end] = 1;
            Graph[end][start] = 1;
            pairs[start].first += 1;
            pairs[end].first += 1;
            pairs[start].second = start;
            pairs[end].second = end;
        }
    }
    else {
        cout << "file not read" << endl;
    }
    sort(pairs.begin(), pairs.end());
    for (int i = pairs.size() - 1; i >= 0; i--) {
        e_counter.push_back(pairs[i].second);
    }
    return Graph;
}

vector<int> solve(vector<vector<int>>& Graph, const vector<int>& e_counter) {
    vector<int> vColors(Graph.size(), -1);
    for (auto it : e_counter) {
        int i = it;
        vector<bool> colored(Graph.size(), false);
        for (int j = 0; j < Graph.size(); j++) {
            if (Graph[i][j] == 1) {
                if (vColors[j] > -1) {
                    colored[vColors[j]] = true;
                }
            }
        }
        for (int k = 0; k < Graph.size(); k++) {
            if (!colored[k]) {
                vColors[i] = k;
                break;
            }
        }
    }
    return vColors;
}

int main()
{
    return 0;
}