// requires C++23 or newer

#include <bits/stdc++.h>

using namespace std;

const string DIGITS {"0123456789"};

int main() {
    size_t nl;
    cin>>nl;
    vector<string> v;
    vector<pair<size_t,size_t>> symbol_coords;
    vector<array<int,4>> number_coords; // in order: row, col, size in chars, num value
    string x;
    size_t num_size;
    for (size_t i=0; i<nl; i++) {
        cin>>x; v.push_back(x);
        for (size_t j=0; j<x.size(); j++) {
            if (x.at(j) == '.') continue;
            // if it's not a digit, add it to symbol_coords
            if (x.at(j)<48 || x.at(j)>57) {
                symbol_coords.emplace_back(i, j);
                cout<<"added symbol at ("<<i<<", "<<j<<")"<<endl;
            }
            // otherwise, it's a number; add it to number_coords
            else {
                // find next non-digit
                size_t k=j;
                for (; k<x.size(); k++) {
                    if (!DIGITS.contains(x.at(k))) break;
                }
                k = min(k, x.size());
                number_coords.push_back({i, j, k-j, stoi(x.substr(j, k-j))});
                cout<<"added nc at ("<<i<<", "<<j<<")"<<" with size "<<k-j<<" and value "<<stoi(x.substr(j, k-j))<<endl;
                // we already know where the numbers are; skip to the next dot
                j = k-1;
            }
        }
    }

    // for each number, check if it is adjacent to a symbol
    // I hoped this would be easier than the other way because you don't have to
    // worry about double-counting numbers that are adjacent two two symbols
    size_t min_row, max_row, min_col, max_col; // for bounds checking
    int sum=0;
    for (const auto& nc : number_coords) {
        min_row = max(0, nc.at(0)-1);
        max_row = min(static_cast<int>(v.size()-1), nc.at(0)+1);
        min_col = max(0, nc.at(1)-1);
        max_col = min(static_cast<int>(v.at(0).size()-1), nc.at(1)+nc.at(2));
        cout
            <<endl
            <<"val "<<nc.at(3)<<endl
            <<"min_row "<<min_row<<endl
            <<"max_row "<<max_row<<endl
            <<"min_col "<<min_col<<endl
            <<"max_col "<<max_col<<endl;
        for (size_t row=min_row; row<=max_row; row++) {
            for (size_t col=min_col; col<=max_col; col++) {
                if (row==nc.at(0) && col>=nc.at(1) && col<nc.at(1)+nc.at(2)) {
                    continue; // don't check the number itself
                }
                if (v.at(row).at(col) != '.') {
                    cout << "adding " << nc.at(3) << endl;
                    sum += nc.at(3);
                    // break out of outer loop
                    row=max_row+1;
                    break;
                }
            }
        }
    }
    cout<<sum<<endl;

    return 0;
}
