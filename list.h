#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include "orange.h"
/**
* Orange List Container
*
* Implements a list container of type oranges.
* The list has an internal iterator for external use. For all functions
* where the state of the iterator after calling that function is not stated,
* it is undefined. That is you cannot assume anything about it.
*
* The following functions are available:
*
*   listCreate               - Creates a new empty list of oranges
*   listDestroy              - Deletes an existing list and frees all resources
*   listCopy                 - Copies an existing list
*   listGetSize              - Returns the size of a given list
*   listInsertFirst          - Inserts an element in the beginning of the list
*   listInsertBeforeCurrent  - Inserts an element right before the place of
*                              internal iterator
*   listInsertAfterCurrent   - Inserts an element right after the place of the
*                              internal iterator
*   listRemoveCurrent        - Removes the element pointed by the internal
*                              iterator
*   listGetCurrent           - Return the current element (pointed by the
*                              internal iterator)
*   listGetFirst             - Sets the internal iterator (also called current
*                              element) to be the first element in the list and
*                              return it.
*   listGetNext              - Advances the list's iterator to the next element
*                              and return it
*   listClear		      	  - Clears all the data from the list
*/

/** Type for defining the list */
typedef struct List_t *List;

/** Type used for returning error codes from list functions */
typedef enum ListResult_t {
	LIST_SUCCESS,
	LIST_NULL_ARGUMENT,
	LIST_OUT_OF_MEMORY,
	LIST_INVALID_CURRENT,
} ListResult;


/**
* Allocates a new List of Oranges.
*
* Creates a new empty list or oranges.
* @return
* 	NULL - if  allocations failed.
* 	A new List of oranges in case of success.
*/
List listCreate();

/**
* Creates a copy of target list.
*
* The new copy will contain all the oranges from the source list in the same
* order.
*
* @param list The target list to copy
* @return
* NULL if a NULL was sent or a memory allocation failed.
* A List containing the same oranges with same order as list otherwise.
*/
List listCopy(List list);

/**
* Returns the number of oranges in a list
*
* @param list The target list which size is requested.
* @return
* -1 if a NULL pointer was sent.
* Otherwise the number of elements in the list.
*/
int listGetSize(List list);

/**
* Sets the internal iterator to the first orange and retrieves it.
*
* The list has an internal iterator (also called current element) to allow
* iteration over the list's oranges. This function sets the iterator to point
* to the first element in the list and return it.
* Use this to start iteraing over the list, searching from the beginning of
* the list and/or get the first element in the list.
* (To continue iteration use listGetNext)
* @code exapmle
* void f(List list) {
*   Orange first = listGetFirst(list);
*   printf("The first element is at address %x\n", first);
* }
* @endcode
*
* @param list The list for which to set the iterator and return the first
* element.
* @return
* NULL is a NULL pointer was sent or the list is empty.
* The first element of the list otherwise
*/
Orange listGetFirst(List list);

/**
* Advances the list's iterator to the next orange and return it
*
* @param list The list for which to advance the iterator
* @return
* NULL if reached the end of the list, the iterator is at an invalid state or
* a NULL sent as argument
* The next element on the list in case of success
*/
Orange listGetNext(List list);

/**
* Returns the current orange (pointed by the iterator)
*
* @param list The list for which to get the iterator
* @return
* NULL if the iterator is at an invalid state or a NULL sent as argument
* The current element on the list in case of success
*/
Orange listGetCurrent(List list);

/**
* Adds a new orange to the list, the new orange will be the first element.
*
* @param list The list for which to add an orange in its start
* @param orange The element to insert. A copy of the element will be
* inserted as supplied by the copying function which is stored in the list
* @return
* LIST_NULL_ARGUMENT if a NULL was sent as list
* LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* an element failed)
* LIST_SUCCESS the element has been inserted successfully
*/
ListResult listInsertFirst(List list, Orange orange);


/**
* Adds a new element to the list, the new element will be place right before
* the current element (As pointed by the inner iterator of the list)
*
* @param list The list for which to add an element before its current element
* @param element The element to insert. A copy of the element will be
* inserted as supplied by the copying function which is stored in the list
* @return
* LIST_NULL_ARGUMENT if a NULL was sent as list
* LIST_INVALID_CURRENT if the list's iterator is in an invalid state (Does
* not point to a legal element in the list)
* LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* an element failed)
* LIST_SUCCESS the element has been inserted successfully
*/
ListResult listInsertBeforeCurrent(List list, Orange orange);

/**
* Adds a new element to the list, the new element will be place right after
* the current element (As pointed by the inner iterator be of the list)
*
* @param list The list for which to add an element after its current element
* @param element The element to insert. A copy of the element will be
* inserted as supplied by the copying function which is stored in the list
* @return
* LIST_NULL_ARGUMENT if a NULL was sent as list
* LIST_INVALID_CURRENT if the list's iterator is in an invalid state (Does
* not point to a legal element in the list)
* LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* an element failed)
* LIST_SUCCESS the element has been inserted successfully
*/
ListResult listInsertAfterCurrent(List list, Orange orange);

/**
* Removes the currently pointed element of the list using the stored freeing
* function
*
* @param list The list for which the current element will be removed
* @return
* LIST_NULL_ARGUMENT if list is NULL
* LIST_INVALID_CURRENT if the current pointer of the list is in invalid state
* LIST_SUCCESS the current element was removed successfully
*/
ListResult listRemoveCurrent(List list);


/**
* Removes all elements from target list.
*
* The elements are deallocated using the stored freeing function
* @param list Target list to remove all element from
* @return
* LIST_NULL_ARGUMENT - if a NULL pointer was sent.
* LIST_SUCCESS - Otherwise.
*/
ListResult listClear(List list);

/**
* listDestroy: Deallocates an existing list. Clears all elements by using the
* stored free function.
*
* @param list Target list to be deallocated. If list is NULL nothing will be
* done
*/
void listDestroy(List list);

/**
* Macro for iterating over a list.
*
* Declares a new variable to hold each element of the list.
* Use this macro for iterating through the list conveniently.
* Note that this mcaro modifies the internal iterator.
* For example, the following code will go through a list of oranges:
* @code
* void printOrangeWeihts(List listOfOranges) {
*   LIST_FOREACH(Orange, org, listOfOranges) {
*     printf("%d\\n", orangeGetWeight(org));
*   }
* }
* @endcode
*
* @param type The type of the elements in the list
* @param iterator The name of the variable to hold the next list element
* @param list the list to iterate over
*/
#define LIST_FOREACH(type,iterator,list) \
	for(type iterator = listGetFirst(list) ; \
		iterator ;\
		iterator = listGetNext(list))

#endif /* LIST_H_ */
