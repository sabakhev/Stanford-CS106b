/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
#include "float.h"
using namespace std;

// Functions
Vector<Loc> pathVec(Loc curr, Grid<Loc> & parents, Loc start);

// Constants
const double CLUSTER_DIFFERENCE = 0.0001;
const int RAND_EDGE_WEIGHT = 10;
const double MAX_COST = DBL_MAX;
/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world, double costFn(Loc from, Loc to, Grid<double>& world), double heuristic(Loc start, Loc end, Grid<double>& world)) {
	Vector <Loc> path;
	Set <Loc> yellow;
	Set <Loc> green;
	TrailblazerPQueue <Loc> queue;
	// This grid has as i,j th parameter the current parent of location with coordinates i and j.
	Grid <Loc> parents (world.numRows(), world.numCols());
	// This grid has as i,j th parameter the current shortest distance to location with coordinates i and j.
	Grid <double> distances (world.numRows(), world.numCols());
	yellow.add(start);
	colorCell(world, start, YELLOW);
	distances[start.row][start.col] = 0;
	queue.enqueue(start, heuristic(start, end, world));
	while(!queue.isEmpty()){
		Loc curr = queue.dequeueMin();
		green.add(curr);
		colorCell(world, curr, GREEN);
		if(curr == end){
			path = pathVec(curr, parents, start);
			return path;
		}
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				if((i != 0 || j != 0) && world.inBounds(curr.row + i, curr.col + j)){
					Loc neighbor = makeLoc(curr.row + i, curr.col + j);
					if(!green.contains(neighbor)){
						double cost = costFn(curr, neighbor, world);
						if(cost < MAX_COST){
							double candidateDistance = distances[curr.row][curr.col] + cost;
							if(!yellow.contains(neighbor)){
								yellow.add(neighbor);
								colorCell(world, neighbor, YELLOW);
								parents[neighbor.row][neighbor.col] = curr;
								distances[neighbor.row][neighbor.col] = candidateDistance;
								queue.enqueue(neighbor, candidateDistance + heuristic(neighbor, end, world));
							} else { 
								if(distances[neighbor.row][neighbor.col] > candidateDistance){
									distances[neighbor.row][neighbor.col] = candidateDistance;
									parents[neighbor.row][neighbor.col] = curr;
									queue.decreaseKey(neighbor, candidateDistance + heuristic(neighbor, end, world));
								}
							}
						}
					}
				}
			}
		}
	}
	return path;
}
// This function takes in the information from the parents grid and returns a vector associated with the path starting from
// Loc start and ending with Loc curr.
Vector<Loc> pathVec(Loc curr, Grid<Loc> & parents, Loc start){
	Stack <Loc> stack;
	Vector <Loc> vec;
	while(curr != start){
		stack.push(curr);
		curr = parents[curr.row][curr.col];
	}
	vec.add(start);
	while(!stack.isEmpty()){
		vec.add(stack.pop());
	}
	return vec;
}
// Initializes "clusters" of the nodes as a grid, where node with location i,j is associated with a cluster represented as a double. 
void initClusters(Grid<double> & clusters){
	double a = 0;
	for(int i = 0; i < clusters.numRows(); i++){
		for(int j = 0; j < clusters.numCols(); j++){
			clusters[i][j] = a;
			a += CLUSTER_DIFFERENCE;
		}
	}
}
// Returns a priority queue with randomly chosen priorities for enqueued edges.
TrailblazerPQueue<Edge> makeRandQueue(int numRows, int numCols){
	TrailblazerPQueue<Edge> queue;
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			if(j != numCols - 1){
				Edge curr = makeEdge(makeLoc(i, j), makeLoc(i, j + 1));
				queue.enqueue(curr, randomReal(0, RAND_EDGE_WEIGHT));
			}
			if(i != numRows - 1){
				Edge curr = makeEdge(makeLoc(i, j), makeLoc(i + 1, j));
				queue.enqueue(curr, randomReal(0, RAND_EDGE_WEIGHT));
			}
		}
	}
	return queue;
}
// This boolean returns wether or not the endpoints of the given edge are in the same cluster
bool endpointsAreInSameCluster(Edge curr, Grid <double> & clusters){
	return clusters[curr.start.row][curr.start.col] == clusters[curr.end.row][curr.end.col];
}
// This void merges the clusters of nodes of corresponding edge
void mergeClusters(Edge curr, Grid <double> & clusters){
	double replaced = clusters[curr.start.row][curr.start.col];
	double replacing = clusters[curr.end.row][curr.end.col];
	for(int i = 0; i < clusters.numRows(); i++){
		for(int j = 0; j < clusters.numCols(); j++){
			if(clusters[i][j] == replaced) clusters[i][j] = replacing;
		}
	}
}
Set<Edge> createMaze(int numRows, int numCols) {
	Set <Edge> mazeEdges;
	Grid <double> clusters(numRows, numCols);
	initClusters(clusters);
	TrailblazerPQueue <Edge> queue = makeRandQueue(numRows, numCols);
	int numClusters = numRows * numCols;
	while(numClusters != 1){
		Edge curr = queue.dequeueMin();
		if(!endpointsAreInSameCluster(curr, clusters)){
			mergeClusters(curr, clusters);
			numClusters --;
			mazeEdges.add(curr);
		}
	}
    return mazeEdges;
}
