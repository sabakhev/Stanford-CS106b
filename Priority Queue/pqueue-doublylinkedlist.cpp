/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	listSize = 0;
	ptr = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (ptr != NULL){
		doubleCell* next = (*ptr).following;
		delete ptr;
		ptr = next;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return listSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return listSize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	doubleCell* enqueued = new doubleCell;
	(*enqueued).value = value;
	(*enqueued).following = ptr;
	(*enqueued).previous = NULL;
	if(ptr != NULL){
		(*ptr).previous = enqueued;
	}
	ptr = enqueued;
	listSize ++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(listSize == 0){
		error("No elements in the list");
	}
	doubleCell* curr = (*ptr).following;
	string min = (*ptr).value;
	while(curr != NULL){
		if((*curr).value < min){
			min = (*curr).value;
		}
		curr = (*curr).following;
	}
	return min;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	string min = peek();
	doubleCell* curr = ptr;
	while((*curr).value != min){
		curr = (*curr).following;
	}
	doubleCell* prev = (*curr).previous;
	doubleCell* next = (*curr).following;
	delete curr;
	if(next != NULL){
		(*next).previous = prev;
	}
	if(prev != NULL){
		(*prev).following = next;
	} else {
		ptr = next;
	}
	listSize --;
	return min;
}

