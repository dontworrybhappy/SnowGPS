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
    //int start;
    //int end;
    index start;
    index end;

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
    
    map <index, vector<Edge>> list;

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

    // hahaha hahaha ha hah hahah
    int first = -1, second, weight, endX, endY;
    while(!ifs.eof()) {
        while (ifs >> first >> second, first != -1) {
            ifs >> weight >> endX >> endY;
            Edge temp;
            temp.weight = weight;
            temp.end = make_pair(endX, endY);
            temp.start = make_pair(first, second);
            list[make_pair(first,second)].push_back(temp);
        }
    }

    /*while(!ifs.eof()) {
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
    }*/

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
    
    
    // does this read in from a file? - apparently not - now they do?
    cin >> START_POSX >> START_POSY;
    cin >> END_POSX >> END_POSY;
        
    int idNum;
    int startx_distance, starty_distace, endx_distance, endy_distance;
    int start_differencex, start_differencey, end_differencex, end_differencey;
       
    // initializes the starting distances by comparing to the first value in the vector 
    startx_distance = vecNodes[0].x_pos - START_POSX;
    starty_distance = vecNodes[0].y_pos - START_POSY;
    endx_distance = vecNodes[0].x_pos - END_POSX;
    endy_distance = vecNodes[0].y_pos - END_POSY;
    
    for(int i = 0; i < vecNodes.size(); i++) {
        start_differencex = vecNodes[i].x_pos - START_POSX;
        start_differencey = vecNodes[i].y_pos - START_POSY;

        if (startx_distance == 0 && starty_distance == 0) { // if the initial value matches the user's position
            index start(START_POSX, START_POSY);
            break;
        }

        if (startx_distance > start_differencex && starty_distance > start_differencey) { // if not
            startx_distance = start_differencex;
            starty_distance = start_differencey;
            idNum = i; // stores for the index creation
        }    
    }

    index start(vecNodes[idNum].x_pos, vecNodes[idNum].y_pos); // creates a start index

    idNum = 0; // resets the idNum for end index

    for(int i = 0; i < vecNodes.size(); i++) {
        end_differencex = vecNodes[i].x_pos - END_POSX;
        end_differencey = vecNodes[i].y_pos - END_POSY;

        if (end_differencex == 0 && end_differencey == 0) { // if the initial value matches the user's position
            index end(END_POSX, END_POSY);
            break;
        }

        if (endx_distance > end_differencex && endy_distance > end_differencey) { // if not
            endx_distance = end_differencex;
            endy_distance = end_differencey;
            idNum = i; // stores for the index creation
        }    
    }

    index end(vecNodes[idNum].x_pos, vecNodes[idNum].y_pos); // creates an end index
        
    /*
    Dijkstras 
    */

    priority_queue<Edge, vector<Edge>, decltype(comp)> frontier(comp);

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
