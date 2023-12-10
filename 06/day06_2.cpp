#include <bits/stdc++.h>

using namespace std;

// constexpr int NUM_RACES {3}; // sample
constexpr int NUM_RACES {4}; // real

int main() {
    string time_s, distance_s;
    string temp;
    string throwaway;
    cin>>throwaway;
    for (size_t i=0; i<NUM_RACES; i++) {
        cin>>temp;
        time_s += temp;
    }
    cin>>throwaway;
    for (size_t i=0; i<NUM_RACES; i++) {
        cin>>temp;
        distance_s += temp;
    }
    long long time = stoll(time_s);
    long long distance = stoll(distance_s);

    // for each race
    // determine the number of ways to beat the record (wbrs)
    // multiply all those together to get the answer
    long long wbr = 0;
    for (size_t h=0; h<time; h++) {
        wbr += (time - h) * h > distance;
    }
    cout << wbr << endl;

    return 0;
}
