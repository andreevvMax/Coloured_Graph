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

int main() {

    // путь до директории с тестами и забил названия файлов из это директории в вектор

    string path = "C:/Users/Максим/Desktop/data";
    auto it = filesystem::directory_iterator(path);
    vector<filesystem::path> array_path;
    copy_if(filesystem::begin(it), filesystem::end(it), std::back_inserter(array_path),
        [](const auto& entry) {
            return filesystem::is_regular_file(entry);
        });

    // для каждого файла выполняю тест

    for (auto& p : array_path) {
        vector<int> e_counter;
        vector<pair<int, int>> edg;
        vector<vector<int>> Graph = Input_Graph(p.string(), edg, e_counter);  
        vector<int> colored2 = solve(Graph, e_counter);
        int max = -1;
        for (int i = 0; i < colored2.size(); i++) {
            if (colored2[i] > max) {
                max = colored2[i];
            }
        }
        cout << p.string() << " " << max + 1 << endl;
        /* cout << max + 1 << " " << 0 << endl;
         for (auto i : colored2) {
             cout << i << " ";
         }
         */
        cout << endl;
        for (auto i : edg) {
            if (colored2[i.first] == colored2[i.second]) {
                cout << "Error, colored test: " << p.string() << endl;
                cout << i.first << " " << i.second << endl;
                break;
            }
        }
    }
    return 0;
}