#include "LinkedList/LinkedList.h"
#include <stdlib.h>
#include <unity.h>

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
	// This is run before EACH test
}

void tearDown(void)
{
	// This is run after EACH test
}

void ListInitialise_ElementSize_ReturnsListAndCountZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	TEST_ASSERT_EQUAL(0, ListCount(list));
	TEST_ASSERT_NOT_NULL(list);

	ListDestroy(&list);
}

void ListDestroy_IllegalParameters_ReturnsErrorCode(void)
{
	int result = ListDestroy(NULL);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, result);
}

void ListDestroy_LinkedList_ReturnsZeroAndLinkedListNull(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int result = ListDestroy(&list);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_NULL(list);
}

void ListCount_IllegalParameters_ReturnsErrorCode(void)
{
	int result = ListCount(NULL);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, result);
}

void ListCount_EmptyList_ReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	size_t count = ListCount(list);

	TEST_ASSERT_EQUAL(0, count);

	ListDestroy(&list);
}

void ListCount_ListFiveElements_ReturnsFive(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	for (int i = 0; i < 5; i++)
	{
		int item = i;
		ListPushFront(list, &item);
	}

	size_t count = ListCount(list);

	TEST_ASSERT_EQUAL(5, count);

	ListDestroy(&list);
}

void ListPushFront_IllegalParameters_ReturnsErrorCode(void)
{
	LinkedList* list = ListInitialise(sizeof(int));
	int item = 0;

	int resultOne = ListPushFront(NULL, &item);
	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, resultOne);

	int resultTwo = ListPushFront(list, NULL);
	TEST_ASSERT_EQUAL(ERROR_ITEM_NULL, resultTwo);

	ListDestroy(&list);
}

void ListPushFront_LinkedListItem_AddsItemAtFrontIncrementsCountAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	int result = ListPushFront(list, &item);

	int* value = 0;
	ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(item, *value);
	TEST_ASSERT_EQUAL(1, ListCount(list));

	ListDestroy(&list);
}

void ListPushFront_LinkedListItemWithItemInList_AddsItemAtFrontFollowedByPreviousFrontIncrementsCountAndReturnsZero(
	void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int itemOne = 42;
	ListPushFront(list, &itemOne);
	int itemTwo = 99;
	int result = ListPushFront(list, &itemTwo);

	int* valueOne = 0;
	ListGetItem(list, 0, (void*)&valueOne);
	int* valueTwo = 0;
	ListGetItem(list, 1, (void*)&valueTwo);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(itemTwo, *valueOne);
	TEST_ASSERT_EQUAL(itemOne, *valueTwo);
	TEST_ASSERT_EQUAL(2, ListCount(list));

	ListDestroy(&list);
}

void ListPushFront_LinkedListItemWithMultipleItemsInList_AddsItemAtFrontFollowedByPreviousFrontIncrementsCountAndReturnsZero(
	void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	for (int i = 0; i < 4; i++)
	{
		int item = i;
		ListPushFront(list, &item);
	}

	int item = 99;
	int result = ListPushFront(list, &item);

	int* value = 0;
	ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(item, *value);
	TEST_ASSERT_EQUAL(5, ListCount(list));

	for (int i = 1; i < 5; i++)
	{
		int* value = 0;
		ListGetItem(list, i, (void*)&value);

		TEST_ASSERT_EQUAL(4 - i, *value);
	}

	ListDestroy(&list);
}

void ListPushBack_IllegalParameters_ReturnsErrorCode(void)
{
	LinkedList* list = ListInitialise(sizeof(int));
	int item = 0;

	int resultOne = ListPushFront(NULL, &item);
	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, resultOne);

	int resultTwo = ListPushFront(list, NULL);
	TEST_ASSERT_EQUAL(ERROR_ITEM_NULL, resultTwo);

	ListDestroy(&list);
}

void ListPushBack_LinkedListItem_AddsItemAtBackIncrementsCountAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	int result = ListPushBack(list, &item);

	int* value = 0;
	ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(item, *value);
	TEST_ASSERT_EQUAL(1, ListCount(list));

	ListDestroy(&list);
}

void ListPushBack_LinkedListItemWithItemInList_AddsItemAtBackIncrementsCountAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int itemOne = 42;
	ListPushBack(list, &itemOne);
	int itemTwo = 99;
	int result = ListPushBack(list, &itemTwo);

	int* valueOne = 0;
	ListGetItem(list, 0, (void*)&valueOne);
	int* valueTwo = 0;
	ListGetItem(list, 1, (void*)&valueTwo);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(itemOne, *valueOne);
	TEST_ASSERT_EQUAL(itemTwo, *valueTwo);
	TEST_ASSERT_EQUAL(2, ListCount(list));

	ListDestroy(&list);
}

