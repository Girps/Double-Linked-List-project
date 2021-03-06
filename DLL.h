#include<iostream>

struct out_of_range {};
struct no_such_element_exception {}; 

template <typename T>
class DLL
{
	struct Node 
	{
		Node* next; 
		Node* prev;
		T data; 
		explicit  Node(T data_Pram) :data{ data_Pram }, next{ nullptr }, prev{nullptr}{}
		~Node(){std::cout << "~[" << data << "]";}
	};
	
	// Private data fields declarations 
	Node* head;
	Node* tail; 
	int size; 

	// Private functions memebers

	/* Function allocates and initializes node on the heap returns a pointer */
	Node* create_Node(T data_Pram) { return new Node(data_Pram);  }

	/* Recursive function saves prior node and reassigns when back tracking*/
	Node* reverse_Helper(Node*& ptr)
	{
		// Base case
		if (ptr == nullptr)
		{
			return nullptr;
		}
		else // Recursive case 
		{
			Node* temp = ptr->prev;
			ptr->prev = reverse_Helper(ptr->next);
			ptr->next = temp;
			return ptr;
		}
	}

	// Public function memebers and constructors 
	public: 
		DLL() :head{ nullptr }, tail{ nullptr }, size{0}{}
		
		/* Deep copy constructor copies data from parameterized linked list to calling object*/
		DLL(const DLL& l_List)
			:head{ nullptr }, tail{ nullptr }, size{0}
		{
			printf("\nDeep copy constructor called\n");
			Node* target = l_List.head; 
			// Allocate nodes to calling object
			while (target != nullptr) 
			{
				// Copy arg list data and traverse
				this->add_Last(target->data);
				target = target->next; 
			}
		}

		/* Move constructor takes resources from rr value and assigns to lvalue */
		DLL( DLL&& rr_List)
			:head{ rr_List.head }, tail{ rr_List.tail }, size{rr_List.size}
		{
			printf("\nMove constructor called\n");
			// set rr value pointer memebers to nullptr 
			rr_List.head = nullptr; 
			rr_List.tail = nullptr; 
			rr_List.size = 0; 
		}

		/* Destructor deletes nodes from list */
		~DLL() { free_Nodes(); std::cout << " list freed"; }

		/* Assingment overloaded operator function copies data from argument 
			and returns a self refecence to support assignent chainging*/
		DLL& operator = (const DLL& l_List) 
		{
			printf("\nDeep assignement called\n");
			if (this->size > l_List.size) 
			{
				// calling obj is bigger remove end of nodes 
				// and began copying data with pointers 
				int diff = this->size - l_List.size; 
				for (int i = 0; i < diff;i++) 
				{
					this->remove_Last(); 
				}
				// Assgin pointers to this head and arg's head
				Node* cursor = head; 
				Node* target = l_List.head; 
				while (cursor != nullptr) 
				{
					// Assign calling obj data to arg obj data
					cursor->data = target->data; 
					// traverse the list
					cursor = cursor->next; 
					target = target->next; 
				}
			}
			else if (this->size < l_List.size) 
			{
				int diff = l_List.size - this->size;
				Node* cursor = head; 
				Node* target =  l_List.head;
				// Copy data from arg list to calling object list
				for (int i = 0; i < this->size;i++) 
				{
					// Copy data
					cursor->data = target->data; 
					// traverse 
					cursor = cursor->next;
					target = target->next; 
				}
				// Add remaing nodes
				for (int i = 0; i < diff;i++) 
				{
					this->add_Last(target->data);
					target = target->next; 
				}
			}
			else 
			{
				// Lists have the same size 
				Node* cursor = head;
				Node* target = l_List.head; 
				
				while (cursor != nullptr) 
				{
					// Assign calling object node data to arg node
					cursor->data = target->data; 
					// Traverse the list
					cursor = cursor->next;
					target = target->next; 
				}
			}
			// Reassign calling object size 
			this->size = l_List.size; 
			return *this; // return self reference
		}

		/* Move assignment overloaded function takes resources of rr list and
			reassigns argument memebrs to null, returns self reference to support
				assignment chaining*/
		DLL& operator = ( DLL&& rr_List)
		{
			printf("\nMove assginement called\n");
			size = rr_List.size; 
			head = rr_List.head; 
			tail = rr_List.tail; 
			
			rr_List.head = nullptr;
			rr_List.tail = nullptr; 
			rr_List.size = 0;

			return *this; 
		}
		
		// getter member functions
		int get_Size() const { return this->size;  }

		/* Void function allocates a node and is added at index offset*/
		void add_Node(T data_Pram, int index) 
		{
			// Throw exception if index is less than 0, equal to or greater than size if not zero
			if (index < 0 || ( index >= size && index != 0 )) 
			{
				throw out_of_range();
			}
			else if (index == 0) 
			{
				add_First(data_Pram); 
			}
			else if (index == size - 1 )
			{
				add_Last(data_Pram); 
			}
			else
			{
				int offset{ index - 1 };
				// Cursor hold address in head pointer
				Node* cursor = head;
				// Find the offset 
				while (index > 0)
				{
					cursor = cursor->next;
					offset--;
				}
				// Have prior node now reassign pointers 
				Node* temp = create_Node(data_Pram);
				temp->prev = cursor;
				temp->next = cursor->next;
				cursor->next->prev = temp;
				cursor->next = temp;
				this->size++; // inc size
			}
		}

