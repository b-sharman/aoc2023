#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct MyMap {
    ll dest, source, length;
};

struct SeedRange {
    ll beg, end;
    int starting_mi; // starting map index

    string repr() const {
        stringstream result;
        result << "[" << beg << ", " << end << "]: " << starting_mi;
        return result.str();
    }
};

int main() {
    string linestr, throwaway;
    stringstream line;
    getline(cin, linestr);
    line << linestr;
    line >> throwaway;
    getline(cin, throwaway);
    getline(cin, throwaway);

    ll temp, beg_range;
    list<SeedRange> seed_ranges;
    for (size_t i=0; line>>temp; i++) {
        if (i % 2) {
            // temp is range size
            seed_ranges.emplace_back(beg_range, beg_range+temp-1, 0);
        }
        else {
            beg_range = temp;
        }
    }

    cout << "seed ranges: ";
    for (const auto& sr : seed_ranges) {
        cout << sr.repr() << "; ";
    }
    cout << endl;

    vector<MyMap> maps;
    vector<int> group_lengths;
    linestr = "placeholder";
    ll end_checker = 0; // how many blank lines in a row
    ll gl = 0;
    ll destt, sourcet, lengtht;
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

    cout << "group lengths: ";
    for (const auto& gl : group_lengths) {
        cout << gl << " ";
    }
    cout << endl;

    MyMap m;
    for (auto sr = seed_ranges.begin(); sr!=seed_ranges.end(); sr++) {
        size_t gi = 0;
        size_t gl_sum = 0;
        for (size_t i=sr->starting_mi; i<maps.size(); i++) {
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

            // don't do anything if the map does not apply to this range
            if (sr->end < m.source || sr->beg >= m.source+m.length) continue;

            cout << "sr: " << sr->repr() << " -> " << m.dest << " " << m.source << " " << m.length << " -> ";

            // if the seed range is within the map range
            // push sr->beg and sr->end through the mapping process
            // otherwise, delete sr and add two to three new srs
            if (sr->beg >= m.source && sr->end < m.source+m.length) {
                sr->beg += m.dest-m.source;
                sr->end += m.dest-m.source;
                // skip to the next group of maps
                if (gi+1 >= group_lengths.size()) {
                    break; // move to next seed
                }
                // -1 because i will get incremented at the end of the loop
                // TODO: would std::advance be a better way to do this?
                i = accumulate(group_lengths.begin(), group_lengths.begin()+gi+1, -1);
            }
            else {
                cout << "partial intersection of sr " << sr->repr() << " and m " << m.dest << " " << m.source << " " << m.length << endl;
                if (sr->beg < m.source) {
                    seed_ranges.emplace_back(sr->beg, m.source-1, i);
                    seed_ranges.emplace_back(m.source, min(sr->end, m.source+m.length-1), i);
                    if (sr->end >= m.source+m.length) { // sr surrounds map range
                        seed_ranges.emplace_back(m.source+m.length, sr->end, i);
                    }
                }
                else if (sr->end >= m.source+m.length) {
                    seed_ranges.emplace_back(sr->beg, m.source+m.length-1, i);
                    seed_ranges.emplace_back(m.source+m.length, sr->end, i);
                }
                sr = seed_ranges.erase(sr);
                sr--; // offset the increment of the next iteration
                cout << "X" << endl;
                break;
            }

            cout << sr->repr() << endl;

            // if the seed is not in the map, no change is required
        }
    }

    cout << "seed ranges: ";
    for (const auto& sr : seed_ranges) {
        cout << sr.repr() << "; ";
    }
    cout << endl;

    cout << "min location: " << min_element(
        seed_ranges.begin(),
        seed_ranges.end(),
        [](const auto& a, const auto& b) {return a.beg < b.beg;}
    )->beg << endl;

    return 0;
}
