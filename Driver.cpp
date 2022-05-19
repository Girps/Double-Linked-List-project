#include <iostream>
#include "DLL.h"
#include <stack>

struct Node
{
	Node* next;
	Node* prev; 
	int data; 
	Node(int data_Pram) :data{ data_Pram }, next{ nullptr }, prev{nullptr} {}
	~Node() {}
}; 


void traverse( Node* cursor) ; 
Node* rec_Rev(Node** ptr);


int main() 
{
	DLL<int> list;
	list.add_First(1);
	list.add_First(2); 
	list.add_First(3);
	list.traverse(); 
	list.reverse();
	list.traverse(); 

	/*for (int i = 0; i < 3; i++)
	{
		myStack.push(cursor_Tra);
		cursor_Tra = cursor_Tra->next;
	}
	Node* target{ nullptr };
	for (int i = 0; i < 3; i++)
	{
		target = myStack.top();
		target->prev = target->next;
		myStack.pop();
		if (!(myStack.empty()))
		{
			target->next = myStack.top();
		}
		else 
		{
			target->next = nullptr; 
		}
	}

	head = new_Head;
	tail = new_tail;*/


	return 0; 
}


void traverse( Node* pram_Cur)  
{
	Node* cursor = pram_Cur; 
	while (cursor != nullptr) 
	{
		printf("[%d]---",cursor->data);
		cursor = cursor->next; 
	}
	printf("NULL");
}
