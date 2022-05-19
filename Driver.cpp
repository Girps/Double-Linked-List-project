#include <iostream>
#include "DLL.h"
#include <stack>


int main() 
{
	DLL<int> list;
	list.add_First(1);
	list.add_First(2); 
	list.add_First(3);
	list.traverse(); 
	list.reverse();
	list.traverse(); 
	

	return 0; 
}
