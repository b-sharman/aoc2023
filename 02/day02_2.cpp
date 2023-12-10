#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t nl;
    cin>>nl;
    string line, gamestr;
    bool x;
    int endindex(-1), ans(0);
    unordered_map<string, unsigned int> colors;
    unordered_map<string, unsigned int> lmax;
    getline(cin, line); // discard empty line
    for (size_t i=1; i<=nl; i++) {
        getline(cin, line);
        cout<<"line: '"<<line<<"'"<<endl;
        line = line.substr(line.find(":") +2);
        cout<<"analyzing line "<<i<<endl;
        x=true;
        lmax = {{"red", 0}, {"green", 0}, {"blue", 0}};
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
                if (color=="red" && num>lmax.at("red")) {
                    lmax.at("red")=num;
                }
                if (color=="green" && num>lmax.at("green")) {
                    lmax.at("green")=num;
                }
                if (color=="blue" && num>lmax.at("blue")) {
                    lmax.at("blue")=num;
                }
            }
            line = line.substr(min(line.size(), static_cast<size_t>(endindex+2)));
        }
        cout<<"adding "<<lmax.at("red")*lmax.at("green")*lmax.at("blue")<<endl;
        ans += lmax.at("red")*lmax.at("green")*lmax.at("blue");
    }
    cout<<ans<<endl;

    return 0;
}
