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
    int x, num_match;
    vector<int> wn;
    vector<int> yh;
    int ans=0;
    for (size_t i=0; i<nl; i++) {
        cin>>throwaway;
        cin>>throwaway;
        wn.clear();
        yh.clear();
        for (size_t j=0; j<NUM_WN; j++) {
            cin>>x;
            wn.push_back(x);
        }
        // discard the |
        cin>>throwaway;
        for (size_t j=0; j<NUM_YH; j++) {
            cin>>x;
            yh.push_back(x);
        }

        num_match=-1;
        cout << endl << "Card " << i+1 << endl;
        for (const auto& wne : wn) {
            for (const auto& yhe : yh) {
                if (yhe == wne) {
                    num_match++;
                    // cout << yhe << " matches " << wne << endl;
                }
            }
        }
        if (num_match > -1) {
            ans += pow(2, num_match);
            cout << "num_match: " << num_match << endl;
            cout << "ans is now " << ans << endl;
        }
    }
    cout << ans << endl;

    return 0;
}
