// dijsktras.cpp
// Shortest Path Algorithm
// Snow GPS
// Jess, Happy, Jeff Ryan
//

#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

/*
Declarations
*/
typedef pair<int, int> index;
typedef pair<int, index> mark;

struct Node{
    int ID;
    int x_pos;
    int y_pos;
};

struct Edge{
    int weight;
    int start;
    int end;
};

/*
Prototypes
*/
auto comp = [](Edge a, Edge b) {return a.value > b.value; };

/*
Main Execution
*/
int main(int argc, char *argv[]) {
    //variables for graph
    int NUM_VERTICES,
        NUM_EDGES;
    int tempID, tempX, tempY;
    //char symbol;
    
    //Variables for start point and end point
    int START_POSX, START_POSY;
    int END_POSX, END_POSY;



    //map<char, int> values;
    //map<index, node> graph;
    
    //Instantiate vector of nodes...
    cin >> NUM_VERTICES;
    vector<Node> v;
    for( int i = 0; i < NUM_VERTICES; i++){
       cin >> tempID >> tempX >> tempY;
       v.push_back({tempID, tempX, tempY});
    }

    /*cin >> num_rows >> num_columns;
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_columns; j++){
            cin >> symbol;
            auto x = index(i,j);
            graph[x].weight = values[symbol];
            if(i != 0){
                graph[index(i-1,j)].edges[x] = values[symbol];
            }
            if( i != num_rows-1){
                graph[index(i+1,j)].edges[x] = values[symbol];
            }
            if(j != 0){
                graph[index(i,j-1)].edges[x] = values[symbol];
            }
            if(j != num_columns -1){
                graph[index(i,j+1)].edges[x] = values[symbol];
            }
        }
    }*/
    
    

    cin >> player_pos_x >> player_pos_y;
    index start(player_pos_x, player_pos_y);
    cin >> player_dest_x >> player_dest_y;
    index end(player_dest_x, player_dest_y);

    /*
    Dijkstras 
    */
    priority_queue<Edge, vector<Edge>, decltype(comp) > frontier(comp);

    map<index, mark> marked;

    for(auto x: graph){
        marked[x.first] = mark(0, index(-1,-1));
    }
   
    frontier.push(Edge{0, start, start});
    while(!frontier.empty()){
        auto v = frontier.top();
        frontier.pop();

        if(marked[v.left].first != 0){
            continue;
        }
        marked[v.left] = mark(v.value, v.right);
        for(auto x:graph[v.left].edges){
            frontier.push(Edge{x.second + v.value, x.first, v.left});
        }
    }

    vector <index> holder;
    auto curr = end;
    int sum = 0;
    while(curr.first != start.first || curr.second != start.second){
        holder.push_back(curr);
        curr = marked[curr].second;
        sum += graph[curr].weight;
    }
    holder.push_back(curr);
    reverse(holder.begin(), holder.end());
    cout << sum << endl;
    for(auto x: holder){
        cout << x.first << " " << x.second << endl;
    }
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
