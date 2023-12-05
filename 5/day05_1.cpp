#include <bits/stdc++.h>

using namespace std;

struct MyMap {
    long dest, source, length;
};

int main() {
    string linestr, throwaway;
    stringstream line;
    getline(cin, linestr);
    line << linestr;
    line >> throwaway;
    getline(cin, throwaway);
    getline(cin, throwaway);

    long temp;
    vector<long> seeds;
    while (line>>temp) {
        seeds.push_back(temp);
    }

    cout << "seeds: ";
    for (const auto& s : seeds) {
        cout << s << " ";
    }
    cout << endl;

    vector<MyMap> maps;
    vector<int> group_lengths;
    linestr = "placeholder";
    long end_checker = 0; // how many blank lines in a row
    long gl = 0;
    long destt, sourcet, lengtht;
    for (; end_checker < 2; gl++) {
        getline(cin, linestr);
        if (linestr.empty()) {
            getline(cin, throwaway); // throw away the "... map:" line
            end_checker++;
            group_lengths.push_back(gl);
            gl=-1;
            continue;
        }
        end_checker = 0;

        line.clear();
        line << linestr;
        line >> destt >> sourcet >> lengtht;
        cout << "adding map: " << destt << " " << sourcet << " " << lengtht << endl;
        maps.emplace_back(destt, sourcet, lengtht);
    }
    group_lengths.pop_back();

    MyMap m;
    for (auto& s : seeds) {
        size_t gi = 0;
        size_t gl_sum = 0;
        for (size_t i=0; i<maps.size(); i++) {
            gi = 0;
            gl_sum = 0;
            for (const auto& gl : group_lengths) {
                gl_sum += gl;
                if (gl_sum > i) {
                    break;
                }
                gi++;
            }
            m = maps.at(i);
            cout << s << " -> " << m.dest << " " << m.source << " " << m.length << " -> ";
            // if the seed is in the map
            if (s >= m.source && s < m.source+m.length) {
                // change the seed to its mapped value
                s += m.dest-m.source;
                // skip to the next group of maps
                if (gi+1 >= group_lengths.size()) {
                    cout << "X" << endl;
                    break; // move to next seed
                }
                // -1 because i will get incremented at the end of the loop
                i = accumulate(group_lengths.begin(), group_lengths.begin()+gi+1, -1);
            }
            // if the seed is not in the map, no change is required
            cout << s << endl;
        }
        cout << endl;
    }

    cout << "seeds: ";
    for (const auto& s : seeds) {
        cout << s << " ";
    }
    cout << endl;

    cout << "min location: " << *min_element(seeds.begin(), seeds.end()) << endl;

    return 0;
}
