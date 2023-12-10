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

const unordered_map<char, vector<D>> CHAR_MAP {
    {'|', {NORTH, SOUTH}},
    {'-', {EAST, WEST}},
    {'L', {NORTH, EAST}},
    {'J', {NORTH, WEST}},
    {'7', {SOUTH, WEST}},
    {'F', {SOUTH, EAST}},
    {'.', {}},
    {'S', {NORTH, WEST, EAST, SOUTH}}
};

const unordered_map<D, D> OPPOSITES {
    {NORTH, SOUTH},
    {WEST, EAST},
    {SOUTH, NORTH},
    {EAST, WEST}
};

const unordered_map<D, char> FILLER {
    {NORTH, '|'},
    {WEST, '-'},
    {SOUTH, '|'},
    {EAST, '-'}
};

const array<D, 4> DIRECTION_ORDER {
    NORTH,
    WEST,
    SOUTH,
    EAST
};

string coord_str(const coord_t& c) {
    stringstream ss;
    ss << "(" << c.x << ", " << c.y << ")";
    return ss.str();
}

coord_t move_coord(coord_t c, D d, int increment) {
    switch (d) {
        case NORTH:
            c.y -= increment;
            break;
        case WEST:
            c.x -= increment;
            break;
        case SOUTH:
            c.y += increment;
            break;
        case EAST:
            c.x += increment;
            break;
    };
    return c;
}

// return the first found valid next direction based on a coordinate
coord_t next_coord(vector<string>& tiles, const coord_t& c, const coord_t& prev, vector<coord_t>* already_visited = nullptr) {
    coord_t p_coord;
    for (const D& dir : CHAR_MAP.at(tiles.at(c.y).at(c.x))) {
        p_coord = move_coord(c, dir, 2);
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
                if (OPPOSITES.at(next_dir) == dir) {
                    coord_t filler_coord = move_coord(p_coord, next_dir, 1);
                    tiles.at(filler_coord.y).at(filler_coord.x) = FILLER.at(next_dir);
                    if (already_visited != nullptr) {
                        already_visited->push_back(p_coord);
                        already_visited->push_back(filler_coord);
                    }
                    return p_coord;
                }
            }
        }
    }

    cout << "No valid coord found, uh oh!" << endl;
    return {-1, -1};
}

pair<coord_t, coord_t> coords_from_start(vector<string>& tiles, const coord_t& start_coord, vector<coord_t>* already_visited) {
    pair<coord_t, coord_t> retval;
    retval.first = next_coord(tiles, start_coord, {-1, -1}, already_visited);
    retval.second = next_coord(tiles, start_coord, retval.first, already_visited);
    return retval;
}

void print_tiles(const vector<string>& tiles) {
    cout << "\n\n\n";
    for (const string& s : tiles) cout << s << '\n';

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
        temp = "." + temp + ".";
        string spaced;
        for (const char& c : temp) {
            spaced += c;
            spaced += ' ';
        }
        spaced = spaced.substr(0, spaced.size()-1);

        start_coord_x = spaced.find('S');
        if (start_coord_x != spaced.npos) {
            start_coord = {start_coord_x, 2*i+2};
            cout << coord_str(start_coord) << endl;
        }
        tiles.push_back(spaced);
        tiles.emplace_back(spaced.size(), ' ');
    }

    string end_string;
    for (size_t i=0; i<w+2; i++) {
        end_string += ". ";
    }
    end_string = end_string.substr(0, end_string.size()-1);
    tiles.emplace(tiles.begin(), tiles.at(0).size(), ' ');
    tiles.insert(tiles.begin(), end_string);
    tiles.push_back(end_string);

    vector<coord_t> already_visited {start_coord};
    pair<coord_t, coord_t> cs = coords_from_start(tiles, start_coord, &already_visited);
    coord_t c0 = cs.first;
    coord_t c1 = cs.second;
    coord_t prev0 = start_coord;
    coord_t prev1 = start_coord;
    coord_t temp0;
    coord_t temp1;
    while (c0 != c1) {
        temp0 = c0;
        temp1 = c1;
        c0 = next_coord(tiles, c0, prev0, &already_visited);
        c1 = next_coord(tiles, c1, prev1, &already_visited);
        prev0 = temp0;
        prev1 = temp1;
    }

    print_tiles(tiles);

    // BFS to find all the Os
    // this is shamelessly ripped from my CSCI 200 assignment
    queue<coord_t> to_visit;
    to_visit.emplace(0, 0);
    already_visited.emplace(already_visited.begin(), 0, 0);
    tiles.at(0).at(0) = 'O';
    while (!to_visit.empty()) {
        coord_t visiting = to_visit.front();
        to_visit.pop();
        for (const auto& dir: DIRECTION_ORDER) {
            coord_t neighbor = move_coord(visiting, dir, 1);
            // don't go out of bounds
            if (neighbor.x < 0 || neighbor.x >= tiles.at(0).size() || neighbor.y < 0 || neighbor.y >= tiles.size()) continue;
            char& neighbor_char = tiles.at(neighbor.y).at(neighbor.x);
            if (find(already_visited.begin(), already_visited.end(), neighbor) == already_visited.end()) {
                // neighbor_char should be a reference, causing this line to overwrite tiles
                neighbor_char = 'O';
                // print_tiles(tiles);
                to_visit.push(neighbor);
                already_visited.push_back(neighbor);
            }
        }
    }

    for (size_t row=0; row<tiles.size(); row++) {
        for (size_t col=0; col<tiles.at(row).size(); col++) {
            char& tile = tiles.at(row).at(col);
            if (
                tile != 'O'
                &&
                find(
                    already_visited.begin(),
                    already_visited.end(),
                    coord_t {col, row}
                ) == already_visited.end()
            ) {
                tile = 'I';
            }
        }
    }

    print_tiles(tiles);

    // remove every other row and col
    int ans = 0;
    vector<string> new_tiles;
    for (size_t i=2; i<tiles.size()-2; i+=2) {
        string temp;
        for (size_t j=2; j<tiles.at(i).size()-2; j+=2) {
            temp += tiles.at(i).at(j);
        }
        ans += count(temp.begin(), temp.end(), 'I');
        new_tiles.push_back(temp);
    }
    print_tiles(new_tiles);

    cout << ans << endl;

    return 0;
}
