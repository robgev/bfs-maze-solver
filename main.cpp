#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Edge {
public:
    int v1;
    int v2;
    int weight;
};

class Edge2 {
public:
    Edge2() = default;
    Edge2(int v2, int weight)
            : v2(v2)
            , weight(weight)
    { }
    int v2;
    int weight;
};

// Adjacency list.
vector<vector<Edge2>> G;

// Adjacency matrix.
vector<vector<int>> G_matrix;

// List of edges.
vector<Edge> G_edges;

// Maze
vector<vector<char>> maze;

void maze_to_graph() {
    int vertexNumber = 0;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[0].size(); j++) {
            if (maze[i][j] == '.') {
                if (i + 1 < maze.size() && maze[i + 1][j] == '.') {
                    Edge current;
                    int vertex2Index = vertexNumber + maze[0].size();
                    current.v1 = vertexNumber;
                    current.v2 = vertexNumber + maze[0].size();
                    G[vertexNumber].push_back(Edge2(current.v2, 1));
                    G[vertex2Index].push_back(Edge2(current.v1, 1));
                }
                if (j + 1 < maze[0].size() && maze[i][j + 1] == '.') {
                    Edge current;
                    current.v1 = vertexNumber;
                    current.v2 = vertexNumber + 1;
                    G[vertexNumber].push_back(Edge2(current.v2, 1));
                    G[vertexNumber + 1].push_back(Edge2(current.v1, 1));
                }
            }
            vertexNumber++;
        }
    }
}

void read_maze() {
    int height, width;
    cin >> height >> width;

    maze.resize(height);
    for (int i = 0; i < height; ++i) {
        maze[i].resize(width);
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cin >> maze[i][j];
        }
    }
    G.resize(height * width);
    maze_to_graph();

}

vector<int> marked;
bool found = false;
void bfs(int v) { // speed = O(|E|)
    queue <int> q;
    marked[v] = -1;
    q.push(v);

    while (!q.empty()) {
        int cv = q.front();

        for (int i = 0; i < G[cv].size(); i++) {
            if (marked[G[cv][i].v2] == -2) {
                marked[G[cv][i].v2] = cv;
                q.push(G[cv][i].v2);
            }
        }

        q.pop();
    }

}

void draw_path() {
    int i = G.size() - 1,
        height = maze.size(),
        width = maze[0].size();
    maze[height - 1][width - 1] = 'x';
    while(marked[i] != -1) {
        int x = marked[i] / width;
        int y = marked[i] % width;
        maze[x][y] = 'x';
        i = marked[i];
    }
}

void output_path() {
    for(int i = 0; i < maze.size(); i++) {
        for(int j = 0; j < maze[0].size(); j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

int main() {
    read_maze();
    marked.resize(G.size()); // size = |V|.
    for (int i = 0; i < G.size(); ++i)
        marked[i] = -2;
    bfs(0);
    draw_path();
    output_path();
    return 0;
}
/*
6 9
..#....##
#...##.##
##.#....#
#..######
#.......#
######...

*/