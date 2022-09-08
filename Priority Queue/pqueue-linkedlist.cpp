/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	ptr = NULL;
	listSize = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while(ptr != NULL){
		cell* following = (*ptr).next;
		delete ptr;
		ptr = following;
	}
}

int LinkedListPriorityQueue::size() {	
	return listSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return listSize == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	if(listSize == 0 || value < (*ptr).value){
		cell* enqueued = new cell;
		(*enqueued).value = value;
		(*enqueued).next = ptr;
		ptr = enqueued;
	} else {
		cell* prev = ptr;
		cell* curr = (*ptr).next;
		while(curr != NULL && (*curr).value <= value){
			prev = curr;
			curr = (*curr).next;
		}
		cell* enqueued = new cell;
		(*enqueued).value = value;
		(*enqueued).next = curr;
		(*prev).next = enqueued;
	}
	listSize ++;
}

string LinkedListPriorityQueue::peek() {
	if(ptr == NULL){
		error("No elements in the list to peek");
	}
	return (*ptr).value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(ptr == NULL){
		error("No elements in the list to dequeue from");
	}
	string str = (*ptr).value;
	cell* following =  (*ptr).next;
	delete ptr;
	ptr = following;
	listSize --;
	return str;
}

