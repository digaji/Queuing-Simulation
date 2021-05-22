// Queue
// a program to implement a linked queue.
#include <iostream>
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

class Queue
{
public:
	queue* q;

	Queue();
	void create_queue();
	queue* insert(int);
	queue* delete_element();
	queue* display();
	int peek();
	void move_next();
};