void ListPushBack_LinkedListItemWithMultipleItemsInList_AddsItemAtBackIncrementsCountAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	for (int i = 0; i < 4; i++)
	{
		int item = i;
		ListPushBack(list, &item);
	}

	int item = 99;
	int result = ListPushBack(list, &item);

	int* value = 0;
	ListGetItem(list, 4, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(item, *value);
	TEST_ASSERT_EQUAL(5, ListCount(list));

	for (int i = 0; i < 4; i++)
	{
		int* value = 0;
		ListGetItem(list, i, (void*)&value);

		TEST_ASSERT_EQUAL(i, *value);
	}

	ListDestroy(&list);
}

void ListPushAt_IllegalParameters_ReturnsErrorCode(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;

	int resultOne = ListPushAt(NULL, 0, &item);
	int resultTwo = ListPushAt(list, 1, &item);
	int resultThree = ListPushAt(list, 0, NULL);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, resultOne);
	TEST_ASSERT_EQUAL(ERROR_INVALID_INDEX, resultTwo);
	TEST_ASSERT_EQUAL(ERROR_ITEM_NULL, resultThree);

	ListDestroy(&list);
}

void ListPushAt_LinkedListItemIndexZero_AddsItemAtBackIncrementsCountAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	int result = ListPushAt(list, 0, &item);

	int* value = 0;
	ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(item, *value);
	TEST_ASSERT_EQUAL(1, ListCount(list));

	ListDestroy(&list);
}

void ListPushAt_LinkedListItemIndexOneWithItemInList_AddsItemAtBackIncrementsCountAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int itemOne = 42;
	ListPushBack(list, &itemOne);

	int itemTwo = 99;
	int result = ListPushAt(list, 1, &itemTwo);

	int* valueOne = 0;
	ListGetItem(list, 0, (void*)&valueOne);
	int* valueTwo = 0;
	ListGetItem(list, 1, (void*)&valueTwo);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(itemOne, *valueOne);
	TEST_ASSERT_EQUAL(itemTwo, *valueTwo);
	TEST_ASSERT_EQUAL(2, ListCount(list));

	ListDestroy(&list);
}

void ListPushAt_LinkedListItemIndexOneWithTwoItemsInList_AddsItemAtMiddleIncrementsCountAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int itemOne = 42;
	ListPushBack(list, &itemOne);
	int itemTwo = 99;
	ListPushBack(list, &itemTwo);

	int insertItem = 10;
	int result = ListPushAt(list, 1, &insertItem);

	int* valueOne = 0;
	ListGetItem(list, 0, (void*)&valueOne);
	int* valueTwo = 0;
	ListGetItem(list, 1, (void*)&valueTwo);
	int* valueThree = 0;
	ListGetItem(list, 2, (void*)&valueThree);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(itemOne, *valueOne);
	TEST_ASSERT_EQUAL(insertItem, *valueTwo);
	TEST_ASSERT_EQUAL(itemTwo, *valueThree);
	TEST_ASSERT_EQUAL(3, ListCount(list));

	ListDestroy(&list);
}

void ListPopFront_IllegalParameters_ReturnsErrorCode(void)
{
	int result = ListPopFront(NULL);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, result);
}

void ListPopFront_LinkedListOneItem_RemovesFrontItemListCountZeroAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	ListPushFront(list, &item);

	int result = ListPopFront(list);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(0, ListCount(list));

	ListDestroy(&list);
}

void ListPopFront_LinkedListTwoItems_RemovesFrontItemListCountOneNextItemFrontAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int itemOne = 42;
	ListPushFront(list, &itemOne);
	int itemTwo = 99;
	ListPushFront(list, &itemTwo);

	int result = ListPopFront(list);

	int* value = 0;
	ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(itemOne, *value);
	TEST_ASSERT_EQUAL(1, ListCount(list));

	ListDestroy(&list);
}

void ListPopBack_IllegalParameters_ReturnsErrorCode(void)
{
	int result = ListPopBack(NULL);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, result);
}

void ListPopBack_LinkedListOneItem_RemovesBackItemListCountZeroAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	ListPushFront(list, &item);

	int result = ListPopBack(list);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(0, ListCount(list));

	ListDestroy(&list);
}

void ListPopBack_LinkedListTwoItems_RemovesBackItemListCountOneSameFrontAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int itemOne = 42;
	ListPushFront(list, &itemOne);
	int itemTwo = 99;
	ListPushFront(list, &itemTwo);

	int result = ListPopBack(list);

	int* value = 0;
	ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(itemTwo, *value);
	TEST_ASSERT_EQUAL(1, ListCount(list));

	ListDestroy(&list);
}

