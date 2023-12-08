#include <bits/stdc++.h>

using namespace std;

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

    string current_pos = "AAA";
    long long num_steps = 0;
    while (current_pos != "ZZZ") {
        if (lr.at(num_steps % lr.size()) == 'L') current_pos = nodes.at(current_pos).first;
        else current_pos = nodes.at(current_pos).second;
        num_steps++;
    }
    cout << num_steps << endl;

    return 0;
}
