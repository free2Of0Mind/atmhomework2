#ifndef CACHE_H_
#define CACHE_H_

#include "list.h"
#include "orange.h"
#define ORANGE_CACHE_SIZE 256
#define CURRENT_MONTH NOV


typedef enum CacheResult_t {
	CACHE_SUCCESS,
	CACHE_ILLEGAL_ARGUMENT,
	CACHE_OUT_OF_MEMORY,
	CACHE_OUT_OF_RANGE,
	CACHE_NO_ELEMENTS_IN_CELL,
	CACHE_SUCCESS_LIST_EMPTY,

} CacheResult;

typedef struct cache_t* Cache;

struct cache_t {
	List* container;
	int cache_size;
	List iterator;
};

/**
 * Creates a new cache of Oranges.
 *
 *
 * @return
 * 	A new allocated cache,
 * 	or NULL in case of error.
 */
Cache cacheCreate();

/**
 * Copies a cache.
 *
 * @return
 * 	A new allocated copy of the cache,
 * 	or NULL in case of error.
 */
Cache cacheCopy(Cache src);


/**
 * Adds an element to the cache.
 *
 * @return
 * 	Result code.
 */
CacheResult cachePush(Cache cache, Orange orange);

/**
 *  frees an element from the cache.
 *
 * @return
 * 	Result code.
 */
CacheResult cacheFreeOrange(Cache cache, int index);

/**
 *  Returns an element from the cache. the element it removed from
 *   the cache and returns to the user inside the pointer org
 *
 * @return
 * 	Result code.
 */
CacheResult cacheGet(Cache cache, int index, Orange* org);

/**
* Sets the internal iterator to the first available cell and retrieves it.
*

* @return
* NULL is a NULL pointer was sent or the cache is empty.
* The first available cell of the cache otherwise
*/
List cacheGetFirst(Cache cache);


/**
* Advances the caches's iterator to the next available cell in the cache and
*  return it
*
* @return
* NULL if reached the end of the cache, the iterator is at an invalid state or
* a NULL sent as argument
* The next cell on the cache in case of success
*/
List cacheGetNext(Cache cache);


/**
* Returns the current cell (pointed by the iterator)
*
* @return
* NULL if the iterator is at an invalid state or a NULL sent as argument
* The current cell on the cache in case of success
*/
List cacheGetCurrent(Cache cache);


/**
 * Destroys a cache - frees its memory.
 */
void cacheDestroy(Cache cache);

/**
 * Get a list of all the oranges that are delivered to the same company and with the same
 * weight.
 *
 *
 * @return
 * 	List of Oranges,
 * 	or NULL in case of error.
 */

List cacheGetOrangesOfCompanyFromCell(Cache cache, char* company,int index);

/**
 * Get a list of all the oranges that are delivered to the same company.
 *
 *
 * @return
 * 	List of Oranges,
 * 	or NULL in case of error.
 */

List cacheGetAllOrangesOfCompany(Cache cache, char* company);


/**
 * Get a list of all the oranges that are delivered to the same company and has
 * The maximum weight. The oranges needs to be removed from the cache.
 *
 *
 * @return
 * 	List of Oranges,
 * 	or NULL in case of error.
 */

List cacheDeliverOrangesWithBiggestWeight(Cache cache);

/**
* Macro for iterating over a cache.
*
* Declares a new variable to hold each cell of the cache.
* Use this macro for iterating through the cache's cells conveniently.
* Note that this macro modifies the internal iterator.
* For example:
* void printOrangeWeihts(Cache cacheOfOranges) {
*   CACHE_FOREACH(cell, cacheOfOranges) {
*     Orange org = listGetFirst(cell);
*     printf("number of oranges in cell %d is %d\n", orangeGetSize(org) listGetSize(cell));
*   }
* }
* @endcode
*
* @param iterator The name of the variable to hold the next cache element
* @param cache the cache to iterate over
*/
#define CACHE_FOREACH(iterator,cache) \
	for(List iterator = cacheGetFirst(cache) ; \
		iterator ;\
		iterator = cacheGetNext(cache))

#endif /* CACHE_H_ */
