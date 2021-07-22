#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct LinkedList
{
	struct LinkedListElement* element;
	size_t dataSize;
	size_t count;
} LinkedList;

typedef struct LinkedListElement
{
	void* data;
	struct LinkedListElement* next;
} LinkedListElement;

static void IncreaseCount(LinkedList* list)
{
	list->count++;
}

static void DecreaseCount(LinkedList* list)
{
	list->count--;
}

static void ClearCount(LinkedList* list)
{
	list->count = 0;
}

LinkedList* ListInitialise(size_t dataSize)
{
	if (dataSize == 0)
	{
		return NULL;
	}

	LinkedList* list = malloc(sizeof(LinkedList));

	if (list == NULL)
	{
		return NULL;
	}

	list->element = NULL;
	list->dataSize = dataSize;
	ClearCount(list);

	return list;
}

int ListDestroy(LinkedList** list)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}

	ListClear(*list);
	free(*list);
	*list = NULL;

	return 0;
}

static void FreeElement(LinkedListElement** element)
{
	free((*element)->data);
	(*element)->data = NULL;

	free(*element);
	*element = NULL;
}

static LinkedListElement* CreateElement(LinkedList* list, void* item)
{
	LinkedListElement* element = malloc(sizeof(LinkedListElement));

	if (element == NULL)
	{
		return NULL;
	}

	element->data = malloc(list->dataSize);
	element->next = NULL;

	if (element->data == NULL)
	{
		free(element);
		element = NULL;

		return NULL;
	}

	memcpy(element->data, item, list->dataSize);

	return element;
}

static LinkedListElement* GetElement(LinkedList* list, size_t index)
{
	LinkedListElement* element = list->element;

	for (size_t i = 0; i < index; i++)
	{
		element = element->next;
	}

	return element;
}

static ssize_t GetIndex(LinkedList* list, void* item, int (*compar)(const void*, const void*))
{
	LinkedListElement* element = list->element;

	size_t index = 0;

	while (element != NULL)
	{
		if (compar(element->data, item) == 0)
		{
			return index;
		}

		element = element->next;
		index++;
	}

	return ERROR_INVALID_ITEM;
}

size_t ListCount(LinkedList* list)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}

	return list->count;
}

int ListPushFront(LinkedList* list, void* item)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (item == NULL)
	{
		return ERROR_ITEM_NULL;
	}

	LinkedListElement* beginElement = list->element;
	LinkedListElement* newElement = CreateElement(list, item);

	if (newElement == NULL)
	{
		return ERROR_ELEMENT_NULL;
	}

	if (beginElement == NULL)
	{
		list->element = newElement;
	}
	else
	{
		list->element = newElement;
		newElement->next = beginElement;
	}

	IncreaseCount(list);

	return 0;
}

int ListPushBack(LinkedList* list, void* item)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (item == NULL)
	{
		return ERROR_ITEM_NULL;
	}

	if (ListCount(list) == 0)
	{
		ListPushFront(list, item);

		return 0;
	}

	LinkedListElement* lastElement = GetElement(list, ListCount(list) - 1);
	LinkedListElement* newElement = CreateElement(list, item);

	if (newElement == NULL)
	{
		return ERROR_ELEMENT_NULL;
	}

	lastElement->next = newElement;

	IncreaseCount(list);

	return 0;
}

int ListPushAt(LinkedList* list, size_t index, void* item)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (index > ListCount(list))
	{
		return ERROR_INVALID_INDEX;
	}
	if (item == NULL)
	{
		return ERROR_ITEM_NULL;
	}

	if (index == 0)
	{
		ListPushFront(list, item);

		return 0;
	}
	if (index == ListCount(list))
	{
		ListPushBack(list, item);

		return 0;
	}

	LinkedListElement* middleElement = GetElement(list, index - 1);
	LinkedListElement* nextElement = middleElement->next;
	LinkedListElement* newElement = CreateElement(list, item);

	if (newElement == NULL)
	{
		return ERROR_ELEMENT_NULL;
	}

	middleElement->next = newElement;
	newElement->next = nextElement;

	IncreaseCount(list);

	return 0;
}

int ListPopFront(LinkedList* list)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (ListCount(list) == 0)
	{
		return ERROR_LIST_EMPTY;
	}

	LinkedListElement* remainingElements = list->element->next;

	FreeElement(&list->element);

	if (remainingElements != NULL)
	{
		list->element = remainingElements;
	}

	DecreaseCount(list);

	return 0;
}

int ListPopBack(LinkedList* list)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (ListCount(list) == 0)
	{
		return ERROR_LIST_EMPTY;
	}

	if (ListCount(list) == 1)
	{
		ListPopFront(list);

		return 0;
	}

	LinkedListElement* secondLastElement = GetElement(list, ListCount(list) - 2);

	FreeElement(&secondLastElement->next);
	DecreaseCount(list);

	return 0;
}

int ListPopAt(LinkedList* list, size_t index)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (ListCount(list) == 0)
	{
		return ERROR_LIST_EMPTY;
	}
	if (index >= ListCount(list))
	{
		return ERROR_INVALID_INDEX;
	}

	if (index == 0)
	{
		ListPopFront(list);

		return 0;
	}
	if (index == ListCount(list) - 1)
	{
		ListPopBack(list);

		return 0;
	}

	LinkedListElement* leftFromRemoveElement = GetElement(list, index - 1);
	LinkedListElement* rightFromRemoveElement = leftFromRemoveElement->next->next;

	FreeElement(&leftFromRemoveElement->next);
	DecreaseCount(list);

	leftFromRemoveElement->next = rightFromRemoveElement;

	return 0;
}

int ListReplace(LinkedList* list, size_t index, void* item)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (ListCount(list) == 0)
	{
		return ERROR_LIST_EMPTY;
	}
	if (index >= ListCount(list))
	{
		return ERROR_INVALID_INDEX;
	}
	if (item == NULL)
	{
		return ERROR_ITEM_NULL;
	}

	LinkedListElement* replaceElement = GetElement(list, index);

	memcpy(replaceElement->data, item, list->dataSize);

	return 0;
}

int ListClear(LinkedList* list)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (ListCount(list) == 0)
	{
		return ERROR_LIST_EMPTY;
	}

	while (ListCount(list) > 0)
	{
		ListPopFront(list);
	}

	return 0;
}

int ListGetItem(LinkedList* list, size_t index, void** item)
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (ListCount(list) == 0)
	{
		return ERROR_LIST_EMPTY;
	}
	if (index >= ListCount(list))
	{
		return ERROR_INVALID_INDEX;
	}
	if (item == NULL)
	{
		return ERROR_ITEM_NULL;
	}

	LinkedListElement* element = GetElement(list, index);

	*item = element->data;

	return 0;
}

int ListGetIndex(LinkedList* list, size_t* index, void* item, int (*compar)(const void*, const void*))
{
	if (list == NULL)
	{
		return ERROR_LIST_NULL;
	}
	if (ListCount(list) == 0)
	{
		return ERROR_LIST_EMPTY;
	}
	if (index == NULL)
	{
		return ERROR_INDEX_NULL;
	}
	if (item == NULL)
	{
		return ERROR_ITEM_NULL;
	}

	ssize_t itemIndex = GetIndex(list, item, compar);

	if (itemIndex == ERROR_INVALID_ITEM)
	{
		return ERROR_INVALID_ITEM;
	}

	*index = itemIndex;

	return 0;
}
