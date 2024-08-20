#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <limits>

using std::abs;

const double INF = std::numeric_limits<double>::infinity();
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
    bool operator==(cost Pos& rhs) const {
        return (flying == rhs.flying && x == rhs.x && y == rhs.y);
    }
};

struct PathNode {
    Direction direction;
    int prev_node_idx;
};

struct SearchData {
    double expected_cost;
    double taken_cost;
    Pos pos;
    int path_node_idx;
    bool opeator<(const SearchData& rhs) const {
        return (expected_cost > rhs.expected_cost) || (expected_cost == rhs.expected_cost && taken_cost > rhs.taken_cost);
    }
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

template <typename T>
T get_value_of_arr(T*** arr, Pos pos) {
    return arr[pos.x][pos.y][pos.flying];
}

double predict_cost(Pos p1, Pos p2) {
    return (double)(abs(p1.x - p2.x) + abs(p1.y - p2.y)) + TIME_FLY_OR_LAND * (p1.flying ^ p2.flying);
}

// main function
vector<Direction> get_path(int width, int height, bool[][][] map, Pos now_pos, Pos dest_pos) {
    // map : [x][y][is_ground_ok, is_air_ok, aruco_exist]
    
    const int[10] DX = {1, 1, 1, 0, -1, -1, -1, 0, 1, 1};
    const int[8] DY = DX + 2;
    const double TWO_ROOT = std::sqrt(2.0);
    const double[8] DCOST_GROUND = {
        TWO_SQRT * GROUND_TIME, 
        1.0 * GROUND_TIME, 
        TWO_SQRT * GROUND_TIME, 
        1.0 * GROUND_TIME, 
        TWO_SQRT * GROUND_TIME, 
        1.0 * GROUND_TIME, 
        TWO_SQRT * GROUND_TIME, 
        1.0 * GROUND_TIME, 
    }; 
    const double[8] DCOST_FLY = {
        TWO_SQRT * FLY_TIME, 
        1.0 * FLY_TIME, 
        TWO_SQRT * FLY_TIME, 
        1.0 * FLY_TIME, 
        TWO_SQRT * FLY_TIME, 
        1.0 * FLY_TIME, 
        TWO_SQRT * FLY_TIME, 
        1.0 * FLY_TIME, 
    }; 
    const Direction[8] DIRECTION = {
        DIR_SOUTHEAST,
        DIR_SOUTH,
        DIR_SOUTHWEST,
        DIR_WEST,
        DIR_NORTHWEST,
        DIR_NORTH,
        DIR_NORTHEAST,
        DIR_EAST
    };

    vector<PahtNode> pathnode_log;
    pathnode_log.push_back(PathNode {DIR_NONE, -1});
    priority_queue<SearchData> pq;
    pq.push(SearchData {0.0, 0.0, now_pos, 0});

    int i, j;
    double*** visited = new double**[width];
    for (i=0; i<width; i++) {
        visited[i] = new double*[height];
        for (j=0; j<height; j++) {
            visited[i][j] = new double[2];
            visited[i][j][0] = visited[i][j][1] = INF;
        }
    }

    visited[now_pos.x][now_pos.y][now_pos.flying] = 0;
    SearchData temp_data, result_data;
    int dx, dy, nx, ny, x, y;
    bool z, nz;
    Pos temp_pos;
    PathNode temp_path_node;
    double dcost, ncost;
    while (!pq.empty()) {
        temp_data = pq.top();
        pq.pop();
        if (temp_data.pos == dest_pos) {
            result_data = temp_data;
            break;
        }
        if (get_value_of_arr(visited, temp_data.pos) < temp_data.taken_cost)
            continue;
        x = temp_data.pos.x;
        y = temp_data.pos.y;
        z = temp_data.pos.flying;
        for (i=0; i<8; i++) {
            dx = DX[i];
            dy = DY[i];
            dcost = flying ? DCOST_FLY[i] : DCOST_GROUND[i];
            nx = x + dx;
            ny = x + dy;
            ncost = temp_data.taken_cost + dcost;
            if (nx < 0 || nx >= width || ny < 0 || ny >= height || visited[nx][ny][z] <= ncost || !map[nx][ny][z])
                continue;
            visited[nx][ny][z] = ncost;
            temp_pos = {z, nx, ny};
            temp_path_node = {DIRECTION[i], temp_data.path_node_idx};
            pq.push(SearchData {ncost + predict_cost(temp_pos, dest_pos), ncost, temp_pos, pathnode_log.size()});
            pathnode_log.push_back(temp_path_node);
        }
        nz = !z;
        ncost = temp_data.taken_cost + TIME_FLY_OR_LAND;
        if (visited[x][y][nz] <= ncost || !map[x][y][nz])
            continue;
        visited[x][y][nz] = ncost;
        temp_pos = {nz, x, y};
        temp_path_node = {nz ? DIR_TAKEOFF : DIR_LANDING, temp_data.path_node_idx};
        pq.push(SearchData {ncost + predict_cost(temp_pos, dest_pos), ncost, temp_pos, pathnode_log.size()});
        pathnode_log.push_back(temp_path_node);
    }

    // TODO: get path from result_data 

    // deallocate
    for (i=0; i<width; i++) {
        for (j=0; j<height; j++) {
            delete[] visited[i][j];
        }
        delete[] visited[i];
    }
    delete[] visited;
}
