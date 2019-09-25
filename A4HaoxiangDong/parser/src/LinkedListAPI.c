
/**
* CIS2750 F2017

 * Assignment 0 redo

 * Haoxiang Dong 0850990  hdong04

 * This file contains the implementation of the linked List API

 * This implementation is based on the List API that I implemented in my Assignment 2 for CIS2520, whcih I took

 * all code is new.

 * my current CIS2750 professor, Denis Nikitenko.

 */



#include "LinkedListAPI.h"


List initializeList(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second))
{
	List new;
	new.head=NULL;
	new.tail=NULL;
	new.deleteData=deleteFunction;
	new.compare=compareFunction;
	new.printData=printFunction;
	new.length=0;
	return new;



}


Node* initializeNode(void* data)
{

	Node * new;
	new = malloc(sizeof(Node));
	new->previous = NULL;
	new->next = NULL;
	new->data = data;
	
	
	

	return new;
}



void insertFront(List* list, void* toBeAdded)
{
	
	if(toBeAdded==NULL||list==NULL)
	{
		return;
	}
	Node * last;
	Node * newhead;
	newhead = initializeNode(toBeAdded);
	if ((list != NULL)&&(list->head != NULL ))
	{
		last = list->head;
		last->previous = newhead;
		newhead->next=last;
		list-> head = newhead;

	}
	else
	{
		if(list->head == NULL)
		{
			list->head = newhead;
			list->tail = newhead;
		}
		else
		{

		}
		
	}
	list->length=list->length+1;
	return;
	


}

void insertBack(List * list, void* toBeAdded)
{
	
	if(toBeAdded==NULL||list==NULL)
	{
		
		return;
	}
	Node * last;
	Node * newtail;
	
	newtail = initializeNode(toBeAdded);
	
	if(list->tail != NULL )
	{
		last= list->tail;
		last->next = newtail;
		newtail->previous =last;
		list->tail = newtail;
	}
	else
	{

		if(list-> tail == NULL)
		{
			
			list->head = newtail;
			list->tail = newtail;
		}
		else
		{

		}


	}
	list->length=list->length+1;
	return;
}


void clearList(List* list)
{
	Node * head;
	Node * next;

	if(list !=NULL)
	{
		head = list->head;
		
		if( head != NULL)
		{
			while(head->next!=NULL)
			{
				//free(head->data);
				list->deleteData(head->data);
				next=head->next;
				free(head);
				head=next;
			}
			list->deleteData(head->data);	
			free(head);
			list->head=NULL;
			list->tail=NULL;
		
		}
		list->length=0;
	}
	return;
}


void insertSorted(List* list, void* toBeAdded)
{
	/*
	if(toBeAdded==NULL||list==NULL)
	{
		return;
	}
	Node * head;
	Node * new;
	Node * top;

	new = initializeNode(toBeAdded);
	
	list->length=list->length+1;

	if(list->head==NULL)
	{
		list->tail=new;
		list->head=new;
		
		return;
	}
	head=list->head;

	while(head->next!=NULL)
	{
		
		if((list->compare(new->data,head->data)) < 0)
		{

			if(head->previous==NULL)
			{
				list->head=new;
				new->next=head;
				head->previous=new;

				return;


			}
			top=head->previous;
			top->next=new;
			new->previous=top;
			new->next=head;
			head->previous=new;
			return;


		}
		if((list->compare(new->data,head->data)) == 0)
		{
			list->length=list->length-1;
			return;
		}

		head=head->next;
		
		
	}
	if((list->compare(new->data,head->data)) < 0)
	{
		if(head->previous==NULL)
		{
			list->head=new;
			new->next=head;
			head->previous=new;
			return;


		}
		top=head->previous;
		top->next=new;
		new->previous=top;
		new->next=head;
		head->previous=new;
		return;


	}
	head->next=new;
	new->previous=head;
	list->tail=new;
	return;
	*/
	if (list == NULL || toBeAdded == NULL){
		return;
	}
	
	if (list->head == NULL){
		insertBack(list, toBeAdded);
		return;
	}
	
	if (list->compare(toBeAdded, list->head->data) <= 0){
		insertFront(list, toBeAdded);
		return;
	}
	
	if (list->compare(toBeAdded, list->tail->data) > 0){
		insertBack(list, toBeAdded);
		return;
	}
	
	Node* currNode = list->head;
	
	while (currNode != NULL){
		if (list->compare(toBeAdded, currNode->data) <= 0){
		
			char* currDescr = list->printData(currNode->data); 
			char* newDescr = list->printData(toBeAdded); 
		
			printf("Inserting %s before %s\n", newDescr, currDescr);

			free(currDescr);
			free(newDescr);
		
			Node* newNode = initializeNode(toBeAdded);
			newNode->next = currNode;
			newNode->previous = currNode->previous;
			currNode->previous->next = newNode;
			currNode->previous = newNode;
		
			return;
		}
	
		currNode = currNode->next;
	}
	
	return;


}


