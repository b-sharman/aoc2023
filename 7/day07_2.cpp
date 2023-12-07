#include <bits/stdc++.h>
#include <execution>

using namespace std;

const unordered_map<char, int> RANK
{
    {'J',  0},
    {'2',  1},
    {'3',  2},
    {'4',  3},
    {'5',  4},
    {'6',  5},
    {'7',  6},
    {'8',  7},
    {'9',  8},
    {'T',  9},
    {'Q', 11},
    {'K', 12},
    {'A', 13},
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

vector<string> joker_permutations(string h) {
    vector<string> ret;
    auto it = find(h.begin(), h.end(), 'J');
    if (it == h.end()) {
        ret.push_back(h);
        return ret;
    }

    // a joker is only more beneficial if it equals another card in the hand
    set<char> v;
    v.insert(h.begin(), h.end());
    for (const char& replacement : v) {
        // don't replace a joker with a joker
        if (replacement == 'J') continue;
        *it = replacement;
        vector<string> next_perms = joker_permutations(h);
        ret.insert(ret.end(), next_perms.begin(), next_perms.end());
    }
    return ret;
}

bool card_comp_h(const string& aj, const string& bj, const string& a, const string& b) {
    int a_hand_rank = hand_rank(aj);
    int b_hand_rank = hand_rank(bj);
    if (a_hand_rank != b_hand_rank) return a_hand_rank < b_hand_rank;

    int a_rank;
    int b_rank;
    for (size_t i=0; i<5; i++) {
        a_rank = RANK.at(a.at(i));
        b_rank = RANK.at(b.at(i));
        if (a_rank != b_rank) return a_rank < b_rank;
    }
    return false;
}

bool card_comp_h_noj(const string& a, const string& b) {
    return card_comp_h(a, b, a, b);
}

string best_joker_permutation(const string& h) {
    if (h == "JJJJJ") return "AAAAA";
    vector<string> pms = joker_permutations(h);
    sort(execution::par, pms.begin(), pms.end(), card_comp_h_noj);
    return pms.back();
}

bool card_comp(const Player& a, const Player& b) {
    return card_comp_h(best_joker_permutation(a.h), best_joker_permutation(b.h), a.h, b.h);
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

    sort(execution::par, players.begin(), players.end(), card_comp);

    long long ans = 0;
    for (size_t i=0; i<players.size(); i++) {
        ans += players.at(i).b * (i+1);
    }
    cout << ans << endl;

    return 0;
}
