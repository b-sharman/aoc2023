#include <bits/stdc++.h>

using namespace std;

// constexpr int NUM_RACES {3}; // sample
constexpr int NUM_RACES {4}; // real

int main() {
    vector<int> times;
    vector<int> distances;
    int temp;
    string throwaway;
    cin>>throwaway;
    for (size_t i=0; i<NUM_RACES; i++) {
        cin>>temp;
        times.push_back(temp);
    }
    cin>>throwaway;
    for (size_t i=0; i<NUM_RACES; i++) {
        cin>>temp;
        distances.push_back(temp);
    }

    // for each race
    // determine the number of ways to beat the record (wbrs)
    // multiply all those together to get the answer
    int ans = 1;
    int wbr;
    for (size_t i=0; i<NUM_RACES; i++) {
        wbr = 0;
        for (size_t h=0; h<times.at(i); h++) {
            wbr += (times.at(i) - h) * h > distances.at(i);
        }
        ans *= wbr;
    }
    cout << ans << endl;

    return 0;
}
