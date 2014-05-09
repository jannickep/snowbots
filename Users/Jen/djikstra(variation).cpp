#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // for exit()
#include <assert.h> // for assert()
#include <stdio.h>
#include <ctype.h>

using namespace std;

int nrows;	// global number of rows
int ncols;	// global number of cols
char *M;	// global character array forming the maze
int *parent;	// global parent or predecessor in paths
int *dist;	// global distance from start (-1 if unvisited)

// The parameter "v" is an index into a global array "parent" that has
// the same dimensions as the maze.  The single integer v encodes
// the (x,y) location where x = v % ncols and y = v / ncols.  So I'm
// using a one-dimensional array to store a two-dimensional array.
// "parent[v]" is the index of the location the path visited before it
// came to location v. If v is the starting location of the path
// then parent[v] equals v.
// v equals -1 indicates no path.

int destination; // global variable for the v-value of destination that takes the 
// least amount of time to get to

// coordinates (x,y)
struct Coordinates {
	int x;
	int y;
};

// convert coordinates (x,y) to v
int convert_to_v(Coordinates x_y) {
	int v;
	v = (x_y.y * ncols) + x_y.x;  // formula for finding v given x and y
	return v;
}

// convert v to coordinates (x,y)
Coordinates convert_to_c(int v) {
	Coordinates x_y;
	x_y.x = v % ncols;  // formula for finding x given v
	x_y.y = v / ncols;  // formula for finding y given v
	return x_y;
}

// check if Coordinates c are still within range of the maze map
// if not, then coordinates c becomes coordinates of v's parent 
void exceeds_graph(Coordinates c, int v) {
	// conditions for coordinates to be out of range of maze map
	if (c.y > nrows || c.y < 0 || c.x > ncols || c.x < 0) { 
	  Coordinates temp = convert_to_c(parent[v]); // get coordinates of v's parent
	  c = temp;  // coordinate c is now coordinate of v's parent
	}
}


// checks possible routes from position v and updates the change of location accordingly
void possible_routes(int v) {
	
	// if the character of position v = 'X', there is no need to continue
	// finding possible routes 
	if (M[v]=='X') return; 
	
	// find the location of the adjacent cells for position v
	Coordinates up, down, right, left, centre;
	centre = convert_to_c(v);  // convert position v to Coordinates called centre
	up = centre; 
	up.y = up.y - 1;        // up is adjacent cell (x, y-1)
	down = centre;
	down.y = down.y + 1;    // down is adjacent cell (x, y+1)
	left = centre;
	left.x = left.x - 1;    // left is adjacent cell (x-1, y)
	right = centre;
	right.x = right.x + 1;  // right is adjacent cell (x+1, y)

	// check if the adjacent coordinates are within range of the maze map
	// if they are not within range, exceeds_graph() will change it to 
	// the coordinates of v's parent
	exceeds_graph(up, v);
	exceeds_graph(down, v);
	exceeds_graph(left, v);
	exceeds_graph(right, v);
	
	// convert the adjacent cells' coordinate location value to v location value 
	int north, south, east, west;  
	north = convert_to_v(up);      // north is up
	south = convert_to_v(down);    // south is down
	east = convert_to_v(right);    // east is right
	west = convert_to_v(left);     // west is left
	
	// int array for v values of all the adjacent cells
	int list_of_possible_moves[4] = {north, south, east, west};
	
	// loop through each value in list of adjacent cell locations
	for (int n = 0; n < 4; n++) { 

		int temp = list_of_possible_moves[n]; // value of current adjacent cell
		
		// updates for the adjacent cell if it is not a parent of v 
		// and if it is a valid space to invade
		if (temp != parent[v] && M[temp] != '-' && M[temp] != '+' && M[temp] != '|') {
			
			if (dist[temp] == -2 && (M[temp] == ' ' || M[temp] == 'X')) {
				dist[temp] = dist[v] + 1;
				parent[temp] = v;
				if (M[temp] == 'X' && destination == -1) {
					destination = temp;
				}
				else {
					possible_routes(temp);
				}
	
			}
	
			else if (dist[temp] == -2 && isdigit(M[temp])) {
				char temp_char = M[temp];
				dist[temp] = atoi(&temp_char) + 1 + dist[v];
				parent[temp] = v;
				possible_routes(temp);
		
			} 
	
			else {
				int new_dist;
				if (isdigit(M[temp])) {
					char temp_char = M[temp];
					new_dist = dist[v] + atoi(&temp_char) + 1;
			
				}
				else {
					new_dist = dist[v] + 1;
					if (M[temp] == 'X') {
			 			if (new_dist < dist[destination]) 
			 				destination = temp;
					}
			
				}

				dist[temp] = min(dist[temp], new_dist);
				
				if (dist[temp] == new_dist) {
					parent[temp] = v;
					if (M[temp] != 'X') possible_routes(temp);
				}
			}
		
		}
	}
}