void ListPopAt_IllegalParameters_ReturnsErrorCode(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;

	int resultOne = ListPopAt(list, 1);

	ListPushFront(list, &item);

	int resultTwo = ListPopAt(NULL, 0);
	int resultThree = ListPopAt(list, 1);

	TEST_ASSERT_EQUAL(ERROR_LIST_EMPTY, resultOne);
	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, resultTwo);
	TEST_ASSERT_EQUAL(ERROR_INVALID_INDEX, resultThree);

	ListDestroy(&list);
}

void ListPopAt_LinkedListOneItemAndIndexZero_RemovesFrontItemListCountZeroAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	ListPushFront(list, &item);

	int result = ListPopAt(list, 0);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(0, ListCount(list));

	ListDestroy(&list);
}

void ListPopAt_LinkedListTwoItemsAndIndexOne_RemovesBackItemListCountOneSameFrontAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int itemOne = 42;
	ListPushFront(list, &itemOne);
	int itemTwo = 99;
	ListPushFront(list, &itemTwo);

	int result = ListPopAt(list, 1);

	int* value = 0;
	ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(itemTwo, *value);
	TEST_ASSERT_EQUAL(1, ListCount(list));

	ListDestroy(&list);
}

void ListPopAt_LinkedListThreeItemsAndIndexOne_RemovesMiddleItemListCountTwoAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	for (int i = 0; i < 3; i++)
	{
		int item = i;
		ListPushBack(list, &item);
	}

	int result = ListPopAt(list, 1);

	int* valueOne = 0;
	ListGetItem(list, 0, (void*)&valueOne);

	int* valueTwo = 0;
	ListGetItem(list, 1, (void*)&valueTwo);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(0, *valueOne);
	TEST_ASSERT_EQUAL(2, *valueTwo);
	TEST_ASSERT_EQUAL(2, ListCount(list));

	ListDestroy(&list);
}

void ListClear_IllegalParameters_ReturnsErrorCode(void)
{
	int result = ListClear(NULL);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, result);
}

void ListClear_LinkedList_ClearsListAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	for (int i = 0; i < 3; i++)
	{
		int item = i;
		ListPushFront(list, &item);
	}

	int result = ListClear(list);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(0, ListCount(list));

	ListDestroy(&list);
}

void ListGetItem_IllegalParameters_ReturnsErrorCode(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;

	int resultTwo = ListGetItem(list, 0, (void*)&item);

	ListPushFront(list, &item);

	int resultOne = ListGetItem(NULL, 0, (void*)&item);
	int resultThree = ListGetItem(list, 1, (void*)&item);
	int resultFour = ListGetItem(list, 0, NULL);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, resultOne);
	TEST_ASSERT_EQUAL(ERROR_LIST_EMPTY, resultTwo);
	TEST_ASSERT_EQUAL(ERROR_INVALID_INDEX, resultThree);
	TEST_ASSERT_EQUAL(ERROR_ITEM_NULL, resultFour);

	ListDestroy(&list);
}

void ListGetItem_LinkedListAndIndexOfItem_GetsItemByPointerAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	ListPushBack(list, &item);

	int* value = 0;
	int result = ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(item, *value);

	ListDestroy(&list);
}

static int CompareItems(const void* itemOne, const void* itemTwo)
{
	return (*(int*)itemOne - *(int*)itemTwo);
}

void ListGetIndex_IllegalParameters_ReturnsErrorCode(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	size_t index = 0;

	int resultTwo = ListGetIndex(list, &index, &item, CompareItems);

	ListPushFront(list, &item);

	int resultOne = ListGetIndex(NULL, &index, &item, CompareItems);
	int resultThree = ListGetIndex(list, NULL, &item, CompareItems);
	int resultFour = ListGetIndex(list, &index, NULL, CompareItems);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, resultOne);
	TEST_ASSERT_EQUAL(ERROR_LIST_EMPTY, resultTwo);
	TEST_ASSERT_EQUAL(ERROR_INDEX_NULL, resultThree);
	TEST_ASSERT_EQUAL(ERROR_ITEM_NULL, resultFour);

	ListDestroy(&list);
}

void ListGetIndex_LinkedListInvalidItemAndCompareFunction_ReturnsErrorInvallidItem(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	ListPushFront(list, &item);

	int value = 1;
	size_t index = 0;
	int result = ListGetIndex(list, &index, &value, CompareItems);

	TEST_ASSERT_EQUAL(ERROR_INVALID_ITEM, result);
	TEST_ASSERT_EQUAL(0, index);

	ListDestroy(&list);
}

void ListGetIndex_LinkedListItemAndCompareFunction_GetsIndexByPointerAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	for (int i = 0; i < 3; i++)
	{
		int item = i;
		ListPushFront(list, &item);
	}

	int value = 1;
	size_t index = 0;
	int result = ListGetIndex(list, &index, &value, CompareItems);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(1, index);

	ListDestroy(&list);
}

