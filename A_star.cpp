/***********************************//*
A* shortest path algorithm
Data:   08/24/19
Author: Letian Lin
*//***********************************/
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */

using namespace std;

static const int x_size = 100; // horizontal size of the map
static const int y_size = 100; // vertical size size of the map
// Define the static global map array, "static" allow us to avoid any collision with other files
static int map[y_size][x_size];   // Define the map
static int closed_nodes_map[y_size][x_size]; // map of closed (tried-out) nodes
static int open_nodes_map[y_size][x_size]; // map of open (not-yet-tried) nodes
static int dir_map[y_size][x_size]; // map of directions
static const int dir=8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

    public:
        node(int xp, int yp, int d, int p)              // Constructor where to initialize the class varibles
            {xPos=xp; yPos=yp; level=d; priority=p;}
    
        int getxPos() const {return xPos;}   // By using "const", the function does not change the variable it called
        int getyPos() const {return yPos;}   // This is a good practice. 
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        // give better priority to going strait instead of diagonally
        void nextLevel(const int & i) // i: direction
        {
             level+=(dir==8?(i%2==0?10:14):10);
        }
        
        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-xPos;
            yd=yDest-yPos;         

            // Euclidian Distance
            d=static_cast<int>(sqrt(xd*xd+yd*yd));

            // Manhattan distance
            //d=abs(xd)+abs(yd);
            
            // Chebyshev distance
            //d=max(abs(xd), abs(yd));

            return(d);
        }
};