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
	queue* insert(int);
	queue* delete_element();
	queue* display();
	int peek();
	int get_size();
	void move_next();
    void free();

private:
	int size;
};
