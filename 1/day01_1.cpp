#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t nl;
    cin>>nl;
    string s;
    int a,b;
    int sum(0);
    for (size_t i=0; i<nl; i++) {
        cin>>s;
        a=b=-1;
        for (const char& c : s) {
            if (c >= 48 && c <= 57) {
                if (a<0) {
                    a=c-48;
                }
                else {
                    b=c-48;
                }
            }
        }
        if (b<0) b=a;
        cout << "adding " << a*10+b << endl;
        sum += a*10+b;
    }
    cout << sum << endl;

    return 0;
}
