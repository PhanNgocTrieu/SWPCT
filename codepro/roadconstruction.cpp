// https://codepro.lge.com/exam/19/overseas-questions-for-previous-test/quiz/8

code
#include <bits/stdc++.h>
using namespace std;
 
int n; // Map Size
int a[110][110]; // Map information
const int INF = 1e9;
 
struct node {
    int x; // Vertical coordinate
    int y; // Horizontal coordinate
    int w; // Weight (for Dijkstra using priority_queue)
};
 
void input_data(){
    char tmp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            a[i][j] = (int)(tmp - '0');
        }
    }
}
 
bool check_valid(int x, int y) {
    if (x < 0 | x >= n) return false;
    if (y < 0 | y >= n) return false;
    return true;
}
 
// Write the soluton using Dijkstra algorithm
int get_answer() {
    // list of directions (left, right, top, bottom)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
     
    // d[i][j] is the minimum cost from source [0,0] to the position [i][j]
    int d[110][110];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = INF;
        }
    }
     
    // Setup priority queue
    auto comparator = [](const node& a, const node& b) {
        return a.w > b.w;
    };
    priority_queue<node, vector<node>, decltype(comparator)> q(comparator);
    q.push({0, 0, 0}); // add source to queue
    d[0][0] = 0; // the cost from source to source is 0
     
    while (!q.empty()) {
        // get the minimum node from priority_queue
        int x = q.top().x;
        int y = q.top().y;
        q.pop();
        if (x == n-1 && y == n-1) {
            // if [x,y] is the destination, stop executing
            break;
        }
        for (int i = 0; i < 4; i++) { // move to left, right, top, bottom
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (check_valid(new_x, new_y) && d[new_x][new_y] > d[x][y] + a[new_x][new_y]) {
                // new_node's current cost is larger, update better cost by moving from current_node
                d[new_x][new_y] = d[x][y] + a[x][y];
                q.push({new_x, new_y, d[new_x][new_y]}); // and add new node to queue
            }
        }
    }
    // remind that d[i][j] is the minimum cost from source [0,0] to [i][j]
    return d[n-1][n-1];
}
 
int main(){
    input_data(); // Input function
    cout << get_answer() << endl; // Output answer
    return 0;
}