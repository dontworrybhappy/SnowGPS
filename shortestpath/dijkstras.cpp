// dijsktras.cpp
// Shortest Path Algorithm
// Snow GPS
// Jess, Happy, Jeff Ryan

#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>

#define MAP_Y(y) (850 - y)

using namespace std;

/*
Declarations
*/
typedef pair<int, int> index;

struct Node{
    int ID;
    int x_pos;
    int y_pos;
};

struct Edge{
    double weight;
    index start;
    index end;

};

/*
Prototypes
*/
auto comp = [](Edge a, Edge b) {return a.weight > b.weight; };

/*
Main Execution
*/
int main(int argc, char *argv[]) {
    //variables for graph
    vector<index> vecNodes;
    
    //Variables for start point and end point
    int START_POSX, START_POSY;
    int END_POSX, END_POSY;
    
    map <index, vector<Edge>> list;

    /*
    Reading in from a file
    */

    string filename = "adjlist.txt";    
    ifstream ifs;
    string theline;

    //cin >> filename;
   
    ifs.open(filename); // open the file 

    if (!ifs) { // if the file does not exist, error out
        cout << "Error opening file: " << filename << endl;
        return 1;
    }

    // hahaha hahaha ha hah hahah
    int first = -1, second, endX, endY;
    double weight = -1;
    while (ifs >> first >> second) {
        index start_pair = make_pair(first, second);
        vecNodes.push_back(start_pair);
        weight = -1;
        while (ifs >> weight >> endX >> endY, weight != -1) {
            Edge temp;
            temp.weight = weight;
            temp.end = make_pair(endX, endY);
            temp.start = start_pair;
            list[make_pair(first,second)].push_back(temp);
            weight = -1;
        }
    }
    
    cin >> START_POSX >> START_POSY;
    cin >> END_POSX >> END_POSY;
        
    int idNum = 0;
    int x_dif = 0;
    int y_dif = 0;
    double distance = 99999;
    double tdis = 0;
    
    for (size_t i = 0; i < vecNodes.size(); i++) {
        x_dif = vecNodes[i].first - START_POSX;
        y_dif = vecNodes[i].second - START_POSY;
        tdis = sqrt(x_dif*x_dif + y_dif*y_dif);
        if (tdis < distance) {
            distance = tdis;
            idNum = i; // stores for the index creation
        }    
    }

    index start(vecNodes[idNum]); // creates a start index

    idNum = 0; // resets the idNum for end index
    distance = 99999;

    for (size_t i = 0; i < vecNodes.size(); i++) {
        x_dif = vecNodes[i].first - END_POSX;
        y_dif = vecNodes[i].second - END_POSY;
        tdis = sqrt(x_dif*x_dif + y_dif*y_dif);
        if (tdis < distance) {
            distance = tdis;
            idNum = i; // stores for the index creation
        }    
    }

    index end(vecNodes[idNum]); // creates an end index
    
    /*
    Dijkstras 
    */

    priority_queue<Edge, vector<Edge>, decltype(comp)> frontier(comp);

    map<index, index> marked;
   
    frontier.push(Edge{0, end, end});
    bool found = false;
    while (!frontier.empty()) {
        auto v = frontier.top();
        frontier.pop();
        if (marked.count(v.end)) {
            continue;
        }
        marked[v.end] = v.start;
        if (v.end == start) {
            found = true;
            break;
        }
        for (auto x:list[v.end]) {
            frontier.push(Edge{x.weight + v.weight, x.start, x.end});
        }
    }
    if (!found) {
        return 2;
    }
    auto curr = start;
    cout << '[';
    while (curr != end) {
        cout << '[' << MAP_Y(curr.second) << ',' << curr.first << "]," << endl;
        curr = marked[curr];
    }
    cout << '[' << MAP_Y(curr.second) << ',' << curr.first << "]]" << endl;
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
