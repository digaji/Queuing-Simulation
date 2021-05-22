// Queue
// a program to implement a linked queue.
#include <iostream>
#include <queue.h>
using namespace std;

struct node
{
	int data;
	node* next;
};

struct queue
{
	node* front;
	node* rear;
};

Queue::Queue()
{
	q = new queue;
	q -> rear = nullptr;
	q -> front = nullptr;
}

queue* Queue::insert(int val)
{
	node *ptr;
	ptr = new node;
	ptr -> data = val;

	// your code
    if (q -> front == nullptr) {
        q -> front = q -> rear = ptr;
        q -> front -> next = q -> rear -> next = nullptr;
    } else {
        q -> rear -> next = ptr;
        q -> rear = ptr;
        q -> rear -> next = nullptr;
    }
	return q;
}

queue* Queue::display()
{
	node* ptr;
	ptr = q -> front;
	if(ptr == nullptr)
		cout << "\n QUEUE IS EMPTY";
	else
	{
		cout << "\n";
		while(ptr!=q -> rear)
		{
			cout << ptr -> data << "\t";
			ptr = ptr -> next;
		}
		cout << ptr -> data << "\t";
	}
	return q;
}

queue* Queue::delete_element()
{
	node* ptr;
	ptr = q -> front;

	// your code
    if (ptr == nullptr) {
        cout << "Underflow" << endl;
    } else {
        q -> front = q -> front -> next;
        delete ptr;
    }
	return q;
}

int Queue::peek()
{
	if(q->front==nullptr)
	{
		cout << "\n QUEUE IS EMPTY";
		return -1;
	}
	else
		return q->front->data;
}
