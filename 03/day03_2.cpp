// requires C++23 or newer

#include <bits/stdc++.h>

using namespace std;

const string DIGITS {"0123456789"};

int main() {
    size_t nl;
    cin>>nl;
    vector<string> v;
    vector<pair<size_t,size_t>> symbol_coords;
    string x;
    size_t num_size;
    for (size_t i=0; i<nl; i++) {
        cin>>x; v.push_back(x);
        for (size_t j=0; j<x.size(); j++) {
            // if it's a *, add it to symbol_coords
            if (x.at(j) == '*') {
                symbol_coords.emplace_back(i, j);
                cout<<"added symbol at ("<<i<<", "<<j<<")"<<endl;
            }
        }
    }

    long long sum=0;
    size_t min_row, max_row, min_col, max_col; // for bounds checking
    vector<size_t> digits;
    for (const auto& sc : symbol_coords) {
        min_row = max(static_cast<size_t>(0), sc.first-1);
        max_row = min(v.size(), sc.first+1);
        min_col = max(static_cast<size_t>(0), sc.second-1);
        max_col = min(v.at(0).size(), sc.second+1);
        cout
            <<endl
            <<"val ("<<sc.first<<", "<<sc.second<<")"<<endl
            <<"min_row "<<min_row<<endl
            <<"max_row "<<max_row<<endl
            <<"min_col "<<min_col<<endl
            <<"max_col "<<max_col<<endl;

        digits.clear();
        for (size_t row=min_row; row<=max_row; row++) {
            for (size_t col=min_col; col<=max_col; col++) {
                // if we find a digit
                if (v.at(row).at(col) >= 48 && v.at(row).at(col) <= 57) {
                    // go forward and backward to get the whole digit
                    size_t beg_ = col;
                    while (beg_ > 0 && (v.at(row).at(beg_-1) >= 48 && v.at(row).at(beg_-1) <= 57)) beg_--;
                    size_t end_ = col;
                    while (end_ < v.at(row).size()-1 && (v.at(row).at(end_+1) >= 48 && v.at(row).at(end_+1) <= 57)) end_++;
                    cout<<"str is "<<v.at(row).substr(beg_, end_-beg_+1)<<endl;
                    digits.push_back(stoul(v.at(row).substr(beg_, end_-beg_+1)));
                    cout<<"added "<<digits.at(digits.size()-1)<<endl;
                    col = end_;
                }
            }
        }
        if (digits.size() == 2) {
            sum += digits.at(0) * digits.at(1);
        }
    }
    cout<<sum<<endl;

    return 0;
}
