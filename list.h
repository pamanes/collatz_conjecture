/*
	Adapted it from list.h from the linux kernel
	http://www.cs.fsu.edu/~baker/devices/lxr/http/source/linux/include/linux/list.h
	Here's an explanation of how it works
	http://isis.poly.edu/kulesh/stuff/src/klist/

*/

struct list_head
{
	struct list_head *next,*prev;
};
/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
*/
static __inline void __list_add(struct list_head *newx, struct list_head *prev, struct list_head *next)
{
	next->prev = newx;
	newx->next = next;
	newx->prev = prev;
	prev->next = newx;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
*/
static __inline void list_add(struct list_head *newx, struct list_head *head)
{
	__list_add(newx, head, head->next);
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static __inline void list_add_tail(struct list_head *newx, struct list_head *head)
{
	__list_add(newx, head->prev, head);
}

static __inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}
 /*
  * Delete a list entry by making the prev/next entries
  * point to each other.
  *
  * This is only for internal list manipulation where we know
  * the prev/next entries already!
 */
static __inline void list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}
/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:        the &struct list_head to use as a loop cursor.
 * @n:          another &struct list_head to use as temporary storage
 * @head:       the head for your list.
*/
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; \
         pos != (head); \
		 pos = n, n = pos->next)
/**
  * list_for_each_prev_safe - iterate over a list backwards safe against removal of list entry
  * @pos:        the &struct list_head to use as a loop cursor.
  * @n:          another &struct list_head to use as temporary storage
  * @head:       the head for your list.
*/
 #define list_for_each_prev_safe(pos, n, head) \
         for (pos = (head)->prev, n = pos->prev; \
              pos != (head); \
              pos = n, n = pos->prev)
/**
  * __list_for_each      -       iterate over a list
  * @pos:        the &struct list_head to use as a loop cursor.
  * @head:       the head for your list.
  *
  * This variant differs from list_for_each() in that it's the
  * simplest possible list iteration code, no prefetching is done.
  * Use this for code that knows the list to be very short (empty
  * or 1 entry) most of the time.
 */
#define list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)
/**
  * list_for_each_prev   -       iterate over a list backwards
  * @pos:        the &struct list_head to use as a loop cursor.
  * @head:       the head for your list.
*/
#define list_for_each_prev(pos, head) \
        for (pos = (head)->prev; pos != (head); pos = pos->prev)
/**
  * list_entry - get the struct for this entry
  * @ptr:        the &struct list_head pointer.
  * @type:       the type of the struct this is embedded in.
  * @member:     the name of the list_struct within the struct.
*/
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member);
	
/**
462  * list_for_each_entry_from - iterate over list of given type from the current point
463  * @pos:        the type * to use as a loop cursor.
464  * @head:       the head for your list.
465  * @member:     the name of the list_struct within the struct.
466  *
467  * Iterate over list of given type, continuing from current position.
468  
 #define list_for_each_entry_from(fcast,pos, type, head, member)                     \
         for (; &pos->member != (head);      \
              pos = (fcast)list_entry(pos->member.next, type, member))
*/

//you can loop this way
/*
	__list_for_each(((struct list_head*)pos), &mylist.list)
	{
		//pointer, type , member	
		temp = (struct nlist *) (pos - offsetof(struct nlist,list));
		printf("number is: %d\n", temp->result);
	}
	//or this other way (more code)
	for (pos = (&mylist.list)->next; pos != (&mylist.list); pos = ((struct list_head *)pos)->next)
	{
		//pointer, type , member	
		temp = (struct nlist *) (pos - offsetof(struct nlist,list));
		printf("number is: %d\n", temp->result);
	}
	
	list_for_each_prev(((struct list_head*)pos), &mylist.list)
	{
		temp = (struct nlist *) (pos - offsetof(struct nlist,list));
		printf("number is: %d\n", temp->result);
	}
	*/
	//use for each safe to delete the list
	/*
	printf("deleting the list using list_for_each_safe()\n");
	list_for_each_safe(((struct list_head*)pos), q, &mylist.list){
		 temp = (struct nlist *) (pos - offsetof(struct nlist,list));
		 printf("freeing item: %d\n", temp->result);
		 list_del(((struct list_head*)pos)->prev, ((struct list_head*)pos)->next);
		 Z_Free(temp);
	}
	*/
