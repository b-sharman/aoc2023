#include <bits/stdc++.h>
#include <execution>

using namespace std;

typedef unsigned long long ull;

int main() {
    string lr;
    cin>>lr;

    unordered_map<string, pair<string, string>> nodes;

    string throwaway, from, l, r;
    getline(cin, throwaway);
    getline(cin, throwaway);
    string line = "not empty";
    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        cout << line << endl;

        stringstream ss {line};
        ss >> from >> throwaway >> l >> r;
        l = l.substr(1, 3);
        r = r.substr(0, 3);
        cout << from << " " << l << " " << r << endl;
        nodes.emplace(from, make_pair(l, r));
    }

    vector<string> starting_poses;
    for (const auto& node : nodes) {
        if (node.first.at(2) == 'A') starting_poses.push_back(node.first);
    }

    vector<ull> cycle_lengths;
    for (string& pos : starting_poses) {
        vector<string> history {pos};
        ull num_steps = 0;
        for (; true; num_steps++) {
            if (lr.at(num_steps % lr.size()) == 'L') pos = nodes.at(pos).first;
            else pos = nodes.at(pos).second;
            history.emplace_back(pos);
            if (pos.at(2) == 'Z') {
                auto it = find(history.begin(), prev(history.end()), history.back());
                if (it != prev(history.end())) {
                    cycle_lengths.push_back(distance(it, prev(history.end())));
                    break;
                }
            }
        }
    }

    cout << accumulate(cycle_lengths.begin(), cycle_lengths.end(), 1ull, lcm<ull, ull>) << endl;

    return 0;
}
