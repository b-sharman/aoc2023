#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    size_t nl, nn;
    cin>>nl>>nn;

    string s;
    ll temp;
    vector<vector<ll>> histories;
    vector<ll> history;
    for (size_t i=0; i<nl; i++) {
        history.clear();
        for (size_t j=0; j<nn; j++) { cin>>temp; history.push_back(temp); }
        histories.push_back(history);
    }

    vector<ll> answers;
    for (const auto& history : histories) {
        vector<vector<ll>> diffs;
        diffs.push_back(history);
        vector<ll> diff {-1};
        while (!diff.empty() && !all_of(diff.begin(), diff.end(), [](const auto& v){return v==0;})) {
            diff.clear();
            for (size_t i=1; i<diffs.back().size(); i++) {
                diff.push_back(diffs.back().at(i) - diffs.back().at(i-1));
                cout << diff.back() << " ";
            }
            cout << endl;
            diffs.push_back(diff);
        }

        vector<ll> begins {0};
        for (auto it=prev(diffs.end(), 2); it>=diffs.begin(); advance(it, -1)) {
            begins.push_back((*it).front() - begins.back());
        }
        cout << "begin: " << begins.back() << endl;
        answers.push_back(begins.back());
    }
    cout << accumulate(answers.begin(), answers.end(), 0) << endl;

    return 0;
}
