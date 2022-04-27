#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

vector<vector<int>> Input_Graph(const string& our_file, vector<pair<int, int>>& Edges_note)
{
    ifstream fin;
    fin.open(our_file);
    vector<vector<int>> Graph;
    int ver, edg;
    Edges_note.clear();
    if (fin.is_open())
    {
        fin >> ver >> edg;
        vector <int> V(ver, 0);
        Graph.resize(ver, V);
        for (int k = 0; k < edg; k++)
        {
            int start, end;
            fin >> start >> end;
            auto p1 = make_pair(start, end);
            Edges_note.push_back(p1);
            Graph[start][end] = 1;
            Graph[end][start] = 1;
        }
    }
    else cout << "Error of reading file" << endl;
    return Graph;
}

vector<int> Solver(vector<vector<int>>& Graph)
{
    vector<int> V_Col(Graph.size(), -1);
    for (int i = 0; i < Graph.size(); i++)
    {
        int color = 0;
        vector<bool> is_colored(Graph.size(), 0);
        for (int j = 0; j < i; j++)
            if (Graph[i][j] == 1)
                is_colored[V_Col[j]] = 1;

        for (int k = 0; k < Graph.size(); k++)
        {
            if (is_colored[k] == 0)
            {
                V_Col[i] = k;
                break;
            }
        }
    }
    return V_Col;
}

int main()
{
    string path = "C:/Users/Максим/Desktop/data";
    auto iter = filesystem::directory_itererator(path);
    vector<filesystem::path> arr;
    copy_if(filesystem::begin(iter), filesystem::end(iter), std::back_inserter(arr),
        [](const auto& entry)
        {
            return filesystem::is_regular_file(entry);
        });

    for (auto& p : arr)
    {
        vector<pair<int, int>> edg;
        vector<vector<int>> Graph = Input_Graph(p.string(), edg);
        vector<int> colored2 = Solver(Graph);
        int max = -1;
        for (int i = 0; i < colored2.size(); i++)
            if (colored2[i] > max)
                max = colored2[i];

        cout << p.string() << " " << max + 1 << endl;
    }
    return 0;
}