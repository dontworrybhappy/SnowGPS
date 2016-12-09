# SnowGPS

Tired of walking out in the cold, harsh South Bend winter?

Well, students of Notre Dame, we have the solution for you!  
Just open **SnowGPS**, touch your destination, and follow the directions!  
It's that simple!  

Using our pathfinding algorithm, we will deliver to you the ideal path
to your destination, minimizing time spent outdoors - thus ensuring that
your next walk to class will be warm and cozy.

Our project can be accessed at: johnbot.me/client
It uses your gps to determine your current location, and you click on the destination you want to go.  It then draws a line on the map between you and your destination that represents the least snowy route.  It works best on mobile because of the more accurate gps information.  

Our project consists of multiple interlocking parts - mostly for our own use.  We have the code for our webpage, stored in the client folder.  This can be run with any webhost with an ssl certificate, but has no internal requirements.  The code for our api is in the folder called api.  It requires node and npm (to get the express library, which it also requries).  If you have npm installed, then going into the api folder and running npm install will fetch and install all dependencies.  The program that actually does dijkstras requires g++ and can be compiled with g++ -std=c++11 dijkstras.cpp -o dijkstras.  It accectps four values from standard input, first the x and y coordinates of the cuser, and then the x and y coordinates of the destination.  Finally, our mapmaker folder, which we used to create our graph, requries pygame.  The actual mapping program can be run with python maping.py.  The program convert.py creates the adjacency list out of the map.  


We also included multiple methods of cleaning up our data. Convert.py removes any extraneous points as well as produces and adjacency list. PrimCheck uses Prim's algorithm to test if we had a connected graph. Those are both located within mapmaker. Our benchmarking programs are located within the test directory. We used thor.py to test the latency of our front end and fresh_goes_better.sh to complete our overall benchmarking. 