void* deleteDataFromList(List* list, void* toBeDeleted)
{
	Node * head;
	Node * last;
	Node * next;
	head=list->head;
	void * returnitem;
	if(toBeDeleted==NULL||list==NULL)
	{
		return NULL;
	}
	list->length=list->length-1;
	while(head->next!=NULL)
	{
		
		if(list->compare(toBeDeleted,head->data)==0)
		{
			
			if(head->previous==NULL)
			{
				if(head->next==NULL)
				{
					list->head=NULL;
					list->tail=NULL;


				}
				else
				{
				
				
					list->head=head->next;
					next=head->next;
					next->previous=NULL;
					head->next=NULL;
					

				}
				


			}
			else
			{
				last=head->previous;
				next=head->next;
				last->next=next;
				head->previous=NULL;
				next->previous=last;
				head->next=NULL;
			}
			returnitem=head->data;
			free(head);
			
				
				
			return returnitem;
				


		}

		
		head=head->next;

		
	}
	if(list->compare(toBeDeleted,head->data)==0)
	{
		if(head->previous==NULL)
		{
			list->tail=NULL;
			list->head=NULL;

		}
		else
		{
			list->tail=head->previous;
			last=head->previous;
			last->next=NULL;
			head->previous=NULL;
		

		}
		returnitem=head->data;
		free(head);
		return returnitem;



	}
	list->length=list->length+1;
	return NULL;

}

void* getFromFront(List list)
{
	if(list.head==NULL)
	{
		return NULL;
	}
	Node * head;
	head=list.head;
	return head->data;
}


void* getFromBack(List list)
{
	if(list.tail==NULL)
	{
		return NULL;
	}	
	Node * tail;
	tail=list.tail;
	return tail->data;
}





char* toString(List list)
{
	Node * head;
	char * end;
	char * frees;
	
	
	head=list.head;
	if(head==NULL||head->data==NULL)
	{
		
		return NULL;

	}
	end=malloc(9750);
	frees=list.printData(head->data);
	
	strcpy(end,frees);
	free(frees);
	while(head->next!=NULL)
	{
		
	

		head=head->next;
		frees=list.printData(head->data);
		strcat (end,frees);
		free(frees);
	}
	return end;
}



ListIterator createIterator(List list)
{


	ListIterator new;
	new.current= list.head;
	return new;
}


void * nextElement(ListIterator * iter)
{

	
	if(iter->current==NULL)
	{
		return NULL;
	}
	Node * last;
	last=iter->current;
	if(last->next!=NULL)
	{
		iter->current=last->next;
	}
	else
	{
		iter->current=NULL;
	}
	
	return last->data;


}




int getLength(List list)
{	
	Node * head;
	head=list.head;
	
	if(head==NULL)
	{
		
		return 0;

	}
	int number;
	number=list.length;
	return number;

}

void* findElement(List list, bool (*customCompare)(const void* first,const void* second), const void* searchRecord)
{
	Node * head;
	head=list.head;
	
	if(head==NULL)
	{
		
		return NULL;

	}
	void * returndata;
	
	while(head!=NULL)
	{
		
		if(customCompare(head->data,searchRecord))
		{
			returndata=head->data;
			return returndata;

		}
		head=head->next;
		
	}


	
	return NULL;

		
}








