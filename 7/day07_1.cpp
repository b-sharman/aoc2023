#include <bits/stdc++.h>
#include <execution>

using namespace std;

const unordered_map<char, int> RANK
{
    {'2',  0},
    {'3',  1},
    {'4',  2},
    {'5',  3},
    {'6',  4},
    {'7',  5},
    {'8',  6},
    {'9',  7},
    {'T',  8},
    {'J',  9},
    {'Q', 10},
    {'K', 11},
    {'A', 12},
};

struct Player {
    string h;
    int b;
};

bool n_of_a_kind(const string& h, const int& n) {
    for (const auto& c : h) {
        if (count(h.begin(), h.end(), c) >= n) return true;
    }
    return false;
}

bool full_house(const string& h) {
    for (size_t i=0; i<h.size()-1; i++) {
        for (size_t j=i+1; j<h.size(); j++) {
            if (
                (count(h.begin(), h.end(), h.at(i)) == 3 && count(h.begin(), h.end(), h.at(j)) == 2)
                ||
                (count(h.begin(), h.end(), h.at(i)) == 2 && count(h.begin(), h.end(), h.at(j)) == 3)
            ) return true;
        }
    }
    return false;
}

bool two_pair(const string& h) {
    char prev_pair = 'x';
    for (const auto& c : h) {
        if (c != prev_pair && count(h.begin(), h.end(), c) >= 2) {
            if (prev_pair != 'x') return true;
            prev_pair = c;
        }
    }
    return false;
}

// returns 0 to 6, higher is better
int hand_rank(const string& h) {
    int ret = 0;
    if (n_of_a_kind(h, 2)) ret = 1;
    if (two_pair(h))       ret = 2;
    if (n_of_a_kind(h, 3)) ret = 3;
    if (full_house(h))     ret = 4;
    if (n_of_a_kind(h, 4)) ret = 5;
    if (n_of_a_kind(h, 5)) ret = 6;
    return ret;
}

bool card_comp(const Player& a, const Player& b) {
    int a_hand_rank = hand_rank(a.h);
    int b_hand_rank = hand_rank(b.h);
    if (a_hand_rank != b_hand_rank) return a_hand_rank < b_hand_rank;

    int a_rank;
    int b_rank;
    for (size_t i=0; i<5; i++) {
        a_rank = RANK.at(a.h.at(i));
        b_rank = RANK.at(b.h.at(i));
        if (a_rank != b_rank) return a_rank < b_rank;
    }
    return false;
}

int main() {
    size_t nl;
    cin>>nl;

    vector<Player> players;
    string temp_hand;
    int temp_bid;
    for (size_t i=0; i<nl; i++) {
        cin>>temp_hand;
        cin>>temp_bid;
        players.emplace_back(temp_hand, temp_bid);
    }

    /*
    // debug
    for (const Player& p : players) {
        cout << p.h << endl;
        if (n_of_a_kind(p.h, 2)) cout << "n_of_a_kind(p.h, 2)" << endl;
        if (two_pair(p.h))       cout << "two_pair(p.h)" << endl;
        if (n_of_a_kind(p.h, 3)) cout << "n_of_a_kind(p.h, 3)" << endl;
        if (full_house(p.h))     cout << "full_house(p.h)" << endl;
        if (n_of_a_kind(p.h, 4)) cout << "n_of_a_kind(p.h, 4)" << endl;
        if (n_of_a_kind(p.h, 5)) cout << "n_of_a_kind(p.h, 5)" << endl;
        cout << endl;
    }
    */

    sort(execution::par, players.begin(), players.end(), card_comp);

    long long ans = 0;
    for (size_t i=0; i<players.size(); i++) {
        ans += players.at(i).b * (i+1);
    }
    cout << ans << endl;

    return 0;
}
