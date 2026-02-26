// samples_linked_lists.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <malloc.h>

#define MAX_ITEMS 100

struct _myNode {
	int data;
	struct _myNode *next;
};

typedef _myNode myNode;


struct _myNodeDlist {
	int data;
	struct _myNodeDlist* next;
	struct _myNodeDlist* prev;
};

typedef _myNodeDlist myNodeDlist;


myNode* createList(int count, int *items)
{
	myNode* temp = NULL;
	myNode* head = NULL;
	myNode* tempHead = NULL;
	int index = 0;

	while (count > 0)
	{
		temp = (myNode*)malloc(sizeof(myNode));
		if (temp == NULL) {
			printf("Error: Failed to allocate memory to linked list node\n");
			if (head != NULL)
			{
				// Add logic to free the list created so far
			}
			return NULL;
		}
		temp->next = NULL;
		temp->data = items[index++];

		if (head == NULL)
		{
			head = temp;
		}
		else
		{
			tempHead = head;
			while (tempHead->next != NULL)
			{
				tempHead = tempHead->next;
			}
			// attach the new temp node to the end of the current list
			tempHead->next = temp;
		}
		count--;
	}
	return head;
}

myNodeDlist* createDList(int count, int* items)
{
	myNodeDlist* temp = NULL;
	myNodeDlist* head = NULL;
	myNodeDlist* tempHead = NULL;
	int index = 0;

	while (count > 0)
	{
		temp = (myNodeDlist*)malloc(sizeof(myNodeDlist));
		if (temp == NULL) {
			printf("Error: Failed to allocate memory to doubly linked list node\n");
			if (head != NULL)
			{
				// Add logic to free the list created so far
			}
			return NULL;
		}
		temp->next = NULL;
		temp->prev = NULL;
		temp->data = items[index++];

		if (head == NULL)
		{
			head = temp;
			// tail can be deduced later by walking through the list from head
			// or you can also return that from the construction function itself.
		}
		else
		{
			tempHead = head;
			while (tempHead->next != NULL)
			{
				tempHead = tempHead->next;
			}
			// attach the new temp node to the end of the current list
			tempHead->next = temp;
			temp->prev = tempHead;
		}
		count--;
	}
	return head;
}


void printDListOrder(myNodeDlist* head)
{
	if (head == NULL)
	{
		printf("The list is NULL\n");
		return;
	}

	while (head != NULL)
	{
		printf("%d", head->data);
		if (head->next != NULL)
		{
			printf(" <-> ");
		}
		head = head->next;
	}
	printf(" NULL\n");
}


void printDListReverse(myNodeDlist* tail)
{
	if (tail == NULL)
	{
		printf("The list is NULL\n");
		return;
	}

	while (tail != NULL)
	{
		printf("%d", tail->data);
		if (tail->prev != NULL)
		{
			printf(" <-> ");
		}
		tail = tail->prev;
	}
	printf(" NULL\n");
}


myNodeDlist* dListAddItemAtIndex(myNodeDlist* head, int data, int index)
{
	myNodeDlist* temp = NULL;
	myNodeDlist* tempHead = NULL;
	if (index < 0)
	{
		printf("Error: Index cannot be negative\n");
		return NULL;
	}
	
	temp = (myNodeDlist*)malloc(sizeof(myNodeDlist));
	if (temp == NULL)
	{
		printf("Error: Failed to allocate memory for the list node\n");
		return NULL;
	}
	else
	{
		temp->data = data;
		temp->next = NULL;
		temp->prev = NULL;
	}

	if (head == NULL)
	{
		head = temp;
		return head;
	}

	if (index == 0)
	{
		// Make temp node as the new head and retrun the head
		head->next->prev = temp;
		temp->next = head->next;
		temp->prev = NULL;
		head = temp;
		return head;
	}
	else
	{
		// Insert element at a given index
		tempHead = head;
		// decrement index to discount the head node
		index--;
		// locate the node at index - 1, so that temp node
		// can be inserted at index
		while ((tempHead->next != NULL) && (index > 0))
		{
			tempHead = tempHead->next;
			index--;
		}

		if (tempHead->next != NULL)
		{
			// Need to insert in between two nodes
			tempHead->next->prev = temp;
			temp->next = tempHead->next;
			temp->prev = tempHead;
			tempHead->next = temp;
		}
		else
		{
			// insert node at the end of the list
			tempHead->next = temp;
			temp->prev = tempHead;
		}
		return head;
	}
}


myNodeDlist* getDListTail(myNodeDlist* list)
{
	myNodeDlist* tail = list;

	if (tail == NULL)
	{
		printf("The list is empty\n");
		return NULL;
	}

	while (tail->next != NULL)
	{
		tail = tail->next;
	}

	return tail;
}


void printList(myNode* list)
{
	if (list == NULL)
	{
		printf("The list is NULL\n");
		return;
	}

	while (list != NULL)
	{
		printf("%d", list->data);
		if (list->next != NULL)
		{
			printf(" -> ");
		}
		list = list->next;
	}
}

// Reversing Linked list without using recursion
myNode* reverseList(myNode* list)
{
	myNode* current = list;
	myNode* prev = list;
	myNode* temp = list;

	if (list == NULL)
	{
		printf("Empty list and nothing to reverse\n");
		return NULL;
	}
	current = current->next;
	if (current == NULL)
	{
		// There is only one node hence return the pointer to prev
		return prev;
	}
	// There are more than one nodes exchange the between current and previous
	// nodes till we reach the end of list
	while (current != NULL)
	{
		temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}
	list->next = NULL;
	list = prev;
	return list;
}

