#include <bits/stdc++.h>

using namespace std;

void buildMatrix(vector<vector<char>>& m, string& val) {
    int j = 0;
    int i = 0;
    for (char t : val) {
        if (t == ',') {
            j++;
            i = 0;
            continue;
        }
        m[j][i] = t;
        i++;
    }
}

bool comparator(vector<int> &a, vector<int> &b) {
    if (a[2] == 0 && b[2] == 0) {
        return a[3] > b[3];
    }
    return a[2] < b[2];
}

class UnionFind {
    public:
        vector<int> arr;
        UnionFind(int s) {
            arr.resize(s);
            for (int i = 0; i < s; i++) arr[i] = i;
        }

        int find(int val) {
            if (arr[val] == val) return val;
            return find(arr[val]);
        }

        void unite(int i, int j) {
            arr[find(i)] = find(j);
        }
};

int toInt(char c) {
    if (c > 96 && c < 97+26) return (int)(c-97+26);
    return (int)(c-65);
}

int main(void) {

    string input;
    getline(cin, input);
    stringstream ss(input);
    string token;

    ss >> token;

    int n = (sqrt(token.size()*4 + 5)-1)/2;
    vector<vector<char>> country(n, vector<char>(n));
    vector<vector<char>> build(n, vector<char>(n));
    vector<vector<char>> destory(n, vector<char>(n));

    
    buildMatrix(country, token);

    ss >> token;
    buildMatrix(build, token);

    ss >> token;
    buildMatrix(destory, token);

    // put all edges weight for exsisting (0), build 
    vector<vector<int>> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (country[i][j] == '1') edges.push_back({i, j, 0, toInt(destory[i][j])});
            edges.push_back({i, j, build[i][j]});
        }
    }

    // use Kruskal's alg to find the MST
    
    sort(edges.begin(), edges.end(), comparator);

    UnionFind U(n);

    int i = 0;
    int count = 0;
    int cost = 0;

    for (;i < (int)edges.size(); ++i) {
        if (count == n-1) break;
        vector<int> curr = edges[i];
        if (U.find(curr[0]) == U.find(curr[1])) {
            if (curr[2] == 0) cost += toInt(destory[curr[0]][curr[1]]);
            continue;
        }

        
        U.unite(curr[0], curr[1]);
        count++;
        // if a build edge is used, add weight
        if (curr[2] != 0) cost += toInt(build[curr[0]][curr[1]]);
    }
    
    // find all remaining edges with with weight 0 and add cost to destory
    for (;i < (int)edges.size(); ++i) {
        if (edges[i][2] == 0) cost += toInt(destory[edges[i][0]][edges[i][1]]);
    }

    // return cost
    
    cout << cost << endl;

    return 0;
}