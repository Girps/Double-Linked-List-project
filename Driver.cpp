#include <iostream>
#include "DLL.h"
#include <time.h>


template<typename T> 
void add_FirstTest(DLL<T>& list_Pram,int n, int range); 
template<typename T>
void add_LastTest(DLL<T>& list_Pram, int n, int range); 
template<typename T>
void remove_FirstTest(DLL<T>& list_Pram, int n); 
template<typename T>
void remove_LastTest(DLL<T>& list_Pram, int n); 


int main() 
{
	// Set seed to clock 
	srand(time(NULL)); 
	DLL<int> list; 
	add_FirstTest(list, 5, 100);
	std::cout << " list size " << list.get_Size() << "\n";

	list.traverse(); 
	list.free_Nodes(); 
	std::cout << " list size " << list.get_Size() << "\n";
	
	add_LastTest(list,5,100); 
	list.traverse(); 
	std::cout << " list size " << list.get_Size() << "\n";

	remove_FirstTest(list,1);
	list.traverse(); 
	remove_LastTest(list,1);
	list.traverse();
	std::cout << " list size " << list.get_Size() << "\n";
	remove_LastTest(list,3);

	std::cout << " list size " << list.get_Size() << "\n";

	add_FirstTest(list,10,100); 
	list.traverse(); 
	list.reverse(); 
	list.traverse(); 
	std::cout << " list size " << list.get_Size() << "\n";


	
	return 0; 
}

/* Function template adds random numbers in range -1 at n amount of times */
template<typename T> 
void add_FirstTest(DLL<T> & list_Pram, int n, int range ) 
{
	// 
	int number = 0; 
	for (int i = 0; i < n; i++) 
	{
		number = rand() % range;
		list_Pram.add_First(number); 
	}
}

/* Template function adds n amount of nodes holding integer of  range-1 to end of list  */
template<typename T>
void add_LastTest(DLL<T>& list_Pram, int n, int range) 
{

	int number = 0;
	for (int i = 0; i < n; i++)
	{
		number = rand() % range;
		list_Pram.add_Last(number);
	}
}

/* Template function removes n amount of nodes from front of list*/
template<typename T>
void remove_FirstTest(DLL<T>& list_Pram, int n) 
{
	for (int i =0; i < n;i++) 
	{
		list_Pram.remove_First(); 
	}
}

/* Template function removes n amount of nodes from end of list*/
template<typename T>
void remove_LastTest(DLL<T>& list_Pram, int n)
{
	for (int i = 0; i < n; i++)
	{
		list_Pram.remove_Last();
	}
}
