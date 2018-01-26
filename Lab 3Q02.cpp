#include<iostream>
using namespace std;

class Node {
	public:
		int data;
		Node* next;
		Node* prev;

		Node() {				// Default constructor for Node
			data = 0;			// initializes the data to zero
			next = NULL;		// and points prev and next to
			prev = NULL;		// NULL.
		}
};

class CLList {
	private:
		Node* dummy;
		int size;

	public:
		CLList() {				// Default CLList constructor
			dummy = NULL;
			size = 0;
		}

		// Member functions of the CLList class
		void insert(int d);
		Node* getNode(int i);
		int insertAt(int i, int d);
		void remove();
		int removeAt(int i);
		int countItems();
		void display();
};

void CLList::insert(int d) {
	Node* new_node = new Node;
	new_node->data = d;

	if (dummy == NULL) {		// Steps to perform when the list is empty.
		dummy = new_node;
		dummy->next = new_node;
		dummy->prev = new_node;
	} else {					// Steps to perform in a list with at least one element.
		(dummy->prev)->next = new_node;
		new_node->next = dummy;
		new_node->prev = dummy->prev;
		dummy->prev = new_node;
	}

	++size;						// Keeps track of number of nodes in list.
}

Node* CLList::getNode(int i) {
	if (size == 0) {			// Checks if the list is empty, then prints error message.
		cout << "List is empty. Nothing to do." << endl;
		return NULL;
	}

	if (i < 1 || i > size) {	// Checks if the value of i is sane.
		cout << "Invalid element position." << endl;
		return NULL;
	}

	Node* p = dummy;			// Placeholder variable used to traverse through the list.


	if (i < size/2) {
		for (int j=0; j<i-1; ++j) {
			p = p->next;
		}
	} else {
		for (int j=0; j<size-i+1; ++j) {
			p = p->prev;
		}
	}

	return p;
}

int CLList::insertAt(int i, int d) {
	if (i < 1 || i > size+1) {		// Checks if the value of i is sane.
		cout << "Invalid element position." << endl;
		return -1;
	}

	if (i == size+1) {			// Calls insert if node is to be added at the end;
		insert(d);
		return 0;
	} 

	Node* new_node = new Node;
	new_node->data = d;

	if (i == 1) {				// Steps for inserting node at the first position.
		new_node->next = dummy;
		new_node->prev = dummy->prev;
		dummy->prev->next = new_node;
		dummy->prev = new_node;
		dummy = new_node;		// dummy needs to be reassigned in this case.
	} else {					// Steps to insert node in the middle.
		Node* p = getNode(i);
		new_node->next = p;
		new_node->prev = p->prev;
		p->prev->next = new_node;
		p->prev = new_node;
	}

	++size;						// Keeps track of number of nodes.
	return 0;
}

void CLList::remove() {
	if (size == 0) {			// Check for empty list.
		cout << "List is empty. Nothing to do." << endl;
		return;
	} else if (size == 1) {
		delete dummy;
		dummy=NULL;
	} else {
		Node* p = dummy->prev;		// p is a placeholder variable which stores
									// the address of the node which is to be deleted.
		dummy->prev = p->prev;
		(p->prev)->next = dummy;
		delete p;
	}

	--size;					// Keeps tracks of number of nodes in the list.
}

int CLList::removeAt(int i) {
	if (i < 1 || i > size) {	// Checks if the value of i is sane.
		cout << "Invalid element position." << endl;
		return -1;
	}

	if (size == 0) {			// Steps to do if the list is empty.
		cout << "List is empty. Nothing to do." << endl;
		return 0;
	} else if (i == size) {		// Steps to do if the last element is to be removed
		remove();
		return 0;
	} else if (i == 1) {		// Steps to do if the first element is to be removed
		(dummy->prev)->next = dummy->next;
		(dummy->next)->prev = dummy->prev;

		Node* p = dummy;
		dummy = dummy->next;	// dummy needs to be taken care of
		delete p;
	} else {					// Things to do for deletion of a non-edge-case node
		Node* p = getNode(i);	// p is a placeholder variable which holds
								// the address of the node to be deleted.
		(p->prev)->next = p->next;
		(p->next)->prev = p->prev;
		delete p;
	}

	--size;				// Keeping track of size of the list.
	return 0;
}

int CLList::countItems() {
	return size;
}

void CLList::display() {
	if (size == 0) {			// Checks if the list is empty, then prints error message.
		cout << "There are no elements in the list. Nothing to do." << endl;
		return;
	}

	Node* p = dummy;		// Placeholder variable; Used to traverse through the list.
	for (int j=0; j<size; ++j) {
		cout << p->data;
		if (p->next != dummy) {
			cout << "->";
		}
		p = p->next;
	}
	cout << endl;
}

int main() {
	CLList l1;
	for (int i=0; i<10; ++i) {
		l1.insert(i+1);
	}

	l1.insertAt(8,0);
	l1.insertAt(4,0);
	l1.insertAt(13,0);
	l1.remove();
	l1.removeAt(1);
	l1.removeAt(5);

	l1.display();
	cout << l1.countItems() << endl;
	return 0;
}
