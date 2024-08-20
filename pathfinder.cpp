#include <vector>
#include <queue>
#include <string>
#include <cmath>

using std::abs;

const double GROUND_TIME = 1.0;
const double FLY_TIME = 1.0;
const double TIME_FLY_OR_LAND = 5.0;

enum Direction {
    DIR_NONE,
    DIR_SOUTHEAST,
    DIR_SOUTH,
    DIR_SOUTHWEST,
    DIR_WEST,
    DIR_NORTHWEST,
    DIR_NORTH,
    DIR_NORTHEAST,
    DIR_EAST,
    DIR_TAKEOFF,
    DIR_LANDING
};

struct Pos {
    bool flying;
    int x;
    int y;
};

struct PathNode {
    Direction direction;
    PathNode* prev_node;
};

struct SearchData {
    double expected_cost;
    double taken_cost;
    Pos pos;
    PathNode* prev_path_node;  // todo: really works???
};

std::string getDirectionName(Direction d) {
    switch (d) {
    	case DIR_SOUTHEAST:
			return std::string("SOUTHEAST");
    	case DIR_SOUTH:
			return std::string("SOUTH");
    	case DIR_SOUTHWEST:
			return std::string("SOUTHWEST");
    	case DIR_WEST:
			return std::string("WEST");
    	case DIR_NORTHWEST:
			return std::string("NORTHWEST");
    	case DIR_NORTH:
			return std::string("NORTH");
    	case DIR_NORTHEAST:
			return std::string("NORTHEAST");
    	case DIR_EAST:
			return std::string("EAST");
    	case DIR_TAKEOFF:
			return std::string("TAKEOFF");
    	case DIR_LANDING:
			return std::string("LANDING");
        default:
            return std::string("none");
    }
}

double predict_cost(Pos p1, Pos p2) {
    return (double)(abs(p1.x - p2.x) + abs(p1.y - p2.y)) + TIME_FLY_OR_LAND * (p1.flying ^ p2.flying);
}

vector<Direction> get_path(int width, int height, bool[] map, Pos now_pos, Pos dest_pos) {
    // map : [x][y][is_ground_ok, is_air_ok, aruco_exist]
    
    const int[10] DX = [1, 1, 1, 0, -1, -1, -1, 0, 1, 1];
    const int[8] DY = DX + 2;
    const double TWO_ROOT = std::sqrt(2.0);
    const double[8] DCOST_GROUND = [
        TWO_SQRT * GROUND_TIME, 
        1.0 * GROUND_TIME, 
        TWO_SQRT * GROUND_TIME, 
        1.0 * GROUND_TIME, 
        TWO_SQRT * GROUND_TIME, 
        1.0 * GROUND_TIME, 
        TWO_SQRT * GROUND_TIME, 
        1.0 * GROUND_TIME, 
    ]; 
    const double[8] DCOST_FLY = [
        TWO_SQRT * FLY_TIME, 
        1.0 * FLY_TIME, 
        TWO_SQRT * FLY_TIME, 
        1.0 * FLY_TIME, 
        TWO_SQRT * FLY_TIME, 
        1.0 * FLY_TIME, 
        TWO_SQRT * FLY_TIME, 
        1.0 * FLY_TIME, 
    ]; 

    priority_queue<> pq;
}
