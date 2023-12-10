#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t nl;
    cin>>nl;
    string line, gamestr;
    bool x;
    int endindex(-1), ans(0);
    unordered_map<string, unsigned int> colors;
    getline(cin, line); // discard empty line
    for (size_t i=1; i<=nl; i++) {
        getline(cin, line);
        cout<<"line: '"<<line<<"'"<<endl;
        line = line.substr(line.find(":") +2);
        cout<<"analyzing line "<<i<<endl;
        x=true;
        while (!line.empty()) {
            endindex = line.find(";");
            if (endindex == line.npos) {
                endindex = line.size();
            }
            gamestr = line.substr(0, endindex);
            istringstream gamess {gamestr};
            colors.clear();
            for (string s; getline(gamess, s, ',');) {
                if (s.starts_with(" ")) {
                    s=s.substr(1);
                }
                colors.insert({s.substr(s.find(" ")+1), stoi((s.substr(0, s.find(" "))))});
            }
            for (const auto& [color, num] : colors) {
                cout<<"color: "<<color<<", num: "<<num<<endl;
                if (
                    (color=="red" && num>12)
                    || (color=="green" && num>13)
                    || (color=="blue" && num>14)
                ) {
                    x=false;
                    break;
                }
            }
            line = line.substr(min(line.size(), static_cast<size_t>(endindex+2)));
        }
        if(x) {
            ans+=i;
            cout<<"i: "<<i<<endl;
        }
    }
    cout<<ans<<endl;

    return 0;
}