myNode* reverseListRecursion(myNode* current, myNode* prev)
{
	myNode* ret = NULL;

	if (current == NULL)
	{
		return NULL;
	}

	if(current->next != NULL)
	{
		ret = reverseListRecursion(current->next, current);
	}
	else
	{
		ret = current;
	}
	current->next = prev;
	return ret;
}

int linked_list_main()
{
	myNode* myList = NULL;
	myNode* myReverseList = NULL;
	int items[MAX_ITEMS] = { 1, 2, 3, 4, 5, 6, 7, 8};
	int itemCount = 8;

	printf("Creating linked list\n");
	printf("Enter the number of items you want in the list:\n");
	scanf_s("%d", &itemCount);
	myList = createList(itemCount, items);

	printf("The created list is:\n");
	printList(myList);

	printf("\nReversing the list\n");
	myReverseList = reverseList(myList);

	printf("\nReversed List is:\n");
	printList(myReverseList);


	/*
	printf("Destroying the Linked List\n");
	destroy_list(myList);

	printf("Destroying the Linked List\n");
	destroy_list(myReverseList);
	*/
	return 0;
}

void dlinked_list_main()
{
	myNodeDlist* myList = NULL;
	myNodeDlist* myReverseList = NULL;
	myNodeDlist* tail = NULL;
	int items[MAX_ITEMS] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int itemCount = 8;

	printf("Creating doubly linked list\n");
	printf("Enter the number of items you want in the list:\n");
	scanf_s("%d", &itemCount);
	if (itemCount < 0 || itemCount > 8 )
	{
		printf("Upto 8 items are supported for simplicity of list creation\n");
		printf("Please enter value less than 8\n");
	}
	myList = createDList(itemCount, items);

	printf("The created doubly linked list is:\n");
	printDListOrder(myList);

	printf("\nReversing the list\n");
	printDListOrder(myList);

	printf("\nReversed List is:\n");
	tail = getDListTail(myList);
	printDListReverse(tail);

	// Add item 10 at index 5
	myList = dListAddItemAtIndex(myList, 10, 5);
	printf("\nUpdated list \n");
	printDListOrder(myList);

	// Add item 20 at index 0
	myList = dListAddItemAtIndex(myList, 20, 0);
	printf("\nUpdated list \n");
	printDListOrder(myList);

	// Add item 999 at index 40 - where 40 index doesn't exists
	// so the item will be added at the end of the list
	myList = dListAddItemAtIndex(myList, 999, 40);
	printf("\nUpdated list \n");
	printDListOrder(myList);

	// Add item 40 at index 1
	myList = dListAddItemAtIndex(myList, 40, 1);
	printf("\nUpdated list \n");
	printDListOrder(myList);

	return;
}

int compare_lists_recursion(myNode* list1, myNode* list2)
{
	if (list1 == NULL && list2 == NULL)
		return 0;

	if (list1 == NULL)
		return -1;

	if (list2 == NULL)
		return 1;

	if (list1->data > list2->data)
		return 1;

	if (list1->data < list2->data)
		return -1;

	return compare_lists_recursion(list1->next, list2->next);
}


int compare_lists(myNode* list1, myNode *list2)
{
	myNode* temp1 = NULL;
	myNode* temp2 = NULL;

	temp1 = list1;
	temp2 = list2;

	if (temp1 == temp2)
	{
		printf("Same lists are provided as inputs\n");
		return 0; // Same lists either empty or non-empty
	}

	do
	{
		if (temp1 == NULL)
		{
			// list1 < list2
			return -1;
		}

		if (temp2 == NULL)
		{
			// list1 > list2
			return 1;
		}

		if (temp1->data < temp2->data)
		{
			return -1;
		}

		if (temp1->data > temp2->data)
		{
			return 1;
		}

		// Continue to next items
		temp1 = temp1->next;
		temp2 = temp2->next;
	} while (temp1 != NULL || temp2 != NULL);

	// we have reached end of both the lists
	// lists are matching
	printf("\nReached end of both the lists\n");
	return 0;
}


void print_result(int result)
{

	if (result == 0)
	{
		printf("Lists are equal\n");
	}
	else if (result < 0)
	{
		printf("List1 < List2\n");
	}
	else
	{
		printf("List1 > List2\n");
	}
}

void compare_lists_main()
{
	// Create the first list
	myNode* myList1 = NULL;
	myNode* myList2 = NULL;

	int items1[MAX_ITEMS] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int items2[MAX_ITEMS] = { 1, 2, 3, 4, 5, 6 };

	int itemCount1 = 8;
	int itemCount2 = 6;
	printf("Creating linked list 1:\n");
	myList1 = createList(itemCount1, items1);

	printf("Creating linked list 2:\n");
	myList2 = createList(itemCount2, items2);

	printf("The created list 1 is:\n");
	printList(myList1);

    printf("\nThe created list 2 is:\n");
	printList(myList2);

	printf("\nResult of comparison of myList1 and myList2:\n");
	int result = compare_lists(myList1, myList2);
	print_result(result);

	printf("\nResult of comparison of empty lists:\n");
	result = compare_lists(NULL, NULL);
	print_result(result);

	printf("\nResult of comparison of same lists:\n");
	result = compare_lists(myList1, myList1);
	print_result(result);

	printf("\nResult of comparison of myList1 and myList2 using recursion:\n");
	result = compare_lists_recursion(myList1, myList2);
	print_result(result);

	printf("\nResult of comparison of empty lists using recursion:\n");
	result = compare_lists_recursion(NULL, NULL);
	print_result(result);

	printf("\nResult of comparison of same lists using recursion:\n");
	result = compare_lists_recursion(myList1, myList1);
	print_result(result);

}

int main()
{
	// Run linked list sample - reverse list - recursive and non-recursive
	//dlinked_list_main();

	// List comparison
	compare_lists_main();
	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
