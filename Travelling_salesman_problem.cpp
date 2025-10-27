#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF INT_MAX
#define SIZE 5

void printMatrix(int matrix[][SIZE]) {
    cout << "Matrix:\n";
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(matrix[i][j] == INF)
                cout << "INF\t";
            else
                cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int reduceMatrix(int matrix[][SIZE], int reduced[][SIZE]) {
    int reductionCost = 0;

    // Copy original matrix
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            reduced[i][j] = matrix[i][j];

    // Row reduction
    for(int i = 0; i < SIZE; i++) {
        int rowMin = INF;
        for(int j = 0; j < SIZE; j++)
            rowMin = min(rowMin, reduced[i][j]);
        if(rowMin != INF && rowMin > 0) {
            reductionCost += rowMin;
            for(int j = 0; j < SIZE; j++)
                if(reduced[i][j] != INF)
                    reduced[i][j] -= rowMin;
        }
    }

    // Column reduction
    for(int j = 0; j < SIZE; j++) {
        int colMin = INF;
        for(int i = 0; i < SIZE; i++)
            colMin = min(colMin, reduced[i][j]);
        if(colMin != INF && colMin > 0) {
            reductionCost += colMin;
            for(int i = 0; i < SIZE; i++)
                if(reduced[i][j] != INF)
                    reduced[i][j] -= colMin;
        }
    }

    return reductionCost;
}

void dfs(int node, int cost, vector<int> &path, vector<bool> &visited, int matrix[][SIZE], int reduced[][SIZE], int &mincost, vector<int> &bestpath) {
    if(path.size() == SIZE) {
        cost += matrix[node][path[0]]; // return to start
        if(cost < mincost) {
            mincost = cost;
            bestpath = path;
        }
        return;
    }

    for(int next = 0; next < SIZE; next++) {
        if(!visited[next] && matrix[node][next] != INF) {
            visited[next] = true;
            path.push_back(next);
            dfs(next, cost + matrix[node][next], path, visited, matrix, reduced, mincost, bestpath);
            path.pop_back();
            visited[next] = false;
        }
    }
}

void Branch_Bound(int matrix[][SIZE], int reduced[][SIZE]) {
    vector<int> path;
    vector<bool> visited(SIZE, false);
    vector<int> bestpath;
    int mincost = INF;
    int currcost = 0;
    int start = 0;

    path.push_back(start);
    visited[start] = true;
    dfs(start, currcost, path, visited, matrix, reduced, mincost, bestpath);

    cout << "\nOptimal path: ";
    for(int v : bestpath)
        cout << v + 1 << " ";
    cout << "1\n";
    cout << "Minimum cost: " << mincost << endl;
}

int main() {
    int matrix[SIZE][SIZE];
    cout << "Enter the adjacency matrix (-1 for INF):\n";
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            int val;
            cin >> val;
            matrix[i][j] = (val == -1) ? INF : val;
        }
    }

    printMatrix(matrix);

    int reduced[SIZE][SIZE] = {0};
    int initial_cost = reduceMatrix(matrix, reduced);
    cout << "\nAfter Reduction (Initial Cost = " << initial_cost << "):\n";
    printMatrix(reduced);

    Branch_Bound(matrix, reduced);
    return 0;
}
