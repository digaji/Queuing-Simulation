// Queue
// a program to implement a linked queue.
#include <iostream>
#include "queue.h"
using namespace std;

Queue::Queue()
{
	q = new queue;
	q -> rear = nullptr;
	q -> front = nullptr;
	size = 0;
}

queue* Queue::insert(int val)
{
	node *ptr;
	ptr = new node;
	ptr -> data = val;

    if (q -> front == nullptr) {
        q -> front = q -> rear = ptr;
        q -> front -> next = q -> rear -> next = nullptr;
		size++;
    } else {
        q -> rear -> next = ptr;
        q -> rear = ptr;
        q -> rear -> next = nullptr;
		size++;
    }
	return q;
}

queue* Queue::display()
{
	node* ptr;
	ptr = q -> front;
	if (ptr == nullptr)
		cout << "\n QUEUE IS EMPTY";
	else
	{
		while(ptr != q -> rear)
		{
			cout << ptr -> data << "\n";
			ptr = ptr -> next;
		}
		cout << ptr -> data << "\n";
	}
	return q;
}

queue* Queue::delete_element()
{
	node* ptr;
	ptr = q -> front;

    if (ptr == nullptr) {
        cout << "Underflow" << endl;
    } else {
        q -> front = q -> front -> next;
        delete ptr;
		size--;
    }
	return q;
}

int Queue::peek()
{
	if (q -> front == nullptr)
	{
		cout << "\n QUEUE IS EMPTY";
		return -1;
	}
	else
		return q -> front -> data;
}

int Queue::get_size()
{
	return size;
}

void Queue::free()
{
    delete q;
    q = NULL;
}