		/* T returning function removes a node at an index, decrements size and return data by value */
		T remove_Node(int index)
		{
			// Throw exception if index is less than 0, equal to or greater than size if not zero
			if (index < 0 || (index >= size && index != 0))
			{
				throw out_of_range();
			}
			else if (index == 0) 
			{
				return remove_First(); 
			}
			else if (index == size - 1) 
			{
				return remove_Last(); 
			}
			else
			{
				int offset{ index - 1 };
				// Cursor hold address in head pointer
				Node* cursor = head;
				// Get Node before the targeted node
				while (offset > 0)
				{
					cursor = cursor->next;
					offset--;
				}
				
				// Now reassing pointers and delete the targeted node
				Node* target = cursor->next;
				cursor->next = target->next; 
				// Assuming the node after wards is not null 
				// Assign node after target prev to cursor node
				if (cursor->next != nullptr) 
				{
					cursor->next->prev = cursor; 
				}
				// Get target node
				T data{ target->data };
				delete target; // remove node from the 
				this->size--; // inc size
				return data; 
			}
		}

		/*Void function allocates node and assigns address at beginning of the list*/
		void add_First(T data_Pram) 
		{
			this->size++; // inc size
			// Create node initalize to local pointer
			Node* temp = create_Node(data_Pram); 
			// If DLList is empty add node
			if (head == nullptr) 
			{
				head = temp; 
				tail = head; 
			}
			else 
			{
				// DDList is not empty move pointers
				// New node becomes the head pointer 
				temp->next = head; 
				head->prev = temp; 
				head = temp; 
			}
		}

		/* Void function allocates node and assigns address at end of the list*/
		void add_Last(T data_Pram) 
		{
			this->size++; // inc size
			Node* temp = create_Node(data_Pram);
			// If empty add node
			if (head == nullptr)
			{
				head = temp; 
				tail = head; 
			}
			else 
			{
				// New node address assinged to tail pointer
				tail->next = temp; 
				temp->prev = tail; 
				tail = temp; 
			}
		}

		/* T returning function removes first node in the linked list, decremements size and returns data by value*/
		T remove_First() 
		{
			/* If list is empty throw an exception*/
			if (head == nullptr) 
			{
				throw no_such_element_exception(); 
				// If removing head 
			}
			else if (head->next == nullptr) 
			{
				T data{}; 
				Node* cursor = head; 
				head = nullptr; 
				tail = head; 
				data = cursor->data;
				delete cursor; 
				this->size--; 
				return data; 
			}// Other wise
			else if (head != nullptr) 
			{
				// assign pointer to head
				Node* cursor = head; 
				head = head->next; // next node is head
				head->prev = nullptr;
				T data{ cursor->data }; 
				// delete old node
				delete cursor;
				// dec size
				this->size--; 
				return data; 
			}	
		}
		
		/* T returning function removes last node in linked list, decrements size and T data by value*/
		T remove_Last() 
		{
			/* If list is empty throw an exception*/
			if (head == nullptr)
			{
				throw no_such_element_exception();
			}
			else if (tail == head) 
			{
				return remove_First(); 
			}
			else if (tail != nullptr) 
			{
				// assign pointer to tail
				Node* target = tail; 
				tail = tail->prev; 
				tail->next = nullptr;
				T data{ target->data }; 
				// delete old tail
				delete target; 
				// dec size
				this->size--;
				return data; 
			}
		}

		/*Void function free nodes in a list and assigns size memeber to 0*/
		void free_Nodes() 
		{
			this->size = 0;
			Node* cursor{ head };
			Node* temp{ head };
			std::cout << "\n"; 
			while (cursor != nullptr) 
			{
				// Delete node prior to next node
				cursor = cursor->next;
				delete temp; 
				temp = cursor; 
			}
			this->head = nullptr;
			this->tail = nullptr; 
		}

		/* Bool returning function linear seaches list for data passsed in the arguement*/
		bool find_Node(T data_Pram) 
		{
			Node* cursor = head; 
			// Traverse list until the end or return when data is found
			while (cursor != nullptr) 
			{
				// Assign pointer to next node
				cursor = cursor->next; 
				if (cursor->data == data_Pram)  
				{
					return true; 
				}
			}
			// Not found return false 
			return false; 
		}

		/* Void function iterates the list and prints node data*/
		void traverse() 
		{
			// Pointer to the head
			Node* cursor = head;
			std::cout << "\n";
			// Pointer is not null assign to next node
			while (cursor != nullptr) 
			{
				std::cout << "[" << cursor->data << "]===";
				cursor = cursor->next; 
			}
			std::cout << "NULL\n"; 
		}

		/*Void returning function reverse linked list and reassgins head and tail*/
		void reverse() 
		{
			Node* new_Head{this->tail};
			Node* new_Tail{this->head};

			reverse_Helper(head); 

			// head assigned tail address 
			// tail assigned head address

			head = new_Head; 
			tail = new_Tail; 
		}

		/*Bool returning overlaoded function compares size and data between
			linked list*/
		bool operator == (const DLL &arg_List) 
		{
			// same size or false
			if (this->size == arg_List.size) 
			{
				Node* cursor = head;
				Node* target = arg_List.head; 
				while (cursor != nullptr) 
				{
					// If data doesn't match return false
					if (cursor->data != target->data) 
					{
						return false;
					}
					// traverse the list
					cursor = cursor->next; 
					target = target->next; 
				}
				// Return true if size and data are the same
				return true; 
			}
			return false;
		}
}; 