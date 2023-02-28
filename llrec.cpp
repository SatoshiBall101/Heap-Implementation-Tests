#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);
void llpivot_recurse(Node *&head, Node *&smaller, Node *&larger, int pivot);

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{

	// smaller and larger may be garbage, so lets set them to null

	smaller = NULL;
	larger = NULL;

	// call to recursive helper:

	llpivot_recurse(head, smaller, larger, pivot);

	head = NULL; // ensure head is NULL

}

void llpivot_recurse(Node *&head, Node *&smaller, Node *&larger, int pivot)
{

	if(head == NULL) // base case
	{
		return;
	}
	else // recursive solution
	{	
		Node* temp = head->next; // save new head

		if(head->val <= pivot)
		{
			smaller = head;
			head = NULL;
			smaller->next = NULL;
			llpivot(temp, smaller->next, larger, pivot);
		}
		else
		{
			larger = head;
			head = head->next;
			larger->next = NULL;
			llpivot(temp, smaller, larger->next, pivot);
		}
	}

}