// dijkstra's algorithm
int dijkstra(int start) {
	
	if (start == -1) return -1;
	possible_routes(start);
	return destination;
}


void printPath( int v ) {
  if( v == -1 ) {
    cout << "No path";
  } else {
    assert( 0 <= v && v < nrows * ncols );
    if( parent[v] != v ) printPath(parent[v]);
    cout << "(" << v % ncols << "," << v / ncols << ")";
  }
}

// Show the path inverted on vt100 terminal (Linux console or xterm window).
void showPath( int v ) {
  int i;
  bool P[ncols * nrows];
  for( i=0; i<ncols*nrows; ++i ) P[i] = false;
  if( v != -1 ) {
    while( parent[v] != v ) {
      P[v] = true;
      v = parent[v];
    }
    P[v] = true;
  }
  i = 0;
  for( int r=0; r<nrows; ++r ) {
    for( int c=0; c<ncols; ++c ) {
      if( P[i] ) {
	//Swap foreground and background
	printf("%c[%d;%d;%dm%c%c[%d;%d;%dm",
	       0x1B,7,37,40,
	       (M[i] == ' ') ? '.':M[i],
	       0x1B,0,37,40);
	//If the previous doesn't work on your terminal, replace with:
	//printf("%c", (M[i] == ' ') ? '.':M[i]);
      } else {
	printf("%c", M[i]);
      }
      ++i;
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {

  if( argc < 2 ) {
    cerr << "Usage: " << argv[0] << " filename" << endl;
    exit(-1);
  }

  ifstream fin (argv[1]);
  if( !fin.is_open() ) {
    cerr << "Can't open " << argv[1] << endl;
    exit(-1);
  }

  fin >> ncols;
  fin >> nrows;
  fin.ignore(256, '\n'); // discard newline

  M = new char[nrows * ncols];
  parent = new int[nrows * ncols];
  dist = new int[nrows * ncols];
  destination = -1;

  int v = 0;
  int startv = -1;
  for( int y=0; y < nrows; ++y ) {
    for( int x=0; x < ncols; ++x ) {
      M[v] = (char)fin.get();
      if( M[v] == '*' ) startv = v;
      ++v;
    }
    fin.ignore(256, '\n'); // discard newline
  }
  fin.close();

  if( startv == -1 ) {
    cerr << "No starting point 'x' in maze." << endl;
    exit(-1);
  }
  
  else {   // if startv is valid
  	for (int i=0; i<(nrows*ncols); i++) {
  	  parent[i] = -1;      // initiate all parents of the coordinates to -1 (default)
  	  dist[i] = -2;        // initiate all distance of coordinates to -2 (default)
  	}
  	parent[startv] = startv; // startv's parent is itself
  	dist[startv] = 0;  // startv's distance to itself is 0
  }  
  
 
  int endv = dijkstra(startv);// CALL YOUR SHORTEST PATH CODE HERE.
  showPath(endv);
  if( endv == -1 ) {
    cout << "No path" << endl;
  } else {
    cout << dist[endv] << " ";
    printPath(endv);
    cout << endl;
  }

  return 0;
}
