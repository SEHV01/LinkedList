# LinkedList

A singly linked list library.

## Getting the source and running the tests

We first need to get the source code. The projects has the [Unity Test](https://github.com/ThrowTheSwitch/Unity) project as a sub module for its unit tests.
-	```
	git clone --recursive https://github.com/SEHV01/LinkedList.git
	cd ./LinkedList
	```
-	```
	mkdir build
	cd ./build
	```
-	```
	cmake ..
	cmake --build . --target LinkedListTest
	```
-	```
	./test/LinkedListTest
	```

## Using the library in your project
To use this library in your project, you need to add this directory to your top level CMakeLists.txt as a subdirectory.
```Cmake
add_subdirectory(<PATH_TO_LINKEDLIST_DIRECTORY>)
```
You will also need to link the library to your project in the CMakeLists.txt where the library is used. 
```CMake
target_link_libraries(<YOUR_TARGET> PRIVATE LinkedList)
```

## API
This library can be used to dynamically store objects. It has a set of functions to interact with the linked list. The functions will take care of memory management. Each function returns zero on success of execution otherwise an error code will be returned.

| Label               	| Error code 	|
|---------------------	|------------	|
| ERROR_LIST_EMPTY    	| -1         	|
| ERROR_LIST_NULL     	| -2         	|
| ERROR_ELEMENT_NULL  	| -3         	|
| ERROR_INDEX_NULL    	| -4         	|
| ERROR_ITEM_NULL     	| -5         	|
| ERROR_INVALID_INDEX 	| -6         	|
| ERROR_INVALID_ITEM  	| -7         	|

### LinkedList* ListInitialize(size_t elementSize)
Initialize a linked list with the element size of a given type.
```c
LinkedList* list = ListInitialize(sizeof(int));
```

### int ListDestroy(LinkedList** list)
Destroy a linked list.
```c
ListDestroy(&list);
```

### size_t ListCount(LinkedList* list)
Get the element count of the linked list.
```c
size_t count = ListCount(list);
```

### int ListPushFront(LinkedList* list, void* item)
Add an element to the front of a linked list.
```c
int item = 42;
ListPushFront(list, &item);
```

### int ListPushBack(LinkedList* list, void* item)
Add an element to the back of a linked list.
```c
int item = 99;
ListPushBack(list, &item);
```

### int ListPushAt(LinkedList* list, size_t index, void* item)
Add an element at a given index of a linked list.
```c
int item = 10;
ListPushAt(list, 1, &insertItem);
```

### int ListPopFront(LinkedList* list)
Remove the first element of a linked list.
```c
ListPopFront(list);
```

### int ListPopBack(LinkedList* list)
Remove the last element of a linked list.
```c
ListPopBack(list);
```

### int ListPopAt(LinkedList* list, size_t index)
Remove the element at a given index of a linked list.
```c
ListPopAt(list, 8);
```

### int ListReplace(LinkedList* list, size_t index, void* item)
Replace an element at a given index of a linked list
```c
ListReplace(list, 0, &replaceItem);
```

### int ListClear(LinkedList* list)
Remove all elements from a linked list.
```c
ListClear(list);
```

### int ListGetItem(LinkedList* list, size_t index, void** item)
Get an item on a given index of an linked list.
```c
int* value = 0;
ListGetItem(list, 0, (void*)&value);
```

### int ListGetIndex(LinkedList* list, size_t* index, void* item, int (\*compar)(const void*, const void*))
Get the index of a given item of a linked list. The user must define a compare function that returns zero when two items are identical.
```c
static int CompareItems(const void* itemOne, const void* itemTwo)
{
	return (*(int*)itemOne - *(int*)itemTwo);
}

···
int item = 42;
size_t index = 0;

ListGetIndex(list, &index, &item, CompareItems);
···
```
