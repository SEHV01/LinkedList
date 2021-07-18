#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

typedef enum ErrorCodes
{
	ERROR_LIST_EMPTY = -1,
	ERROR_LIST_NULL = -2,
	ERROR_ELEMENT_NULL = -3,
	ERROR_INDEX_NULL = -4,
	ERROR_ITEM_NULL = -5,
	ERROR_INVALID_INDEX = -6,
	ERROR_INVALID_ITEM = -7
} ErrorCodes;

typedef struct LinkedList LinkedList;

LinkedList* ListInitialise(size_t elementSize);
int ListDestroy(LinkedList** list);

size_t ListCount(LinkedList* list);

int ListPushFront(LinkedList* list, void* item);
int ListPushBack(LinkedList* list, void* item);
int ListPushAt(LinkedList* list, size_t index, void* item);

int ListPopFront(LinkedList* list);
int ListPopBack(LinkedList* list);
int ListPopAt(LinkedList* list, size_t index);

int ListReplace(LinkedList* list, size_t index, void* item);

int ListClear(LinkedList* list);

int ListGetItem(LinkedList* list, size_t index, void** item);
int ListGetIndex(LinkedList* list, size_t* index, void* item, int (*compar)(const void*, const void*));

#endif
