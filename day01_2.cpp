#include <bits/stdc++.h>

using namespace std;

const unordered_map<string, int> DIGITS
{
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

int main() {
    size_t nl;
    cin>>nl;
    string s;
    char c;
    int a,b;
    int sum(0);
    bool found(false);
    for (size_t i=0; i<nl; i++) {
        cin>>s;
        a=b=-1;
        while (!s.empty()) {
            c=s.at(0);
            if (c >= 48 && c <= 57) {
                if (a<0) a=c-48;
                else b=c-48;
            }
            else {
                for (const auto& [ds, di] : DIGITS) {
                    if (s.starts_with(ds)) {
                        if (a<0) a=di;
                        else b=di;
                        s=s.substr(ds.size()-1);
                        found=true;
                        continue;
                    }
                }
            }
            if (!found) {
                s=s.substr(1);
            }
            found=false;
        }
        if (b<0) b=a;
        cout << "adding " << a*10+b << endl;
        sum += a*10+b;
    }
    cout << sum << endl;

    return 0;
}