void ListReplace_IllegalParameters_ReturnsErrorCode(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;

	int resultTwo = ListReplace(list, 0, &item);

	ListPushFront(list, &item);

	int resultOne = ListReplace(NULL, 0, &item);
	int resultThree = ListReplace(list, 1, &item);
	int resultFour = ListReplace(list, 0, NULL);

	TEST_ASSERT_EQUAL(ERROR_LIST_NULL, resultOne);
	TEST_ASSERT_EQUAL(ERROR_LIST_EMPTY, resultTwo);
	TEST_ASSERT_EQUAL(ERROR_INVALID_INDEX, resultThree);
	TEST_ASSERT_EQUAL(ERROR_ITEM_NULL, resultFour);

	ListDestroy(&list);
}

void ListReplace_LinkedListIndexAndReplaceItem_ReplacesItemAtIndexAndReturnsZero(void)
{
	LinkedList* list = ListInitialise(sizeof(int));

	int item = 42;
	ListPushFront(list, &item);

	int replaceItem = 99;
	int result = ListReplace(list, 0, &replaceItem);

	int* value = 0;
	ListGetItem(list, 0, (void*)&value);

	TEST_ASSERT_EQUAL(0, result);
	TEST_ASSERT_EQUAL(replaceItem, *value);
	TEST_ASSERT_EQUAL(1, ListCount(list));

	ListDestroy(&list);
}

int main(void)
{
	UNITY_BEGIN();

	MY_RUN_TEST(ListInitialise_ElementSize_ReturnsListAndCountZero);
	MY_RUN_TEST(ListDestroy_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListDestroy_LinkedList_ReturnsZeroAndLinkedListNull);
	MY_RUN_TEST(ListCount_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListCount_EmptyList_ReturnsZero);
	MY_RUN_TEST(ListCount_ListFiveElements_ReturnsFive);
	MY_RUN_TEST(ListPushFront_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListPushFront_LinkedListItem_AddsItemAtFrontIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPushFront_LinkedListItemWithItemInList_AddsItemAtFrontFollowedByPreviousFrontIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPushFront_LinkedListItemWithMultipleItemsInList_AddsItemAtFrontFollowedByPreviousFrontIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPushBack_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListPushBack_LinkedListItem_AddsItemAtBackIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPushBack_LinkedListItemWithItemInList_AddsItemAtBackIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPushBack_LinkedListItemWithMultipleItemsInList_AddsItemAtBackIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPushAt_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListPushAt_LinkedListItemIndexZero_AddsItemAtBackIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPushAt_LinkedListItemIndexOneWithItemInList_AddsItemAtBackIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPushAt_LinkedListItemIndexOneWithTwoItemsInList_AddsItemAtMiddleIncrementsCountAndReturnsZero);
	MY_RUN_TEST(ListPopFront_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListPopFront_LinkedListOneItem_RemovesFrontItemListCountZeroAndReturnsZero);
	MY_RUN_TEST(ListPopFront_LinkedListTwoItems_RemovesFrontItemListCountOneNextItemFrontAndReturnsZero);
	MY_RUN_TEST(ListPopBack_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListPopBack_LinkedListOneItem_RemovesBackItemListCountZeroAndReturnsZero);
	MY_RUN_TEST(ListPopBack_LinkedListTwoItems_RemovesBackItemListCountOneSameFrontAndReturnsZero);
	MY_RUN_TEST(ListPopAt_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListPopAt_LinkedListOneItemAndIndexZero_RemovesFrontItemListCountZeroAndReturnsZero);
	MY_RUN_TEST(ListPopAt_LinkedListTwoItemsAndIndexOne_RemovesBackItemListCountOneSameFrontAndReturnsZero);
	MY_RUN_TEST(ListPopAt_LinkedListThreeItemsAndIndexOne_RemovesMiddleItemListCountTwoAndReturnsZero);
	MY_RUN_TEST(ListClear_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListClear_LinkedList_ClearsListAndReturnsZero);
	MY_RUN_TEST(ListGetItem_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListGetItem_LinkedListAndIndexOfItem_GetsItemByPointerAndReturnsZero);
	MY_RUN_TEST(ListGetIndex_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListGetIndex_LinkedListInvalidItemAndCompareFunction_ReturnsErrorInvallidItem);
	MY_RUN_TEST(ListGetIndex_LinkedListItemAndCompareFunction_GetsIndexByPointerAndReturnsZero);
	MY_RUN_TEST(ListReplace_IllegalParameters_ReturnsErrorCode);
	MY_RUN_TEST(ListReplace_LinkedListIndexAndReplaceItem_ReplacesItemAtIndexAndReturnsZero);

	return UNITY_END();
}
