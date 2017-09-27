#include "list.h"
#include "list_itr.h"
#include "innar.h"

#include <stdio.h>
#include <stdlib.h>

#define ITR_IS_TAIL(itr) ( ( (Node*)(itr) )->m_next == (itr) )


/*
	Iterator for Linked List

	Create by Natali Mesika
	Update 30.12.2016
*/ 
/*find the begin of the list*/
ListItr ListItr_Begin(const List* _list)
{
	
	if(NULL == _list)
	{
		return NULL;
	}

	return _list->head.m_next;
}

/*Will be the stop condition*/
ListItr ListItr_End(const List* _list)
{
	if(NULL == _list)
	{
		return NULL;
	}
	
	return (void*)&(_list->tail);
}


int ListItr_Equals(const ListItr _a, const ListItr _b)
{

	if(NULL == _a || NULL == _b)
	{
		return 0;
	}
	return(_a == _b)?1: 0;
}

ListItr ListItr_Next(ListItr _itr)
{
	Node* node_itr = _itr;
		
	if(NULL == _itr)
	{
		return NULL;
	}
	
	return node_itr->m_next;
}

/*Get itertator to the previous element*/
ListItr ListItr_Prev(ListItr _itr)
{
	Node* node_itr = _itr;
	
	if(NULL == _itr)
	{
		return NULL;
	}
	node_itr =( (Node*)_itr)->m_prev;
	if(node_itr->m_prev == node_itr)
	{
			return  _itr;
	}
/*	if( NULL == node_itr->m_prev->m_prev )*/
/*	{*/
/*		return  _itr;*/
/*	}*/

	return  node_itr->m_prev;
}

/*void* ListItr_Get(ListItr _itr)*/
/*{*/
/*	Node* ptrNode = _itr;*/
/*	*/
/*	if(NULL == _itr)*/
/*	{*/
/*		return NULL;*/
/*	}*/

/*	if( ITR_IS_TAIL(_itr))*/
/*	{*/
/*		return  _itr;*/
/*	}*/
/*	*/
/*	return  (ptrNode->m_data );*/
/*}*/

void* ListItr_Get(ListItr _itr)
{
	/*what happens if get is pointing at the head?*/
	if (NULL == _itr || ((Node*)_itr)->m_next == (Node*)_itr)
	{
		return NULL; 
	}
	return ((Node*)_itr)->m_data; 
}

void* ListItr_Set(ListItr _itr, void* _element)
{

	Node* beforeChange;
	Node* iter = _itr;
	
	if(NULL == _itr || NULL == _element) 
	{
		return NULL;
	}
	
	if(iter->m_next->m_next == ( (iter->m_next)) )
	{
		return _itr;
	}
	
	beforeChange = ( iter->m_data );
	( iter->m_data ) = _element;
	
	return beforeChange;
}

 
ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	Node* newNode;
	Node* ptrNode = _itr;

	if (NULL == _itr || NULL == _element) 
	{
		return NULL;
	}
	
	newNode = (Node*)malloc(sizeof(Node));
	
	if (NULL == newNode)
	{
		return NULL;
	} 
	
	newNode->m_data = _element;
	newNode->m_prev = (ptrNode)->m_prev;
	newNode->m_next = ptrNode;
	
	ptrNode->m_prev->m_next = newNode;
	ptrNode->m_prev = newNode;

	return _itr;
}


void* ListItr_Remove(ListItr _itr)
{
	Node* remove;
	void* removItem;
	if(NULL == _itr) 
	{
		return NULL;
	}
	remove = _itr;
	
	remove->m_next->m_prev = remove->m_prev;
	remove->m_prev->m_next = remove->m_next;
	
	removItem = remove->m_data;
	
	free(remove);
	
	return removItem;
}












