#include<iostream>

struct out_of_range {};

template <typename T>
class DLL
{
	struct Node 
	{
		Node* next; 
		Node* prev;
		T data; 
		Node(T data_Pram) :data{ data_Pram }, next{ nullptr }, prev{nullptr}{}
		~Node(){std::cout << "~[" << data << "]";}
	};
	
	// Private data fields declarations 
	Node* head;
	Node* tail; 
	int size; 

	// Private functions memebers
	Node* create_Node(T data_Pram) { return new Node(data_Pram);  }

	public: 
		DLL() :head{ nullptr }, tail{ nullptr }, size{0}{}
		
		/* Deep copy constructor copies data from parameterized linked list to calling object*/
		DLL(const DLL& l_List)
			:head{ nullptr }, tail{ nullptr }, size{l_List}
		{
			Node* temp = l_List.head; 
			// Allocate nodes to calling object
			while (temp != nullptr) 
			{
				this->add_Last(l_List->data);
			}
		}

		/* Move constructor takes resources from rr value and assigns to lvalue */
		DLL(const DLL&& rr_List)
			:head{ rr_List.head }, tail{ rr_List.tail }, size{rr_List.size}
		{
			// set rr value pointer memebers to nullptr 
			rr_List.head = nullptr; 
			rr_List.tail = nullptr; 
			rr_List.size = 0; 
		}

		~DLL() { std::cout << "list freed" }

		// Function memebers
		DLL& operator = (const DLL& l_List) {}
		DLL& operator = (const DLL&& rr_List) {}
		
		// getter member functions
		void get_Size() const { return this->size;  }

		/* Void function allocates a node and is added at index offset*/
		void add_Node(T data_Pram, int index) 
		{
			// Throw exception if index is less than 0, equal to or greater than size
			if (index < 0 || index >= size) 
			{
				throw out_of_range; 
			}
			int offset{index-1}; 
			// Cursor hold address in head pointer
			Node* cursor = head; 
			// Find the offset 
			while (index > 0 ) 
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

		/* Void function removes first node in the linked list and decremements size*/
		void remove_First() 
		{
			if (head != nullptr) 
			{
				// assign pointer to head
				Node* cursor = head; 
				head = head->next; // next node is head
				head->prev = nullptr
				// delete old node
				delete cursor;
				// dec size
				this->size--; 
			}	
		}
		/* Void function removes last node in linked list and decrements size*/
		void remove_Last() 
		{
			if (tail != nullptr) 
			{
				// assign pointer to tail
				Node* cursor = tail; 
				tail = tail->prev; 
				tail->next = nullptr;
				// delete tail
				delete tail; 
				// dec size
				this->size--; 
			}
		}

		/*Void function free nodes in a list and assigns size memeber to 0*/
		void free_Nodes() 
		{
			this->size = 0;
			Node* cursor{ head };
			Node* temp{ head };
			while (cursor != nullptr) 
			{
				// Delete node prior to next node
				cursor->next = cursor;
				delete temp; 
				temp->next = temp; 
			}
		}


}; 