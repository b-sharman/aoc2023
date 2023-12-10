#include <bits/stdc++.h>

using namespace std;

// constexpr int NUM_WN {5}; // 5 for sample, 10 for real
constexpr int NUM_WN {10}; // 5 for sample, 10 for real
// constexpr int NUM_YH {8}; // 8 for sample, 25 for real
constexpr int NUM_YH {25}; // 8 for sample, 25 for real

int main() {
    size_t nl;
    cin>>nl;

    string throwaway;
    int x, c;
    vector<int> wn;
    vector<int> yh;
    vector<int> copies(nl, 1);
    for (size_t i=0; i<nl; i++) {
        cin>>throwaway;
        cin>>throwaway;
        wn.clear();
        yh.clear();
        for (size_t j=0; j<NUM_WN; j++) {
            cin>>x;
            wn.push_back(x);
        }
        cin>>throwaway; // discard the |
        for (size_t j=0; j<NUM_YH; j++) {
            cin>>x;
            yh.push_back(x);
        }

        c = 0;
        for (const auto& wne : wn) {
            for (const auto& yhe : yh) {
                if (yhe == wne) {
                    c++;
                }
            }
        }
        for (size_t j=1; j<=c; j++) {
            copies.at(i+j) += copies.at(i);
        }
    }
    cout << accumulate(copies.begin(), copies.end(), 0) << endl;

    return 0;
}
