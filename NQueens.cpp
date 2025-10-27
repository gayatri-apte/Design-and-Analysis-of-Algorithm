#include "bits/stdc++.h"
using namespace std;

class NQP {
private:
    int n;
    vector<int> x;

    bool place(int k, int i) {
        for (int j = 0; j < k; j++) {
            if (x[j] == i || abs(x[j] - i) == abs(j - k))
                return false;
        }
        return true;
    }

    void printArr() {
        cout << "\nOne of the solutions:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (x[i] == j)
                    cout << " Q ";
                else
                    cout << " . ";
            }
            cout << endl;
        }
        cout << "\nQueen positions:\n";
        for (int i = 0; i < n; i++) {
            cout << "Row " << i + 1 << " -> Column " << x[i] + 1 << endl;
        }
    }

    void Nqueens(int k) {
        for (int i = 0; i < n; i++) {
            if (place(k, i)) {
                x[k] = i;
                if (k == n - 1)
                    printArr();
                else
                    Nqueens(k + 1);
            }
        }
    }

public:
    NQP() {
        cout << "Enter the length or width of the chessboard: ";
        cin >> n;
        x.resize(n);
        cout << "\nAll possible solutions:\n";
        Nqueens(0);
    }
};

int main() {
    NQP queen;
    return 0;
}
