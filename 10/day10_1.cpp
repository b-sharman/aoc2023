#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
typedef pair<int, int> coord_t;

enum D {
    NORTH,
    WEST,
    SOUTH,
    EAST
};

unordered_map<char, vector<D>> CHAR_MAP {
    {'|', {NORTH, SOUTH}},
    {'-', {EAST, WEST}},
    {'L', {NORTH, EAST}},
    {'J', {NORTH, WEST}},
    {'7', {SOUTH, WEST}},
    {'F', {SOUTH, EAST}},
    {'.', {}},
    {'S', {NORTH, WEST, EAST, SOUTH}}
};

unordered_map<D, D> OPPOSITES {
    {NORTH, SOUTH},
    {WEST, EAST},
    {SOUTH, NORTH},
    {EAST, WEST}
};

string coord_str(const coord_t& c) {
    stringstream ss;
    ss << "(" << c.x << ", " << c.y << ")";
    return ss.str();
}

coord_t move_coord(coord_t c, D d) {
    switch (d) {
        case NORTH:
            c.y--;
            break;
        case WEST:
            c.x--;
            break;
        case SOUTH:
            c.y++;
            break;
        case EAST:
            c.x++;
            break;
    };
    return c;
}

// return the first found valid next direction based on a coordinate
coord_t next_coord(const vector<string>& tiles, const coord_t& c, const coord_t& prev) {
    coord_t p_coord;
    for (const D& dir : CHAR_MAP.at(tiles.at(c.y).at(c.x))) {
        p_coord = move_coord(c, dir);
        if (
            p_coord != prev
            &&
            p_coord.x >=0 && p_coord.x < tiles.at(c.y).size()
            &&
            p_coord.y >=0 && p_coord.y < tiles.size()
        ) {
            // for each direction of CHAR_MAP.at(p_coord)
            // if the opposite of that direction is one of the directions of CHAR_MAP.at(c), return p_coord
            for (const D& next_dir : CHAR_MAP.at(tiles.at(p_coord.y).at(p_coord.x))) {
                if (OPPOSITES.at(next_dir) == dir) return p_coord;
            }
        }
    }

    cout << "No valid coord found, uh oh!" << endl;
    return {-1, -1};
}

pair<coord_t, coord_t> coords_from_start(const vector<string>& tiles, const coord_t& start_coord) {
    pair<coord_t, coord_t> retval;
    retval.first = next_coord(tiles, start_coord, {-1, -1});
    retval.second = next_coord(tiles, start_coord, retval.first);
    return retval;
}

int main() {
    size_t h, w;
    cin>>h>>w;

    vector<string> tiles;
    string temp; getline(cin, temp);
    coord_t start_coord;
    size_t start_coord_x;
    for (size_t i=0; i<h; i++) {
        getline(cin, temp);
        start_coord_x = temp.find('S');
        if (start_coord_x != temp.npos) {
            start_coord = {start_coord_x, i};
            cout << coord_str(start_coord) << endl;
        }
        tiles.push_back(temp);
    }

    /**
     * start at S
     * determine which of the four adjacent tiles are the correct pipes
     * while the loop is incomplete
     *     for each of those tiles, find the correct next tile and increment a distance counter
     * when the two paths converge, that's the end tile
     */

    pair<coord_t, coord_t> cs = coords_from_start(tiles, start_coord);
    auto pretty_tiles = tiles;
    coord_t c0 = cs.first;
    coord_t c1 = cs.second;
    coord_t prev0 = start_coord;
    coord_t prev1 = start_coord;
    int counter = 1;
    coord_t temp0;
    coord_t temp1;
    for (; c0 != c1; counter++) {

        /*
        pretty_tiles.at(c0.y).at(c0.x) = counter+48;
        pretty_tiles.at(c1.y).at(c1.x) = counter+48;
        cout << endl;
        for (const string& s : pretty_tiles) cout << s << endl;
        */

        temp0 = c0;
        temp1 = c1;
        c0 = next_coord(tiles, c0, prev0);
        c1 = next_coord(tiles, c1, prev1);
        prev0 = temp0;
        prev1 = temp1;
    }
    cout << counter << endl;

    return 0;
}
