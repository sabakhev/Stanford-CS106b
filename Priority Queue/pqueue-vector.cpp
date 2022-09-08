/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vec.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	vec.add(value);
}

string VectorPriorityQueue::peek() {
	if(vec.isEmpty()){
		error("No elements in the queue");
	} 

	string minString = vec[0];
	for(int i = 1; i < vec.size(); i++){
		if(vec[i] < minString){
			minString = vec[i];
		}
	}
	return minString;
}

string VectorPriorityQueue::dequeueMin() {
	if(vec.isEmpty()){
		error("No elements in the queue");
	} else {
		string minString = vec[0];
		int min = 0;
		for(int i = 1; i < vec.size(); i++){
			if(vec[i] < minString){
				minString = vec[i];
				min = i;
			}
		}
		vec.remove(min);
		return minString;
	}
}

