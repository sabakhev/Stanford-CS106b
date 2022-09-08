/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	index = 0;
	allocatedLength = 10;
	arr = new string[10];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete []arr;
}

int HeapPriorityQueue::size() {
	return index;
}

bool HeapPriorityQueue::isEmpty() {
	return index == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(index == allocatedLength - 1){
		grow();
	}
	index ++;
	arr[index] = value;
	if(index != 1){
		int n = index;
		while(arr[n] < arr[n/2]){
			swapElems(n, n/2);
			n = n/2;
		}
	}
}

string HeapPriorityQueue::peek() {
	if(index == 0){
		error("No elements in the list");
	}
	return arr[1];
}

string HeapPriorityQueue::dequeueMin() {
	string str = peek();
	swapElems(1, index);
	index --;
	bubbleDown(1);
	return str;
}
void HeapPriorityQueue::bubbleDown(int n){
	if(2*n <= index && arr[n] > arr[2*n]){
		if(2*n + 1 <= index && arr[2*n] > arr[2*n + 1]){
			swapElems(n, 2*n + 1);
			bubbleDown(2*n + 1);
		} else {
		swapElems(n, 2*n);
		bubbleDown(2*n);
		}
	} else if(2*n + 1 <= index && arr[n] > arr[2*n + 1]){
		swapElems(n, 2*n + 1);
		bubbleDown(2*n + 1);
	}
}
void HeapPriorityQueue::grow() {
	string *newptr = new string [2*allocatedLength];
	for(int i = 1; i < allocatedLength; i++){
		newptr[i] = arr[i];
	}
	delete []arr;
	arr = newptr;
	allocatedLength *= 2;
}
void HeapPriorityQueue::swapElems(int a, int b){
	string tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

