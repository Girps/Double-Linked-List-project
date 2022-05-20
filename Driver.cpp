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
template<typename T>
DLL<T> ret_DLL(); 

int main() 
{
	// Set seed to clock 
	srand(time(NULL)); 
	DLL<int> list; 
	list.add_First(1);
	list.add_First(2);
	list.add_First(3); 
	
	std::cout << list.remove_Node(1); 
	return 0; 
}

/*UDT reference returning function creates a UDT and returns UDT function tests move constructor and move assignement*/
template<typename T>
DLL<T> ret_DLL() 
{
	DLL<T> local; 
	int number = 0;
	for (int i = 0; i < 10; i++)
	{
		number = rand() % 100;
		local.add_First(number);
	}
	return local; 
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
