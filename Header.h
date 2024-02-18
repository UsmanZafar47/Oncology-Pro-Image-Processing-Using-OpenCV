#include<iostream>
using namespace std;


class node
{
public:
	int data;
	node* next;

	node()
	{
		data = 0;
		next = NULL;
	}


};


class LinkedList
{
public:
	node* head;
	LinkedList()
	{
		head = NULL;
	}


	bool isEmpty()
	{
		if (head->next == head && head->data == 0)
			return true;
		else
			return false;
	}

	void insert(int index, int value)
	{
		node* newnode = new node();
		newnode->data = value;
		newnode->next = NULL;


		if (head == NULL)
		{
			head = newnode;
			head->next = head;
		}
		else if (index == 0) {
			newnode->data = value;
			newnode->next = head;
			head = newnode;
		}
		else {

			node* currentnode = head;
			int currentindex = 1;
			
			while (currentnode && currentindex < index)
			{
				currentnode = currentnode->next;
				currentindex++;
			}

			newnode->next = currentnode->next;
			currentnode->next = newnode;
			newnode->data = value;

		}
	}

	void insertatend( int val)
	{
		//create a new node
		node* newNode = new node;
		newNode->data = val;
		newNode->next = NULL;

		//if head is NULL, it is an empty list
		if (head == NULL)
			head = newNode;
		//Otherwise, find the last node and add the newNode
		else
		{
			node* lastNode = head;

			//last node's next address will be NULL.
			while (lastNode->next != NULL)
			{
				lastNode = lastNode->next;
			}

			//add the newNode at the end of the linked list
			lastNode->next = newNode;
		}

	}

	int searchList(int item)
	{
		node* temp;
		int i = 0;
		temp = head;
		if (head == NULL)
		{
			cout << "\nEmpty List\n";
		}
		else
		{
			while (temp != NULL)
			{
				if (temp->data == item)
				{
					/*cout << "Item found at location: ";
					cout << (i + 1);
					*/break;
				}
				i++;
				temp = temp->next;
			}
		}
		return i + 1;
	}

	void Update(int old, int newval)
	{
		int index = searchList(old);

		node* currentnode = head;
		for (int i = 0; i < index; i++)
		{
			currentnode = currentnode->next;
		}

		currentnode->data = newval;

	}

	void Delete(int key)
	{
		node* temp = head;
		node* prev = NULL;

		if (temp != NULL && temp->data == key)
		{
			head = temp->next;
			delete temp;
			return;
		}
		else
		{
			while (temp != NULL && temp->data != key)
			{
				prev = temp;
				temp = temp->next;
			}
			if (temp == NULL)
				return;

			prev->next = temp->next;

			delete temp;
		}


	}



	void printList() {
		node* temp = head;
		if (temp != NULL) {
			do {
				cout << temp->data << " ";
				if (temp->data == -1)
					cout << endl;
				temp = temp->next;

			} while (temp != NULL);
		}
	}


};
