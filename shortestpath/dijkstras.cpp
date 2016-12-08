// dijsktras.cpp
// Shortest Path Algorithm
// Snow GPS
// Jess, Happy, Jeff Ryan


#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>

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
    int NUM_VERTICES;
    int NUM_EDGES;
    int tempID, tempX, tempY;
    int tempWeight, tempStart, tempEnd;
    vector<Node> vecNodes;
    vector<Edge> vecEdges;
    
    //Variables for start point and end point
    int START_POSX, START_POSY;
    int END_POSX, END_POSY;

    /*
    Reading in from a file
    */

    string filename;    
    ifstream ifs;
    string theline;

    cin >> filename;
   
    ifs.open(filename); // open the file 

    if(!ifs) { // if the file does not exist, error out
        cout << "Error opening file: " << filename << endl;
        return 1;
    }

    while(!ifs.eof()) {
        ifs >> NUM_VERTICES;

        for(int i = 0; i < NUM_VERTICES; i++) {
            ifs >> tempID >> tempX >> tempY;
            Node temp1;
            temp1.ID = tempID;
            temp1.x_pos = tempX;
            temp1.y_pos = tempY;
            vecNodes.push_back(temp1); 
        }
            ifs >> NUM_EDGES;

        for(int i = 0; i < NUM_EDGES; i++){
            ifs >> tempStart >> tempEnd >> tempWeight;
            Edge temp2;
            temp2.weight = tempWeight;
            temp2.start = tempStart;
            temp2.end = tempEnd;
            vecEdges.push_back(temp2);
        }
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
    
    
    // does this read in from a file?
    cin >> START_POSX >> START_POSY;
    index start(START_POSX, START_POSY);
    cin >> END_POSX >> END_POSY;
    index end(START_POSX, START_POSY);

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
