#include <stdlib.h>
#include "list.h"
#include "Inner_list.h"

/********************************************************/
/*				ADT - Double Linked List				*/
/*				C file									*/
/*				Created by: Adi Ben Zeev				*/
/*				Created at: 20.12.16					*/
/*				last edited:							*/
/********************************************************/



/*
#define HEAD_TAIL_DATA (5555)

typedef struct Node Node;

struct Node
{
	void* 	m_data;
	Node* 	m_next;
	Node* 	m_prev;
};

struct List
{
	Node 	m_head;
	Node 	m_tail;
};
*/

/***********************************************************/


/****** List_Create ******/

List* List_Create(void)
{
	List* newlist;
	
	newlist = (List*)malloc(1 * sizeof(List));
	if (NULL == newlist)
	{
		return NULL;
	}
	
	newlist->m_head.m_prev = NULL;
	(newlist->m_head).m_next = &(newlist->m_tail);
	(newlist->m_head.m_data) = (void*)HEAD_TAIL_DATA; /* TODO - generic */
	
	newlist->m_tail.m_next = &(newlist->m_tail);
	(newlist->m_tail).m_prev = &(newlist->m_head);
	((newlist->m_tail).m_data) = NULL;
/*	((newlist->m_tail).m_data) = (void*)HEAD_TAIL_DATA; */ /* TODO - generic */
	
	return newlist;
}

/****** List_Destroy ******/

void List_Destroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* temp;
	Node* tempTail;
	/*TODO - add a nextTemp for stepping forward. then no need to look back - like Natali !! */
	
	if (NULL == _pList || NULL == *_pList ) /* (NULL == *_pList) -> maybe irrelevant and need to remove. but maybe relevant for double destroy ? */
	{
		return;
	}
	if (((*_pList)->m_head.m_data) != (void*)HEAD_TAIL_DATA)
	{
		return;
	}
	
	tempTail = &((*_pList)->m_tail);
	temp = (*_pList)->m_head.m_next;
	while ( temp != tempTail) 
	{
		if (NULL != _elementDestroy)
		{
			_elementDestroy((void*)temp->m_data);
		}
		temp = temp->m_next;
		free(temp->m_prev);
	}
	
	/* OLD WHILE LOOP - for maybe future reference (?) */
	/*
	while (((*_pList)->m_head).m_next != &((*_pList)->m_tail))
	{
		temp = (*_pList)->m_head.m_next;
		temp->m_prev->m_next = temp->m_next;
		temp->m_next->m_prev = temp->m_prev;
		temp->m_next = NULL;
		temp->m_prev = NULL;
		
		if (NULL != _elementDestroy)
		{
			_elementDestroy((void*)temp);
		}
		
	}
	*/
	
	(*_pList) = NULL;
	free(*_pList);
	
	return;
}


/****** List_PushHead ******/

List_Result List_PushHead(List* _list, void* _item)
{
	Node* new_node;
	List_Result err = LIST_SUCCESS;
	
	if (NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if ((_list->m_head.m_data) != (void*)HEAD_TAIL_DATA)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if (NULL == _item)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	
	new_node = (Node*)malloc(1*sizeof(Node));
	if (NULL == new_node)
	{
		return LIST_ALLOCATION_ERROR;
	}
	
	new_node->m_data = _item;
	new_node->m_next = (_list->m_head).m_next; 
	new_node->m_prev = &(_list->m_head); 
	new_node->m_next->m_prev = new_node;
	new_node->m_prev->m_next = new_node;
	/* in comment - like above, but less generic  */
	/*
	((_list->m_head).m_next)->m_prev = new_node; 
	(_list->m_head).m_next = new_node;
	*/
	
	
	return err;
}


/****** List_PushTail ******/

List_Result List_PushTail(List* _list, void* _item)
{
		Node* new_node;
	List_Result err = LIST_SUCCESS;
	
	if (NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if ((_list->m_head.m_data) != (void*)HEAD_TAIL_DATA)
	{
		return LIST_UNINITIALIZED_ERROR;
	}

	if (NULL == _item)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	
	new_node = (Node*)malloc(1*sizeof(Node));
	if (NULL == new_node)
	{
		return LIST_ALLOCATION_ERROR;
	}
	
	new_node->m_data = _item;
	new_node->m_next = &(_list->m_tail);
	new_node->m_prev = (_list->m_tail).m_prev;
	new_node->m_next->m_prev = new_node;
	new_node->m_prev->m_next = new_node;
	/* in comment - like above, but less generic  */
	/*
	((_list->m_tail).m_prev)->m_next = new_node;
	(_list->m_tail).m_prev = new_node;
	*/
	
	
	return err;
}


/****** List_PopHead ******/

List_Result List_PopHead(List* _list, void** _pItem)
{
	List_Result err = LIST_SUCCESS;
	Node* remNode;
	
	if (NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if ((_list->m_head.m_data) != (void*)HEAD_TAIL_DATA)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if (NULL == _pItem)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	if (_list->m_head.m_next == &(_list->m_tail))
	{
		return LIST_UNDERFLOW_ERROR;
	}
	
	
	remNode = (_list->m_head).m_next;
	remNode->m_prev->m_next = remNode->m_next;
	remNode->m_next->m_prev = remNode->m_prev;
	remNode->m_next = NULL;
	remNode->m_prev = NULL;
	
	*_pItem = remNode->m_data;
	free(remNode);
	
	return err;
	
}

/****** List_PopTail ******/

List_Result List_PopTail(List* _list, void** _pItem)
{
	
	List_Result err = LIST_SUCCESS;
	Node* remNode;
	
	if (NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if ((_list->m_head.m_data) != (void*)HEAD_TAIL_DATA)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if (NULL == _pItem)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	if (_list->m_head.m_next == &(_list->m_tail))
	{
		return LIST_UNDERFLOW_ERROR;
	}
	
	
	remNode = (_list->m_tail).m_prev;
	remNode->m_prev->m_next = remNode->m_next;
	remNode->m_next->m_prev = remNode->m_prev;
	remNode->m_next = NULL;
	remNode->m_prev = NULL;
	
	
	*_pItem = remNode->m_data;
	free(remNode);
	
	
	return err;
	
}


 
 /****** List_Size ******/
 
size_t List_Size(const List* _list)
{
	Node* nextNode = NULL;
	size_t listSize = 0;
	
	if (NULL == _list)
	{
		return 0;
	}
	if ((_list->m_head.m_data) != (void*)HEAD_TAIL_DATA)
	{
		return 0;
	}
	
	
	nextNode = _list->m_head.m_next;
	
	while ( NULL != nextNode && nextNode != &(_list->m_tail) )
	{
		++listSize;
		nextNode = nextNode->m_next;
	}
		
	
	return listSize;
}

/*
size_t List_Size(const List* _list)
{
	Node_t* nextNode	= NULL;
	size_t	counter		= 0;
	
	if ( ! List_IsValid(_list) )
	{
		return 0;
	}
	
	nextNode = _list->m_head.m_next;
	
	while ( NULL != nextNode && nextNode != &(_list->m_tail) )
	{
		counter++;
		nextNode = nextNode->m_next;
	}
	
	return counter;
}
*/








